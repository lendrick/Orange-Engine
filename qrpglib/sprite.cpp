#ifdef WIN32
#include <windows.h>
#endif

#include "sprite.h"
#include <iostream>
#include <fstream>
#include <string.h>

using std::cout;
using std::ifstream;
using std::ofstream;

Sprite::Sprite(Bitmap * b, QString spritename) {
  bitmap = b;
  //AddState();
  //AddFrame(0, 100, 0);
  name = spritename;
  if(name.isEmpty()) name = b->GetName();
  sprites.push_back(this);
  spritenames[name] = sprites.size() - 1;
  thisSprite = new Resource(Resource::Sprite, sprites.size()-1, this->name, spritefolder);
  id = thisSprite->GetID();
  x1 = y1 = x2 = y2 = x_origin = y_origin = 0;
}

Sprite::Sprite(QString spritename) {
  bitmap = 0;
  name = spritename;
  sprites.push_back(this);
  spritenames[name] = sprites.size() - 1;
  thisSprite = new Resource(Resource::Sprite, sprites.size()-1, this->name, spritefolder);
  id = thisSprite->GetID();
  x1 = y1 = x2 = y2 = x_origin = y_origin = 0;
}

Sprite::Sprite(char * filename, Bitmap * b, QString spritename) {
  bitmap = b;
  if(!Load(filename)) cprint("Invalid file: " + QString(filename) + "\n");
  name = spritename;
  if(name.isEmpty()) name = b->GetName();
  sprites.push_back(this);
  spritenames[name] = sprites.size() - 1;
  thisSprite = new Resource(Resource::Sprite, sprites.size()-1, this->name, spritefolder);
  id = thisSprite->GetID();
  x1 = y1 = x2 = y2 = x_origin = y_origin = 0;
}

Sprite::~Sprite() {
  int id = thisSprite->GetID();
  delete thisSprite;
  while(!states.isEmpty())
    delete states.takeFirst();
  sprites[id] = 0;
  spritenames.take(name);
}

bool Sprite::SetName(QString spritename) {
  if(spritenames.contains(spritename)) {
    return false;
  }
  
  spritenames[spritename] = spritenames[name];
  spritenames.remove(name);
  name = spritename;
  thisSprite->setText(0, name);
  return true;
}
  
bool Sprite::Load(char * filename) {
  ifstream file(filename);
  char xspr[5];
  int i, j, state_count, frame_count;

  file.read(xspr, 4);
  xspr[4] = 0;
  if(strcmp("XSPR", xspr)) return false;

  file.read((char *) &state_count, sizeof(int));
  
  cout << "states: " << state_count << "\n";

  for(i = 0; i < state_count; i++) {
    State * s = new State;
    file.read((char *) &(s->loop), sizeof(int));
    file.read((char *) &frame_count, sizeof(int));
    s->max_time = 0;

    states.push_back(s);

    cout << "frames: " << frame_count << "\n";
    for(j = 0; j < frame_count; j++) {
      int bitmap, duration;
      file.read((char *) &bitmap, sizeof(int));
      file.read((char *) &duration, sizeof(int));
      
      cout << " " << bitmap << " " << duration << "\n";

      AddFrame(i, duration, bitmap);
    }
  }

  file.close();
  return true;
}

void Sprite::Save(QString filename) {
  QFile outfile(filename);
  outfile.open(QIODevice::WriteOnly);
  QTextStream file(&outfile);

  file << "<!DOCTYPE XSPR>\n";
  file << "<sprite>\n";
  int s, f, i, j, max, loop;

  file << "  <name>" << name << "</name>\n";

  file << "  <origin x='" << x_origin << "' y='" << y_origin << "' />";
  file << "  <boundingbox x1='" << x1 << "' y1='" << y1 
    << "' x2='" << x2 << "' y2='" << y2 << "' />";

  s = states.size();
  file << "  <tileset>";
  file << bitmap->GetName();
  file << "</tileset>\n";
  file << "  <states>" << s << "</states>\n";
  
  for(i = 0; i < s; i++) {
    file << "  <state>\n";
    f = states[i]->frames.size();
    max = states[i]->max_time;
    loop = states[i]->loop;
    file << "    <loop>" << loop << "</loop>\n";
    file << "    <frames>" << f << "</frames>\n";
    file << "    <name>" << states[i]->name << "</name>\n";

    for(j = 0; j < f; j++) {
      file << "    <frame>\n";
      int b, d;
      b = states[i]->frames[j]->bitmap;
      d = states[i]->frames[j]->duration;
      file << "      <bitmap>" << b << "</bitmap>\n";
      file << "      <duration>" << d << "</duration>\n";
      file << "    </frame>\n";
    }
    file << "  </state>\n";
  }

  file << "</sprite>\n";
  outfile.close();
}

