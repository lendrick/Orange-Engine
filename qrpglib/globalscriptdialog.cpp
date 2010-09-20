#include "globalscriptdialog.h"
#include "scriptdialog.h"
#include "scripttab.h"
#include "rpgengine.h"
#include "globals.h"

GlobalScriptDialog::GlobalScriptDialog() :
    ScriptDialog()
{
  setWindowTitle("Global Scripts");
  for(int i = 0; i < RPGEngine::getScriptCount(); i++) {
    //message(QString::number(i) + ": " + entity->getScript(i));
    ScriptTab * scriptTab = new ScriptTab(RPGEngine::getScriptCondition(i), RPGEngine::getScript(i));
    scriptTabs->addTab(scriptTab, QString::number(i + 1));
  }
}

int GlobalScriptDialog::exec() {
  int r = QDialog::exec();

  if(r == QDialog::Accepted) {
    // Save changes to map
    RPGEngine::clearScripts();
    for(int i = 0; i < scriptTabs->count(); i++) {
      ScriptTab * widget = dynamic_cast<ScriptTab *> (scriptTabs->widget(i));
      if(widget) {
        int condition = widget->conditionSelect->currentIndex();
        QString script = widget->scriptText->toPlainText();

        RPGEngine::addScript(condition, script);
      } else {
        message("ScriptDialog: tab is not of type ScriptTab");
      }
    }
  }

  return r;
}
