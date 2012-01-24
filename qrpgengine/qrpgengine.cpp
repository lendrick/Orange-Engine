#ifdef WIN32
#include <windows.h>
#endif

#include <QtCore>
#include <QtGui>
#include <QGLWidget>
#include "globals.h"
#include "project.h"
#include "enginewindow.h"
#include "resource.h"
#include "player.h"
#include "npc.h"
#include "rpgengine.h"
#include "projectreader.h"
#include "talkbox.h"
#include "scriptutils.h"
#include "qmlutils.h"

// for testing
#include <cstdlib>

/*
#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif
*/

int main(int argc, char *argv[]) {
#if defined(_MSC_VER)
  //_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
  //_CrtSetBreakAlloc(201852);
#endif
  qputenv("QML_ENABLE_TEXT_IMAGE_CACHE", "true");

  is_editor = false;
//#if QT_VERSION < 0x040600
  QGL::setPreferredPaintEngine(QPaintEngine::OpenGL2);
//#endif
  QApplication::setGraphicsSystem("opengl");
  QApplication mapedit(argc, argv);
  mainGLWidget = new QGLWidget();
  EngineWindow mainwindow;

  mapBox = mainwindow.mapBox;
  declarativeEngine = mapBox->engine();
  initScriptEngine();

  RPGEngine::init();
  //mainGLWidget = new QGLWidget;
  play = true;

  QTreeWidget * resources = new QTreeWidget;
  bitmapfolder = new Resource(Resource::Folder, 0, "Tilesets", resources);
  mapfolder = new Resource(Resource::Folder, 0, "Maps", resources);
  spritefolder = new Resource(Resource::Folder, 0, "Sprites", resources);
  scriptfolder = new Resource(Resource::Folder, 0, "Scripts", resources);
  entityfolder = new Resource(Resource::Folder, 0, "Entities", resources);

  ProjectReader projectReader;
  Project * loadedProject;
  //int id = QFontDatabase::addApplicationFont("PfennigBold.otf");
  QFontDatabase::addApplicationFont("PfennigBold.otf");
  talkBoxBackground = new QPixmap("ui.png");

  if(!QDir::setCurrent("Tech Demo 2")) {
    message("Could not change directory!\n" + QDir::currentPath());
    return 1;
  }

  loadedProject = projectReader.read("Tech Demo 2.xproj");

  mainwindow.resize(1024, 768);
  mainwindow.show();
  mapBox->setDrawMode(LayerView::AllOpaque);

  /*
  mapBox->setMap(0);
  mapBox->setLayer(0);
  maps[0]->reset();
  */

  RPGEngine::setPlayerEntity(new Player);
  /*
  playerEntity->setPos(150, 50);
  playerEntity->setSprite(sprites[0]);
  playerEntity->addToMap(1);
  //mainwindow.mapBox->GetMap()->AddEntity(0, p);
  mainwindow.mapBox->setCamera(playerEntity);
  */

  /*
  for(int i = 0; i < 500; i++) {
    Npc * n = new Npc("dude" + QString::number(i));
    n->setSprite(sprites[0]);
    n->setPos(rand() % 200 - 100 + screen_x / 2, rand() % 200 - 100 + screen_y / 2);
    for(int j = 0; j < 5; j++) {
      n->queueMove(rand() % 400 - 200, rand() % 400 - 200, rand() % 10 + 30);
    }
    mainwindow.mapBox->GetMap()->AddEntity(3, n);
  }
  */

  //TalkBoxProxy * tb = new TalkBoxProxy("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.");
  //tb->deleteLater();
  //declarativeEngine = mapBox->engine();

  qmlUtils = new QmlUtils;
  declarativeEngine->rootContext()->setContextProperty("utils", qmlUtils);

  //bool dirExists = QDir::setCurrent("scripts");
  scriptUtils->include("scripts/init.js");
  //if(dirExists) QDir::setCurrent("..");

  apptime.start();
  fpstime.start();
  timeLastFrame = apptime.elapsed();
  mapedit.exec();

#ifdef _MSC_VER
  //_CrtDumpMemoryLeaks();
#endif

  return 0;
}
