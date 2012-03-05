#include <QtGui>
#include <QFormLayout>
#include <QGroupBox>
#include <QDialogButtonBox>
#include <QMessageBox>
#include "newbitmapdialog.h"
#include "filebrowser.h"
#include "globals.h"

NewBitmapDialog::NewBitmapDialog(QWidget * parent) :
  QDialog(parent) {
  setModal(true);
  setWindowTitle("New Tileset");

  QVBoxLayout * layout = new QVBoxLayout(this);
  
  QFormLayout * form = new QFormLayout();
  layout->addLayout(form);
  
  QGroupBox * sizeBox = new QGroupBox("Tile Dimensions");
  layout->addWidget(sizeBox);
  
  QFormLayout * sizeForm = new QFormLayout();
  sizeBox->setLayout(sizeForm);

  QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);

  xspin = new QSpinBox(this);
  xspin->setRange(1, 512);
  xspin->setSingleStep(4);
  xspin->setValue(32);
  yspin = new QSpinBox(this);
  yspin->setRange(1, 512);
  yspin->setSingleStep(4);
  yspin->setValue(32);

  image = new FileBrowser("Images (*.png *.bmp *.jpg)", this);
  bitmapname = new QLineEdit(this);
  
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(submit()));
  
  form->addRow("Name:", bitmapname);
  form->addRow("Image file:", image);
  
  sizeForm->addRow("Width:", xspin);
  sizeForm->addRow("Height:", yspin);
}

void NewBitmapDialog::submit() {
  if(bitmapnames.contains(bitmapname->text())) {
    QMessageBox::critical(this, "Error", "The name you entered, '" + bitmapname->text() +
      "', is already in use by another tileset.  Please choose a different name.");
    bitmapname->setFocus();
    bitmapname->selectAll();
  } else if(bitmapname->text().isEmpty() || bitmapname->text().isNull()) {
    QMessageBox::critical(this, "Error", "You must give your tileset a name.");
    bitmapname->setFocus();
  } else if(image->text().isEmpty() || image->text().isNull()) {
    QMessageBox::critical(this, "Error", "You must select an image.");
  } else if(!QFile::exists(image->text())) {
    QMessageBox::critical(this, "Error", "The image file, '" + image->text() + 
    "', does not exist.  Please select an image.");    
  } else {
    emit accept();
  }
}

int NewBitmapDialog::exec() {
  xspin->setValue(32);
  yspin->setValue(32);
  bitmapname->clear();
  image->clear();
  return QDialog::exec();
}
