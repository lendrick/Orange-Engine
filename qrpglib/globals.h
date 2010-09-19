#ifndef GLOBALS_H
#define GLOBALS_H 1

#include <QtCore>
#include <QtGui>
#include <QtScript>
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

class Map;
class MapBox;
class Bitmap;
class Sprite;
class Resource;
class MainWindow;
class Project;
class Entity;
class ScriptUtils;
class Player;
class QRPGConsole;
class ImageFrame;
class TalkBox;

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
extern QList < Entity * > entities;

extern QHash < QString, int > mapnames;
extern QHash < QString, int > bitmapnames;
extern QHash < QString, int > spritenames;
extern QHash < QString, int > entitynames;
extern QHash < QString, int > mapentitynames;

extern QTime apptime;
extern QTime fpstime;

extern Project * currentProject;
extern MainWindow * mainWindow;
extern Map * currentMap;

extern QGLWidget * mainGLWidget;

extern QScriptEngine * scriptEngine;
//extern QScriptEngineDebugger * scriptDebugger;
extern ScriptUtils * scriptUtils;

extern bool play;

extern int screen_x;
extern int screen_y;

extern int timeLastFrame;
extern int timeSinceLastFrame;

extern MapBox * mapBox;
extern Player * playerEntity;
extern QRPGConsole * console;

extern bool is_editor;

extern bool viewTilePos;
extern bool viewEntityNames;
extern bool viewGrid;

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
    Start,
    Touch,
    Activate,
    EveryFrame
  };

  static const QStringList conditions() {
    return QStringList()
      << "Start"
      << "Touch"
      << "Activate"
      << "Every Frame";
  };
};

#endif
