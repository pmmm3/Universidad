#include "techo.h"


void _techo::transformaciones()
{
    glPushMatrix();
    glScalef(0.8, 0.1, 0.8);

}


void _techo::draw_line()
{
    transformaciones();
    Cubo_obj.draw_line();
    glPopMatrix();
}
