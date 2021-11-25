#include "pincho.h"

void _pincho::transformaciones()
{
    glRotatef(180, 1, 0, 0);
    glScalef(0.15, 0.4, 0.15);
}

void _pincho::draw_line()
{
    glPushMatrix();
    movimiento();
    transformaciones();
    Cono.draw_line();
    glPopMatrix();
}

void _pincho::movimiento()
{
    glRotatef(alpha, 0, 1, 0);
}

void _pincho::update_aplha()
{
    alpha += speed;
}
void _pincho::decrease_alpha()
{
    alpha += -1;
}
void _pincho::increase_alpha()
{
    alpha += 1;
}
void _pincho::decrease_speed()
{
    speed += -1;
}
void _pincho::increase_speed()
{
    speed += 1;
}

