#ifndef GUI_H
#define GUI_H 1

#include <QGLWidget>
#include <QtCore>

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
  bool mapSelected();

public slots:
  void showNewLayerDialog(int);
  void showEntityDialog(EntityPointer);
  void showPropertyEditor(ObjectPointer);
  void showMapScriptDialog(Map *);
  void showGlobalScriptDialog();
  void deleteLayer(int);
  void resourceSelected();

  void aboutQt();
  
  void newProject();
  void loadProject();
  void loadProject(QString);
  void saveProject();

  void newMap();
  void loadMap();
  void saveMap();

  void newBitmap();
  
  void newSprite();

  void setMapButtonsDisabled(bool);
  void setTilesetButtonsDisabled(bool);
  void setLayerButtonsDisabled(bool);
  void setLayerButtonsForMap(int);

  void updateMousePos(int, int, int, int);

  void updateProjectTitle(QString);

  void play();

  void setViewTilePos(bool);
  void setViewEntityNames(bool);
  void setViewGrid(bool);
  void setViewBoundingBoxes(bool);

  void setPaintModeDraw(bool);
  void setPaintModeBrush(bool);
  void setPaintModeFill(bool);
  void setPaintModeSelectBox(bool);

signals:
  void setMap(int);
  void setTiles(int);
  void updateLayers();
  void updateMapStatus(QString);

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
  QMenu * fileMenu;
  QMenu * resourceMenu;
  QMenu * mapMenu;
  QMenu * editMenu;
  QMenu * tilesetMenu;
  QMenu * spriteMenu;
  QMenu * viewMenu;
  QMenu * helpMenu;

  // Toolbars
  QToolBar * mapToolBar;
  QToolBar * paintToolBar;

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
  QAction * viewBoundingBoxesAction;

  QAction * paintDrawAction;
  QAction * paintBrushAction;
  QAction * paintFillAction;
  QAction * paintSelectBoxAction;

  QAction * cutAction;
  QAction * copyAction;
  QAction * pasteAction;
  QAction * deleteAction;
  QAction * selectAllAction;
  QAction * selectNoneAction;

  // Other stuff
  QString appTitle;

protected:
  //bool event(QEvent *event);
};

#endif
