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
#include "mapscriptdialog.h"
#include "globalscriptdialog.h"
#include "mapreader.h"
#include "projectreader.h"
#include "mapscene.h"
#include "rpgengine.h"
#include "propertyeditor.h"

MainWindow::MainWindow() :
  QMainWindow() {
  initIcons();
  appTitle = "QRPG Editor";

  setWindowTitle(appTitle);

  mapwin = new MapWindow(0);
  mapBox = mapwin->mapbox;
  mapwin->resize(400, 400);

  // Create the main menu
  fileMenu = menuBar()->addMenu("&File");
  editMenu = menuBar()->addMenu("&Edit");
  resourceMenu = menuBar()->addMenu("&Resources");
  mapMenu = resourceMenu->addMenu("&Maps");
  mapMenu->setDisabled(true);
  tilesetMenu = resourceMenu->addMenu("&Tilesets");
  tilesetMenu->setDisabled(true);
  spriteMenu = resourceMenu->addMenu("&Sprites");
  spriteMenu->setDisabled(true);
  viewMenu = menuBar()->addMenu("&View");
  helpMenu = menuBar()->addMenu("&Help");

  //////////////////////////////////////////////////////////////
  // Create the toolbar
  mapToolBar = addToolBar("MapToolBar");
  mapToolBar->setIconSize(QSize(32, 32));

  paintToolBar = new QToolBar("PaintToolBar");
  addToolBar(Qt::LeftToolBarArea, paintToolBar);
  paintToolBar->setIconSize(QSize(32, 32));

  // iconsets

  aboutQtAction = new QAction("About &Qt", 0);
  helpMenu->addAction(aboutQtAction);
  connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQt()));

  //setUsesBigPixmaps(true);
  
  newprojectAction = new QAction(*newprojectIcon, "&New Project...", 0);
  connect(newprojectAction, SIGNAL(triggered()), this, SLOT(newProject()));
  mapToolBar->addAction(newprojectAction);
  fileMenu->addAction(newprojectAction);

  openprojectAction = new QAction(*openprojectIcon, "&Open Project...", 0);
  connect(openprojectAction, SIGNAL(triggered()), this, SLOT(loadProject()));
  mapToolBar->addAction(openprojectAction);
  fileMenu->addAction(openprojectAction);

  saveprojectAction = new QAction(*saveprojectIcon, "&Save Project...", 0);
  connect(saveprojectAction, SIGNAL(triggered()), this, SLOT(saveProject()));
  mapToolBar->addAction(saveprojectAction);
  fileMenu->addAction(saveprojectAction);

  fileMenu->addSeparator();
  quitAction = new QAction("Exit", 0);
  connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));
  fileMenu->addAction(quitAction);

  mapToolBar->addSeparator();

  // Edit menu

  cutAction = editMenu->addAction("Cu&t");
  cutAction->setShortcut(QKeySequence("Ctrl+X"));
  connect(cutAction, SIGNAL(triggered()), mapBox->mapScene, SLOT(cutSelection()));

  copyAction = editMenu->addAction("&Copy");
  copyAction->setShortcut(QKeySequence("Ctrl+C"));
  connect(copyAction, SIGNAL(triggered()), mapBox->mapScene, SLOT(copySelection()));

  pasteAction = editMenu->addAction("&Paste");
  pasteAction->setShortcut(QKeySequence("Ctrl+V"));
  connect(pasteAction, SIGNAL(triggered()), mapBox->mapScene, SLOT(pasteSelection()));

  deleteAction = editMenu->addAction("&Delete");
  deleteAction->setShortcut(QKeySequence("Del"));
  connect(deleteAction, SIGNAL(triggered()), mapBox->mapScene, SLOT(deleteSelection()));

  editMenu->addSeparator();

  selectAllAction = editMenu->addAction("Select &All");
  selectAllAction->setShortcut(QKeySequence("Ctrl+A"));
  connect(selectAllAction, SIGNAL(triggered()), mapBox->mapScene, SLOT(selectAll()));

  selectNoneAction = editMenu->addAction("Select &None");
  selectNoneAction->setShortcut(QKeySequence("Ctrl+N"));
  connect(selectNoneAction, SIGNAL(triggered()), mapBox->mapScene, SLOT(selectNone()));

  // Map operation buttons

  /*
  Action = new QAction(*Icon, "", 0);
  connect(Action, SIGNAL(triggered()), this, SLOT());
  MapToolBar->addAction(Action);
  Menu->addAction(Action);
  */

  newmapAction = new QAction(*newmapIcon, "New &Map", 0);
  connect(newmapAction, SIGNAL(triggered()), this, SLOT(newMap()));
  mapToolBar->addAction(newmapAction);
  mapMenu->addAction(newmapAction);
  newmapAction->setDisabled(true);

  openmapAction = new QAction(*openmapIcon, "Import Map", 0);
  connect(openmapAction, SIGNAL(triggered()), this, SLOT(loadMap()));
  mapToolBar->addAction(openmapAction);
  mapMenu->addAction(openmapAction);
  openmapAction->setDisabled(true);

  savemapAction = new QAction(*savemapIcon, "Export Map", 0);
  connect(savemapAction, SIGNAL(triggered()), this, SLOT(saveMap()));
  mapToolBar->addAction(savemapAction);
  mapMenu->addAction(savemapAction);
  savemapAction->setDisabled(true);

  /*
  QAction * savemapasAction = new QAction(*savemapasIcon, "Export Map", 0);
  connect(savemapasAction, SIGNAL(triggered()), this, SLOT(SaveMap()));
  MapToolBar->addAction(savemapasAction);
  MapMenu->addAction(savemapasAction);
  */

  mapMenu->addSeparator();

  // Bitmap buttons
  mapToolBar->addSeparator();
  //MapToolBar->addWidget(new QLabel("Bitmaps "));
 
  newbitmapAction = new QAction(*bitmapbuttonIcon, "New &Tileset", 0);
  connect(newbitmapAction, SIGNAL(triggered()), this, SLOT(newBitmap()));
  mapToolBar->addAction(newbitmapAction);
  tilesetMenu->addAction(newbitmapAction);
  newbitmapAction->setDisabled(true);

  mapToolBar->addSeparator();
  
  newspriteAction = new QAction(*spriteIcon, "New &Sprite", 0);
  connect(newspriteAction, SIGNAL(triggered()), this, SLOT(newSprite()));
  mapToolBar->addAction(newspriteAction);
  spriteMenu->addAction(newspriteAction);
  newspriteAction->setDisabled(true);

  mapToolBar->addSeparator();
  
  appPlayAction = new QAction(*appPlayIcon, "Start Game", 0);
  connect(appPlayAction, SIGNAL(triggered()), this, SLOT(play()));
  mapToolBar->addAction(appPlayAction);
  fileMenu->addAction(appPlayAction);
  appPlayAction->setDisabled(true);
    
  mapToolBar->addSeparator();

  QActionGroup * mapActionGroup = new QActionGroup(0);
  mapEditAction = mapActionGroup->addAction(*mapEditIcon, "Edit Map");
  mapEditAction->setCheckable(true);
  mapToolBar->addAction(mapEditAction);

  mapEntityAction = mapActionGroup->addAction(*mapEntityIcon, "Edit Entities");
  mapEntityAction->setCheckable(true);
  mapToolBar->addAction(mapEntityAction);
  
  // View menu
  viewGridAction = new QAction("&Grid", 0);
  viewGridAction->setCheckable(true);
  viewGridAction->setShortcut(QKeySequence("Ctrl+'"));
  viewMenu->addAction(viewGridAction);
  connect(viewGridAction, SIGNAL(toggled(bool)), this, SLOT(setViewGrid(bool)));

  viewTilePosAction = new QAction("Tile &Coordinates", 0);
  viewTilePosAction->setCheckable(true);
  viewTilePosAction->setShortcut(QKeySequence("Ctrl+Shift+'"));
  viewMenu->addAction(viewTilePosAction);
  connect(viewTilePosAction, SIGNAL(toggled(bool)), this, SLOT(setViewTilePos(bool)));

  viewEntityNamesAction = new QAction("Entity &Names", 0);
  viewEntityNamesAction->setCheckable(true);
  viewEntityNamesAction->setShortcut(QKeySequence("Ctrl+;"));
  viewMenu->addAction(viewEntityNamesAction);
  connect(viewEntityNamesAction, SIGNAL(toggled(bool)), this, SLOT(setViewEntityNames(bool)));
  
  viewBoundingBoxesAction = new QAction("&Bounding Boxes", 0);
  viewBoundingBoxesAction->setCheckable(true);
  viewBoundingBoxesAction->setShortcut(QKeySequence("Ctrl+Shift+;"));
  viewMenu->addAction(viewBoundingBoxesAction);
  connect(viewBoundingBoxesAction, SIGNAL(toggled(bool)), this, SLOT(setViewBoundingBoxes(bool)));

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
  // The paint toolbar

  QActionGroup * paintActionGroup = new QActionGroup(0);

  paintDrawAction = paintActionGroup->addAction(*paintPencilIcon, "Draw");
  paintDrawAction->setCheckable(true);
  paintToolBar->addAction(paintDrawAction);

  paintBrushAction = paintActionGroup->addAction(*paintBrushIcon, "Brushes");
  paintBrushAction->setCheckable(true);
  paintToolBar->addAction(paintBrushAction);

  paintFillAction = paintActionGroup->addAction(*paintCanIcon, "Fill");
  paintFillAction->setCheckable(true);
  paintToolBar->addAction(paintFillAction);

  paintSelectBoxAction = paintActionGroup->addAction(*paintBoxIcon, "Select Box");
  paintSelectBoxAction->setCheckable(true);
  paintToolBar->addAction(paintSelectBoxAction);

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
	  this, SLOT(resourceSelected()));

  layerPanel = new LayerPanel(this);
  this->addDockWidget(Qt::LeftDockWidgetArea, layerPanel, Qt::Vertical);
  layerPanel->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

  connect(layerPanel, SIGNAL(addLayer(int)), this, SLOT(showNewLayerDialog(int)));
  connect(layerPanel, SIGNAL(delLayer(int)), this, SLOT(deleteLayer(int)));
  setLayerButtonsDisabled(true);
  
  ////////////////////////////////////////////////////////////
  // The map window

  setCentralWidget(mapwin);

  connect(this, SIGNAL(setMap(int)), mapwin->mapbox, SLOT(setMap(int)));
  connect(this, SIGNAL(setMap(int)), this, SLOT(setLayerButtonsForMap(int)));
  connect(this, SIGNAL(setMap(int)), layerPanel, SLOT(updateData()));
  connect(this, SIGNAL(updateLayers()), layerPanel, SLOT(updateData()));
  connect(this, SIGNAL(setTiles(int)), tiles, SLOT(setTiles(int)));
  connect(layerPanel, SIGNAL(setDrawMode(LayerView::LayerViewMode)),
          mapwin, SIGNAL(setDrawMode(LayerView::LayerViewMode)));
  connect(tiles->tilebox, SIGNAL(tileChanged(int)), mapwin->mapbox, SLOT(setCurrentTile(int)));
  
  connect(layerPanel, SIGNAL(selectLayer(int)), mapwin->mapbox, SLOT(setLayer(int)));
  connect(mapEditAction, SIGNAL(triggered()), mapBox, SLOT(setEditMode()));
  connect(mapEntityAction, SIGNAL(triggered()), mapBox, SLOT(setEntityMode()));

  connect(paintDrawAction, SIGNAL(triggered()), this, SLOT(setPaintModeDraw()));
  connect(paintFillAction, SIGNAL(triggered()), this, SLOT(setPaintModeFill()));
  connect(paintSelectBoxAction, SIGNAL(triggered()), this, SLOT(setPaintModeSelectBox()));
  connect(paintBrushAction, SIGNAL(triggered()), this, SLOT(setPaintModeBrush()));


  connect(mapBox, SIGNAL(mousePos(int, int, int, int)), 
    this, SLOT(updateMousePos(int, int, int, int)));
  connect(this, SIGNAL(updateMapStatus(QString)), mapwin, SLOT(updateStatus(QString)));
  connect(mapBox->mapScene, SIGNAL(showEntityDialog(EntityPointer)), this, SLOT(showEntityDialog(EntityPointer)));
  connect(mapBox->mapScene, SIGNAL(showPropertyEditor(ObjectPointer)), this, SLOT(showPropertyEditor(ObjectPointer)));

  connect(mapBox->mapScene, SIGNAL(showMapScriptDialog(Map *)), this, SLOT(showMapScriptDialog(Map *)));
  connect(mapBox->mapScene, SIGNAL(showGlobalScriptDialog()), this, SLOT(showGlobalScriptDialog()));
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

