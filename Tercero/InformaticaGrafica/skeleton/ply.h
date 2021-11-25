/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef PLY_H
#define PLY_H

#include "object3d.h"
#include <string>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _ply:public _object3D
{
private:
    std::string nombre_archivo_ply;
public:
  _ply(const std::string & nombre_archivo,float Size=1.0);
  void leer();
};

#endif
