#include "input.h"

Input::Input() {
  up = down = left = right = ok = cancel = action = console = false;
}

Input * input = new Input;