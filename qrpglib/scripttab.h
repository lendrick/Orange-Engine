#ifndef SCRIPTTAB_H
#define SCRIPTTAB_H

#include <QtGui>

class JsHighlighter;

class CoordinateWidget : public QFrame {
  Q_OBJECT
public:
  CoordinateWidget(QWidget * parent = 0, int nx = 0, int ny = 0);
  QSpinBox * x;
  QSpinBox * y;
};

class ScriptTab : public QFrame {
  Q_OBJECT
  friend class EntityDialog;
  friend class MapScriptDialog;
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

#endif // SCRIPTTAB_H
