#ifndef SCRIPTTAB_H
#define SCRIPTTAB_H

#include <QtGui>
#include <QFrame>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFormLayout>

class JsHighlighter;

class ScriptTab : public QFrame {
  Q_OBJECT
  friend class ScriptDialog;
  friend class MapScriptDialog;
  friend class GlobalScriptDialog;
  friend class EntityDialog;
public:
  ScriptTab(int condition = 0, QString script = "");
protected:
  QComboBox * conditionSelect;
  QTextEdit * scriptText;
  JsHighlighter * highlighter;
  QVBoxLayout * layout;
  QFormLayout * formLayout;
};

#endif // SCRIPTTAB_H
