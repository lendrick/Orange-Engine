#include <QtGui>
#include "talkbox.h"
#include "outlinestyle.h"
#include "globals.h"
#include "mapbox.h"

TalkBox::TalkBox(QString text, QGraphicsItem * parent) : ImageFrame(talkBoxBackground, parent) {
  //setAttribute(Qt::WA_TranslucentBackground);
  //setWindowFlags(Qt::FramelessWindowHint);
  QGraphicsLinearLayout * layout = new QGraphicsLinearLayout(Qt::Vertical);
  setLayout(layout);
  setGeometry(10, 300, 620, 170);
  
  QLabel * label = new QLabel;
  //OutlineStyle * outlineStyle = new OutlineStyle();
  label->setStyle(new QWindowsStyle);
  label->setWordWrap(true);
  label->setText(text);
  //label->setBackgroundRole(QPalette::Base);
  label->setAttribute(Qt::WA_TranslucentBackground);
  labelProxy = new QGraphicsProxyWidget();
  labelProxy->setWidget(label);
  //labelProxy->setScale(.5);
  layout->addItem(labelProxy);

  
  label->setStyleSheet(
    //"background: transparent;"
    "color: rgba(255, 255, 255, 255);"
    "font-size: 27px;"
    "font-weight: bold;"
    "font-family: Pfennig, Sans;"
    "margin: 10px;"
  );
  
  mapBox->mapScene->addItem(this);
  QStateMachine * machine = new QStateMachine;
  QState * fadeIn = new QState(machine);
  fadeIn->assignProperty(labelProxy, "opacity", qreal(0));
  machine->setInitialState(fadeIn);
  
  QState * display = new QState(machine);
  display->assignProperty(labelProxy, "opacity", qreal(1));
  
  QAbstractTransition * transition1 = fadeIn->addTransition(display);
  QPropertyAnimation * animation = new QPropertyAnimation(labelProxy, "opacity");
  animation->setDuration(750);
  transition1->addAnimation(animation);
  
  machine->start();
  
  //transition1->addAnimation(animation);

}

void TalkBox::showEvent(QShowEvent * e) {
  ImageFrame::showEvent(e);
  /*
  int w = 620;
  int h = 170;
  int x = (640 - w) / 2;
  int y = 480 - h - x;

  int sw = 620 * .8;
  int sh = 170 * .8;
  int sx = (640 - sw) / 2;
  int sy = 640 - sh - sx;

  QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
  animation->setDuration(250);
  animation->setStartValue(QRect(sx, sy, sw, sh));
  animation->setEndValue(QRect(x, y, w, h));
  animation->start();  
  //while(1) message(QString::number(animation->currentTime()));
  */
}

void TalkBox::say(QString s) {

}

void TalkBox::next() {
}

void TalkBox::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) {
//  QColor c(property("textcolor").value<QColor>());
  ImageFrame::paint(painter, option, widget);
}