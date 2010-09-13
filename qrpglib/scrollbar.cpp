#ifdef WIN32
#include <windows.h>
#endif

#include "scrollbar.h"
#include <iostream>

using std::cout;

void ScrollBar::setRange(int start, int end) {
  setMinimum(start);
  setMaximum(end);
  setValue(0);
  emit valueChanged(0);
}
