#ifndef ROTACION_V1_H
#define ROTACION_V1_H
#include <QtMath>
#include "object3d.h"
class rotacion_v1:public _object3D
{
public:
    const double PI=M_PI;
    std::vector<_vertex3f> perfil; // vector de los puntos que hacen el perfil
    _vertex3f p_0, p_n; // puntos del eje a rotar
    int cortes; // numero de revoluciones


    rotacion_v1(float size=1,int cortes=4);
    void Girar(int cortes,double angulo_a_girar=360);
    _vertex3f Rotar_eje_y(const _vertex3f &punto,double angulo);
};

#endif // ROTACION_V1_H
