#ifdef WIN32
#include <windows.h>
#endif

#include <QtCore>
#include <QtGui>

#include "globals.h"
#include "gui.h"
#include "project.h"

int main(int argc, char *argv[]) {
  is_editor = true;
//#if QT_VERSION >= 0x040600
  QGL::setPreferredPaintEngine(QPaintEngine::OpenGL2);
//#endif
  play = false;
  QApplication mapedit(argc, argv);
  mainGLWidget = new QGLWidget(QGLFormat(QGL::SampleBuffers));
  MainWindow mainwindow;
  mainWindow = &mainwindow;

  //mapBox = mainwindow.mapBox();

  declarativeEngine = mapBox->engine();
  initScriptEngine();

  //QMessageBox::warning(0, "...", QString::number(argc));
  
  if(argc == 2) {
    QString file(argv[1]);
    mainwindow.loadProject(file);
  }
  
  //mapedit.setMainWidget(&mainwindow);
  mainwindow.resize(1024, 768);
  mainwindow.show();
  
  apptime.start();
  mapedit.exec();
}
