#include "scriptdialog.h"
#include "entitydialog.h"
#include "entity.h"
#include "entityscripttab.h"
#include "jshighlighter.h"
#include <QtGui>

EntityDialog::EntityDialog(Entity * e) : ScriptDialog() {
  entity = e;
  
  if(!e) return;

  nameInput = new QLineEdit;
  nameInput->setText(entity->getName());
  formLayout->addRow("Name", nameInput);
  
  spriteSelect = new QComboBox;
  for(int i = 0; i < sprites.size(); i++) 
    if(sprites[i]) spriteSelect->addItem(sprites[i]->getName(), QVariant(i));
  formLayout->addRow("Sprite", spriteSelect);
  //message(entity->getSprite()->GetName());
  spriteSelect->setCurrentIndex(entity->getSprite()->getId());
  //message("Sprite row: " + QString::number(entity->getSprite()->GetId()));

  stateSelect = new QComboBox;
  formLayout->addRow("State", stateSelect);
  updateStateSelect();
  stateSelect->setCurrentIndex(entity->getState());

  connect(spriteSelect, SIGNAL(currentIndexChanged(int)), this, SLOT(updateStateSelect()));

  // Reconnect this signal, because we overloaded the function
  disconnect(addScriptButton, SIGNAL(pressed()), this, SLOT(addScript()));
  connect(addScriptButton, SIGNAL(pressed()), this, SLOT(addScript()));
  
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
    // Save changes to entity
    entity->setName(nameInput->text());
    entity->setSprite(sprites[spriteSelect->itemData(spriteSelect->currentIndex()).toInt()]);
    entity->setState(stateSelect->currentIndex());
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
  Sprite * s = sprites[spriteSelect->itemData(spriteSelect->currentIndex()).toInt()];
  for(int i = 0; i < s->getStateCount(); i++)
    stateSelect->addItem(s->getStateName(i));
  if(stateSelect->count() >= index) stateSelect->setCurrentIndex(index);
}
