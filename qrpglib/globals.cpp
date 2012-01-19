#include <QtCore>
#include <QtScript>
#include <QtDeclarative>
//#include <QtScriptTools/QScriptEngineDebugger>
#include "globals.h"
#include "map.h"
#include "bitmap.h"
#include "sprite.h"
#include "tileselect.h"
#include "project.h"
#include "scriptutils.h"
#include "entity.h"
#include "mapbox.h"
#include "qrpgconsole.h"
#include "talkbox.h"
#include "qmlutils.h"
#include "rpgscript.h"
#include "qdeclarativedebughelper_p.h"

QTreeWidget * maplist;
Resource * mapfolder;
Resource * spritefolder;
Resource * bitmapfolder;
Resource * scriptfolder;
Resource * entityfolder;
Resource * currentresource = 0;

TalkBox * talkBoxTest;

bool is_editor = false;
bool rpgEngineStarting = false;

TileSelect * tiles;

QList < Map * > maps;
QList < Bitmap * > bitmaps;
QList < Sprite * > sprites;
QList < RPGScript > globalScripts;

QHash < QString, int > mapnames;
QHash < QString, int > bitmapnames;
QHash < QString, int > spritenames;
QHash < QString, int > entityNames;
QHash < QString, int > staticEntityNames;
QHash < QString, int > mapentitynames;

QTime apptime;
QTime fpstime;

Project * currentProject = 0; 
MainWindow * mainWindow = 0;
Map * currentMap = 0;
QGLWidget * mainGLWidget = 0;
MapBox * mapBox = 0;
Player * playerEntity = 0;
QRPGConsole * console = 0;
int paintMode = PaintMode::Draw;

QScriptEngine * scriptEngine;
//QScriptEngineDebugger * scriptDebugger;
QDeclarativeEngine * declarativeEngine;


ScriptUtils * scriptUtils;
QmlUtils * qmlUtils;

QPixmap * talkBoxBackground;
int timeLastFrame = 0;
int timeSinceLastFrame = 0;
int frames = 0;
int framesThisSecond = 0;

int screen_x = 0;
int screen_y = 0;

bool play = false;

bool viewTilePos = false;
bool viewEntityNames = false;
bool viewGrid = false;
bool viewBoundingBoxes = false;
bool paused = false;

void message(QString s)
{
  qDebug() << "MESSAGE: " << s;
  QMessageBox b;
  b.setText(s);
  b.exec();
}

void cprint(QString s) {
  if(console) console->append(s);
}

void escapeCData(QString & s) {
  s.replace("]]>", "]]]]><![CDATA[>");
}

void initScriptEngine()
{
  //scriptEngine = new QScriptEngine;

  scriptEngine = QDeclarativeDebugHelper::getScriptEngine(declarativeEngine);
  declarativeEngine->setOutputWarningsToStandardError(true);
  //QDeclarativeExpression *expr = new QDeclarativeExpression(declarativeEngine->rootContext(), mapBox->rootObject(), "plasmoid.setEngine(plasmoid)");
  //expr->evaluate();
  //delete expr;

  qDebug() << scriptEngine;
  //scriptDebugger = new QScriptEngineDebugger;
  //scriptDebugger->attachTo(scriptEngine);
  scriptUtils = new ScriptUtils;

  qDebug() << "init script engine";
}
