#include "mango.h"

void _mango::transformaciones()
{
    glPushMatrix();
    glScalef(0.1, 0.4,0.1);
}

// void _mango::draw_point()
// {
//     transformaciones();
//     Cilindro.draw_point();
//     glPopMatrix();
// }
void _mango::draw_line()
{
    transformaciones();
    Cilindro.draw_line();
    glPopMatrix();
}
