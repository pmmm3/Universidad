#include "trampa.h"

void _trampa::draw_line()
{
    //Techo
    glPushMatrix();
    glTranslatef(0, 1.45, 0);
    Techo.draw_line();
    glPopMatrix();

    //Brazo
    glPushMatrix();
    //Movimiento
    //Vuelvo a la posición metiendolo en el techo
    glTranslatef(0, +1.45, 0);
    //Roto en el eje
    glRotatef(alpha, 0, 0, 1);
    //Lo llevo al eje
    glTranslatef(0, -1.4, 0);
    Brazo.draw_line();
    glPopMatrix();
}

void _trampa::update_alpha_brazo()
{
    if (alpha + speed >= ALPHA_MIN && alpha + speed <= ALPHA_MAX)
        alpha += speed;
    else
        speed = 0;
}
void _trampa::increase_alpha_brazo()
{
    if (alpha + 5 >= ALPHA_MIN && alpha + 5 <= ALPHA_MAX)
        alpha += 5;
}
void _trampa::decrease_alpha_brazo()
{
    if (alpha - 5 >= ALPHA_MIN && alpha - 5 <= ALPHA_MAX)
        alpha += -5;
}
void _trampa::increase_speed_brazo()
{
    speed += 1;
}
void _trampa::decrease_speed_brazo()
{
    speed += -1;
}

void _trampa::update_alpha_pelota()
{
    Brazo.update_alpha_pelota();
}
void _trampa::increase_alpha_pelota()
{
    Brazo.increase_alpha_pelota();
}
void _trampa::decrease_alpha_pelota()
{
    Brazo.decrease_alpha_pelota();
}
void _trampa::increase_speed_pelota()
{
    Brazo.increase_speed_pelota();
}
void _trampa::decrease_speed_pelota()
{
    Brazo.decrease_speed_pelota();
}

void _trampa::update_d_soporte()
{
    Brazo.update_d_soporte();
}
void _trampa::subir_soporte()
{
    Brazo.subir_soporte();
}
void _trampa::bajar_soporte()
{
    Brazo.bajar_soporte();
}
void _trampa::subir_v_soporte()
{
    Brazo.subir_v_soporte();
}
void _trampa::bajar_v_soporte()
{
    Brazo.bajar_v_soporte();
}

void _trampa::update_aplha_pincho()
{
    Brazo.update_aplha_pincho();
}
void _trampa::increase_alpha_pincho()
{
    Brazo.increase_alpha_pincho();
}
void _trampa::decrease_alpha_pincho()
{
    Brazo.decrease_alpha_pincho();
}
void _trampa::decrease_speed_pincho()
{
    Brazo.decrease_speed_pincho();
}
void _trampa::increase_speed_pincho()
{
    Brazo.increase_speed_pincho();
}