#ifdef WIN32
#include <windows.h>
#endif

#include <QImage>
#include <QtCore>
#include <qgl.h>
#include <iostream>
#include <GL/glu.h>
#include "globals.h"
#include "bitmap.h"

using std::cout;

Bitmap::Bitmap(QString image, int spr_w, int spr_h, 
	       int origin_x, int origin_y, QString bmpname) {
  this->image = image;
  this->x_origin = origin_x;
  this->y_origin = origin_y;
  this->width = spr_w;
  this->height = spr_h;
  this->isStub = true;

  QFileInfo fileinfo(image);
  this->filePath = fileinfo.absoluteFilePath();
  
  if(!bmpname.isEmpty()) {
    this->name = bmpname;
  } else {
    this->name = image;
  }

  bitmaps.push_back(this);
  bitmapnames[this->name] = bitmaps.size() - 1;
  thisBitmap = new Resource(Resource::Bitmap, bitmaps.size()-1, this->name, bitmapfolder);

  //cout << "Creating " << width << " " << height << "\n";
}

bool Bitmap::setName(QString n)
{
  if(bitmapnames.contains(n)) {
    return false;
  }
  
  bitmapnames[n] = bitmapnames[name];
  bitmapnames.remove(name);
  name = n;
  thisBitmap->setText(0, name);
  return true;
}

void Bitmap::unStub() {
  this->gl_texture = load_texture(this->filePath);

  int x, y;
  Tile * zero = new Tile;
  tiles.push_back(zero);
  for(y = tex_h - tex_h % this->height - this->height; 
      y >= 0; y -= this->height) {
    for(x = 0; x < tex_w - tex_w % this->width; x += this->width) {
      Tile * t = new Tile;
      /*
      t->x1 = (float) x / (float) pow2(tex_w);
      t->x2 = (float) (x + this->width) / (float) pow2(tex_w);
      t->y1 = (float) y / (float) pow2(tex_h);
      t->y2 = (float) (y + this->height) / (float) pow2(tex_h);
      */
      t->x1 = (float) x / (float) tex_w;
      t->x2 = (float) (x + this->width) / (float) tex_w;
      t->y1 = (float) y / (float) tex_h;
      t->y2 = (float) (y + this->height) / (float) tex_h;

      tiles.push_back(t);
    }
  }

  //cout << "Disenstubulating.\n" << width << " " << height << "\n";
  
  isStub = false;
  //cout << "Unstub\n";
}

void Bitmap::stub() {
  int i;
  for(i = 0; i < tiles.size(); i++) {
    delete tiles[i];
  }
  tiles.clear();
  glDeleteTextures(1, &gl_texture);
  isStub = true;
  //cout << "Stub\n";
}

Bitmap::~Bitmap() {
  stub();
}
  
int Bitmap::tileCount() {
  if(isStub) unStub();
  //cout << "Size " << tiles.size() << "\n";
  return tiles.size();
}

void Bitmap::draw(int tile, float x, float y, float opacity, float scale) {
  if(isStub) unStub();
  if(tile == 0) return;

  int w = width * scale;
  int h = height * scale;
  
  // don't bother drawing things that aren't on the screen.
  if(x + w < 0 || y + h < 0 || x > screen_x || y > screen_y) return;

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);   // Turn Blending On
  if(opacity == 1.0)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  else
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0, 1.0, 1.0, opacity);
  glBindTexture(GL_TEXTURE_2D, gl_texture);
      
  glBegin(GL_POLYGON);
  glTexCoord2f(tiles[tile]->x1, tiles[tile]->y1); glVertex3f(x, y + h, 0);
  glTexCoord2f(tiles[tile]->x1, tiles[tile]->y2); glVertex3f(x, y, 0);
  glTexCoord2f(tiles[tile]->x2, tiles[tile]->y2); glVertex3f(x + w, y, 0);
  glTexCoord2f(tiles[tile]->x2, tiles[tile]->y1); glVertex3f(x + w, y + h, 0);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void Bitmap::drawBoundingBox(int tile, float x, float y) {
  // don't bother drawing things that aren't on the screen.
  int w = width;
  int h = height;

  if(x + w < 0 || y + h < 0 || x > screen_x || y > screen_y) return;

  glColor4f(1.0, 1.0, 0.5, 1);
      
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y + h, 0);
  glVertex3f(x, y, 0);
  glVertex3f(x + w, y, 0);
  glVertex3f(x + w, y + h, 0);
  glEnd();
}

