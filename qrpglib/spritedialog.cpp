#include <QtCore>
#include "spritedialog.h"
#include "spritewidget.h"
#include "tileselect.h"
#include "globals.h"
#include "icons.h"
#include "sprite.h"

SpriteDialog::SpriteDialog(QWidget * parent) : QDialog(parent) {
  sprite = 0;
  setModal(false);
 
  QVBoxLayout * layout = new QVBoxLayout(this);

  QToolBar * mainToolbar = new QToolBar();
  layout->addWidget(mainToolbar);

  addspriteAction = mainToolbar->addAction(*addspriteIcon, "New Sprite");
  delspriteAction = mainToolbar->addAction(*delspriteIcon, "Delete Sprite");
  mainToolbar->addSeparator();
  mainToolbar->addWidget(new QLabel("Current Sprite:  "));
  currentSpriteBox = new QComboBox();
  mainToolbar->addWidget(currentSpriteBox);
  currentSpriteBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

  QSplitter * vSplitter = new QSplitter(Qt::Vertical);
  layout->addWidget(vSplitter);
  
  QSplitter * hLayout = new QSplitter(Qt::Horizontal);
  vSplitter->addWidget(hLayout);

  spriteBox = new QGroupBox("Sprite");
  QVBoxLayout * spriteBoxLayout = new QVBoxLayout();
  spriteBox->setLayout(spriteBoxLayout);

  spriteWidget = new SpriteWidget();
  spriteWidget->setMinimumSize(250, 250);
  spriteBoxLayout->addWidget(spriteWidget);

  QToolBar * spriteToolbar = new QToolBar();
  spriteBoxLayout->addWidget(spriteToolbar);
  QWidget * spriteSpacer = new QWidget();
  spriteSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  spriteToolbar->addWidget(spriteSpacer);
  resetButton = spriteToolbar->addAction(*startIcon, "Rewind");
  stopButton = spriteToolbar->addAction(*stopIcon, "Stop");
  pauseButton = spriteToolbar->addAction(*pauseIcon, "Pause");
  playButton = spriteToolbar->addAction(*playIcon, "Play");

  timeSlider = new QSlider(Qt::Horizontal);
  spriteBoxLayout->addWidget(timeSlider);
  hLayout->addWidget(spriteBox);
  
  QFrame * mainFrame = new QFrame();
  mainFrame->setContentsMargins(0, 0, 0, 0);
  hLayout->setContentsMargins(0, 0, 0, 0);
  hLayout->addWidget(mainFrame);
  hLayout->setCollapsible(0, false);
  hLayout->setCollapsible(1, false);
  
  QVBoxLayout * mainLayout = new QVBoxLayout();
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainFrame->setLayout(mainLayout);
  
  spriteInfoBox = new QGroupBox("Sprite Information");
  mainLayout->addWidget(spriteInfoBox);
  
  QFormLayout * mainFormLayout = new QFormLayout();
  spriteInfoBox->setLayout(mainFormLayout);
  
  spriteName = new QLineEdit();
  spriteTileset = new QComboBox();
  
  //spriteName->setValidator(new QRegExpValidator(QRegExp("\\S.*"), 0));
  mainFormLayout->addRow("Name:", spriteName);
  mainFormLayout->addRow("Tileset:", spriteTileset);
  
  QHBoxLayout * tableLayout = new QHBoxLayout();
  mainLayout->addLayout(tableLayout);

  stateListBox = new QGroupBox("States");
  QVBoxLayout * stateListLayout = new QVBoxLayout();
  stateListBox->setLayout(stateListLayout);
  stateList = new QListWidget();
  stateListLayout->addWidget(stateList);
  stateList->setSelectionMode(QAbstractItemView::SingleSelection);
  QToolBar * stateToolbar = new QToolBar();
  stateListLayout->addWidget(stateToolbar);  

  QWidget * stateSpacer = new QWidget();
  stateSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  stateToolbar->addWidget(stateSpacer);
  stateDelAction = new QAction(*delsmallIcon, "Delete Frame", 0);
  stateToolbar->addAction(stateDelAction);
  stateAddAction = new QAction(*addsmallIcon, "Add State", 0);
  stateToolbar->addAction(stateAddAction);

  tableLayout->addWidget(stateListBox);

  frameTableBox = new QGroupBox("Frames");
  QVBoxLayout * frameTableLayout = new QVBoxLayout();  
  frameTableBox->setLayout(frameTableLayout);
  frameTable = new QTableWidget();

  QStringList headings;
  headings.push_back("Duration");
  durationColumn = 0;
  frameTable->setColumnCount(1);
  frameTable->setHorizontalHeaderLabels(headings);
  frameTable->setSelectionMode(QAbstractItemView::SingleSelection);

  frameTableLayout->addWidget(frameTable);
  QToolBar * frameToolbar = new QToolBar();
  frameTableLayout->addWidget(frameToolbar);

  QWidget * frameSpacer = new QWidget();
  frameSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  frameToolbar->addWidget(frameSpacer);
  frameDelAction = new QAction(*delsmallIcon, "Delete Frame", 0);
  frameToolbar->addAction(frameDelAction);
  frameAddAction = new QAction(*addsmallIcon, "Add Frame", 0);
  frameToolbar->addAction(frameAddAction);

  tableLayout->addWidget(frameTableBox);

  tileSelect = new TileSelect();
  vSplitter->addWidget(tileSelect);
  vSplitter->setCollapsible(0, false);
  vSplitter->setCollapsible(1, false);

  connect(addspriteAction, SIGNAL(triggered()), this, SLOT(addSprite()));
  connect(delspriteAction, SIGNAL(triggered()), this, SLOT(delSprite()));

  connect(stateAddAction, SIGNAL(triggered()), this, SLOT(addState()));
  connect(stateDelAction, SIGNAL(triggered()), this, SLOT(delState()));
  connect(frameAddAction, SIGNAL(triggered()), this, SLOT(addFrame()));
  connect(frameDelAction, SIGNAL(triggered()), this, SLOT(delFrame()));

  connect(playButton, SIGNAL(triggered()), spriteWidget, SLOT(Play()));
  connect(pauseButton, SIGNAL(triggered()), spriteWidget, SLOT(Pause()));
  connect(stopButton, SIGNAL(triggered()), spriteWidget, SLOT(Stop()));

  connect(frameTable, SIGNAL(currentCellChanged(int, int, int, int)), 
    this, SLOT(frameChanged(int)));
  connect(frameTable, SIGNAL(itemChanged(QTableWidgetItem *)), 
    this, SLOT(durationChanged(QTableWidgetItem *)));
  connect(stateList, SIGNAL(currentRowChanged(int)), 
    this, SLOT(stateChanged(int)));

  connect(tileSelect->tilebox, SIGNAL(TileChanged(int)), this, SLOT(tileChanged(int)));

  connect(spriteWidget, SIGNAL(updateTime(int)), this, SLOT(updateSpriteSliderCurrent(int)));

  connect(currentSpriteBox, SIGNAL(currentIndexChanged(QString)), 
    this, SLOT(spriteChanged(QString)));
  connect(spriteName, SIGNAL(editingFinished()), this, SLOT(spriteNameChanged()));
  connect(spriteTileset, SIGNAL(currentIndexChanged(QString)), 
    this, SLOT(tilesetChanged(QString)));
}