void MainWindow::resourceSelected() {
  Resource * item = static_cast<Resource *> (maplist->currentItem());
  currentresource = static_cast<Resource *> (maplist->currentItem());
  if(item->type() == Resource::Map) {
    emit setMap(item->getID());
    tiles->setTileset(maps[item->getID()]->getTileset());
  } else if(item->type() == Resource::Bitmap) {
    emit setMap(-1);
    emit setTiles(item->getID());
  } else if(item->type() == Resource::Sprite) {
    emit setMap(-1);
    //emit SetTiles(item->GetID());
  } else if(item->type() == Resource::Folder) {
    emit setMap(-1);
    emit setTiles(-1);
  }
}

void MainWindow::showNewLayerDialog(int before) {
  if(newlayerdialog->exec() == QDialog::Accepted ) {
    mapwin->mapbox->getMap()->insertLayerBefore(before, newlayerdialog->xspin->value(),
			newlayerdialog->yspin->value(),
			newlayerdialog->wrapcheck->isChecked(),
      tiles->getTile(),
      newlayerdialog->layername->text()
    );
    emit updateLayers();
  }
}

void MainWindow::deleteLayer(int layer) {
  if(QMessageBox::warning(this, "Delete Layer?", 
    "Deleting a layer cannot be undone.  Proceed?",
    QMessageBox::Ok|QMessageBox::Cancel, QMessageBox::Cancel) == QMessageBox::Ok)
    mapwin->mapbox->deleteLayer(layer);
  emit updateLayers();
}

