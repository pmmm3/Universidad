#ifndef TRAMPA_H
#define TRAMPA_H

#include "brazo.h"
#include "techo.h"

class _trampa
{
    _techo Techo;
    _brazo Brazo;
    float alpha = 0;
    float speed = 1;
    const float ALPHA_MAX = 60;
    const float ALPHA_MIN = -60;

public:
    //Rotar en z todo el brazo
    void update_alpha_brazo();
    void increase_alpha_brazo();
    void decrease_alpha_brazo();
    void increase_speed_brazo();
    void decrease_speed_brazo();

    //Rotar la pelota en y
    void update_alpha_pelota();
    void increase_alpha_pelota();
    void decrease_alpha_pelota();
    void increase_speed_pelota();
    void decrease_speed_pelota();

    //Subir y bajar soporte
    void update_d_soporte();
    void subir_soporte();
    void bajar_soporte();
    void subir_v_soporte();
    void bajar_v_soporte();

    //Mover el pincho solo
    void update_aplha_pincho();
    void increase_alpha_pincho();
    void decrease_alpha_pincho();
    void increase_speed_pincho();
    void decrease_speed_pincho();
    void draw_line();
};
#endif // TRAMPA_H