void SpriteDialog::show() {
  updateTilesets();
  updateSpritePulldown();
  QDialog::show();
}

void SpriteDialog::durationChanged(QTableWidgetItem * item) {
  disconnect(frameTable, SIGNAL(itemChanged(QTableWidgetItem *)), 
    this, SLOT(durationChanged(QTableWidgetItem *)));
  QString duration = item->text();
  int state = stateList->currentRow();
  int frame = frameTable->currentRow();
  if(state >= 0 && frame >= 0) {
    int old_duration = sprite->GetDuration(state, frame);
    int d = duration.toInt();
    if(d) {
      sprite->SetDuration(state, frame, d);
      updateFrames();
    } else {
      item->setText(QString::number(old_duration));
    }
  }
  connect(frameTable, SIGNAL(itemChanged(QTableWidgetItem *)), 
    this, SLOT(durationChanged(QTableWidgetItem *)));
}

void SpriteDialog::updateTilesets() {
  QStringList tilesetNames;
  int i = 0;

  for(i = 0; i < bitmaps.size(); i++) {
    if(bitmaps[i]) {
      tilesetNames.push_back(bitmaps[i]->GetName());
    }
  }
  tilesetNames.sort();

  spriteTileset->clear();
  spriteTileset->addItem("");
  for(i = 0; i < tilesetNames.size(); i++)
    spriteTileset->addItem(tilesetNames[i], QVariant(bitmapnames[tilesetNames[i]]));
}

