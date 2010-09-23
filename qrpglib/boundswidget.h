#ifndef BOUNDSWIDGET_H
#define BOUNDSWIDGET_H

#include <QFrame>
#include "coordinatewidget.h"

class BoundsWidget : public QFrame
{
  Q_OBJECT
public:
  explicit BoundsWidget(QWidget *parent = 0);
  CoordinateWidget topLeft;
  CoordinateWidget bottomRight;
signals:

public slots:

};

#endif // BOUNDSWIDGET_H
