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
  bool SetName(QString spritename);
  QString GetName() { return name; };

  Bitmap * GetTileset() { return bitmap; }
  void SetTileset(Bitmap * b) { bitmap = b; }

  bool Load(char * filename);
  void Save(QString filename);
  void Draw(int state, int time, int x, int y, double opacity = 1.0);
  void DrawFrame(int state, int frame, int x, int y, double opacity = 1.0);
  void DrawBoundingBox(int x, int y);
  void AddState(QString name = "New state");
  void InsertState(int pos, QString name = "New state");
  void DelState(int pos);
  
  void AddFrame(int state, int duration, int bitmap);
  void InsertFrame(int state, int frame, int duration, int bitmap);
  void DelFrame(int state, int frame);

  void SetDuration(int state, int frame, int duration);
  void SetBitmap(int state, int frame, int bitmap);

  int GetStates() const;
  int GetFrames(int state) const;
  int GetDuration(int state, int frame) const;
  int GetBitmap(int state, int frame) const;
  int GetId() const { return id; };
  QString GetStateName(int state) const { return states[state]->name; };
  void SetStateName(int state, QString stateName) { states[state]->name = stateName; };

  void GetBoundingBox(int &, int &, int &, int &);
  void GetOrigin(int &, int &);
  void SetOrigin(int, int);
  void SetBoundingBox(int, int, int, int);
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
