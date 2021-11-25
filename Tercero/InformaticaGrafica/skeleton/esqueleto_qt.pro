HEADERS += \
  brazo.h \
  chess_board.h \
  cilindro.h \
  colors.h \
  basic_object3d.h \
  cono.h \
  cube.h \
  esfera.h \
  mango.h \
  object3d.h \
  axis.h \
  object_rot.h \
  objetos_ply.h \
  objetos_ply_rotados.h \
  pelota_punzante.h \
  pincho.h \
  rotacion_v1.h \
  soporte.h \
  soporte_pincho.h \
  techo.h \
  tetrahedron.h \
  glwidget.h \
  trampa.h \
  window.h \
  file_ply_stl.h

SOURCES += \
  basic_object3d.cc \
  brazo.cc \
  chess_board.cc \
  cilindro.cc \
  cono.cc \
  cube.cc \
  esfera.cc \
  mango.cc \
  object3d.cc \
  axis.cc \
  object_rot.cc \
  objetos_ply.cc \
  objetos_ply_rotados.cc \
  pelota_punzante.cc \
  pincho.cc \
  rotacion_v1.cc \
  soporte.cc \
  soporte_pincho.cc \
  techo.cc \
  tetrahedron.cc \
  main.cc \
  glwidget.cc \
  trampa.cc \
  window.cc \
  file_ply_stl.cc


LIBS += -L/usr/X11R6/lib64 -lGL


CONFIG += c++11
QT += widgets
