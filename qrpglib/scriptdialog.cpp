#include "scriptdialog.h"
#include "scripttab.h"

ScriptDialog::ScriptDialog() : QDialog(0) {
  layout = new QVBoxLayout;
  setLayout(layout);

  formLayout = new QFormLayout;
  layout->addLayout(formLayout);

  buttonLayout = new QHBoxLayout;
  layout->addLayout(buttonLayout);

  addScriptButton = new QPushButton("New Script");
  delScriptButton = new QPushButton("Delete Script");
  spacer = new QWidget();
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

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(scriptTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(deleteScript(int)));

}

void ScriptDialog::addScript() {
  ScriptTab * newScriptTab = new ScriptTab;
  scriptTabs->addTab(newScriptTab, QString::number(scriptTabs->count() + 1));
  scriptTabs->setCurrentIndex(scriptTabs->count() - 1);
}

void ScriptDialog::delScript() {
  deleteScript(scriptTabs->currentIndex());
}

void ScriptDialog::deleteScript(int index) {
  if(QMessageBox::warning(this, "Delete this script?", "Really delete this script?",
    QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok)
    scriptTabs->removeTab(index);
}

