#include <QtGui>
#include "globals.h"
#include "newlayerdialog.h"
#include "resource.h"
#include "map.h"

NewLayerDialog::NewLayerDialog(QWidget * parent) :
  QDialog(parent) {
  setModal(true);
  setWindowTitle("New Layer");
  xspin = new QSpinBox(this);
  xspin->setRange(1, 10000);
  xspin->setSingleStep(10);
  xspin->setValue(50);
  yspin = new QSpinBox(this);
  yspin->setRange(1, 10000);
  yspin->setSingleStep(10);
  yspin->setValue(50);
  wrapcheck = new QCheckBox(this);
  layername = new QLineEdit();
  
  QVBoxLayout * layout = new QVBoxLayout(this);
  QGroupBox * sizeBox = new QGroupBox("Layer Dimensions");
  layout->addWidget(sizeBox);
  
  QFormLayout * mapSizeForm = new QFormLayout(sizeBox);
  
  mapSizeForm->addRow("Name:", layername);
  mapSizeForm->addRow("Width:", xspin);
  mapSizeForm->addRow("Height:", yspin);
  mapSizeForm->addRow("Wrap?", wrapcheck);
  
  QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);
  layout->addWidget(buttonBox);

  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(submit()));  
}

void NewLayerDialog::submit() {
  emit accept();
}

int NewLayerDialog::exec() {
  if(maps.size() == 0) {
    QMessageBox::critical(this, "Error", "You must create a map before you can create layers.");
    return QDialog::Rejected;
  } else if(!currentresource || currentresource->type() != Resource::Map) {
    QMessageBox::critical(this, "Error", "No map is currently selected.  You must select a map to create layers.");
    return QDialog::Rejected;
  }
  layername->setText("Layer " + QString::number(currentMap->getLayerCount() + 1));

  return QDialog::exec();
}