void SpriteDialog::updateWidgets() {
  if(sprite == 0) {
    //clear all widgets
    spriteName->clear();
    spriteTileset->setCurrentIndex(0);
    frameTable->clearContents();
    stateList->clear();
    spriteWidget->SetSprite(0);
    tileSelect->SetTileset(0);
  } else {
    spriteName->setText(sprite->GetName());
    if(sprite->GetTileset()) { 
      setTileset(sprite->GetTileset()->GetName());
      tileSelect->SetTileset(sprite->GetTileset());
    }
    updateStates();
    updateFrames();
    spriteWidget->SetSprite(sprite);
    spriteWidget->SetState(0);
    spriteWidget->SetFrame(0);
  }
}

void SpriteDialog::updateStates() {
  stateList->clear();
  if(sprite) {
    int states = sprite->GetStates();
    for(int i = 0; i < states; i++)
      stateList->addItem(sprite->GetStateName(i));
  }
}

void SpriteDialog::updateFrames() {
  int totalDuration = 0;
  frameTable->clearContents();
  frameTable->setRowCount(0);
  if(sprite) {
    if(stateList->currentRow() > -1) {
      int frames = sprite->GetFrames(stateList->currentRow());
      for(int i = 0; i < frames; i++) {
        frameTable->insertRow(i);
        totalDuration += sprite->GetDuration(stateList->currentRow(), i);
        QString duration = QString::number(sprite->GetDuration(stateList->currentRow(), i));
        QTableWidgetItem * frame = 
          new QTableWidgetItem(duration);
        frameTable->setItem(i, 0, frame);
      }
    }
  }
  updateSpriteSliderCurrent(0);
  updateSpriteSliderDuration(totalDuration);
}

void SpriteDialog::spriteChanged(QString name) {
  if((!name.isEmpty() && !name.isNull()) && spritenames.contains(name)) {
    sprite = sprites[spritenames[name]];
  } else {
    sprite = 0;
  }

  updateWidgets();
}

void SpriteDialog::tilesetChanged(QString name) {
  if(sprite == 0) return;
  if((!name.isEmpty() && !name.isNull()) && bitmapnames.contains(name)) {
    sprite->SetTileset(bitmaps[bitmapnames[name]]);
    tileSelect->SetTileset(bitmaps[bitmapnames[name]]);
  }

  updateWidgets();
}

void SpriteDialog::stateChanged(int state) {
  updateFrames();
  spriteWidget->SetState(state);
  spriteWidget->SetFrame(0);
  tileSelect->tilebox->SetSelected(
    sprite->GetBitmap(stateList->currentRow(), frameTable->currentRow()));
}

void SpriteDialog::frameChanged(int frame) {
  spriteWidget->SetFrame(frame);
  tileSelect->tilebox->SetSelected(
    sprite->GetBitmap(stateList->currentRow(), frameTable->currentRow()));
}

void SpriteDialog::tileChanged(int tile) {
  sprite->SetBitmap(stateList->currentRow(), frameTable->currentRow(), tile);
  spriteWidget->updateGL();
}

void SpriteDialog::updateSpritePulldown() {
  QStringList spriteNames;
  int i = 0;

  for(i = 0; i < sprites.size(); i++) {
    if(sprites[i]) {
      spriteNames.push_back(sprites[i]->GetName());
    }
  }
  spriteNames.sort();

  currentSpriteBox->clear();
  for(i = 0; i < spriteNames.size(); i++)
    currentSpriteBox->addItem(spriteNames[i], QVariant(spritenames[spriteNames[i]]));

  disable(spritenames.size() == 0);
}

void SpriteDialog::addSprite() {
  QString name = AddSpriteDialog::name();

  if(!name.isEmpty() && !name.isNull()) {
    new Sprite(name);
  }
  updateSpritePulldown();
  setCurrentSprite(name);
}

void SpriteDialog::delSprite() {
  QString n = currentSpriteBox->currentText();
  //message(n);
  if(!n.isEmpty() && !n.isNull()) {
    if(QMessageBox::warning(0, "Warning", "Really delete this sprite?", 
      QMessageBox::Ok|QMessageBox::Cancel) != QMessageBox::Cancel) {
      delete sprites[spritenames[n]];
      updateSpritePulldown();
      spriteChanged("");
    }
  }
}

void SpriteDialog::setCurrentSprite(QString name) {
  int index = currentSpriteBox->findText(name);
  if(index >= 0) 
    currentSpriteBox->setCurrentIndex(index);
}

