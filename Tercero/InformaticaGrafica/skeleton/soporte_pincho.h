#ifndef SOPORTE_PINCHO_H
#define SOPORTE_PINCHO_H

#include "soporte.h"
#include "pincho.h"

class _soporte_pincho
{
private:
    _soporte Soporte;
    _pincho Pincho;
public:
    void update_aplha_pincho();

    void increase_alpha_pincho();
    void decrease_alpha_pincho();

    void increase_speed_pincho();
    void decrease_speed_pincho();

    void draw_line();
};

#endif // SOPORTE_PINCHO_H
