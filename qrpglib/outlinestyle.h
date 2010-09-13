#ifndef OUTLINESTYLE_H 
#define OUTLINESTYLE_H 1

#include <QtGui>
#include <QWindowsStyle>

class OutlineStyle : public QWindowsStyle {
  Q_OBJECT
public:
  OutlineStyle(QColor c = QColor(255, 255, 255), 
                           QColor oc = QColor(0, 0, 0), qreal w = 2.0);
  QRect itemTextRect(const QFontMetrics &metrics, const QRect &rect, int alignment, bool enabled,
                       const QString &text) const;
  void drawItemText(QPainter *painter, const QRect &rect, int alignment, const QPalette &pal,
                          bool enabled, const QString& text, QPalette::ColorRole textRole) const;
  void setColor(QColor c);
  void setOutlineColor(QColor c);
  void setOutlineWidth(qreal w);

private:
  QColor color;
  QColor outlineColor;
  qreal outlineWidth;
};

#endif
