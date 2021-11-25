/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "chess_board.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_chess_board::_chess_board(float Size)
{
  Vertices.resize(4);

  Vertices[0] =_vertex3f(-Size/2,-Size/2,0);
  Vertices[1] =_vertex3f(Size/2,-Size/2,0);
  Vertices[2] =_vertex3f(Size/2,Size/2,0);
  Vertices[3] =_vertex3f(-Size/2,Size/2,0);

  Triangles.resize(2);

  Triangles[0] = _vertex3ui(0,1,3);
  Triangles[1] = _vertex3ui(1,2,3);

  Coordenadas_textura.resize(Vertices.size());
  Coordenadas_textura[0] = _vertex2f(0, 0);
  Coordenadas_textura[1] = _vertex2f(1, 0);
  Coordenadas_textura[2] = _vertex2f(1, 1);
  Coordenadas_textura[3] = _vertex2f(0, 1);
}
