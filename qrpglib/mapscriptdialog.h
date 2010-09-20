#ifndef MAPSCRIPTDIALOG_H
#define MAPSCRIPTDIALOG_H

#include "scriptdialog.h"

class MapScriptDialog : public ScriptDialog
{
  Q_OBJECT
public:
  explicit MapScriptDialog(Map * m);

signals:

public slots:
  int exec();

private:
  Map * map;

};

#endif // MAPSCRIPTDIALOG_H
