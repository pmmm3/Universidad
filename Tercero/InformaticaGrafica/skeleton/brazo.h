#ifndef BRAZO_H
#define BRAZO_H

#include "mango.h"
#include "pelota_punzante.h"

class _brazo
{
private:
    _mango Mango;
    _pelota_punzante Pelota;
    float alpha = 0;
    float speed = 1;
    const float ALPHA_MAX = 60;
    const float ALPHA_MIN = -60;

public:
    void update_alpha_pelota();
    void increase_alpha_pelota();
    void decrease_alpha_pelota();
    void increase_speed_pelota();
    void decrease_speed_pelota();

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
#endif // BRAZO_H
