/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "glwidget.h"
#include "window.h"
#include <QImageReader>

using namespace std;
using namespace _gl_widget_ne;
using namespace _colors_ne;

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

_gl_widget::_gl_widget(_window *Window1) : Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

/*****************************************************************************/ /**
 * Evento tecla pulsada
 *
 *
 *
 *****************************************************************************/

void _gl_widget::keyPressEvent(QKeyEvent *Keyevent)
{
  switch (Keyevent->key())
  {
  case Qt::Key_1:
    Object = OBJECT_TETRAHEDRON;
    break;
  case Qt::Key_2:
    Object = OBJECT_CUBE;
    break;
  case Qt::Key_3:
    Object = OBJECT_PLY;
    break;
  case Qt::Key_4:
    Object = OBJECT_CONO;
    break;
  case Qt::Key_5:
    Object = OBJECT_CILINDRO;
    break;
  case Qt::Key_6:
    Object = OBJECT_ESFERA;
    break;
  case Qt::Key_7:
    Object = OBJECT_TRAMPA;
    break;
  case Qt::Key_8:
    Object = OBJECT_CHESS;
    break;

  case Qt::Key_Q:
    Trampa.increase_alpha_brazo();
    break;
  case Qt::Key_W:
    Trampa.decrease_alpha_brazo();
    break;
  case Qt::Key_S:
    Trampa.subir_soporte();
    break;
  case Qt::Key_D:
    Trampa.bajar_soporte();
    break;
  case Qt::Key_Z:
    Trampa.increase_alpha_pincho();
    break;
  case Qt::Key_X:
    Trampa.decrease_alpha_pincho();
    break;
  case Qt::Key_E:
    Trampa.increase_speed_brazo();
    break;
  case Qt::Key_R:
    Trampa.decrease_speed_brazo();
    break;
  case Qt::Key_T:
    Trampa.subir_v_soporte();
    break;
  case Qt::Key_Y:
    Trampa.bajar_v_soporte();
    break;
  case Qt::Key_U:
    Trampa.increase_speed_pincho();
    break;
  case Qt::Key_I:
    Trampa.decrease_speed_pincho();
    break;
  case Qt::Key_V:
    Trampa.increase_alpha_pelota();
    break;
  case Qt::Key_B:
    Trampa.decrease_alpha_pelota();
    break;
  case Qt::Key_H:
    Trampa.increase_speed_pelota();
    break;
  case Qt::Key_N:
    Trampa.decrease_speed_pelota();
    break;
  case Qt::Key_A:
    animation();
    break;

  case Qt::Key_J:
    //Luz 0
    seleccion_luz_0 = !seleccion_luz_0;
    seleccion_luz_1 = false;
    if (!seleccion_luz_0)
      glDisable(GL_LIGHTING);
    break;
  case Qt::Key_K:
    //Luz 1
    seleccion_luz_1 = !seleccion_luz_1;
    seleccion_luz_0 = false;
    if (!seleccion_luz_1)
      glDisable(GL_LIGHTING);
    break;
  case Qt::Key_M:
    //Material
    seleccion_material = (seleccion_material + 1) % 3;
    break;
  case Qt::Key_P:
    Draw_point = !Draw_point;
    break;
  case Qt::Key_L:
    Draw_line = !Draw_line;
    break;
  case Qt::Key_F1:
    Draw_fill = !Draw_fill;
    glDisable(GL_LIGHTING);
    //Añado esta linea para que no esten las dos activas a la vez dado que las dos rellenan
    Draw_chess = false;
    Draw_smooth = false;
    Draw_flat = false;
    break;

  case Qt::Key_F2:
    Draw_chess = !Draw_chess;
    glDisable(GL_LIGHTING);

    //Añado esta linea para que no esten las dos activas a la vez dado que las dos rellenan
    Draw_fill = false;
    Draw_flat = false;
    Draw_smooth = false;
    break;

  case Qt::Key_F3:
    Draw_flat = !Draw_flat;
    Draw_fill = false;
    Draw_smooth = false;
    Draw_chess = false;
    break;
  case Qt::Key_F4:
    Draw_smooth = !Draw_smooth;
    Draw_flat = false;
    Draw_fill = false;
    Draw_chess = false;
    break;

  case Qt::Key_F5:
      Draw_texture_no_light=!Draw_texture_no_light;
      break;

  case Qt::Key_F6:
    Draw_texture_flat = !Draw_texture_flat;
    break;
  case Qt::Key_F7:
    Draw_texture_smooth= !Draw_texture_smooth;
    break;

  case Qt::Key_Left:
    Observer_angle_y -= ANGLE_STEP;
    break;
  case Qt::Key_Right:
    Observer_angle_y += ANGLE_STEP;
    break;
  case Qt::Key_Up:
    Observer_angle_x -= ANGLE_STEP;
    break;
  case Qt::Key_Down:
    Observer_angle_x += ANGLE_STEP;
    break;
  case Qt::Key_PageUp:
    Observer_distance *= 1.2;
    break;
  case Qt::Key_PageDown:
    Observer_distance /= 1.2;
    break;
  }

  update();
}

