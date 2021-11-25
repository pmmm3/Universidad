#include "rotacion_v1.h"

rotacion_v1::rotacion_v1(float size,int cortes)
{
    //perfil.push_back(_vertex3f(0,-size/2,0));
    //perfil.push_back(_vertex3f(size/2,-size/2,0));
    //perfil.push_back(_vertex3f(size/2,+size/2,0));
    //perfil.push_back(_vertex3f(0,size/2,0));

    //this->Girar(cortes);
}
/**
 * @brief rotacion_v1::Girar
 * @param cortes
 */
void rotacion_v1::Girar(int cortes,double angulo_a_girar)
{
    _vertex3f aux;
    //double angulo = (2*PI)/(cortes); //Standar
    double angulo = (angulo_a_girar*PI/180)/(cortes-1);
    double angulo_aux=angulo;//No es 0 por que el primer corte son los puntos del perfil
    int tam = perfil.size();
    bool tapa_abajo,tapa_arriba=false;


    if(perfil[0].x==0)
    {
        //tapa de abajo
        p_0=perfil[0];
        tapa_abajo=true;
    }
    else
    {
        //Si no lo forzamos
        //p_0=_vertex3f(0,perfil[0].y,0);
    }
    //Quitamos el punto por que al estar en el eje no se rotará
    perfil.erase(perfil.begin());
    if(perfil[perfil.size()-1].x==0)
    {
        //tapa de arriba
        p_n=perfil[tam-1];
        tapa_arriba=true;
    }
    else
    {
        //p_n=_vertex3f(0,perfil[perfil.size()-1].y,0);
    }
    //Quitamos el punto por que al estar en el eje no se rotará
    perfil.pop_back();

    //Actualizo los puntos del perfil
    tam = perfil.size();


    //Genero los vertices

    /*
     *
     * Cilindro

                7

    1       3       5       1

    0       2       4       0

                6

     * Cono

                4

    0       1       2       0

                3


    */

    Vertices.clear();

    //Añado primero los puntos del perfil que me quedan
    for(int i=0;i<tam;i++)
    {
       Vertices.push_back(perfil[i]);
    }
    //Añado los puntos del perfil que me quedaba rotados
    for(int i=1;i < cortes;i++)
    {

        for (int k =0; k< tam ;k++)
        {
            Vertices.push_back(Rotar_eje_y(perfil[k],angulo_aux));
        }
        angulo_aux+=angulo;
    }

    //Añado Los puntos del eje al final quedandome con sus posiciones
    Vertices.push_back(p_0);
    int pos_0=Vertices.size()-1;
    Vertices.push_back(p_n);
    int pos_n=Vertices.size()-1;



    //Genero los triangulos
    Triangles.clear();

    int indice=0;
    int indice_aux2=0;
    if(tapa_abajo)
    {

        //int indice_aux2=1*tam %(tam*cortes);

        for(int i=0;i < cortes ;i++)
        {
            indice=i*tam %(tam*cortes);
            indice_aux2=(i+1)*tam %(tam*cortes);
            Triangles.push_back(_vertex3ui(indice,pos_0,indice_aux2));
            //indice=indice_aux2;
        }
    }
    if (tapa_arriba)
    {

        //int indice_aux2=1*tam %(tam*cortes);

        for(int i=0;i <= cortes ;i++)
        {
            indice=i*tam %(tam*cortes) + tam-1;
            indice_aux2=(i+1)*tam %(tam*cortes) + tam -1;
            Triangles.push_back(_vertex3ui(pos_n,indice,indice_aux2));
            //indice=indice_aux2;
        }
    }
    if (tam>1)
    {
        int aux_mod=Vertices.size()-2;
        //Debo generar los triangulos intermedios
        for(int i = 0; i < tam-1; i++)
        {
            for(int j = 0; j < cortes+1; j++)
            {
                indice=(i+(j*tam)) ;
                Triangles.push_back(_vertex3ui(indice%aux_mod,(indice+tam)%aux_mod ,(indice+1)%aux_mod)); //Caras pares
                Triangles.push_back(_vertex3ui((indice+1)%aux_mod,(indice+tam)%aux_mod,(indice+1+tam)%aux_mod)); //Caras impares
            }
        }
    }


}
/**
 * @brief rotacion_v1::Rotar_eje_y
 * @param punto
 * @param angulo
 * @return  _vertex3f
 * @note Usando las formulas de rotación
 */
_vertex3f rotacion_v1::Rotar_eje_y(const _vertex3f &punto,double angulo)
{
    _vertex3f aux;
    aux.x = (punto.z * sin(angulo))+(punto.x * cos(angulo));
    aux.y =  punto.y;
    aux.z = (punto.z * cos(angulo))-(punto.x * sin(angulo));
    return aux;
}
