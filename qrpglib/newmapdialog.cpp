#include <QtGui>
#include "newmapdialog.h"
#include "globals.h"
#include "bitmap.h"

NewMapDialog::NewMapDialog(QWidget * parent) :
  QDialog(parent) {
  setModal(true);
  setWindowTitle("New Map");
  
  QVBoxLayout * layout = new QVBoxLayout(this);
  QFormLayout * formLayout = new QFormLayout();
  layout->addLayout(formLayout);
  
  mapname = new QLineEdit();
  formLayout->addRow("Name:", mapname);
  
  tileset = new QComboBox();
  formLayout->addRow("Tileset:", tileset);
  
  QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
}

void NewMapDialog::submit() {
  if(mapnames.contains(mapname->text())) {
    QMessageBox::critical(this, "Error", "The name you entered, '" + mapname->text() +
      "', is already in use by another map.  Please choose a different name.");
    mapname->setFocus();
    mapname->selectAll();
  } else {
    emit accept();
  }
}

int NewMapDialog::exec() {
  if(bitmaps.size() == 0) {
    QMessageBox::critical(this, "Error", "You must load a tileset before you create a map.");
    return QDialog::Rejected;
  }
  
  mapname->clear();
  tileset->clear();
  for(int i = 0; i < bitmaps.size(); i++) {
    tileset->addItem(bitmaps[i]->getName());
  }
  return QDialog::exec();
}
