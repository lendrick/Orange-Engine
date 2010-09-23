#include "boundswidget.h"
#include "coordinatewidget.h"

BoundsWidget::BoundsWidget(QWidget *parent, int x1, int y1, int x2, int y2) :
    QGroupBox(parent)
{
  setTitle("Bounds");

  formLayout = new QFormLayout;
  setLayout(formLayout);

  topLeft = new CoordinateWidget(this, x1, y1);
  formLayout->addRow("Upper left bound", topLeft);

  bottomRight = new CoordinateWidget(this, x2, y2);
  formLayout->addRow("Lower right bound", bottomRight);
}

void BoundsWidget::getBounds(int &x1, int &y1, int &x2, int &y2) {
  x1 = topLeft->x->value();
  y1 = topLeft->y->value();
  x2 = bottomRight->x->value();
  y2 = bottomRight->y->value();
}
