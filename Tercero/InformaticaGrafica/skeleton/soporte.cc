#include "soporte.h"

void _soporte::transformaciones()
{
    glScalef(0.1, 0.2, 0.1);
}

void _soporte::draw_line()
{
    glPushMatrix();
    transformaciones();
    Cubo.draw_line();
    glPopMatrix();
}
