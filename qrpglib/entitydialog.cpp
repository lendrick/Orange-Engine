#include "scriptdialog.h"
#include "entitydialog.h"
#include "entity.h"
#include "entityscripttab.h"
#include "jshighlighter.h"
#include "boundswidget.h"
#include <QtGui>

EntityDialog::EntityDialog(Entity * e) : ScriptDialog() {
  entity = e;
  
  if(!e) return;

  nameInput = new QLineEdit;
  nameInput->setText(entity->getName());
  formLayout->addRow("Name", nameInput);
  
  spriteSelect = new QComboBox;
  spriteSelect->addItem("NONE", QVariant(-1));
  for(int i = 0; i < sprites.size(); i++) 
    if(sprites[i]) spriteSelect->addItem(sprites[i]->getName(), QVariant(i));
  formLayout->addRow("Sprite", spriteSelect);
  //message(entity->getSprite()->GetName());
  if(entity->getSprite())
    spriteSelect->setCurrentIndex(entity->getSprite()->getId() + 1);
  else
    spriteSelect->setCurrentIndex(0);

  //message("Sprite row: " + QString::number(entity->getSprite()->GetId()));

  stateSelect = new QComboBox;
  formLayout->addRow("State", stateSelect);
  updateStateSelect();
  stateSelect->setCurrentIndex(entity->getState());

  connect(spriteSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStateSelect()));

  // Reconnect this signal, because we overloaded the function
  disconnect(addScriptButton, SIGNAL(pressed()), this, SLOT(addScript()));
  connect(addScriptButton, SIGNAL(pressed()), this, SLOT(addScript()));

  useDefaultBoundingBox = new QCheckBox("Use default bounding box");

  if(!(e->getOverrideBoundingBox()))
    useDefaultBoundingBox->setCheckState(Qt::Checked);

  layout->insertWidget(1, useDefaultBoundingBox);

  solid = new QCheckBox("Solid");
  if(e->isSolid())
    solid->setCheckState(Qt::Checked);
  layout->insertWidget(1, solid);
  int x1, y1, x2, y2;
  e->getBoundingBox(x1, y1, x2, y2);

  /*
  c1 = new CoordinateWidget(0, x1, y1);
  formLayout->addRow("Upper left bound", c1);

  c2 = new CoordinateWidget(0, x2, y2);
  formLayout->addRow("Lower right bound", c2);
  */
  bounds = new BoundsWidget(this, x1, y1, x2, y2);

  //connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), c1, SLOT(setDisabled(bool)));
  //connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), c2, SLOT(setDisabled(bool)));
  connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), bounds, SLOT(setDisabled(bool)));

  layout->insertWidget(3, bounds);
  if(!(e->getOverrideBoundingBox())) {
    useDefaultBoundingBox->setCheckState(Qt::Checked);
    bounds->setDisabled(true);
  } else {
    useDefaultBoundingBox->setCheckState(Qt::Unchecked);
    bounds->setDisabled(false);
  }

  /*
  if(!(e->getOverrideBoundingBox())) {
    useDefaultBoundingBox->setCheckState(Qt::Checked);
    c1->setDisabled(true);
    c2->setDisabled(true);
  } else {
    useDefaultBoundingBox->setCheckState(Qt::Unchecked);
    c1->setDisabled(false);
    c2->setDisabled(false);
  }
  */


  setWindowTitle(entity->getName());

  for(int i = 0; i < entity->getScriptCount(); i++) {
    int x1, y1, x2, y2;
    bool defCoords = entity->usesDefaultBounds(i);

    x1 = y1 = x2 = y2 = 0;
    if(!defCoords)
      entity->getScriptBoundingBox(i, x1, y1, x2, y2);

    //message(QString::number(i) + ": " + entity->getScript(i));
    EntityScriptTab * scriptTab = new EntityScriptTab(entity->getScriptCondition(i), entity->getScript(i), defCoords, x1, y1, x2, y2);
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
    int bx1, by1, bx2, by2;
    bounds->getBounds(bx1, by1, bx2, by2);

    // Save changes to entity
    entity->setName(nameInput->text());

    if(spriteSelect->itemData(spriteSelect->currentIndex()).toInt() == -1)
      entity->setSprite(0);
    else
      entity->setSprite(sprites[spriteSelect->itemData(spriteSelect->currentIndex()).toInt()]);

    entity->setState(stateSelect->currentIndex());
    entity->setBoundingBox(bx1, by1, bx2, by2);
    entity->setOverrideBoundingBox(!(useDefaultBoundingBox->checkState() == Qt::Checked));
    entity->setSolid(solid->checkState() == Qt::Checked);
    entity->clearScripts();
    for(int i = 0; i < scriptTabs->count(); i++) {
      EntityScriptTab * widget = dynamic_cast<EntityScriptTab *> (scriptTabs->widget(i));
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
  EntityScriptTab * newScriptTab = new EntityScriptTab;
  scriptTabs->addTab(newScriptTab, QString::number(scriptTabs->count() + 1));
  scriptTabs->setCurrentIndex(scriptTabs->count() - 1);
}

void EntityDialog::updateStateSelect() {
  int index = stateSelect->currentIndex();
  stateSelect->clear();
  if(spriteSelect->itemData(spriteSelect->currentIndex()).toInt() >= 0) {
    Sprite * s = sprites[spriteSelect->itemData(spriteSelect->currentIndex()).toInt()];
    for(int i = 0; i < s->getStateCount(); i++)
      stateSelect->addItem(s->getStateName(i));

    qDebug() << stateSelect->count() << " " << index;

    if(stateSelect->count() >= index) {
      stateSelect->setCurrentIndex(index);
    }

    if(stateSelect->count() > 0 && index <= 0) {
      stateSelect->setCurrentIndex(0);
    }
  }
}
