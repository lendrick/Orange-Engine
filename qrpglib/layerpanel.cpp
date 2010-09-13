#include <QtGui>
#include "layerpanel.h"
#include "icons.h"
#include "globals.h"
#include "mapwindow.h"

LayerTable::LayerTable(QWidget * parent) : QTableWidget(parent) {
  setDragEnabled(true);
  setDragDropMode(QAbstractItemView::InternalMove);
  setDragDropOverwriteMode(false);
  setDropIndicatorShown(true);
  viewport()->setAcceptDrops(true);
  setSelectionMode(QAbstractItemView::SingleSelection);
}

void LayerTable::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
    startPos = event->pos();
  QTableWidget::mousePressEvent(event);
}

void LayerTable::mouseMoveEvent(QMouseEvent *event)
{
  if (event->buttons() & Qt::LeftButton) {
    int distance = (event->pos() - startPos).manhattanLength();
    if (distance >= QApplication::startDragDistance())
      performDrag();
  }
  QTableWidget::mouseMoveEvent(event);
}

void LayerTable::performDrag()
{
  //int selectedRow = selectedItems()[0]->text().toInt();
  int selectedRow = rowAt(startPos.y());
  QString plainText = QString::number(selectedRow);
  //QMessageBox::warning(0, "info", "performDrag: " + plainText);
  if (plainText.isEmpty())
      return;

  QMimeData *mimeData = new QMimeData;
  mimeData->setData("text/rpgx-map-layer-id", plainText.toAscii());
  //QMessageBox::warning(0, "info", "performDrag: " + QString(mimeData->data("text/rpgx-map-layer-id")));

  QDrag *drag = new QDrag(this);
  drag->setMimeData(mimeData);
//  if (drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction)
//    removeRow(selectedRow);
  drag->exec(Qt::MoveAction);
}

void LayerTable::dragEnterEvent(QDragEnterEvent *event)
{
  LayerTable *source =
          qobject_cast<LayerTable *>(event->source());
  if (source && source == this) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
  }
}

void LayerTable::dragMoveEvent(QDragMoveEvent *event)
{
  LayerTable *source =
          qobject_cast<LayerTable *>(event->source());
  if (source && source == this) {
    event->setDropAction(Qt::MoveAction);
    event->accept();
  }

  QTableWidget::dragMoveEvent(event);
}

void LayerTable::dropEvent(QDropEvent *event)
{
  LayerTable *source =
          qobject_cast<LayerTable *>(event->source());
  if (source && source == this) {
    int newRow = rowAt(event->pos().y());
    if(newRow == -1) newRow = rowCount() - 1;
    int oldRow = QString(event->mimeData()->data("text/rpgx-map-layer-id")).toInt();
    //QMessageBox::warning(0, "info", "dropEvent: " + QString::number(oldRow) + " -> " + QString::number(newRow));
    event->setDropAction(Qt::MoveAction);
    event->accept();
    emit rowDragged(oldRow, newRow);
  }
}

QStringList LayerTable::mimeTypes() const {
  return QStringList("text/rpgx-map-layer-id");
}

/****************************************************/

LayerPanel::LayerPanel(QWidget * parent) : QDockWidget(parent)
{
  this->setWindowTitle("Layers");
  QFrame * layerFrame = new QFrame;
  this->setWidget(layerFrame);

  QVBoxLayout * layout = new QVBoxLayout;
  layerFrame->setLayout(layout);

  QFormLayout * viewForm = new QFormLayout;
  layout->addLayout(viewForm);

  layerViewSelect = new QComboBox();
  layerViewSelect->addItem("All layers", QVariant(LayerView::All));
  layerViewSelect->addItem("Only this layer", QVariant(LayerView::OnlyThis));
  layerViewSelect->addItem("Only layers below", QVariant(LayerView::AllBelow));
  viewForm->addRow("View:", layerViewSelect);

  layerTable = new LayerTable();

  QStringList headings;
  //headings.push_back("#");
  headings.push_back("Name");
  nameColumn = 0;
  layerTable->setColumnCount(1);
  layerTable->setHorizontalHeaderLabels(headings);
  //layerTable->setColumnWidth(0, 20);
  layerTable->setColumnWidth(0, 220);

  layout->addWidget(layerTable);

  layerButtons = new QToolBar();
  layout->addWidget(layerButtons);

  QWidget * spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  layerButtons->addWidget(spacer);
  delLayerAction = new QAction(*delsmallIcon, "Delete Layer", this);
  delLayerAction->setShortcut(QKeySequence::Delete);
  delLayerAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);

  layerButtons->addAction(delLayerAction);
  layerTable->addAction(delLayerAction);
  addLayerAction = layerButtons->addAction(*addsmallIcon, "Add Layer");
  
  connect(layerTable, SIGNAL(rowDragged(int, int)), this, SLOT(layerMoved(int, int)));
  connect(layerTable, SIGNAL(cellChanged(int, int)), this, SLOT(renameLayer(int, int)));
  connect(layerTable, SIGNAL(cellClicked(int, int)), this, SLOT(cellClicked(int, int)));
  connect(addLayerAction, SIGNAL(triggered()), this, SLOT(addLayerButton()));
  connect(delLayerAction, SIGNAL(triggered()), this, SLOT(delLayerButton()));
  connect(layerViewSelect, SIGNAL(currentIndexChanged(int)),
    this, SLOT(viewModeChanged(int)));
  updateData();
}