int Bitmap::pow2(int x) {
  int a = 1;
  
  while(x > a) {
    a *= 2;
  }
  return a;
}

GLuint Bitmap::load_texture(QString name) {
  QImage temp, texture;
  GLuint gltex;

  if(!temp.load(name)) {
    message("Could not load texture " + name);
  } 

  texture = QGLWidget::convertToGLFormat(temp);


  glGenTextures(1, &gltex);
  glBindTexture(GL_TEXTURE_2D, gltex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
	       texture.width(),
	       texture.height(),
	       0, GL_RGBA, GL_UNSIGNED_BYTE,
	       texture.bits());


  this->tex_w = texture.width();
  this->tex_h = texture.height();
  //width = this->tex_w;
  //height = this->tex_h;

  return gltex;
}

void Bitmap::save(QString filename)
{
  QFile outfile(filename);
  outfile.open(QIODevice::WriteOnly);
  QTextStream f(&outfile);

  f << "<!DOCTYPE xtile>\n";
  f << "<tileset>\n";
  f << "  <name>" << name << "</name>\n";
  f << "  <image>" << image << "</image>\n";
  f << "  <width>" << width << "</width>\n";
  f << "  <height>" << height << "</height>\n";
  f << "  <xorigin>" << x_origin << "</xorigin>\n";
  f << "  <yorigin>" << y_origin << "</yorigin>\n";
  f << "</tileset>\n";

  QFile::copy(filePath, image);
  outfile.close();
}


Bitmap * BitmapReader::read(QIODevice * device)
{
  setDevice(device);
  bitmap = 0;
  
  while (!atEnd()) {
    readNext();
    //message("read: Token (" + tokenString() + "): " + name().toString());
    if (isStartElement()) {
      if (name() == "tileset")
        readBitmap();
      else
        raiseError(QObject::tr("This is not an xtile file."));
    }
  }

  if(!error())
    return bitmap;
  else
    return 0;
}

Bitmap * BitmapReader::read(QString filename)
{
  QFile f(filename);
  f.open(QIODevice::ReadOnly);
  fileinfo = QFileInfo(f);
  return read(&f);
}

void BitmapReader::readBitmap()
{
  Q_ASSERT(isStartElement() && name() == "tileset");
  QString n = "";
  QString image = "";
  int width = 0, height = 0, x_origin = 0, y_origin = 0;

  while (!atEnd()) {
    readNext();
 
    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "name")
      {
        n = readElementText();
      }
      else if (name() == "image")
      {
        image = readElementText();
      }
      else if (name() == "height")
      {
        height = readElementText().toInt();
      }
      else if (name() == "width")
      {
        width = readElementText().toInt();
      }
      else if (name() == "xorigin")
      {
        x_origin = readElementText().toInt();
      }
      else if (name() == "yorigin")
      {
        y_origin = readElementText().toInt();
      }
      else
      {
        readUnknownElement();
      }
    }
  }
  
  bitmap = new Bitmap(image, width, height, x_origin, y_origin, n);
}

void BitmapReader::readUnknownElement()
{
  Q_ASSERT(isStartElement());

  while (!atEnd()) {
    readNext();
    //message("readUnknownElement: Token (" + tokenString() + "): " + name().toString());

    if (isEndElement())
      break;

    if (isStartElement())
      readUnknownElement();
  }
}
