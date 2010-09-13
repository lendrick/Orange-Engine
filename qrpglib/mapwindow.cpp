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

#include "globals.h"
#include "scrollbar.h"
#include "outlinestyle.h"

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

  status = new QStatusBar(this);

  connect(mapbox, SIGNAL(SetXRange(int, int)), 
	  HScroll, SLOT(setRange(int, int)));
  connect(mapbox, SIGNAL(SetYRange(int, int)), 
	  VScroll, SLOT(setRange(int, int)));

  connect(VScroll, SIGNAL(valueChanged(int)),
	  mapbox, SLOT(SetY(int)));
  connect(HScroll, SIGNAL(valueChanged(int)),
	  mapbox, SLOT(SetX(int)));

  connect(mapbox, SIGNAL(SetXScroll(int)),
	  HScroll, SLOT(setValue(int)));
  connect(mapbox, SIGNAL(SetYScroll(int)),
	  VScroll, SLOT(setValue(int)));
  
  connect(this, SIGNAL(setDrawMode(LayerView::LayerViewMode)), mapbox, SLOT(setDrawMode(LayerView::LayerViewMode)));

  Grid->addWidget(mapbox, 0, 0);
  Grid->addWidget(VScroll, 0, 1);
  Grid->addWidget(HScroll, 1, 0);
  Grid->addWidget(status, 2, 0, 1, 2);
}

void MapWindow::updateStatus(QString s) {
  status->showMessage(s);
}