void SpriteDialog::setTileset(QString name) {
  int index = spriteTileset->findText(name);
  if(index >= 0)
    spriteTileset->setCurrentIndex(index);
}

void SpriteDialog::spriteNameChanged() {
  renameSprite(spriteName->text());
}

void SpriteDialog::renameSprite(QString name) {
  if(sprite == 0) return;
  if(!name.isEmpty() && !name.isNull()) {
    disconnect(currentSpriteBox, SIGNAL(currentIndexChanged(QString)), 
      this, SLOT(spriteChanged(QString)));
    sprite->SetName(name);
    updateSpritePulldown();
    setCurrentSprite(name);
    connect(currentSpriteBox, SIGNAL(currentIndexChanged(QString)), 
      this, SLOT(spriteChanged(QString)));
  } else {
    QMessageBox::critical(0, "Error", "Sprite name must not be blank.");
  }
}

void SpriteDialog::addState() {
  if(sprite) {
    QString name = AddStateDialog::name();
    sprite->AddState(name);
    updateStates();
    stateList->setCurrentRow(stateList->count()-1);
    updateFrames();
  }
}

void SpriteDialog::addFrame() {
  int state = stateList->currentRow();
  if(sprite && state > -1) {
    int duration = 250;
    sprite->AddFrame(state, duration, 0);
    updateFrames();
  }
}

void SpriteDialog::delState() {
  int state = stateList->currentRow();
  if(sprite && state > -1) {
    sprite->DelState(state);
    updateStates();
    updateFrames();
  }
}

void SpriteDialog::delFrame() {
  int state = stateList->currentRow();
  int frame = frameTable->currentRow();
  if(sprite && state >= 0 && frame >= 0) {
    sprite->DelFrame(state, frame);
    updateFrames();
  }
}

void SpriteDialog::updateSpriteSliderCurrent(int time) {
  timeSlider->setValue(time);
}

void SpriteDialog::updateSpriteSliderDuration(int time) {
  timeSlider->setRange(0, time);
  spriteWidget->updateDuration(time);
}

void SpriteDialog::disable(bool disabled) {
  spriteBox->setDisabled(disabled);
  spriteInfoBox->setDisabled(disabled);
  stateListBox->setDisabled(disabled);
  frameTableBox->setDisabled(disabled);
  delspriteAction->setDisabled(disabled);
  currentSpriteBox->setDisabled(disabled);
  addspriteAction->setDisabled(false);
}

QString AddSpriteDialog::name() {
  QString * name = new QString();
  QDialog * addSpriteDialog = new QDialog;
  QFormLayout * layout = new QFormLayout;
  addSpriteDialog->setLayout(layout);
  QLineEdit * spriteName = new QLineEdit;
  layout->addRow("Name:", spriteName);
  QDialogButtonBox * buttons = 
    new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  layout->addRow(buttons);
  connect(buttons, SIGNAL(accepted()), addSpriteDialog, SLOT(accept()));
  connect(buttons, SIGNAL(rejected()), addSpriteDialog, SLOT(reject()));
  int result = QDialog::Accepted;
  while(result == QDialog::Accepted && (name->isEmpty() || name->isNull())) {
    result = addSpriteDialog->exec();
    if(result == QDialog::Accepted) {
      if(!spritenames.contains(spriteName->text()))
        *name = spriteName->text();  
      else
        QMessageBox::critical(0, "Error", "There is already a sprite by this name.  Please choose another name.");
    }
  } 

  delete addSpriteDialog;
  return *name;
}

QString AddStateDialog::name() {
  QString * name = new QString();
  QDialog * addStateDialog = new QDialog;
  QFormLayout * layout = new QFormLayout;
  addStateDialog->setLayout(layout);
  QLineEdit * stateName = new QLineEdit;
  layout->addRow("Name:", stateName);
  QDialogButtonBox * buttons = 
    new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
  layout->addRow(buttons);
  connect(buttons, SIGNAL(accepted()), addStateDialog, SLOT(accept()));
  connect(buttons, SIGNAL(rejected()), addStateDialog, SLOT(reject()));
  int result = QDialog::Accepted;
  while(result == QDialog::Accepted && (name->isEmpty() || name->isNull())) {
    result = addStateDialog->exec();
    *name = stateName->text();  
  } 

  delete addStateDialog;
  return *name;
}