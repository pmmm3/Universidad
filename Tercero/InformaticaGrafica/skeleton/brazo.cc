#include "brazo.h"

void _brazo::draw_line()
{
    glMatrixMode(GL_MODELVIEW);

    //Mango
    glPushMatrix();
    //Transformación
    glTranslatef(0, 1.2, 0);
    Mango.draw_line();
    glPopMatrix();

    //Pelota
    glPushMatrix();
    //Movimiento pelota
    glTranslatef(0, +1, 0);
    glRotatef(alpha, 1, 0, 0);
    glTranslatef(0, -1, 0);
    //Pintado
    Pelota.draw_line();
    glPopMatrix();
}

void _brazo::update_alpha_pelota()
{
    if (alpha + speed >= ALPHA_MIN && alpha + speed <= ALPHA_MAX)
        alpha += speed;
    else
        speed = 0;
}
void _brazo::increase_alpha_pelota()
{
    if (alpha + 5 >= ALPHA_MIN && alpha + 5 <= ALPHA_MAX)
        alpha += 5;
}
void _brazo::decrease_alpha_pelota()
{
    if (alpha - 5 >= ALPHA_MIN && alpha - 5 <= ALPHA_MAX)
        alpha += -5;
}
void _brazo::increase_speed_pelota()
{
    speed += 1;
}
void _brazo::decrease_speed_pelota()
{
    speed += -1;
}

void _brazo::update_d_soporte()
{
    Pelota.update_d_soporte();
}
void _brazo::subir_soporte()
{
    Pelota.subir_soporte();
}
void _brazo::bajar_soporte()
{
    Pelota.bajar_soporte();
}
void _brazo::subir_v_soporte()
{
    Pelota.subir_v_soporte();
}
void _brazo::bajar_v_soporte()
{
    Pelota.bajar_v_soporte();
}

void _brazo::update_aplha_pincho()
{
    Pelota.update_aplha_pincho();
}
void _brazo::decrease_alpha_pincho()
{
    Pelota.decrease_alpha_pincho();
}
void _brazo::increase_alpha_pincho()
{
    Pelota.increase_alpha_pincho();
}
void _brazo::decrease_speed_pincho()
{
    Pelota.decrease_speed_pincho();
}
void _brazo::increase_speed_pincho()
{
    Pelota.increase_speed_pincho();
}