void MainWindow::loadProject() {
  QString currentProjectFilename(QFileDialog::getOpenFileName(
    this,
    "Choose a file",
    ".",
    "Projects (*.xproj)"
  ));
  loadProject(currentProjectFilename);
}

void MainWindow::loadProject(QString currentProjectFilename) {
  ProjectReader projectReader;
  Project * loadedProject;

  if(!currentProjectFilename.isEmpty() && !currentProjectFilename.isNull()) {
    if(currentProject) delete currentProject;
    emit setMap(-1);
    emit setTiles(-1);
    if((loadedProject = projectReader.read(currentProjectFilename))) {
      currentProject = loadedProject;
      setMapButtonsDisabled(false);
      setTilesetButtonsDisabled(false);
    } else {
      QMessageBox::critical(0, "Error", "Project '" + currentProjectFilename + "' could not be loaded.");
    }
  }
}

void MainWindow::newProject() {
  if(newprojectdialog->exec() == QDialog::Accepted) {
    emit setMap(-1);
    emit setTiles(-1);
    if(currentProject) delete currentProject;
    currentProject = new Project(newprojectdialog->projectname->text());
    setMapButtonsDisabled(false);
    setTilesetButtonsDisabled(false);
  }
}

void MainWindow::saveProject() {
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

void MainWindow::newSprite() {
  spritedialog->show();
}

void MainWindow::newMap() {
  if(newmapdialog->exec() == QDialog::Accepted ) {
    tiles->tilebox->makeCurrent();
    Map * m = new Map(bitmaps[newmapdialog->tileset->currentIndex()], 0, 0, 1, 1, newmapdialog->mapname->text());
    maplist->setCurrentItem(m->getThisMap());
    showNewLayerDialog(0);
  }
}

void MainWindow::loadMap() {
  MapReader mapReader;
  Map * m = mapReader.read(QFileDialog::getOpenFileName(
    this, 
    "Choose a file",
    ".",
    "Maps (*.xmap)"
  ));
  maplist->setCurrentItem(m->getThisMap());
}

void MainWindow::saveMap() {
  Resource * item = static_cast<Resource *> (maplist->currentItem());

  if(item && item->type() == Resource::Map)
    maps[item->getID()]->save(
			       QFileDialog::getSaveFileName(
               this,
               "Choose a file",
		            ".",
                "Maps (*.xmap)"
             ));
}

void MainWindow::newBitmap() {
  if(newbitmapdialog->exec() == QDialog::Accepted ) {
    tiles->tilebox->makeCurrent();
    new Bitmap(
			    newbitmapdialog->image->text(),
			    newbitmapdialog->xspin->value(),
			    newbitmapdialog->yspin->value(), 
			    0, 0, newbitmapdialog->bitmapname->text());
  }
}

void MainWindow::setMapButtonsDisabled(bool disabled) {
  newmapAction->setDisabled(disabled);
  openmapAction->setDisabled(disabled);
  savemapAction->setDisabled(disabled);
  appPlayAction->setDisabled(disabled);
}

void MainWindow::setTilesetButtonsDisabled(bool disabled) {
  newbitmapAction->setDisabled(disabled);
  newspriteAction->setDisabled(disabled);
}

void MainWindow::setLayerButtonsDisabled(bool disabled) {
  layerPanel->setDisabled(disabled);
  //addlayerAction->setDisabled(disabled);
  //deletelayerAction->setDisabled(disabled);
}

void MainWindow::setLayerButtonsForMap(int m) {
  if(m == -1) setLayerButtonsDisabled(true);
  else setLayerButtonsDisabled(false);
}

void MainWindow::updateProjectTitle(QString projtitle) {
  setWindowTitle(projtitle + " - " + appTitle);
}

void MainWindow::showEntityDialog(EntityPointer x) {
  EntityDialog d(x);
  d.exec();
}

void MainWindow::showMapScriptDialog(Map * x) {
  MapScriptDialog d(x);
  d.exec();
}

void MainWindow::showPropertyEditor(ObjectPointer x) {
  PropertyEditor d(x);
  d.exec();
}

void MainWindow::showGlobalScriptDialog() {
  GlobalScriptDialog d;
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

void MainWindow::aboutQt() {
  QMessageBox::aboutQt(0);
}

void MainWindow::updateMousePos(int x, int y, int tx, int ty) {
  QString s = QString::number(x) + ", " + QString::number(y) + " (" +
    QString::number(tx) + ", " + QString::number(ty) + ")";
  emit updateMapStatus(s);
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

void MainWindow::setViewBoundingBoxes(bool b) {
  viewBoundingBoxes = b;
}

void MainWindow::setPaintModeBrush() {
  paintMode = PaintMode::Brush;
}

void MainWindow::setPaintModeDraw() {
  paintMode = PaintMode::Draw;
}

void MainWindow::setPaintModeSelectBox() {
  paintMode = PaintMode::SelectBox;
}

void MainWindow::setPaintModeFill() {
  paintMode = PaintMode::Fill;
}

/*
bool MainWindow::event(QEvent *event) {
  //qDebug() << "MainWindow: " << RPGEngine::eventName(event);
  return QMainWindow::event(event);
}
*/

