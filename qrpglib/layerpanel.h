#ifndef LAYERPANEL_H
#define LAYERPANEL_H 1
#include <QtGui>
#include <QToolBar>
#include <QTableWidget>
#include <QDockWidget>
#include <QComboBox>
#include "globals.h"

class LayerTable : public QTableWidget {
  Q_OBJECT
public:
  LayerTable(QWidget * parent = 0);
protected:

  void mouseMoveEvent(QMouseEvent * event);
  void performDrag();
  void mousePressEvent(QMouseEvent *event);
  void dragEnterEvent(QDragEnterEvent *event);
  void dragMoveEvent(QDragMoveEvent *event);
  void dropEvent(QDropEvent *event);

  QMenu * layerPopupMenu;
  QAction * layerPropertiesAction;

  QStringList mimeTypes() const;
  //bool dropMimeData(int row, int column, const QMimeData* data, Qt::DropAction action);

  QPoint startPos;

  int clickedLayer;
  /*
  QMimeData * mimeData(const QList<QTableWidgetItem *> items ) const;
  void dragMoveEvent(QDragMoveEvent* e);
  void dragEnterEvent(QDragEnterEvent* e);
  */
public slots:
  //void removeRow(int);
  void showLayerPropertiesDialog();
protected slots:
  //void rowMoved(int row, int oldIndex, int newIndex);
signals:
  void rowDragged(int, int);
};

class LayerPanel : public QDockWidget
{
  Q_OBJECT
public:
  LayerPanel(QWidget * parent = 0);
  ~LayerPanel();

  QComboBox * layerViewSelect;
  LayerTable * layerTable;

  QToolBar * layerButtons;
  QAction * addLayerAction;
  QAction * delLayerAction;

private:
  int nameColumn;

signals:
  void addLayer(int);
  void delLayer(int);
  void selectLayer(int);
  void setDrawMode(LayerView::LayerViewMode);

public slots:
  void addLayerButton();
  void delLayerButton();
  void updateData();
  void renameLayer(int, int);
  void cellClicked(int, int);
  void setDisabled(bool);
  void viewModeChanged(int);
  void layerMoved(int, int);
};

#endif
