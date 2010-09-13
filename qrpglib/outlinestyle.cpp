#include <QtGui>
#include "outlinestyle.h"
  
OutlineStyle::OutlineStyle(QColor c, QColor oc, qreal w) : QWindowsStyle()
{
  color = c;
  outlineColor = oc;
  outlineWidth = w;
}

void OutlineStyle::setColor(QColor c)
{
  color = c;
}

void OutlineStyle::setOutlineColor(QColor c)
{
  outlineColor = c;
}

void OutlineStyle::setOutlineWidth(qreal w)
{
  outlineWidth = w;
}

QRect OutlineStyle::itemTextRect(const QFontMetrics &metrics, const QRect &rect, int alignment, bool enabled,
                       const QString &text) const
{
  QRect result;
  int x, y, w, h;
  rect.getRect(&x, &y, &w, &h);
  if (!text.isEmpty()) {
    result = metrics.boundingRect(x, y, 
      w + outlineWidth * 2, h + outlineWidth * 2, alignment, text);
    if (!enabled && styleHint(SH_EtchDisabledText)) {
      result.setWidth(result.width()+1);
      result.setHeight(result.height()+1);
    }
  } else {
    result = QRect(x, y, w, h);
  }
  return result;
}

void OutlineStyle::drawItemText(QPainter *painter, const QRect &rect, int alignment, 
const QPalette &pal, bool enabled, const QString& text, QPalette::ColorRole textRole) const
{
  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);
  if (text.isEmpty())
    return;
  QPen savedPen;
  QBrush savedBrush;

  if (textRole != QPalette::NoRole) {
    savedPen = painter->pen();
    painter->setPen(QPen(outlineColor, outlineWidth));
    
    savedBrush = painter->brush();
    painter->setBrush(QBrush(color));
  }  
  
  /*
  if (!enabled) {
    if (styleHint(SH_DitherDisabledText)) {
      painter->drawText(rect, alignment, text);
      painter->fillRect(painter->boundingRect(rect, alignment, text), QBrush(painter->background().color(), Qt::Dense5Pattern));
      return;
    } else if (styleHint(SH_EtchDisabledText)) {
      QPen pen = painter->pen();
      painter->setPen(pal.light().color());
      painter->drawText(rect.adjusted(1, 1, 1, 1), alignment, text);
      painter->setPen(pen);
    }
  }
  */
  
  QPainterPath textPath;
  QRect r = rect;
  r.setTop(r.top() - outlineWidth * 2);
  r.setBottom(r.bottom() + outlineWidth * 2);
  r.setLeft(r.left() + outlineWidth);
  r.setRight(r.right() - outlineWidth);
  r.moveBottom(r.bottom() - outlineWidth - painter->fontMetrics().descent());
  
  textPath.addText(r.bottomLeft(), painter->font(), text);
  painter->drawPath(textPath);
  if (textRole != QPalette::NoRole) {
    painter->setPen(savedPen);
    painter->setBrush(savedBrush);
  }
  
  painter->restore();
}

