#ifndef ENTITYDIALOG_H
#define ENTITYDIALOG_H 1

#include <QtGui>
#include "jshighlighter.h"

class Entity;
class ScriptTab;

class EntityDialog : public QDialog {
  Q_OBJECT
public:
  EntityDialog(Entity *);
public slots:
  int exec();  
  void addScript();
  void delScript();
  void deleteScript(int);
  void updateStateSelect();
private:
  QComboBox * spriteSelect;
  QComboBox * stateSelect;
  QLineEdit * nameInput;
  QTabWidget * scriptTabs;
  Entity * entity;
};


#endif
