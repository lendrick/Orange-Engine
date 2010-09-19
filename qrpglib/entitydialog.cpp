#include "entitydialog.h"
#include "entity.h"
#include "scripttab.h"
#include "jshighlighter.h"
#include <QtGui>

CoordinateWidget::CoordinateWidget(QWidget * parent, int nx, int ny) : QFrame(parent) {
  QHBoxLayout * layout = new QHBoxLayout;
  setLayout(layout);

  x = new QSpinBox;
  y = new QSpinBox;

  setContentsMargins(0, 0, 0, 0);
  layout->setContentsMargins(0, 0, 0, 0);

  x->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  y->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  x->setRange(-1000000, 1000000);
  y->setRange(-1000000, 1000000);
  x->setValue(nx);
  y->setValue(ny);

  QLabel * xLabel = new QLabel("X:");
  QLabel * yLabel = new QLabel(" Y:");
  xLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  yLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  layout->addWidget(xLabel);
  layout->addWidget(x);
  layout->addWidget(yLabel);
  layout->addWidget(y);

  QWidget * spacer = new QWidget;
  spacer->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
  layout->addWidget(spacer);
}


EntityDialog::EntityDialog(Entity * e) : QDialog(0) {
  entity = e;
  
  if(!e) return;

  QVBoxLayout * layout = new QVBoxLayout;
  setLayout(layout);

  QFormLayout * formLayout = new QFormLayout;
  layout->addLayout(formLayout);

  nameInput = new QLineEdit;
  nameInput->setText(entity->getName());
  formLayout->addRow("Name", nameInput);
  
  spriteSelect = new QComboBox;
  for(int i = 0; i < sprites.size(); i++) 
    if(sprites[i]) spriteSelect->addItem(sprites[i]->GetName(), QVariant(i));
  formLayout->addRow("Sprite", spriteSelect);
  //message(entity->getSprite()->GetName());
  spriteSelect->setCurrentIndex(entity->getSprite()->GetId());
  //message("Sprite row: " + QString::number(entity->getSprite()->GetId()));

  stateSelect = new QComboBox;
  formLayout->addRow("State", stateSelect);
  updateStateSelect();
  stateSelect->setCurrentIndex(entity->getState());

  QHBoxLayout * buttonLayout = new QHBoxLayout;
  layout->addLayout(buttonLayout);

  QPushButton * addScriptButton = new QPushButton("New Script");
  QPushButton * delScriptButton = new QPushButton("Delete Script");
  QWidget * spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
  
  connect(addScriptButton, SIGNAL(pressed()), this, SLOT(addScript()));
  connect(delScriptButton, SIGNAL(pressed()), this, SLOT(delScript()));
  connect(spriteSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStateSelect()));
  
  addScriptButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  delScriptButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  buttonLayout->addWidget(addScriptButton);
  buttonLayout->addWidget(delScriptButton);
  buttonLayout->addWidget(spacer);

  scriptTabs = new QTabWidget;
  scriptTabs->setTabsClosable(true);
  scriptTabs->setMovable(true);
  layout->addWidget(scriptTabs);
  scriptTabs->setMinimumSize(400, 300);

  QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(scriptTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteScript(int)));

  setWindowTitle(entity->getName());

  for(int i = 0; i < entity->getScriptCount(); i++) {
    int x1, y1, x2, y2;
    bool defCoords = entity->usesDefaultBounds(i);

    x1 = y1 = x2 = y2 = 0;
    if(!defCoords)
      entity->getScriptBoundingBox(i, x1, y1, x2, y2);

    //message(QString::number(i) + ": " + entity->getScript(i));
    ScriptTab * scriptTab = new ScriptTab(entity->getScriptCondition(i), entity->getScript(i), defCoords, x1, y1, x2, y2);
    scriptTabs->addTab(scriptTab, QString::number(i + 1));    
  }
}

int EntityDialog::exec() {
  if(!entity) {
    message("Entity dialog requires an entity.");
    return 0;
  }
  
  int r = QDialog::exec();
  
  if(r == QDialog::Accepted) {
    // Save changes to entity
    entity->setName(nameInput->text());
    entity->setSprite(sprites[spriteSelect->itemData(spriteSelect->currentIndex()).toInt()]);
    entity->setState(stateSelect->currentIndex());
    entity->clearScripts();
    for(int i = 0; i < scriptTabs->count(); i++) {
      ScriptTab * widget = dynamic_cast<ScriptTab *> (scriptTabs->widget(i));
      if(widget) {
        int condition = widget->conditionSelect->currentIndex();
        QString script = widget->scriptText->toPlainText();
        bool defCoords = (widget->useDefaultBoundingBox->checkState() == Qt::Checked);
        int x1, y1, x2, y2;
        x1 = y1 = x2 = y2 = 0;
        if(!defCoords) {
          x1 = widget->c1->x->value();
          y1 = widget->c1->y->value();
          x2 = widget->c2->x->value();
          y2 = widget->c2->y->value();
        }
        entity->addScript(condition, script, defCoords, x1, y1, x2, y2);
      } else {
        message("EntityDialog: tab is not of type ScriptTab");
      }
    }
  }

  return r;
}

void EntityDialog::addScript() {
  ScriptTab * newScriptTab = new ScriptTab;
  scriptTabs->addTab(newScriptTab, QString::number(scriptTabs->count() + 1));
  scriptTabs->setCurrentIndex(scriptTabs->count() - 1);
}

void EntityDialog::delScript() {
  deleteScript(scriptTabs->currentIndex());
}

void EntityDialog::deleteScript(int index) {
  if(QMessageBox::warning(this, "Delete this script?", "Really delete this script?", 
    QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok) 
    scriptTabs->removeTab(index);
}

void EntityDialog::updateStateSelect() {
  int index = stateSelect->currentIndex();
  stateSelect->clear();
  Sprite * s = sprites[spriteSelect->itemData(spriteSelect->currentIndex()).toInt()];
  for(int i = 0; i < s->GetStates(); i++)
    stateSelect->addItem(s->GetStateName(i));
  if(stateSelect->count() >= index) stateSelect->setCurrentIndex(index);
}
