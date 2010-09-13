#include <QtGui>
#include "enginewindow.h"
#include "mapbox.h"
#include "input.h"
#include "globals.h"
#include "qrpgconsole.h"

EngineWindow::EngineWindow() : QDialog() {
  mapBox = new MapBox;
  QVBoxLayout * layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
  mapBox->setStyleSheet("border-style: none; padding: 0;");
  layout->addWidget(mapBox);
  
  console = new QRPGConsole;
  mapBox->addWidget(console);
  console->hide();
  console->setGeometry(0, height() - 200, width(), 200);
}

void EngineWindow::resizeEvent(QResizeEvent * event) {
  if(console) console->setGeometry(0, height() - 200, width(), 200);
}
