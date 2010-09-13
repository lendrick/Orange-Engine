#include <QtGui>
#include "newprojectdialog.h"
#include "globals.h"

NewProjectDialog::NewProjectDialog(QWidget * parent) :
  QDialog(parent) {
  setModal(true);
  setWindowTitle("New Project");

  QVBoxLayout * layout = new QVBoxLayout(this);
  
  QFormLayout * form = new QFormLayout();
  layout->addLayout(form);
  
  QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);


  projectname = new QLineEdit(this);
  
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
  
  form->addRow("Name:", projectname);
}

void NewProjectDialog::submit() {
  if(projectname->text().isEmpty() || projectname->text().isNull()) {
    QMessageBox::critical(this, "Error", "You must give your project a name.");
    projectname->setFocus();
  } else {
    emit accept();
  }
}

int NewProjectDialog::exec() {
  projectname->clear();
  return QDialog::exec();
}
