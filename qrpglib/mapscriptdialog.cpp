#include "mapscriptdialog.h"
#include "scripttab.h"
#include "map.h"

MapScriptDialog::MapScriptDialog(Map * m) : QDialog(0) {
  map = m;
  QVBoxLayout * layout = new QVBoxLayout;
  setLayout(layout);

  QHBoxLayout * buttonLayout = new QHBoxLayout;
  layout->addLayout(buttonLayout);

  QPushButton * addScriptButton = new QPushButton("New Script");
  QPushButton * delScriptButton = new QPushButton("Delete Script");
  QWidget * spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

  connect(addScriptButton, SIGNAL(pressed()), this, SLOT(addScript()));
  connect(delScriptButton, SIGNAL(pressed()), this, SLOT(delScript()));

  addScriptButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  delScriptButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  buttonLayout->addWidget(addScriptButton);
  buttonLayout->addWidget(delScriptButton);
  buttonLayout->addWidget(spacer);

  scriptTabs = new QTabWidget;
  scriptTabs->setTabsClosable(true);
  scriptTabs->setMovable(true);
  layout->addWidget(scriptTabs);
  scriptTabs->setMinimumSize(400, 300);

  QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(scriptTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteScript(int)));

  setWindowTitle("Map Scripts");

  for(int i = 0; i < map->getScriptCount(); i++) {
    //message(QString::number(i) + ": " + entity->getScript(i));
    ScriptTab * scriptTab = new ScriptTab(map->getScriptCondition(i), map->getScript(i));
    scriptTabs->addTab(scriptTab, QString::number(i + 1));
  }
}

int MapScriptDialog::exec() {
  int r = QDialog::exec();

  if(r == QDialog::Accepted) {
    // Save changes to map
    map->clearScripts();
    for(int i = 0; i < scriptTabs->count(); i++) {
      ScriptTab * widget = dynamic_cast<ScriptTab *> (scriptTabs->widget(i));
      if(widget) {
        int condition = widget->conditionSelect->currentIndex();
        QString script = widget->scriptText->toPlainText();

        map->addScript(condition, script);
      } else {
        message("MapScriptDialog: tab is not of type ScriptTab");
      }
    }
  }

  return r;
}

void MapScriptDialog::addScript() {
  ScriptTab * newScriptTab = new ScriptTab;
  scriptTabs->addTab(newScriptTab, QString::number(scriptTabs->count() + 1));
  scriptTabs->setCurrentIndex(scriptTabs->count() - 1);
}

void MapScriptDialog::delScript() {
  deleteScript(scriptTabs->currentIndex());
}

void MapScriptDialog::deleteScript(int index) {
  if(QMessageBox::warning(this, "Delete this script?", "Really delete this script?",
    QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok)
    scriptTabs->removeTab(index);
}

