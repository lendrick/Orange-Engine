#include "entityscripttab.h"
#include "scripttab.h"
#include "globals.h"
#include "jshighlighter.h"

CoordinateWidget::CoordinateWidget(QWidget * parent, int nx, int ny) : QFrame(parent) {
  QHBoxLayout * layout = new QHBoxLayout;
  setLayout(layout);

  x = new QSpinBox;
  y = new QSpinBox;

  setContentsMargins(0, 0, 0, 0);
  layout->setContentsMargins(0, 0, 0, 0);

  x->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  y->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  x->setRange(-1000000, 1000000);
  y->setRange(-1000000, 1000000);
  x->setValue(nx);
  y->setValue(ny);

  QLabel * xLabel = new QLabel("X:");
  QLabel * yLabel = new QLabel(" Y:");
  xLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  yLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  layout->addWidget(xLabel);
  layout->addWidget(x);
  layout->addWidget(yLabel);
  layout->addWidget(y);

  QWidget * spacer = new QWidget;
  spacer->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
  layout->addWidget(spacer);
}


EntityScriptTab::EntityScriptTab(int condition, QString script, bool defBounds,
                                 int x1, int y1, int x2, int y2)
                                   : ScriptTab(condition, script)
{
  useDefaultBoundingBox = new QCheckBox;
  useDefaultBoundingBox->setCheckState(Qt::Checked);
  formLayout->addRow("Use default bounds", useDefaultBoundingBox);

  c1 = new CoordinateWidget(0, x1, y1);
  formLayout->addRow("Upper left bound", c1);

  c2 = new CoordinateWidget(0, x2, y2);
  formLayout->addRow("Lower right bound", c2);

  connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), c1, SLOT(setDisabled(bool)));
  connect(useDefaultBoundingBox, SIGNAL(toggled(bool)), c2, SLOT(setDisabled(bool)));

  if(defBounds) {
    useDefaultBoundingBox->setCheckState(Qt::Checked);
    c1->setDisabled(true);
    c2->setDisabled(true);
  } else {
    useDefaultBoundingBox->setCheckState(Qt::Unchecked);
    c1->setDisabled(false);
    c2->setDisabled(false);
  }
}
