#ifndef PINCHO_H
#define PINCHO_H

#include "cono.h"

/*****************************************************************************
 *
 *
 *
 *****************************************************************************/

class _pincho
{
private:
  _cono Cono = _cono(1, 20, 360);
  float alpha = 0;
  float speed = 1;
  void movimiento();
  void transformaciones();

public:
  void update_aplha();

  void increase_alpha();
  void decrease_alpha();

  void increase_speed();
  void decrease_speed();

  void draw_line();
};

#endif
