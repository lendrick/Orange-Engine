#include <QtGui>
#include <QIcon>
#include "icons.h"

QIcon * newprojectIcon;
QIcon * openprojectIcon;
QIcon * saveprojectIcon;

QIcon * newmapIcon;
QIcon * openmapIcon;
QIcon * savemapIcon;
QIcon * savemapasIcon;

QIcon * addlayerIcon;
QIcon * insertlayerIcon;
QIcon * deletelayerIcon;

QIcon * playbuttonIcon;
QIcon * pausebuttonIcon;
QIcon * stopbuttonIcon;

QIcon * bitmapbuttonIcon;

QIcon * delsmallIcon;
QIcon * addsmallIcon;

QIcon * spriteIcon;
QIcon * addspriteIcon;
QIcon * delspriteIcon;

QIcon * pauseIcon;
QIcon * playIcon;
QIcon * startIcon;
QIcon * stopIcon;

QIcon * appPlayIcon;

QIcon * mapEditIcon;
QIcon * mapEntityIcon;

QIcon * paintPencilIcon;
QIcon * paintBrushIcon;
QIcon * paintCanIcon;
QIcon * paintBoxIcon;

void initIcons() {
  newprojectIcon = new QIcon("pixmaps/project_new.png");
  openprojectIcon = new QIcon("pixmaps/project_open.png");
  saveprojectIcon = new QIcon("pixmaps/project_save.png");

  newmapIcon = new QIcon("pixmaps/map_new.png");
  openmapIcon = new QIcon("pixmaps/map_open.png");
  savemapIcon = new QIcon("pixmaps/map_save.png");
  savemapasIcon = new QIcon("pixmaps/filesaveas.png");
  
  addlayerIcon = new QIcon("pixmaps/layer_add.png");
  insertlayerIcon = new QIcon("pixmaps/edit_add.png");
  deletelayerIcon = new QIcon("pixmaps/layer_delete.png");

  playbuttonIcon = new QIcon("pixmaps/player_play.png");
  pausebuttonIcon = new QIcon("pixmaps/player_stop.png");
  stopbuttonIcon = new QIcon("pixmaps/player_pause.png");

  bitmapbuttonIcon = new QIcon("pixmaps/tiles.png");

  delsmallIcon = new QIcon("pixmaps/del_small.png");
  addsmallIcon = new QIcon("pixmaps/add_small.png");
  
  spriteIcon = new QIcon("pixmaps/sprite.png");
  addspriteIcon = new QIcon("pixmaps/sprite_add.png");
  delspriteIcon = new QIcon("pixmaps/sprite_delete.png");

  playIcon = new QIcon("pixmaps/control_play.png");
  pauseIcon = new QIcon("pixmaps/control_pause.png");
  startIcon = new QIcon("pixmaps/control_start.png");
  stopIcon = new QIcon("pixmaps/control_stop.png");

  appPlayIcon = new QIcon("pixmaps/app_play.png");
  
  mapEditIcon = new QIcon("pixmaps/map_edit.png");
  mapEntityIcon = new QIcon("pixmaps/flag_red.png");

  paintPencilIcon = new QIcon("pixmaps/pencil.png");
  paintBrushIcon = new QIcon("pixmaps/paintbrush.png");
  paintCanIcon = new QIcon("pixmaps/paintcan.png");
  paintBoxIcon = new QIcon("pixmaps/selectbox.png");
}
