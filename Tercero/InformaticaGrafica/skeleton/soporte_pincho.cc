#include "soporte_pincho.h"

void _soporte_pincho::draw_line()
{
    //Soporte
    glPushMatrix();
    glTranslatef(0, 0.3, 0); //0.2 de cono + 0.1 de la mitad de soporte
    Soporte.draw_line();
    glPopMatrix();
    //Pincho
    glPushMatrix();
    Pincho.draw_line();
    glPopMatrix();
}

void _soporte_pincho::update_aplha_pincho()
{
    Pincho.update_aplha();
}
void _soporte_pincho::decrease_alpha_pincho()
{
    Pincho.decrease_alpha();
}
void _soporte_pincho::increase_alpha_pincho()
{
    Pincho.increase_alpha();
}
void _soporte_pincho::decrease_speed_pincho()
{
    Pincho.decrease_speed();
}
void _soporte_pincho::increase_speed_pincho()
{
    Pincho.increase_speed();
}
