/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "cube.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_cube::_cube(float Size)
{
  Vertices.resize(8);

  Vertices[0] =_vertex3f(-Size/2,-Size/2,Size/2);
  Vertices[1] =_vertex3f(Size/2,-Size/2,Size/2);
  Vertices[2] =_vertex3f(Size/2,Size/2,Size/2);
  Vertices[3] =_vertex3f(-Size/2,Size/2,Size/2);
  Vertices[4] =_vertex3f(Size/2,Size/2,-Size/2);
  Vertices[5] =_vertex3f(-Size/2,Size/2,-Size/2);
  Vertices[6] =_vertex3f(-Size/2,-Size/2,-Size/2);
  Vertices[7] =_vertex3f(Size/2,-Size/2,-Size/2);
  Triangles.resize(12);

  Triangles[0] = _vertex3ui(0,1,3);
  Triangles[1] = _vertex3ui(1,2,3);
  Triangles[2] = _vertex3ui(1,7,2);
  Triangles[3] = _vertex3ui(7,4,2);
  Triangles[4] = _vertex3ui(7,6,4);
  Triangles[5] = _vertex3ui(6,5,4);
  Triangles[6] = _vertex3ui(6,0,5);
  Triangles[7] = _vertex3ui(0,3,5);
  Triangles[8] = _vertex3ui(3,2,5);
  Triangles[9] = _vertex3ui(2,4,5);
  Triangles[10] = _vertex3ui(0,1,6);
  Triangles[11] = _vertex3ui(1,7,6);

}

