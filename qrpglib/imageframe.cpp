#include <QtGui>
#include "imageframe.h"

ImageFrame::ImageFrame(QPixmap * p, QGraphicsItem * parent) : QGraphicsWidget(parent) {
  //brush = new QBrush(*p);
  //brush->setTileRule
  pixmap = p;
  //setAttribute(Qt::WA_TranslucentBackground);
}

ImageFrame::~ImageFrame() {
}

void ImageFrame::paint(QPainter * paint, const QStyleOptionGraphicsItem * option, QWidget * widget) {
  paint->setRenderHint(QPainter::SmoothPixmapTransform, true);
  paint->drawPixmap(0, 0, size().width(), size().height(), *pixmap);
  //paint.drawPixmap(frameGeometry(), *pixmap);
}