void Sprite::Draw(int state, int time, int x, int y, double opacity) {
  // Don't crash on empty sprites!
  if(bitmap == 0 || state < 0) return;
  if(state >= states.size()) return;
  if(states[state]->frames.size() == 0) return;
  
  if(states[state]->loop >= 0) {
    time %= states[state]->max_time;
  } else if(time > states[state]->max_time) {
    time = states[state]->max_time;
  }

  int i = 0;
  bool done = false;
  while(!done && i < states[state]->frames.size()) {
    //    cout << time << " " << i << " " <<
    //      states[state]->frames[i]->end_time << "\n";
    if(states[state]->frames[i]->end_time >= time) {
      bitmap->Draw(states[state]->frames[i]->bitmap, x - x_origin, y - y_origin, opacity);
      //bitmap->DrawBoundingBox(states[state]->frames[i]->bitmap, x, y);
      //DrawBoundingBox(x, y);
      done = true;
    }
    i++;
  } 
}

void Sprite::DrawFrame(int state, int frame, int x, int y, double opacity) {
  if(bitmap && state >= 0 && frame >= 0 && states.size() > state && states[state]->frames.size() > frame) 
    bitmap->Draw(states[state]->frames[frame]->bitmap, x, y, opacity);
}

void Sprite::DrawBoundingBox(int x, int y) { 
  // don't bother drawing things that aren't on the screen.
  if(x + x2 < 0 || y + y2 < 0 || x + x1 > screen_x || y + y1 > screen_y) return;

  glColor4f(1.0, 1.0, 0.5, 1);
      
  glBegin(GL_LINE_LOOP);
  glVertex3f(x + x1, y + y1, 0);
  glVertex3f(x + x2, y + y1, 0);
  glVertex3f(x + x2, y + y2, 0);
  glVertex3f(x + x1, y + y2, 0);
  glEnd();
}

void Sprite::AddState(QString stateName) {
  State * s = new State;
  s->name = stateName;
  s->max_time = 0;
  states.push_back(s);
}

void Sprite::InsertState(int pos, QString stateName) 
{
  State * s = new State;
  s->name = stateName;
  s->max_time = 0;
  if(pos == -1) pos = 0;
  states.insert(pos, s);
}

void Sprite::DelState(int pos) 
{
  delete states.takeAt(pos);
}

void Sprite::AddFrame(int state, int duration, int bitmap) {
  InsertFrame(state, states[state]->frames.size(), duration, bitmap);
}

void Sprite::InsertFrame(int state, int frame, int duration, int bitmap) {
  if(state < states.size()) {
    int end_time = 0;
    if(states[state]->frames.size())
      end_time = states[state]->frames[states[state]->frames.size()-1]->end_time;
    end_time += duration;

    Frame * f = new Frame;
    f->bitmap = bitmap;
    f->end_time = end_time;
    f->duration = duration;
    states[state]->frames.insert(frame, f);
    states[state]->max_time += duration;
  }
}

void Sprite::DelFrame(int state, int frame) {
  delete states[state]->frames.takeAt(frame);
}

void Sprite::SetDuration(int state, int frame, int duration) {
  if(state < states.size()) {
    if(frame < states[state]->frames.size()) {
      int time_diff = duration - states[state]->frames[frame]->duration;
      int i;

      states[state]->frames[frame]->duration = duration;

      for(i = frame; i < states[state]->frames.size(); i++)
	      states[state]->frames[i]->end_time += time_diff;

      states[state]->max_time += time_diff;
    }
  }   
}

void Sprite::SetBitmap(int state, int frame, int bitmap) {
  //cout << "SetBitmap " << state << " " << frame << " " << bitmap << "\n";
  if(state >= 0 && state < states.size()) {
    if(frame >= 0 && frame < states[state]->frames.size()) {
      states[state]->frames[frame]->bitmap = bitmap;
    }
  }
}

int Sprite::GetStates() const {
  return states.size();
}

int Sprite::GetFrames(int state) const {
  if(state < states.size()) {
    return states[state]->frames.size();
  }
  return 0;
}

