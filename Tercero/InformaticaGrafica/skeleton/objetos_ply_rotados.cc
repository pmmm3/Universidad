/**
  * @file objectos_ply.cc
  * @brief Representacion de un objeto con formato tipo .ply
 */
#include "objetos_ply_rotados.h"
#include <fstream> //Para el archivo
#include <file_ply_stl.h> // Para leer tipo ply


_objeto_ply_rotados::_objeto_ply_rotados(string archivo,int cortes)
{
    //vector<float> vertexs_aux;
    //vector<unsigned int> triangulos_aux;
    //string arch = archivo.toStdString();
    _file_ply File_ply;
    if (File_ply.open(archivo))
    {
        File_ply.read(perfil,Triangles);
        std::cout << "Archivo leido correctamente\n";
        Girar(cortes);
    }
    else
        std::cout << "Error ,no se ha abierto el archivo\n";

}

_objeto_ply_rotados::_objeto_ply_rotados(int cortes)
{
    string arch="/home/pablo/IG/Practicas/P2/skeleton/ply_models/ant.ply";
    _file_ply File_ply;
    if (File_ply.open(arch))
    {
        File_ply.read(perfil,Triangles);
        Girar(cortes);
        std::cout << "Archivo leido correctamente\n";
    }
    else
        std::cout << "Error ,no se ha abierto el archivo\n";


}