/*****************************************************************************/ /**
 * Limpiar ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::clear_window()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/*****************************************************************************/ /**
 * Funcion para definir la transformación de proyeccion
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_projection()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
  // Front_plane>0  Back_plane>PlanoDelantero)
  glFrustum(X_MIN, X_MAX, Y_MIN, Y_MAX, FRONT_PLANE_PERSPECTIVE, BACK_PLANE_PERSPECTIVE);
}

/*****************************************************************************/ /**
 * Funcion para definir la transformación de vista (posicionar la camara)
 *
 *
 *
 *****************************************************************************/

void _gl_widget::change_observer()
{
  // posicion del observador
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -Observer_distance);
  glRotatef(Observer_angle_x, 1, 0, 0);
  glRotatef(Observer_angle_y, 0, 1, 0);
}

/*****************************************************************************/ /**
 * Funcion que dibuja los objetos
 *
 *
 *
 *****************************************************************************/

void _gl_widget::draw_objects()
{
  Axis.draw_line();

  if (Draw_point)
  {
    glPointSize(5);
    glColor3fv((GLfloat *)&BLACK);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_point();
      break;
    case OBJECT_CUBE:
      Cube.draw_point();
      break;
    case OBJECT_PLY:
      o_ply.draw_point();
      break;
    case OBJECT_CONO:
      Cono.draw_point();
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_point();
      break;
    case OBJECT_ESFERA:
      Esfera.draw_point();
      break;
    case OBJECT_CHESS:
      Chess.draw_point();
      break;
    default:
      break;
    }
  }

  if (Draw_line)
  {
    glLineWidth(3);
    glColor3fv((GLfloat *)&MAGENTA);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_line();
      break;
    case OBJECT_CUBE:
      Cube.draw_line();
      break;
    case OBJECT_PLY:
      o_ply.draw_line();
      break;
    case OBJECT_CONO:
      Cono.draw_line();
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_line();
      break;
    case OBJECT_ESFERA:
      Esfera.draw_line();
      break;
    case OBJECT_TRAMPA:
      Trampa.draw_line();
      break;
    case OBJECT_CHESS:
      Chess.draw_line();
      break;

    default:
      break;
    }
  }

  if (Draw_fill)
  {

    glColor3fv((GLfloat *)&BLUE);
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_fill();
      break;
    case OBJECT_CUBE:
      Cube.draw_fill();
      break;
    case OBJECT_PLY:
      o_ply.draw_fill();
      break;
    case OBJECT_CONO:
      Cono.draw_fill();
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_fill();
      break;
    case OBJECT_ESFERA:
      Esfera.draw_fill();
      break;
    case OBJECT_CHESS:
      Chess.draw_fill();
      break;
    default:
      break;
    }
  }

  if (Draw_chess)
  {

    //glColor3fv((GLfloat *) &RED);
    //Dado que voy a cambiar el color
    //y tengo que hacerlo a a la hora de pintar para que vaya cambiando
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_chess();
      break;
    case OBJECT_CUBE:
      Cube.draw_chess();
      break;
    case OBJECT_PLY:
      o_ply.draw_chess();
      break;
    case OBJECT_CONO:
      Cono.draw_chess();
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_chess();
      break;
    case OBJECT_ESFERA:
      Esfera.draw_chess();
      break;
    case OBJECT_CHESS:
      Chess.draw_chess();
      break;
    default:
      break;
    }
  }
  if (Draw_flat)
  {
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_flat_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_CUBE:
      Cube.draw_flat_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_PLY:
      o_ply.draw_flat_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_CONO:
      Cono.draw_flat_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_flat_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_ESFERA:
      Esfera.draw_flat_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    default:
      break;
    }
  }
  if (Draw_smooth)
  {
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_smooth_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_CUBE:
      Cube.draw_smooth_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_PLY:
      o_ply.draw_smooth_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_CONO:
      Cono.draw_smooth_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_smooth_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    case OBJECT_ESFERA:
      Esfera.draw_smooth_light(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    default:
      break;
    }
  }
  if (Draw_texture_no_light)
  {
    if(Image.isNull())
      cargar_textura();
    switch (Object)
    {
    case OBJECT_TETRAHEDRON:
      Tetrahedron.draw_texture_no_light();
      break;
    case OBJECT_CUBE:
      Cube.draw_texture_no_light();
      break;
    case OBJECT_PLY:
      o_ply.draw_texture_no_light();
      break;
    case OBJECT_CONO:
      Cono.draw_texture_no_light();
      break;
    case OBJECT_CILINDRO:
      Cilindro.draw_texture_no_light();
      break;
    case OBJECT_ESFERA:
      Esfera.draw_texture_no_light();
      break;

    case OBJECT_CHESS:
        Chess.draw_texture_no_light();
        break;
    default:
      break;
    }
  }
  if (Draw_texture_flat)
  {
    if (Image.isNull())
      cargar_textura();
    switch (Object)
    {
    case OBJECT_CHESS:
      Chess.draw_texture_flat(seleccion_luz_0, seleccion_luz_1, seleccion_material);
      break;
    default:
      break;
    }
  }
  if (Draw_texture_smooth)
  {
    if (Image.isNull())
       cargar_textura();
     switch (Object)
     {
       case OBJECT_CHESS:
         Chess.draw_texture_smooth(seleccion_luz_0, seleccion_luz_1, seleccion_material);
        break;
       default:
        break;
     }
  }
}
/*****************************************************************************/ /**
 * Evento de dibujado
 *
 *
 *
 *****************************************************************************/

