#ifndef GLOBALSCRIPTDIALOG_H
#define GLOBALSCRIPTDIALOG_H

#include "scriptdialog.h"

class GlobalScriptDialog : public ScriptDialog
{
  Q_OBJECT
public:
  GlobalScriptDialog();

signals:

public slots:
  int exec();

};

#endif // GLOBALSCRIPTDIALOG_H
