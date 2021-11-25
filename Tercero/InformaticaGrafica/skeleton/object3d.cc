/*! \file
 * Copyright Domingo Martín Perandres
 * email: dmartin@ugr.es
 * web: http://calipso.ugr.es/dmartin
 * 2003-2019
 * GPL 3
 */

#include "object3d.h"

using namespace _colors_ne;

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_line()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++)
    {
        //glVertex3fv((GLfloat *) &Vertices[i]);
        //glVertex3f(Triangles[i]._0,)
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
    }
    glEnd();
}

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_fill()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++)
    {
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
    }
    glEnd();
}

/*****************************************************************************/ /**
 *
 *
 *
 *****************************************************************************/

void _object3D::draw_chess()
{
    bool alternar = true;
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++)
    {
        //Cambio de color
        alternar = !alternar;
        //Defino el color
        if (alternar)
            glColor3fv((GLfloat *)&RED);
        else
            glColor3fv((GLfloat *)&GREEN);

        glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
    }
    glEnd();
}

void _object3D::draw_flat_light(bool luz0, bool luz1, int i_material)
{
    if (!normales_calculadas_triangulo)
        calculoNormalesTriangulo();

    //Seleccionar Luz
    if (luz0)
    {
        config_luz0();
        glDisable(GL_LIGHT1);
    }
    else if (luz1)
    {
        config_luz1();
        glDisable(GL_LIGHT2);
    }
    else
    {
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }

    //definir el material
    config_material(i_material);

    //definir el shading
    glShadeModel(GL_FLAT);

    //Habilitar  iluminación
    glEnable(GL_LIGHTING);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (unsigned int i = 0; i < Triangles.size(); i++)
    {
        glNormal3f(NormalesTriangulo[i]._0, NormalesTriangulo[i]._1, NormalesTriangulo[i]._2);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
    }
    glEnd();
}
void _object3D::draw_smooth_light(bool luz0, bool luz1, int i_material)
{
    //Habilitar luz e iluminación
    glEnable(GL_LIGHTING);
    if (!normales_calculadas_vertice)
        calculoNormalesVertice();

    //Seleccionar Luz
    if (luz0)
    {
        config_luz0();
        glDisable(GL_LIGHT1);
    }
    else if (luz1)
    {
        config_luz1();
        glDisable(GL_LIGHT2);
    }
    else
    {
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT2);
    }

    //definir el material
    config_material(i_material);

    //definir el shading
    glShadeModel(GL_SMOOTH);

    //Habilitar  iluminación
    glEnable(GL_LIGHTING);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);

    for (unsigned int i = 0; i < Triangles.size(); i++)
    {
        glNormal3f(NormalesVertice[Triangles[i]._0]._0,
                   NormalesVertice[Triangles[i]._0]._1,
                   NormalesVertice[Triangles[i]._0]._2);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);

        glNormal3f(NormalesVertice[Triangles[i]._1]._0,
                   NormalesVertice[Triangles[i]._1]._1,
                   NormalesVertice[Triangles[i]._1]._2);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);

        glNormal3f(NormalesVertice[Triangles[i]._2]._0,
                   NormalesVertice[Triangles[i]._2]._1,
                   NormalesVertice[Triangles[i]._2]._2);
        glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
    }
    glEnd();
}

_vertex3f _object3D::ProductoVectorial(const _vertex3f &v_a, const _vertex3f &v_b)
{
    _vertex3f producto;
    producto.x = (v_a._1 * v_b._2) - (v_a._2 * v_b._1);
    producto.y = -((v_a._0 * v_b._2) - (v_a._2 * v_b._0));
    producto.z = (v_a._0 * v_b._1) - (v_a._1 * v_b._0);
    return producto;
}
void _object3D::Normalizar(_vertex3f &v)
{
    float modulo = sqrt((v._0 * v._0) + (v._1 * v._1) + (v._2 * v._2));
    v._0 = v._0 / modulo;
    v._1 = v._1 / modulo;
    v._2 = v._2 / modulo;
}

