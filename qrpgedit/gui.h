#ifndef GUI_H
#define GUI_H 1

#include <QGLWidget>
#include <qdialog.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qtoolbutton.h>

#include "filebrowser.h"
#include "map.h"
#include "mapwindow.h"
#include "spritedialog.h"
#include "newbitmapdialog.h"
#include "newmapdialog.h"
#include "newlayerdialog.h"
#include "spritedialog.h"
#include "newprojectdialog.h"
#include "layerpanel.h"
#include "tileselect.h"

class SpriteDialog;
class MapWindow;
class Entity;

/* Note:  Change map list into general resource list, with maps,
   tilesets, sprites, scripts, etc each listed under their own
   list item, preferably with an icon of some type. */

void init_pixmaps();

/* TODO:  Implement tileset editing dialog */

/* TODO:  Implement sprite editing dialog */

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();
  bool MapSelected();

public slots:
  void ShowNewLayerDialog(int);
  void ShowEntityDialog(Entity *);
  void ShowMapScriptDialog(Map *);
  void deleteLayer(int);
  void ResourceSelected();

  void AboutQt();
  
  void NewProject();
  void LoadProject();
  void LoadProject(QString);
  void SaveProject();

  void NewMap();
  void LoadMap();
  void SaveMap();

  void NewBitmap();
  
  void NewSprite();

  void SetMapButtonsDisabled(bool);
  void SetTilesetButtonsDisabled(bool);
  void SetLayerButtonsDisabled(bool);
  void SetLayerButtonsForMap(int);

  void UpdateMousePos(int, int, int, int);

  void UpdateProjectTitle(QString);

  void play();

  void setViewTilePos(bool);
  void setViewEntityNames(bool);
  void setViewGrid(bool);

signals:
  void SetMap(int);
  void SetTiles(int);
  void updateLayers();
  void UpdateMapStatus(QString);

private:
  // Map window
  MapWindow * mapwin;

  // Dialogs
  NewLayerDialog * newlayerdialog;
  NewMapDialog * newmapdialog;
  NewBitmapDialog * newbitmapdialog;
  NewProjectDialog * newprojectdialog;
  SpriteDialog * spritedialog;
  TileSelect * tiles;

  // Menus
  QMenu * FileMenu;
  QMenu * ResourceMenu;
  QMenu * MapMenu;
  QMenu * TilesetMenu;
  QMenu * SpriteMenu;
  QMenu * ViewMenu;
  QMenu * HelpMenu;

  // Toolbars
  QToolBar * MapToolBar;

  // Dockable dialogs
  QDockWidget * tileDock;
  QDockWidget * mapDock;
  LayerPanel * layerPanel;

  // Actions
  QAction * newprojectAction;
  QAction * openprojectAction;
  QAction * saveprojectAction;
  QAction * quitAction;
  QAction * newmapAction;
  QAction * openmapAction;
  QAction * savemapAction;
  QAction * addlayerAction;
  QAction * deletelayerAction;
  QAction * newbitmapAction;
  QAction * newspriteAction;
  QAction * appPlayAction;
  QAction * mapEditAction;
  QAction * mapEntityAction;
  QAction * aboutQtAction;
  QAction * viewTilePosAction;
  QAction * viewGridAction;
  QAction * viewEntityNamesAction;

  // Other stuff
  QString appTitle;
};

#endif
