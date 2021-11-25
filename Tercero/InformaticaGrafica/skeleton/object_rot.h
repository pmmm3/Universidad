#ifndef OBJECT_ROT_H
#define OBJECT_ROT_H
#include <QtMath>
#include "object3d.h"

class _objeto_rot:public _object3D
{
public:
    const double PI=M_PI;
    std::vector<_vertex3f> perfil; // vector de los puntos que hacen el perfil
    _vertex3f p_1, p_2; // puntos del eje a rotar
    int cortes; // numero de revoluciones
    double alpha, beta;
    bool tapa_arriba=false;
    bool tapa_abajo=false;

    _objeto_rot();
    void Girar(double n,double a_inicio,double a_fin);
    _vertex3f RotY(_vertex3f punto, double angulo);

};

#endif // OBJECT_ROT_H
