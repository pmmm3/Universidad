#include "pelota_punzante.h"

void _pelota_punzante::draw_line()
{
    glPushMatrix();
    //Esfera
    glTranslatef(0, 0.7, 0);
    glScalef(0.6, 0.6, 0.6);
    Esfera.draw_line();
    glPopMatrix();

    //Soporte_Pincho
    glPushMatrix();
    glTranslatef(0, d_soporte, 0);
    soportePincho.draw_line();

    glPopMatrix();
}

void _pelota_punzante::update_d_soporte()
{
    //0 << d_soporte << 0.2
    //std::cout << "valor " + to_string(d_soporte) << "\t";
    //std::cout << "speed " + to_string(speed) << endl;
    if ((d_soporte + speed >= 0) && (d_soporte + speed <= 0.3))
    {
        d_soporte += speed;
    }
    else
    {
        speed = 0;
    }
}
void _pelota_punzante::bajar_soporte()
{
    if (d_soporte - 0.05 >= 0 && d_soporte - 0.05 <= 0.3)
        d_soporte += -0.05;
}
void _pelota_punzante::subir_soporte()
{
    if (d_soporte + 0.05 >= 0 && d_soporte + 0.05 <= 0.3)
        d_soporte += 0.05;
}
void _pelota_punzante::bajar_v_soporte()
{
    speed += -0.05;
}
void _pelota_punzante::subir_v_soporte()
{
    speed += 0.05;
}
void _pelota_punzante::update_aplha_pincho()
{
    soportePincho.update_aplha_pincho();
}

void _pelota_punzante::increase_alpha_pincho()
{
    soportePincho.increase_alpha_pincho();
}
void _pelota_punzante::decrease_alpha_pincho()
{
    soportePincho.decrease_alpha_pincho();
}
void _pelota_punzante::increase_speed_pincho()
{
    soportePincho.increase_speed_pincho();
}
void _pelota_punzante::decrease_speed_pincho()
{
    soportePincho.decrease_speed_pincho();
}