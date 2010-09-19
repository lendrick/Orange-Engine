#ifndef MAPSCRIPTDIALOG_H
#define MAPSCRIPTDIALOG_H

#include <QtGui>
#include "jshighlighter.h"

class Map;

class MapScriptDialog : public QDialog {
  Q_OBJECT
public:
  MapScriptDialog(Map * m);
public slots:
  int exec();
  void addScript();
  void delScript();
  void deleteScript(int);
private:
  QTabWidget * scriptTabs;
  Map * map;
};

#endif
