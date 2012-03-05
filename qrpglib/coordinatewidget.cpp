#include "coordinatewidget.h"

#include <QtGui>
#include <QHBoxLayout>
#include <QLabel>

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
