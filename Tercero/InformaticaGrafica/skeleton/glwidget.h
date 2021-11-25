/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */


#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QKeyEvent>

#include <QTimer>

#include <iostream>
#include "vertex.h"
#include "colors.h"
#include "axis.h"
#include "tetrahedron.h"
#include "cube.h"
#include "objetos_ply.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "rotacion_v1.h"
#include "techo.h"
#include "soporte.h"
#include "mango.h"
#include "pincho.h"
#include "soporte_pincho.h"
#include "pelota_punzante.h"
#include "brazo.h"
#include "trampa.h"
#include "chess_board.h"
namespace _gl_widget_ne {

  const float X_MIN=-.1;
  const float X_MAX=.1;
  const float Y_MIN=-.1;
  const float Y_MAX=.1;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=1000;
  const float DEFAULT_DISTANCE=2;
  const float ANGLE_STEP=1;

  typedef enum {MODE_DRAW_POINT,MODE_DRAW_LINE,MODE_DRAW_FILL,MODE_DRAW_CHESS} _mode_draw;
  typedef enum {OBJECT_TETRAHEDRON,OBJECT_CUBE,OBJECT_PLY,OBJECT_CONO,OBJECT_CILINDRO,OBJECT_ESFERA,OBJECT_TRAMPA, OBJECT_PRUEBA,OBJECT_CHESS} _object;
}

class _window;


/*****************************************************************************//**
 *
 *
 *
 *****************************************************************************/

class _gl_widget : public QOpenGLWidget
{
Q_OBJECT
public:
  _gl_widget(_window *Window1);

  void clear_window();
  void change_projection();
  void change_observer();

  void draw_axis();
  void draw_objects();

  void animation();

  void cargar_textura(string archivo_texture = "/home/pablo/Documentos/IG/Practicas/P4/skeleton/texturas/tablero.jpg");

protected:
  void resizeGL(int Width1, int Height1) Q_DECL_OVERRIDE;
  void paintGL() Q_DECL_OVERRIDE;
  void initializeGL() Q_DECL_OVERRIDE;
  void keyPressEvent(QKeyEvent *Keyevent) Q_DECL_OVERRIDE;

private slots:
  void tick();


private:
  _window *Window;

  _axis Axis;
  _tetrahedron Tetrahedron;
  _cube Cube;
  _gl_widget_ne::_object Object;

  _cono Cono;

  _objeto_ply o_ply;
  _cilindro Cilindro;
  _esfera Esfera;

  _trampa Trampa;

  _trampa Prueba;

  _chess_board Chess;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;
  bool Draw_chess;
  bool Draw_flat;
  bool Draw_smooth;




  //Textura
  bool Draw_texture_no_light;
  bool Draw_texture_flat;
  bool Draw_texture_smooth;

  bool seleccion_luz_1;
  bool seleccion_luz_0;
  int seleccion_material;

  QImage Image;

  float Observer_angle_x;
  float Observer_angle_y;
  float Observer_distance;

  QTimer Timer;
  bool Animation;
};

#endif
