#ifndef ENTITYDIALOG_H
#define ENTITYDIALOG_H 1

#include <QtGui>
#include "jshighlighter.h"
#include "scriptdialog.h"
#include "boundswidget.h"
#include "entity.h"

class EntityDialog : public ScriptDialog {
  Q_OBJECT
public:
  EntityDialog(EntityPointer);
public slots:
  int exec();
  void updateStateSelect();
  void addScript();
protected:
  QComboBox * spriteSelect;
  QComboBox * stateSelect;
  QLineEdit * nameInput;
  EntityPointer entity;
  BoundsWidget * bounds;
  QCheckBox * useDefaultBoundingBox;
  QCheckBox * solid;
};


#endif
