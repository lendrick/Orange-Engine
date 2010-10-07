#include <QtGui>
#include "globals.h"
#include "layerdialog.h"
#include "resource.h"
#include "map.h"

LayerDialog::LayerDialog(Map::Layer * l, QWidget * parent) :
  QDialog(parent) {
  layer = l;
  setModal(true);
  setWindowTitle("Edit Layer");

  xspin = new QSpinBox(this);
  xspin->setRange(1, 10000);
  xspin->setSingleStep(10);
  xspin->setValue(layer->width);
  yspin = new QSpinBox(this);
  yspin->setRange(1, 10000);
  yspin->setSingleStep(10);
  yspin->setValue(layer->height);
  wrapcheck = new QCheckBox();
  wrapcheck->setChecked(layer->wrap);
  layername = new QLineEdit(layer->name);

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

void LayerDialog::submit() {
  emit accept();
}

int LayerDialog::exec() {
  if(QDialog::exec()) {
    layer->resize(xspin->value(), yspin->value(), 0);
    layer->wrap = wrapcheck->isChecked();
    layer->name = layername->text();
  }
}
