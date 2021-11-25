#ifndef ESFERA_H
#define ESFERA_H
#include "rotacion_v1.h"

class _esfera:public rotacion_v1{
public:
    _esfera(double size=1,int cortes=50,double angulo=360);
    void calculoNormalesVertice();
};



#endif
