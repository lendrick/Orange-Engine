#ifdef WIN32
#include <windows.h>
#endif

#include "mapwindow.h"
#include "bitmap.h"
#include "tileselect.h"
#include "map.h"

#include <qgl.h>
#include <QtGui>
#include <qtimer.h>
#include <iostream>
#include <vector>
#include <QTime>
#include <QGridLayout>

#include "globals.h"
#include "scrollbar.h"
#include "outlinestyle.h"
#include "rpgengine.h"

using std::cout;

MapWindow::MapWindow(QWidget *parent) 
  : QWidget(parent) {
  QGridLayout * Grid = new QGridLayout(this);
  mapbox = new MapBox(this);
  ScrollBar * VScroll = new ScrollBar(Qt::Vertical, this);
  ScrollBar * HScroll = new ScrollBar(Qt::Horizontal, this);
  QSizePolicy * p = new QSizePolicy(QSizePolicy::Fixed,
				    QSizePolicy::Expanding);
  VScroll->setSizePolicy(*p);

  connect(mapbox, SIGNAL(setXRange(int, int)),
	  HScroll, SLOT(setRange(int, int)));
  connect(mapbox, SIGNAL(setYRange(int, int)),
	  VScroll, SLOT(setRange(int, int)));

  connect(VScroll, SIGNAL(valueChanged(int)),
          mapbox, SLOT(setY(int)));
  connect(HScroll, SIGNAL(valueChanged(int)),
          mapbox, SLOT(setX(int)));

  connect(mapbox, SIGNAL(setXScroll(int)),
	  HScroll, SLOT(setValue(int)));
  connect(mapbox, SIGNAL(setYScroll(int)),
	  VScroll, SLOT(setValue(int)));
  
  connect(this, SIGNAL(setDrawMode(LayerView::LayerViewMode)), mapbox, SLOT(setDrawMode(LayerView::LayerViewMode)));

  Grid->addWidget(mapbox, 0, 0);
  Grid->addWidget(VScroll, 0, 1);
  Grid->addWidget(HScroll, 1, 0);
}

void MapWindow::updateStatus(QString s) {
  emit updateMapStatus(s);
}

/*
bool MapWindow::event(QEvent *event)
{
  if(event->type() != 43) {
    qDebug() << "MapWindow: " << RPGEngine::eventName(event);
  }
  return QWidget::event(event);
}
*/
