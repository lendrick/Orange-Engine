#ifndef ENTITYDIALOG_H
#define ENTITYDIALOG_H 1

#include <QtGui>
#include "jshighlighter.h"

class Entity;

class CoordinateWidget : public QFrame {
  Q_OBJECT
public:
  CoordinateWidget(QWidget * parent = 0, int nx = 0, int ny = 0);
  QSpinBox * x;
  QSpinBox * y;
};

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

class ScriptTab : public QFrame {
  Q_OBJECT
  friend class EntityDialog;
public:
  ScriptTab(int condition = 0, QString script = "", bool defCoords = true, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
private:
  QComboBox * conditionSelect;
  QCheckBox * useDefaultBoundingBox;
  CoordinateWidget * c1;
  CoordinateWidget * c2;
  QTextEdit * scriptText;
  JsHighlighter * highlighter;
};

#endif
