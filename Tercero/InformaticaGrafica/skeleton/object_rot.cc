#include "object_rot.h"
_objeto_rot::_objeto_rot(){}

void _objeto_rot::Girar(double n, double a_inicio, double a_fin)
{
    double angulo=((a_fin-a_inicio/n)*PI/180.0);
    double a_inico_rad=a_inicio*PI/180.0;

/**

Eje y |
      0        0
      |
      |
      |
    __0________0_______ Eje x
      |
Que él primer punto tenga la x = 0 quiere decir que puede haber tapa superior y es un punto dentro del eje y
Que él último punto tenga la x = 0 quiere decir que puede haber tapa inferior y es un punto dentro del eje y
*/
    if(perfil[0].x==0)
    {
        // Lo quito del vector y lo guardo en p_1 para despues no girarlo con el resto
        tapa_arriba=true;
        p_1=perfil[0];
        perfil.erase(perfil.begin());
    }
    else
    {
        p_1=_vertex3f(0,perfil[0].y,0);
    }
    if (perfil[perfil.size()-1].x==0)
    {
        //Igual que con la tapa de arriba
        tapa_abajo=true;
        p_2=perfil[perfil.size()-1];
        perfil.pop_back();
    }
    else
    {
        p_2=_vertex3f(0,perfil[perfil.size()-1].y,0);
    }
    int nuevo_tam= perfil.size();
    int giros= nuevo_tam*n;
    _vertex3ui cara;

    for (int k=1; k<=n;k++)
    {
        Vertices.push_back(RotY(perfil[0],a_inico_rad+angulo*k));

        for(unsigned int j=1;j<perfil.size();j++)
        {
            int i=k*nuevo_tam+j;
            Vertices.push_back((RotY(perfil[j],a_inico_rad + angulo*k)));
            cara=_vertex3ui((i-nuevo_tam),i,(i-nuevo_tam-1));
            Triangles.push_back(cara);
            cara=_vertex3ui(i,i-1,i-nuevo_tam-1);
            Triangles.push_back(cara);
        }
    }

    if(tapa_arriba)
    {
        Vertices.push_back(p_1);
        int pos_p_1=Vertices.size()-1;
        {
            for(int i=0;i<giros;i+=nuevo_tam)
            {
                cara=_vertex3ui(pos_p_1,i,i+nuevo_tam);
                Triangles.push_back(cara);
            }
        }
    }
    if(tapa_abajo)
    {
        Vertices.push_back(p_2);
        int pos_p_2=Vertices.size()-1;
        {
            for(int i=0;i<giros;i+=nuevo_tam)
            {
                cara=_vertex3ui(pos_p_2,i,i+nuevo_tam);
                Triangles.push_back(cara);
            }
        }
    }

}

_vertex3f _objeto_rot::RotY(_vertex3f punto, double angulo)
{
    _vertex3f aux;
    aux.x=punto.x*cos(angulo)+punto.z*sin(angulo);
    aux.y=punto.y;
    aux.z=punto.x*(-sin(angulo))+punto.z*cos(angulo);
    return aux;
}
