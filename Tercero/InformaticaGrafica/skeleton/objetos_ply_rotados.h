/**
  * @file objectos_ply.h
  * @brief Representacion de un objeto con formato tipo .ply
 */

#ifndef OBJETOS_PLY_H
#define OBJETOS_PLY_H


#include "rotacion_v1.h"
#include <QString>


/**
  * @class _objeto_ply
  * @brief Clase para construir un objeto ply que hereda de _Object3D
*/
class _objeto_ply_rotados:public rotacion_v1
{
public:
    _objeto_ply_rotados(int cortes=3);
    _objeto_ply_rotados(string archivo,int cortes=3);
};

#endif // OBJETOS_PLY_H
