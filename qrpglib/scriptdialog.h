#ifndef SCRIPTDIALOG_H
#define SCRIPTDIALOG_H

#include <QtGui>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QDialog>
#include <QTabWidget>
#include <QGroupBox>
#include "jshighlighter.h"

class Map;

class ScriptDialog : public QDialog {
  Q_OBJECT
public:
  ScriptDialog();
public slots:
  virtual int exec() = 0;
  void addScript();
  void delScript();
  void deleteScript(int);
protected:
  QTabWidget * scriptTabs;
  QVBoxLayout * layout;
  QHBoxLayout * buttonLayout;
  QFormLayout * formLayout;
  QPushButton * addScriptButton;
  QPushButton * delScriptButton;
  QDialogButtonBox * buttonBox;
  QGroupBox * scriptBox;
  QVBoxLayout * scriptBoxLayout;
  QWidget * spacer;
};

#endif
