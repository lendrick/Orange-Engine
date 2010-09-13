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
//  QGL::setPreferredPaintEngine(QPaintEngine::OpenGL);
//#endif
  play = false;
  QApplication mapedit(argc, argv);
  initScriptEngine();
  mainGLWidget = new QGLWidget;
  MainWindow mainwindow;
  mainWindow = &mainwindow;

  //QMessageBox::warning(0, "...", QString::number(argc));
  
  if(argc == 2) {
    QString file(argv[1]);
    mainwindow.LoadProject(file);
  }
  
  //mapedit.setMainWidget(&mainwindow);
  mainwindow.resize(1024, 768);
  mainwindow.show();
  
  apptime.start();
  mapedit.exec();
}
