#ifndef RPGENGINE_H
#define RPGENGINE_H

class Map;
class Player;

class RPGEngine
{
public:
  static void init();
  static void setCurrentMap(Map *);
  static void setPlayerEntity(Player *);
  static Map * getCurrentMap();
  static Player * getPlayerEntity();
};

#endif // RPGENGINE_H
