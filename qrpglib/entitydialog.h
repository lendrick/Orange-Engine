#ifndef ENTITYDIALOG_H
#define ENTITYDIALOG_H 1

#include <QtGui>
#include "jshighlighter.h"
#include "scriptdialog.h"

class Entity;

class EntityDialog : public ScriptDialog {
  Q_OBJECT
public:
  EntityDialog(Entity *);
public slots:
  int exec();
  void updateStateSelect();
  void addScript();
protected:
  QComboBox * spriteSelect;
  QComboBox * stateSelect;
  QLineEdit * nameInput;
  Entity * entity;
};


#endif
