/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "basic_object3d.h"


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _object3D:public _basic_object3D
{
  private:
    bool normales_calculadas_vertice = false;
    bool normales_calculadas_triangulo = false;

    _vertex3f ProductoVectorial(const _vertex3f &v_a, const _vertex3f &v_b);

  public:
    vector<_vertex3ui> Triangles;
    vector<_vertex2f> Coordenadas_textura;
    vector<_vertex3f> NormalesTriangulo;
    vector<_vertex3f> NormalesVertice;
    void Normalizar(_vertex3f &v);
    void calculoNormalesTriangulo();
    void calculoNormalesVertice();

    void config_luz0();

    float angulo_luz1 = 0;
    float posX = 100, posY = 100, posZ = 100;
    void config_luz1();

    void update_luz1();

    void config_material(int i_material);

    void draw_line();
    void draw_fill();
    void draw_chess();
    void draw_flat_light(bool luz0,bool luz1, int i_material);
    void draw_smooth_light(bool luz0, bool luz1, int i_material);

    void draw_texture_no_light();
    void draw_texture_flat(bool luz0, bool luz1, int i_material);
    void draw_texture_smooth(bool luz0, bool luz1, int i_material);
};

#endif // OBJECT3D_H