void _object3D::calculoNormalesTriangulo()
{
    NormalesTriangulo.resize(Triangles.size());
    int tam = NormalesTriangulo.size();
    for (int i = 0; i < tam; i++)
    {
        //Calculo v_a y v_b
        _vertex3f v_a = Vertices[Triangles[i]._1] - Vertices[Triangles[i]._0];
        _vertex3f v_b = Vertices[Triangles[i]._2] - Vertices[Triangles[i]._0];

        //Producto Vectorial
        _vertex3f producto = ProductoVectorial(v_a, v_b);
        //Normalizo
        Normalizar(producto);

        NormalesTriangulo[i] = producto;
    }
    normales_calculadas_triangulo = true;
}
void _object3D::calculoNormalesVertice()
{
    //Media de las normales por cada vertice
    if (!normales_calculadas_triangulo)
        calculoNormalesTriangulo();

    NormalesVertice.resize(Vertices.size());
    int tam = NormalesVertice.size();
    //Inicializo a 0
    for (int i = 0; i < tam; i++)
    {
        NormalesVertice[i] = _vertex3f(0.0, 0.0, 0.0);
    }

    //Para cada triangulo añadimos su normal de los tres vertices
    for (int i = 0; i < tam; i++)
    {
        NormalesVertice[Triangles[i]._0] += NormalesTriangulo[i];
        NormalesVertice[Triangles[i]._1] += NormalesTriangulo[i];
        NormalesVertice[Triangles[i]._2] += NormalesTriangulo[i];
    }

    //Normalizamos
    for (int i = 0; i < tam; i++)
    {
        if(NormalesVertice[i].module() > 0)
            Normalizar(NormalesVertice[i]);
    }

    normales_calculadas_vertice = true;
}

void _object3D::config_luz0()
{
    //Luz 0

    //Habilitar 0
    glEnable(GL_LIGHT2);

    //Posición , el ultimo 0 = infinito
    GLfloat p_Light2[4] = {0, 0, 1, 0};
    glLightfv(GL_LIGHT2, GL_POSITION, p_Light2);

    //Ambiental - gris
    //_vertex4f gris = _vertex4f(0.1, 0.1, 0.1, 1);
    _vertex4f gris = _vertex4f(1, 1, 1, 1);
    glLightfv(GL_LIGHT2, GL_AMBIENT, (GLfloat *)&gris);
    //Difusa
    _vertex4f blanco = _vertex4f(1, 1, 1, 1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, (GLfloat *)&blanco);

    //Especular
    glLightfv(GL_LIGHT2, GL_SPECULAR, (GLfloat *)&blanco);
}

void _object3D::update_luz1()
{
    angulo_luz1 += 0.001;
    //angulo_luz1 = int(angulo_luz1) % 360;
    posX = posX * cos(angulo_luz1) + posZ * sin(angulo_luz1);
    posY = 0;
    posX = posX * sin(angulo_luz1) + posZ * cos(angulo_luz1);
}

