#ifndef CILINDRO_H
#define CILINDRO_H
#include "rotacion_v1.h"

class _cilindro:public rotacion_v1{
public:
    _cilindro(double size=1,int cortes=40,double angulo = 360);
};



#endif
