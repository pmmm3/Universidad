#include "esfera.h"

_esfera::_esfera(double size,int cortes,double angulo)
{
    for(int i=0; i<=180; i++)
    {
        perfil.push_back(_vertex3f(size/2*sin((PI/180)*i),size/2*cos((PI/180)*i) ,0));
    }

    this->Girar(cortes,angulo);
}

//La normal de cada vertice coincide del centro  a dicho punto
void _esfera::calculoNormalesVertice()
{
    NormalesVertice.resize(Vertices.size());
    int tam = Vertices.size();
    for (int i = 0; i < tam; i++)
    {
        NormalesVertice[i] = Vertices[i];
        Normalizar(NormalesVertice[i]);
    }
}
