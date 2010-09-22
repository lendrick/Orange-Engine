#ifndef RPGENGINE_H
#define RPGENGINE_H

class Map;
class Player;

#include <QtCore>

class RPGEngine
{
public:
  static void init();
  static void setCurrentMap(Map *);
  static void setPlayerEntity(Player *);
  static Map * getCurrentMap();
  static Player * getPlayerEntity();

  static void addScript(int, QString);
  static void clearScripts();
  static int getScriptCount();
  static QString getScript(int);
  static int getScriptCondition(int);
  static void dumpEvent(QEvent *);
};

#endif // RPGENGINE_H
