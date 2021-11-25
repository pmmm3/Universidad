/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#include "ply.h"
#include <fstream>

/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

_ply::_ply(const std::string & nombre_archivo,float Size)
{

  int num_v,num_c;
  //Abrir archivo
  std::string aux;
  ifstream lec;
  nombre_archivo_ply=nombre_archivo;
  lec.open(nombre_archivo_ply.c_str());

  //Comprobar si falla el open
  if(!lec.is_open())
  {
      printf("Error al abrir el archivo ply");
  }
  else
  {
      //Empezar a leer

      lec >> aux;
      if(aux != "ply")
          printf("Error en el formato del archivo, se esperaba leer 'ply' ");
      else
      {
          while(!lec.eof() && aux != "vertex")
          {
              lec >> aux;
          }
          lec >> num_v;//Numero de vertices
          while(!lec.eof() && aux != "face")
          {
              lec >> aux;
          }
          lec >> num_c;//Numero de caras
          while(!lec.eof() && aux != "end_header")
          {
              lec >> aux;
          }

          //Leo num_v veces para obtener los vertices
          Vertices.resize(num_v);
          for (int i = 0 ; i < num_v;i++)
          {
              float x_aux,y_aux,z_aux;
              lec >> x_aux;
              lec >> y_aux;
              lec >> z_aux;
              Vertices[i]=_vertex3f(x_aux,y_aux,z_aux);
          }

          //Leo num_c veces para obtener los triangulos
          Triangles.resize(num_c);

          Triangles[0]=_vertex3ui(0,1,3);
          Triangles[1]=_vertex3ui(1,2,3);
          Triangles[2]=_vertex3ui(2,0,3);
          Triangles[3]=_vertex3ui(0,2,1);
      }

  }
  //Cierro el archivo
  lec.close();
}