void LayerPanel::addLayerButton() {
  if(layerTable->rowCount() > 0 && layerTable->currentRow() >= 0)
    emit addLayer(layerTable->currentRow());
  else
    emit addLayer(0);
}

void LayerPanel::delLayerButton() {
  int row = layerTable->currentRow();
  if(row >= 0 && layerTable->rowCount() > 0)
    emit delLayer(row);
  if(row >= layerTable->rowCount()) row--;
  if(row >= 0) layerTable->setCurrentCell(row, 0);
}

void LayerPanel::updateData() {
  disconnect(layerTable, SIGNAL(cellChanged(int, int)), this, SLOT(renameLayer(int, int)));
  layerTable->clearContents();
  layerTable->setRowCount(0);
  if(currentMap) {
    int layers = currentMap->GetLayers();
    layerTable->setRowCount(layers);
    for(int i = 0; i < layers; i++) {
      //QTableWidgetItem * layer = new QTableWidgetItem(QString::number(i));
      QTableWidgetItem * layerName = new QTableWidgetItem(currentMap->GetLayerName(i));
      layerName->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsEditable|Qt::ItemIsEnabled);
      //layerTable->setItem(i, 0, layer);
      layerTable->setItem(i, nameColumn, layerName);
    }
  }
  connect(layerTable, SIGNAL(cellChanged(int, int)), this, SLOT(renameLayer(int, int)));
  if(layerTable->rowCount() == 0)
    delLayerAction->setDisabled(true);
  else
    delLayerAction->setDisabled(false);
}

void LayerPanel::cellClicked(int row, int column) {
  emit selectLayer(row);
}

void LayerPanel::layerMoved(int oldRow, int newRow) {
  //QMessageBox::warning(0, "info", "layerMoved: " + QString::number(oldRow) + " -> " + 
    //QString::number(newRow));
  //if(newRow > oldRow) newRow -= 1;
  currentMap->moveLayer(oldRow, newRow);
  updateData();
  layerTable->setCurrentCell(newRow, 0);
  //layerTable->setRangeSelected(
  //  QTableWidgetSelectionRange(newRow, 0, newRow+1, 1), 
  //  true);
}

void LayerPanel::renameLayer(int row, int column) {

  //QMessageBox::warning(0, "info", "cellChanged: " + QString::number(row) + ", " + 
   // QString::number(column));
  if(column != nameColumn) return;
  //QMessageBox::warning(0, "info", "Setting layer " + QString::number(row) + " name to '" + layerTable->item(row, column)->text() + "'");
  currentMap->SetLayerName(row, layerTable->item(row, column)->text());
}

void LayerPanel::setDisabled(bool disabled) {
  layerViewSelect->setDisabled(disabled);
  layerTable->clearContents();
  layerTable->setDisabled(disabled);
  delLayerAction->setDisabled(disabled);
  addLayerAction->setDisabled(disabled);
  QDockWidget::setDisabled(disabled);
}

void LayerPanel::viewModeChanged(int index) {
  emit(setDrawMode((LayerView::LayerViewMode) layerViewSelect->itemData(index).toInt()));
}

LayerPanel::~LayerPanel()
{
}

