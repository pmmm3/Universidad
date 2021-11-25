#ifndef PELOTA_PUNZANTE_H
#define PELOTA_PUNZANTE_H

#include "esfera.h"
#include "soporte_pincho.h"

class _pelota_punzante
{
private:
    _esfera Esfera;
    _soporte_pincho soportePincho;
    float d_soporte = 0;
    float speed = 0.1;
    void movimiento();
    void transformaciones();

public:
    void update_d_soporte();
    void subir_soporte();
    void bajar_soporte();
    void subir_v_soporte();
    void bajar_v_soporte();

    void update_aplha_pincho();
    void increase_alpha_pincho();
    void decrease_alpha_pincho();
    void increase_speed_pincho();
    void decrease_speed_pincho();

    void draw_line();
};

#endif // PELOTA_PUNZANTE_H