void _object3D::config_luz1()
{
    //Luz 1

    //Habilitar 1
    glEnable(GL_LIGHT1);

    //Posición , (x,y,z) = (100,100,100)
    GLfloat p_Light1[4] = {posX, posY, posZ, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, p_Light1);

    //Ambiental - magenta oscuro
    _vertex4f magenta_oscuro = _vertex4f(0.1, 0, 0.1, 1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, (GLfloat *)&magenta_oscuro);
    //Difusa - magenta
    _vertex4f magenta = _vertex4f(1, 0, 1, 1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, (GLfloat *)&magenta);

    //Especular
    glLightfv(GL_LIGHT1, GL_SPECULAR, (GLfloat *)&magenta);
}
void _object3D::config_material(int i_material)
{
    //http://devernay.free.fr/cours/opengl/materials.html
    GLfloat esmeralda_a[4] = {0.0215, 0.1745, 0.0215, 1};
    GLfloat esmeralda_d[4] = {0.07568, 0.61424, 0.07568, 1};
    GLfloat esmeralda_s[4] = {0.633, 0.727811, 0.633, 1};

    GLfloat bronze_a[4] = {0.2125, 0.1275, 0.054, 1};
    GLfloat bronze_d[4] = {0.714, 0.4284, 0.18144, 1};
    GLfloat bronze_s[4] = {0.393548, 0.271906, 0.166721, 1};

    GLfloat jade_a[4] = {0.135, 0.2225, 0.1575, 1};
    GLfloat jade_d[4] = {0.54, 0.89, 0.63, 1};
    GLfloat jade_s[4] = {0.316228, 0.316228, 0.316228, 1};

    //Cambio solo la componente difusa
    switch (i_material)
    {
    case 0:
        glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&esmeralda_a);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&esmeralda_d);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&esmeralda_s);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.6);
        break;
    case 1:
        glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&bronze_a);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&bronze_d);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&bronze_s);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.2);
        break;
    case 2:
        glMaterialfv(GL_FRONT, GL_AMBIENT, (GLfloat *)&jade_a);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat *)&jade_d);
        glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *)&jade_s);
        glMaterialf(GL_FRONT, GL_SHININESS, 0.1);
        break;

    default:
        break;
    }
}
void _object3D::draw_texture_no_light()
{
    if ( Coordenadas_textura.size()>0)
    {
        glDisable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);

        glColor4f(1, 1, 1, 1);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        for (unsigned int i = 0; i < Triangles.size(); i++)
        {
            glTexCoord2fv((GLfloat *) & Coordenadas_textura[Triangles[i]._0]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._1]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._2]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
        }
        glEnd();
    }
}
void _object3D::draw_texture_flat(bool luz0, bool luz1, int i_material)
{
    if (Coordenadas_textura.size() > 0)
    {
        if (!normales_calculadas_triangulo)
            calculoNormalesTriangulo();

        //Seleccionar Luz
        if (luz0)
        {
            config_luz0();
            glDisable(GL_LIGHT1);
        }
        else if (luz1)
        {
            config_luz1();
            glDisable(GL_LIGHT2);
        }
        else
        {
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
        }

        //definir el material
        config_material(i_material);

        //definir el shading
        glShadeModel(GL_FLAT);

        //Habilitar  iluminación
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);

        glColor4f(1, 1, 1, 1);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        for (unsigned int i = 0; i < Triangles.size(); i++)
        {
            glNormal3f(NormalesTriangulo[i]._0, NormalesTriangulo[i]._1, NormalesTriangulo[i]._2);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._0]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._1]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._2]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
        }
        glEnd();
    }
}
void _object3D::draw_texture_smooth(bool luz0, bool luz1, int i_material)
{
    if (Coordenadas_textura.size() > 0)
    {
        if (!normales_calculadas_triangulo)
            calculoNormalesTriangulo();

        //Seleccionar Luz
        if (luz0)
        {
            config_luz0();
            glDisable(GL_LIGHT1);
        }
        else if (luz1)
        {
            config_luz1();
            glDisable(GL_LIGHT2);
        }
        else
        {
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
        }

        //definir el material
        config_material(i_material);

        //definir el shading
        glShadeModel(GL_SMOOTH);

        //Habilitar  iluminación
        glEnable(GL_LIGHTING);
        glEnable(GL_TEXTURE_2D);
        glColor4f(1, 1, 1, 1);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_TRIANGLES);
        for (unsigned int i = 0; i < Triangles.size(); i++)
        {
            glNormal3f(NormalesTriangulo[i]._0, NormalesTriangulo[i]._1, NormalesTriangulo[i]._2);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._0]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].x]);
            glNormal3f(NormalesTriangulo[i]._0, NormalesTriangulo[i]._1, NormalesTriangulo[i]._2);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._1]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].y]);
            glNormal3f(NormalesTriangulo[i]._0, NormalesTriangulo[i]._1, NormalesTriangulo[i]._2);
            glTexCoord2fv((GLfloat *)&Coordenadas_textura[Triangles[i]._2]);
            glVertex3fv((GLfloat *)&Vertices[Triangles[i].z]);
        }
        glEnd();
    }
}