int Sprite::GetDuration(int state, int frame) const {
  if(state < states.size()) {
    if(frame < states[state]->frames.size()) {
      return states[state]->frames[frame]->duration;
    }
  }
  return 0;
}

int Sprite::GetBitmap(int state, int frame) const {
  if(state >= 0 && state < states.size()) {
    if(frame >= 0 && frame < states[state]->frames.size()) {
      return states[state]->frames[frame]->bitmap;
    }
  }
  return 0;
}

void Sprite::GetBoundingBox(int & x1, int & y1, int & x2, int & y2) {
/*
x1 = y1 = 0;
  if(bitmap) {
    bitmap->GetSize(x2, y2);
  } else {
    x2 = y2 = 0;
  }
  */
  x1 = this->x1;
  y1 = this->y1;
  x2 = this->x2;
  y2 = this->y2;
}

void Sprite::SetBoundingBox(int bx1, int by1, int bx2, int by2) {
  x1 = bx1;
  y1 = by1;
  x2 = bx2;
  y2 = by2;
}

void Sprite::GetOrigin(int & xo, int & yo) {
  xo = x_origin;
  yo = y_origin;
}

void Sprite::SetOrigin(int xo, int yo) {
  x_origin = xo;
  y_origin = yo;
}

Sprite::State::State() {
  loop = 0;
  max_time = 0;
}

Sprite::State::~State() {
  while(!frames.isEmpty())
    delete frames.takeFirst();
}

void SpriteReader::tokenDebug()
{
  if(isCharacters ())
  {
   // message("DEBUG -- CHARACTERS: " + readElementText());
  }
  else
  {
    //message("DEBUG: " + tokenString() + ": " + name().toString() + " [" + readElementText() + "]");
  }
}

Sprite * SpriteReader::read(QIODevice * device)
{
  setDevice(device);
  sprite = 0;

  while (!atEnd()) {
    readNext();
    if (isStartElement()) {
      if (name() == "sprite")
        readSprite();
      else
        raiseError(QObject::tr("This is not an xspr file."));
    }
  }

  if(!error())
    return sprite;
  else
    return 0;
}

Sprite * SpriteReader::read(QString filename)
{
  QFile f(filename);
  f.open(QIODevice::ReadOnly);
  return read(&f);
}

void SpriteReader::readSprite()
{
  Q_ASSERT(isStartElement() && name() == "sprite");
  sprite = new Sprite();

  while (!atEnd()) {
    readNext();
    //message("readMap: Token (" + tokenString() + "): " + name().toString());

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "name")
      {
        sprite->SetName(readElementText());
      }
      else if (name() == "state")
      {
        readState();
      }
      else if (name() == "tileset")
      {
        sprite->SetTileset(bitmaps[bitmapnames[readElementText()]]);
      }
      else if (name() == "origin")
      {
        QXmlStreamAttributes a = attributes();
        int x = a.value("x").toString().toInt();
        int y = a.value("y").toString().toInt();
        sprite->SetOrigin(x, y);

        // Advance the parser.
        readElementText();
      }
      else if (name() == "boundingbox")
      {
        QXmlStreamAttributes a = attributes();
        int x1 = a.value("x1").toString().toInt();
        int y1 = a.value("y1").toString().toInt();
        int x2 = a.value("x2").toString().toInt();
        int y2 = a.value("y2").toString().toInt();
        sprite->SetBoundingBox(x1, y1, x2, y2);        

        // Advance the parser.
        readElementText();
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void SpriteReader::readState()
{
  Q_ASSERT(isStartElement() && name() == "state");
  sprite->AddState();
  int currentState = sprite->GetStates() - 1;

  QString stateName;
  QString loop;

  while (!atEnd()) {
    readNext();
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if(name() == "loop") {
        loop = readElementText();
      }
      else if (name() == "name")
      {
        stateName = readElementText();
        sprite->SetStateName(currentState, stateName);
      }
      else if (name() == "frame")
      {
        readFrame(currentState);
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void SpriteReader::readFrame(int currentState)
{
  Q_ASSERT(isStartElement() && name() == "frame");
  QString bitmap;
  QString duration;

  while (!atEnd()) {
    readNext();
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "bitmap")
      {
        bitmap = readElementText();
      }
      else if (name() == "duration")
      {
        duration = readElementText();
      }
      else
      {
        readUnknownElement();
      }
    }
  }

  sprite->AddFrame(currentState, duration.toInt(), bitmap.toInt());
}

void SpriteReader::readUnknownElement()
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