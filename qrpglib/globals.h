#ifndef GLOBALS_H
#define GLOBALS_H 1

#include <QtCore>
#include <QtGui>
#include <QtScript>
#include <QtDeclarative>
#include <QGLWidget>
//#include <QtScriptTools/QScriptEngineDebugger>

struct LayerView {
  enum LayerViewMode {
    All,
    OnlyThis,
    AllBelow,
    AllOpaque
  };
};

struct MapEditorMode {
  enum MapEditorModeEnum {
    Edit,
    Entity,
    Select,
    Brush
  };
};

struct PaintMode {
  enum PaintModeEnum {
    Draw,
    Brush,
    SelectBox,
    Fill
  };
};

class Map;
class MapBox;
class Bitmap;
class Sprite;
class Resource;
class MainWindow;
class Project;
class ScriptUtils;
class Player;
class QRPGConsole;
class ImageFrame;
class TalkBox;
class RPGScript;
class QmlUtils;

extern TalkBox * talkBoxTest;

extern Resource * mapfolder;
extern Resource * spritefolder;
extern Resource * bitmapfolder;
extern Resource * scriptfolder;
extern Resource * entityfolder;
extern Resource * currentresource;

extern QList < Map * > maps;
extern QList < Bitmap * > bitmaps;
extern QList < Sprite * > sprites;
extern QList < RPGScript > globalScripts;

extern QHash < QString, int > mapnames;
extern QHash < QString, int > bitmapnames;
extern QHash < QString, int > spritenames;
extern QHash < QString, int > entityNames;
extern QHash < QString, int > staticEntityNames;
extern QHash < QString, int > mapentitynames;

extern QTime apptime;
extern QTime fpstime;

extern Project * currentProject;
extern MainWindow * mainWindow;
extern Map * currentMap;

extern QGLWidget * mainGLWidget;

extern QScriptEngine * scriptEngine;
extern QDeclarativeEngine * declarativeEngine;
extern QmlUtils * qmlUtils;
//extern QScriptEngineDebugger * scriptDebugger;
extern ScriptUtils * scriptUtils;

extern bool play;

extern int screen_x;
extern int screen_y;

extern int timeLastFrame;
extern int timeSinceLastFrame;
extern int frames;
extern int framesThisSecond;


extern MapBox * mapBox;
extern Player * playerEntity;
extern QRPGConsole * console;

extern bool is_editor;

extern bool viewTilePos;
extern bool viewEntityNames;
extern bool viewGrid;
extern bool viewBoundingBoxes;

extern bool rpgEngineStarting;

extern int paintMode;

extern QPixmap * talkBoxBackground;

void message(QString s);
void cprint(QString s);
void initScriptEngine();
void escapeCData(QString & s);

class Resource;
//class TileSelect;

extern QTreeWidget * maplist;
//extern TileSelect * tiles;

struct ScriptCondition {
  enum ScriptConditionEnum {
    Load,
    UnLoad,
    Enter,
    Exit,
    Activate,
    Touching,
    EveryFrame
  };

  static const QStringList conditions() {
    return QStringList()
      << "Load"
      << "UnLoad"
      << "Enter"
      << "Exit"
      << "Activate"
      << "Touching"
      << "Every Frame";
  }
};

#endif
