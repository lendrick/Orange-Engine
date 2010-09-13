#ifndef event_h
#define event_h 1

#include "polygon.h"

class Event {
public:
  virtual bool IsColliding(Polygon * p) = 0;
};

#endif
