#include <QtGui>
#include "talkbox.h"
#include "outlinestyle.h"
#include "globals.h"
#include "mapbox.h"
#include "mapscene.h"

TalkBoxProxy::TalkBoxProxy(QString text, QGraphicsItem * parent) : QGraphicsProxyWidget(parent) {
  widget = new TalkBox(text, this);
  setWidget(widget);

  mapBox->mapScene->addItem(this);
  //setAttribute(Qt::WA_DeleteOnClose);
  connect(widget, SIGNAL(destroyed()), this, SLOT(deleteLater()));
  //deleteLater();
}

TalkBox::TalkBox(QString text, QGraphicsProxyWidget * p) : QTextEdit(0) {
  setReadOnly(true);
  //setAttribute(Qt::WA_TranslucentBackground);
  //setWindowFlags(Qt::FramelessWindowHint);
  proxy = p;

  setGeometry(10, 300, 620, 170);
  setText(text);
  setStyle(new QWindowsStyle());
  setStyleSheet( "TalkBox {"
    "background: transparent;"
    "border-image: url(../interface/box.png) 28 28 28 28 stretch stretch;"
    "color: rgba(255, 255, 255, 255);"
    "border-width: 28px;"
    "font-size: 30px;"
    "font-weight: bold;"
    "font-family: Pfennig, Sans;"
    "margin: 0;}"
  );
  viewport()->unsetCursor();
  verticalScrollBar()->hide();
  setAttribute(Qt::WA_DeleteOnClose);

  QFontMetrics fontMetrics(font());
  lineHeight = fontMetrics.lineSpacing();
}

void TalkBox::showEvent(QShowEvent * e) {

}

void TalkBox::say(QString s) {

}

void TalkBox::next() {
}

void TalkBox::mousePressEvent(QMouseEvent *e) {
  pageDown();
}

void TalkBox::mouseMoveEvent(QMouseEvent *e) {
}

void TalkBox::mouseDoubleClickEvent(QMouseEvent *e) {
  pageDown();
}

void TalkBox::enterEvent(QEvent *e)
{
}

void TalkBox::leaveEvent(QEvent *e)
{
}

void TalkBox::pageDown() {
  verticalScrollBar()->setValue(verticalScrollBar()->value() + lineHeight * 3);

  if(verticalScrollBar()->value() == verticalScrollBar()->maximum()) {
    //proxy->setWidget(0);
    //proxy->deleteLater();
    //deleteLater();
    //message("..");
    close();
    //setText("Hello, world!");
  }
}

TalkBox::~TalkBox() {
}
