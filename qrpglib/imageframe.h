#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H 1

#include <QtGui>

class ImageFrame : public QGraphicsWidget {
  Q_OBJECT
public:
  ImageFrame(QPixmap * p, QGraphicsItem * parent = 0);
  ~ImageFrame();
  virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
private:
  QPixmap * pixmap;
};

#endif