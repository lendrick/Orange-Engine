#ifdef WIN32
#include <windows.h>
#endif

#include <QtGui>

#include "filebrowser.h"
#include "globals.h"
#include "gui.h"
#include "tileselect.h"
#include "mapwindow.h"
#include "spritewidget.h"
#include "sprite.h"
#include "bitmap.h"
#include "project.h"
#include "resource.h"
#include "newbitmapdialog.h"
#include "newmapdialog.h"
#include "newlayerdialog.h"
#include "spritedialog.h"
#include "icons.h"
#include "layerpanel.h"
#include "entitydialog.h"
#include "entity.h"


MainWindow::MainWindow() :
  QMainWindow() {
  initIcons();
  appTitle = "RPGX Editor";

  setWindowTitle(appTitle);

  // Create the main menu
  FileMenu = menuBar()->addMenu("&File");
  ResourceMenu = menuBar()->addMenu("&Resources");
  MapMenu = ResourceMenu->addMenu("&Maps");
  MapMenu->setDisabled(true);
  TilesetMenu = ResourceMenu->addMenu("&Tilesets");
  TilesetMenu->setDisabled(true);
  SpriteMenu = ResourceMenu->addMenu("&Sprites");
  SpriteMenu->setDisabled(true);
  ViewMenu = menuBar()->addMenu("&View");
  HelpMenu = menuBar()->addMenu("&Help");

  //////////////////////////////////////////////////////////////
  // Create the toolbar
  MapToolBar = addToolBar("MapToolBar");
  MapToolBar->setIconSize(QSize(32, 32));

  // iconsets

  aboutQtAction = new QAction("About &Qt", 0);
  HelpMenu->addAction(aboutQtAction);
  connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(AboutQt()));

  //setUsesBigPixmaps(true);
  
  newprojectAction = new QAction(*newprojectIcon, "&New Project...", 0);
  connect(newprojectAction, SIGNAL(triggered()), this, SLOT(NewProject()));
  MapToolBar->addAction(newprojectAction);
  FileMenu->addAction(newprojectAction);

  openprojectAction = new QAction(*openprojectIcon, "&Open Project...", 0);
  connect(openprojectAction, SIGNAL(triggered()), this, SLOT(LoadProject()));
  MapToolBar->addAction(openprojectAction);
  FileMenu->addAction(openprojectAction);

  saveprojectAction = new QAction(*saveprojectIcon, "&Save Project...", 0);
  connect(saveprojectAction, SIGNAL(triggered()), this, SLOT(SaveProject()));
  MapToolBar->addAction(saveprojectAction);
  FileMenu->addAction(saveprojectAction);

  FileMenu->addSeparator();
  quitAction = new QAction("Exit", 0);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
  FileMenu->addAction(quitAction);

  MapToolBar->addSeparator();

  // Map operation buttons

  /*
  Action = new QAction(*Icon, "", 0);
  connect(Action, SIGNAL(triggered()), this, SLOT());
  MapToolBar->addAction(Action);
  Menu->addAction(Action);
  */

  newmapAction = new QAction(*newmapIcon, "New &Map", 0);
  connect(newmapAction, SIGNAL(triggered()), this, SLOT(NewMap()));
  MapToolBar->addAction(newmapAction);
  MapMenu->addAction(newmapAction);
  newmapAction->setDisabled(true);

  openmapAction = new QAction(*openmapIcon, "Import Map", 0);
  connect(openmapAction, SIGNAL(triggered()), this, SLOT(LoadMap()));
  MapToolBar->addAction(openmapAction);
  MapMenu->addAction(openmapAction);
  openmapAction->setDisabled(true);

  savemapAction = new QAction(*savemapIcon, "Export Map", 0);
  connect(savemapAction, SIGNAL(triggered()), this, SLOT(SaveMap()));
  MapToolBar->addAction(savemapAction);
  MapMenu->addAction(savemapAction);
  savemapAction->setDisabled(true);

  /*
  QAction * savemapasAction = new QAction(*savemapasIcon, "Export Map", 0);
  connect(savemapasAction, SIGNAL(triggered()), this, SLOT(SaveMap()));
  MapToolBar->addAction(savemapasAction);
  MapMenu->addAction(savemapasAction);
  */

  MapMenu->addSeparator();

  // Bitmap buttons
  MapToolBar->addSeparator();
  //MapToolBar->addWidget(new QLabel("Bitmaps "));
 
  newbitmapAction = new QAction(*bitmapbuttonIcon, "New &Tileset", 0);
  connect(newbitmapAction, SIGNAL(triggered()), this, SLOT(NewBitmap()));
  MapToolBar->addAction(newbitmapAction);
  TilesetMenu->addAction(newbitmapAction);
  newbitmapAction->setDisabled(true);

  MapToolBar->addSeparator();
  
  newspriteAction = new QAction(*spriteIcon, "New &Sprite", 0);
  connect(newspriteAction, SIGNAL(triggered()), this, SLOT(NewSprite()));
  MapToolBar->addAction(newspriteAction);
  SpriteMenu->addAction(newspriteAction);
  newspriteAction->setDisabled(true);

  MapToolBar->addSeparator();
  
  appPlayAction = new QAction(*appPlayIcon, "Start Game", 0);
  connect(appPlayAction, SIGNAL(triggered()), this, SLOT(play()));
  MapToolBar->addAction(appPlayAction);
  FileMenu->addAction(appPlayAction);
  appPlayAction->setDisabled(true);
    
  MapToolBar->addSeparator();

  QActionGroup * mapActionGroup = new QActionGroup(0);
  mapEditAction = mapActionGroup->addAction(*mapEditIcon, "Edit Map");
  mapEditAction->setCheckable(true);
  MapToolBar->addAction(mapEditAction);

  mapEntityAction = mapActionGroup->addAction(*mapEntityIcon, "Edit Entities");
  mapEntityAction->setCheckable(true);
  MapToolBar->addAction(mapEntityAction);
  
  // View menu
  viewGridAction = new QAction("&Grid", 0);
  viewGridAction->setCheckable(true);
  viewGridAction->setShortcut(QKeySequence("Ctrl+'"));
  ViewMenu->addAction(viewGridAction);
  connect(viewGridAction, SIGNAL(toggled(bool)), this, SLOT(setViewGrid(bool)));

  viewTilePosAction = new QAction("Tile &Coordinates", 0);
  viewTilePosAction->setCheckable(true);
  viewTilePosAction->setShortcut(QKeySequence("Ctrl+Shift+'"));
  ViewMenu->addAction(viewTilePosAction);
  connect(viewTilePosAction, SIGNAL(toggled(bool)), this, SLOT(setViewTilePos(bool)));

  viewEntityNamesAction = new QAction("Entity &Names", 0);
  viewEntityNamesAction->setCheckable(true);
  viewEntityNamesAction->setShortcut(QKeySequence("Ctrl+;"));
  ViewMenu->addAction(viewEntityNamesAction);
  connect(viewEntityNamesAction, SIGNAL(toggled(bool)), this, SLOT(setViewEntityNames(bool)));
  
  //////////////////////////////////////////////////////////////  
  tileDock = new QDockWidget("Tiles");
  this->addDockWidget(Qt::LeftDockWidgetArea, tileDock, Qt::Vertical);
  QTabWidget * TileTab = new QTabWidget();
  tileDock->setWidget(TileTab);
  tileDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
  
  tiles = new TileSelect(TileTab);
  tiles->resize(200, 300);
  TileTab->addTab(tiles, "Tiles");

  ////////////////////////////////////////////////////////////
  // The resource list;

  mapDock = new QDockWidget("Resources");
  this->addDockWidget(Qt::LeftDockWidgetArea, mapDock, Qt::Vertical);
  maplist = new QTreeWidget();
  mapDock->setWidget(maplist);  
  maplist->setHeaderLabel("Resources");
  mapDock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
  maplist->setRootIsDecorated(true);

  bitmapfolder = new Resource(Resource::Folder, 0, "Tilesets", maplist);
  mapfolder = new Resource(Resource::Folder, 0, "Maps", maplist);
  spritefolder = new Resource(Resource::Folder, 0, "Sprites", maplist);
  scriptfolder = new Resource(Resource::Folder, 0, "Scripts", maplist);
  entityfolder = new Resource(Resource::Folder, 0, "Entities", maplist);

  connect(maplist, SIGNAL(itemSelectionChanged()),
	  this, SLOT(ResourceSelected()));

  layerPanel = new LayerPanel(this);
  this->addDockWidget(Qt::LeftDockWidgetArea, layerPanel, Qt::Vertical);
  layerPanel->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

  connect(layerPanel, SIGNAL(addLayer(int)), this, SLOT(ShowNewLayerDialog(int)));
  connect(layerPanel, SIGNAL(delLayer(int)), this, SLOT(deleteLayer(int)));
  SetLayerButtonsDisabled(true);
  
  ////////////////////////////////////////////////////////////
  // The map window
  mapwin = new MapWindow(0);
  mapBox = mapwin->mapbox;
  mapwin->resize(400, 400);

  setCentralWidget(mapwin);

  connect(this, SIGNAL(SetMap(int)), mapwin->mapbox, SLOT(SetMap(int)));
  connect(this, SIGNAL(SetMap(int)), this, SLOT(SetLayerButtonsForMap(int)));
  connect(this, SIGNAL(SetMap(int)), layerPanel, SLOT(updateData()));
  connect(this, SIGNAL(updateLayers()), layerPanel, SLOT(updateData()));
  connect(this, SIGNAL(SetTiles(int)), tiles, SLOT(SetTiles(int)));
  connect(layerPanel, SIGNAL(setDrawMode(LayerView::LayerViewMode)),
          mapwin, SIGNAL(setDrawMode(LayerView::LayerViewMode)));
  connect(tiles->tilebox, SIGNAL(TileChanged(int)), mapwin->mapbox, SLOT(setCurrentTile(int)));
  
  connect(layerPanel, SIGNAL(selectLayer(int)), mapwin->mapbox, SLOT(SetLayer(int)));
  connect(mapEditAction, SIGNAL(triggered()), mapBox, SLOT(setEditMode()));
  connect(mapEntityAction, SIGNAL(triggered()), mapBox, SLOT(setEntityMode()));

  connect(mapBox, SIGNAL(mousePos(int, int, int, int)), 
    this, SLOT(UpdateMousePos(int, int, int, int)));
  connect(this, SIGNAL(UpdateMapStatus(QString)), mapwin, SLOT(updateStatus(QString)));
  connect(mapBox->mapScene, SIGNAL(ShowEntityDialog(Entity *)), this, SLOT(ShowEntityDialog(Entity *)));

  
  mapEditAction->trigger();
  
  // Create dialogs
  newlayerdialog = new NewLayerDialog(this);
  newmapdialog = new NewMapDialog(this);
  newbitmapdialog = new NewBitmapDialog(this);
  newprojectdialog = new NewProjectDialog(this);
  spritedialog = new SpriteDialog(this);
  //spritedialog = new SpriteDialog(centralWidget(), 0, tiles->tilebox);
  //spritedialog->show();
}

