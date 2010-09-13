#include <QtGui>
#include "mapbox.h"

class EngineWindow : public QDialog {
public:
  EngineWindow();
  MapBox * mapBox;
  
  //void keyPressEvent(QKeyEvent * event);
  //void keyReleaseEvent(QKeyEvent * event);
  //void keyEvent(int key, int eventType);
  void resizeEvent(QResizeEvent * event);
};
