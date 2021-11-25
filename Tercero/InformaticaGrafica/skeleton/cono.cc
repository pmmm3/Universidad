#include "cono.h"

_cono::_cono(double size,int cortes,double angulo)
{
    perfil.push_back(_vertex3f(0,-size/2,0));
    perfil.push_back(_vertex3f(size/2,-size/2,0));
    //perfil.push_back(_vertex3f(size/2,+size/2,0));
    perfil.push_back(_vertex3f(0,size/2,0));
    this->Girar(cortes,angulo);
}