MainWindow::~MainWindow() {
}

void MainWindow::ResourceSelected() {
  Resource * item = static_cast<Resource *> (maplist->currentItem());
  currentresource = static_cast<Resource *> (maplist->currentItem());
  if(item->Type() == Resource::Map) {
    emit SetMap(item->GetID());
    tiles->SetTileset(maps[item->GetID()]->GetTileset());
  } else if(item->Type() == Resource::Bitmap) {
    emit SetMap(-1);
    emit SetTiles(item->GetID());
  } else if(item->Type() == Resource::Sprite) {
    emit SetMap(-1);
    //emit SetTiles(item->GetID());
  } else if(item->Type() == Resource::Folder) {
    emit SetMap(-1);
    emit SetTiles(-1);
  }
}

void MainWindow::ShowNewLayerDialog(int before) {
  if(newlayerdialog->exec() == QDialog::Accepted ) {
    mapwin->mapbox->GetMap()->InsertLayerBefore(before, newlayerdialog->xspin->value(),
			newlayerdialog->yspin->value(),
			newlayerdialog->wrapcheck->isChecked(),
      tiles->GetTile(),
      newlayerdialog->layername->text()
    );
    emit updateLayers();
  }
}

void MainWindow::deleteLayer(int layer) {
  if(QMessageBox::warning(this, "Delete Layer?", 
    "Deleting a layer cannot be undone.  Proceed?",
    QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok)
    mapwin->mapbox->DeleteLayer(layer);
  emit updateLayers();
}

void MainWindow::LoadProject() {
  QString currentProjectFilename(QFileDialog::getOpenFileName(
    this,
    "Choose a file",
    ".",
    "Projects (*.xproj)"
  ));
  LoadProject(currentProjectFilename);
}

void MainWindow::LoadProject(QString currentProjectFilename) {
  ProjectReader projectReader;
  Project * loadedProject;

  if(!currentProjectFilename.isEmpty() && !currentProjectFilename.isNull()) {
    if(currentProject) delete currentProject;
    emit SetMap(-1);
    emit SetTiles(-1);
    if((loadedProject = projectReader.read(currentProjectFilename))) {
      currentProject = loadedProject;
      SetMapButtonsDisabled(false);
      SetTilesetButtonsDisabled(false);
    } else {
      QMessageBox::critical(0, "Error", "Project '" + currentProjectFilename + "' could not be loaded.");
    }
  }
}

void MainWindow::NewProject() {
  if(newprojectdialog->exec() == QDialog::Accepted) {
    emit SetMap(-1);
    emit SetTiles(-1);
    if(currentProject) delete currentProject;
    currentProject = new Project(newprojectdialog->projectname->text());
    SetMapButtonsDisabled(false);
    SetTilesetButtonsDisabled(false);
  }
}

void MainWindow::SaveProject() {
  QString name = QFileDialog::getExistingDirectory(this, 
    tr("Open Directory"),
    ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  //message(name);
  
  if(!name.isNull() && !name.isEmpty()) {
    currentProject->Save(name);
    message("Project saved.");
  }
}

void MainWindow::NewSprite() {
  spritedialog->show();
}

void MainWindow::NewMap() {
  if(newmapdialog->exec() == QDialog::Accepted ) {
    tiles->tilebox->makeCurrent();
    Map * m = new Map(bitmaps[newmapdialog->tileset->currentIndex()], 0, 0, 1, 1, newmapdialog->mapname->text());
    maplist->setCurrentItem(m->ThisMap());
    ShowNewLayerDialog(0);
  }
}

void MainWindow::LoadMap() {
  MapReader mapReader;
  Map * m = mapReader.read(QFileDialog::getOpenFileName(
    this, 
    "Choose a file",
    ".",
    "Maps (*.xmap)"
  ));
  maplist->setCurrentItem(m->ThisMap());
}

void MainWindow::SaveMap() {
  Resource * item = static_cast<Resource *> (maplist->currentItem());

  if(item && item->Type() == Resource::Map)
    maps[item->GetID()]->Save( 
			       QFileDialog::getSaveFileName(
               this,
               "Choose a file",
		            ".",
                "Maps (*.xmap)"
             ));
}

void MainWindow::NewBitmap() {
  if(newbitmapdialog->exec() == QDialog::Accepted ) {
    tiles->tilebox->makeCurrent();
    new Bitmap(
			    newbitmapdialog->image->text(),
			    newbitmapdialog->xspin->value(),
			    newbitmapdialog->yspin->value(), 
			    0, 0, newbitmapdialog->bitmapname->text());
  }
}

void MainWindow::SetMapButtonsDisabled(bool disabled) {
  newmapAction->setDisabled(disabled);
  openmapAction->setDisabled(disabled);
  savemapAction->setDisabled(disabled);
  appPlayAction->setDisabled(disabled);
}

void MainWindow::SetTilesetButtonsDisabled(bool disabled) {
  newbitmapAction->setDisabled(disabled);
  newspriteAction->setDisabled(disabled);
}

void MainWindow::SetLayerButtonsDisabled(bool disabled) {
  layerPanel->setDisabled(disabled);
  //addlayerAction->setDisabled(disabled);
  //deletelayerAction->setDisabled(disabled);
}

void MainWindow::SetLayerButtonsForMap(int m) {
  if(m == -1) SetLayerButtonsDisabled(true);
  else SetLayerButtonsDisabled(false);
}

void MainWindow::UpdateProjectTitle(QString projtitle) {
  setWindowTitle(projtitle + " - " + appTitle);
}

void MainWindow::ShowEntityDialog(Entity * x) {
  EntityDialog d(x);
  d.exec();
}

void MainWindow::play() {
  bool dirExists = QDir::setCurrent("scripts");
  QFile f("startup.js");
  f.open(QIODevice::ReadOnly);
  QTextStream in(&f);
  QString script = in.readAll();
  f.close();
  if(dirExists) QDir::setCurrent("..");

  //script = "rpgx.messageBox('Hello, world!');";
  scriptEngine->evaluate(script);
}

void MainWindow::AboutQt() {
  QMessageBox::aboutQt(0);
}

void MainWindow::UpdateMousePos(int x, int y, int tx, int ty) {
  QString s = QString::number(x) + ", " + QString::number(y) + " (" +
    QString::number(tx) + ", " + QString::number(ty) + ")";
  emit UpdateMapStatus(s);
}

void MainWindow::setViewTilePos(bool b) {
  viewTilePos = b;
}

void MainWindow::setViewEntityNames(bool b) {
  viewEntityNames = b;
}

void MainWindow::setViewGrid(bool b) {
  viewGrid = b;
}