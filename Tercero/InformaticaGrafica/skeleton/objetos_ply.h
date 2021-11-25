/**
  * @file objectos_ply.h
  * @brief Representacion de un objeto con formato tipo .ply
 */

#ifndef OBJETOS_PLY_H
#define OBJETOS_PLY_H


#include "object3d.h"
#include <QString>


/**
  * @class _objeto_ply
  * @brief Clase para construir un objeto ply que hereda de _Object3D
*/
class _objeto_ply:public _object3D
{
public:
    _objeto_ply();
    _objeto_ply(string archivo);
};

#endif // OBJETOS_PLY_H
