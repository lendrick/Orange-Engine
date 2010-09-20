#include <QtGui>
#include "talkbox.h"
#include "outlinestyle.h"
#include "globals.h"
#include "mapbox.h"

TalkBox::TalkBox(QString text, QGraphicsItem * parent) : QTextEdit(0) {
  setReadOnly(true);
  //setAttribute(Qt::WA_TranslucentBackground);
  //setWindowFlags(Qt::FramelessWindowHint);

  proxy = new QGraphicsProxyWidget(parent);
  proxy->setWidget(this);

  setGeometry(10, 300, 620, 170);
  setText(text);
  setStyle(new QWindowsStyle());
  setStyleSheet(
    "background: transparent;"
    "border-image: url('../pixmaps/box.png') 50 50 50 50 stretch;"
    "color: rgba(255, 255, 255, 255);"
    "font-size: 27px;"
    "font-weight: bold;"
    "font-family: Pfennig, Sans;"
    "margin: 10px;"
  );
  
  mapBox->mapScene->addItem(proxy);

}

void TalkBox::showEvent(QShowEvent * e) {

}

void TalkBox::say(QString s) {

}

void TalkBox::next() {
}


