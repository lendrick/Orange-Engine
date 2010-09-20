#ifndef sprite_h
#define sprite_h 1

#include "bitmap.h"
#include <QtCore>

class Bitmap;
class Resource;

class Sprite {
public:
  Sprite(Bitmap *, QString spritename = "");
  Sprite(char * filename, Bitmap * b, QString spritename = "");
  Sprite(QString spritename = "");
  ~Sprite();
  bool setName(QString spritename);
  QString getName() { return name; }

  Bitmap * getTileset() { return bitmap; }
  void setTileset(Bitmap * b) { bitmap = b; }

  bool load(char * filename);
  void save(QString filename);
  void draw(int state, int time, int x, int y, double opacity = 1.0);
  void drawFrame(int state, int frame, int x, int y, double opacity = 1.0);
  void drawBoundingBox(int x, int y);
  void addState(QString name = "New state");
  void insertState(int pos, QString name = "New state");
  void delState(int pos);
  
  void addFrame(int state, int duration, int bitmap);
  void insertFrame(int state, int frame, int duration, int bitmap);
  void delFrame(int state, int frame);

  void setDuration(int state, int frame, int duration);
  void setBitmap(int state, int frame, int bitmap);

  int getStateCount() const;
  int getFrameCount(int state) const;
  int getDuration(int state, int frame) const;
  int getBitmap(int state, int frame) const;
  int getId() const { return id; }
  QString getStateName(int state) const { return states[state]->name; }
  void setStateName(int state, QString stateName) { states[state]->name = stateName; }

  void getBoundingBox(int &, int &, int &, int &);
  void getOrigin(int &, int &);
  void setOrigin(int, int);
  void setBoundingBox(int, int, int, int);
protected:
  int x1, y1, x2, y2;
  int x_origin, y_origin;

  struct Frame {
    int end_time;
    int duration;
    int bitmap;
  };

  struct State {
    QList <Frame *> frames;
    int max_time;
    int loop;
    QString name;
    State();
    ~State();
  };

  QList <State *> states;
  Bitmap * bitmap;
  Resource * thisSprite;
  QString name;
  int id;
};

class SpriteReader : public QXmlStreamReader
{
public:
  Sprite * read(QIODevice * device);
  Sprite * read(QString filename);

private:
  void readSprite();
  void readState();
  void readFrame(int currentState);
  void readUnknownElement();
  void tokenDebug();

  Sprite * sprite;
};

#endif