void _gl_widget::paintGL()
{
  clear_window();
  change_projection();
  change_observer();
  draw_objects();
}

/*****************************************************************************/ /**
 * Evento de cambio de tamaño de la ventana
 *
 *
 *
 *****************************************************************************/

void _gl_widget::resizeGL(int Width1, int Height1)
{
  glViewport(0, 0, Width1, Height1);
}

/*****************************************************************************/ /**
 * Inicialización de OpenGL
 *
 *
 *
 *****************************************************************************/

void _gl_widget::initializeGL()
{
  const GLubyte *strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1')
  {
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
  }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";

  int Max_texture_size = 0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cerr << "Max texture size: " << Max_texture_size << "\n";

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glEnable(GL_DEPTH_TEST);
  ;

  Observer_angle_x = 0;
  Observer_angle_y = 0;
  Observer_distance = DEFAULT_DISTANCE;

  Draw_point = true;
  Draw_line = false;
  Draw_fill = false;
  Draw_chess = false;
  Draw_flat = false;
  Draw_smooth = false;


  Draw_texture_no_light=true;
  Draw_texture_flat = false;
  Draw_texture_smooth = false;

  seleccion_luz_1 = false;
  seleccion_luz_0 = false;
  seleccion_material = 0;

  Object = _gl_widget_ne::OBJECT_TETRAHEDRON;

  Timer.setInterval(0);
  connect(&Timer, SIGNAL(timeout()), this, SLOT(tick()));
  Animation = false;
}

void _gl_widget::tick()
{
  //grado Actualización jerarquico
  Trampa.update_alpha_brazo();
  Trampa.update_alpha_pelota();
  Trampa.update_d_soporte();
  Trampa.update_aplha_pincho();


  //La luz LIGHT1 se mueve al rededor de los objetos
  Tetrahedron.update_luz1();
  Cube.update_luz1();
  Cono.update_luz1();
  o_ply.update_luz1();
  Cilindro.update_luz1();
  Esfera.update_luz1();
  //Trampa.update_luz1();
  Chess.update_luz1();

  //update
  update();
}
void _gl_widget::animation()
{
  Animation = !Animation;
  if (Animation)
  {
    Timer.start();
  }
  else
  {
    Timer.stop();
  }
}
void _gl_widget::cargar_textura(string archivo_textura)
{
  // Code for reading an image

  QString File_name(archivo_textura.c_str());
  //QString File_name = QString::fromStdString(archivo_textura);
  QImageReader Reader(File_name);
  Reader.setAutoTransform(true);
  Image = Reader.read();

  if (Image.isNull())
  {
    cerr << "No se puede cargar la textura : " << archivo_textura << endl;
    exit(-1);
  }
  Image = Image.mirrored();
  Image = Image.convertToFormat(QImage::Format_RGB888);
  // Code to control the application of the texture
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  // Code to pass the image to OpenGL to form a texture 2D
  glTexImage2D(GL_TEXTURE_2D, 0, 3, Image.width(), Image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, Image.bits());
}
