#ifndef BOUNDSWIDGET_H
#define BOUNDSWIDGET_H

#include <QFrame>
#include "coordinatewidget.h"

class BoundsWidget : public QGroupBox
{
  Q_OBJECT
public:
  explicit BoundsWidget(QWidget *parent = 0, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
  void getBounds(int &, int &, int &, int &);
  CoordinateWidget topLeft;
  CoordinateWidget bottomRight;
protected:
  QFormLayout * formLayout;

signals:

public slots:

};

#endif // BOUNDSWIDGET_H
