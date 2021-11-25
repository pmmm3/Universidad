
//	g++ -O2 -o ejecutable codigo.cpp 
//	./ejecutable data.txt
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;
struct Alumno
{
    string id;
    int altura;
    Alumno() : id ("nulo"),altura(0){}
    Alumno(string id, int altura): id(id), altura(altura){}

};

Alumno CrearAlumno(const string &datos)
{
    istringstream iss(datos);
    Alumno alumno;
    iss>>alumno.id >> alumno.altura;
    return alumno;
}
bool LeerDatos(const char*fichero, vector<Alumno> &alumnos,vector<int>&esquis ,int &N, int &M)
{
    alumnos.clear();
    esquis.clear();
    string linea;
    bool parar=false;

    //Abro el fichero
    ifstream f(fichero);
    if (!f)
    {
        return false;
    }

    //Busqueda de comienzo de datos
    while(f && !parar)
    {
        getline(f,linea);
        parar = (linea == "NUM_ALUMNOS");
    }
    parar = false;
    
    //Numero de alumnos
    getline(f,linea);
    N = stoi(linea);
    //Leo cada alumno
    int i=0;
    while (f && i < N)
    {
        getline(f,linea);
        alumnos.push_back(CrearAlumno(linea));
        ++i;
    }

    //Numero de esquis
    while(f && !parar)
    {
        getline(f,linea);
        parar = (linea == "NUM_ESQUIS");
    }
    parar = false;

    getline(f,linea);
    M = stoi(linea);
    
    //Leo cada alumno
    i=0;
    while (f && i < M)
    {
        getline(f,linea);
        esquis.push_back(stoi(linea));
        i++;
    }
    return true;
}

template <class T>
void eliminar_pos_vec(int indice, vector<T> &v) // O(n)
{
    int tam = v.size();
    if (indice < tam && indice >=0)
    {
        for(int i = indice; i < tam-1 ; i++)
            v[i]=v[i+1];
        v.pop_back();
    }
    else
    {
        cout<<"error";
    }
    
}
vector<pair<string,int>> greedy(vector<Alumno> alumnos,vector<int> esquis)
{
    vector<pair<string,int>>asignacion;
    double error_cuadratico =0;

    int num_alumnos=alumnos.size();
    
    //Borramos el vector
    asignacion.clear();

    int it=0;
    while (it<num_alumnos)
    {
        int pos_alumno,pos_talla=-1;

        //Comprobamos si hay solución posible con los esquis actuales
        int ini=-1;
        int k=0;
        while (k<=esquis.size() && ini==-1)
        {
            if (esquis[k]>=alumnos[0].altura){
               ini=k;
            }
            k++;
        }
        //Si no encontramos esquis disponibles se termina el programa
        if (ini ==-1)
        {
            cout<<"No se ha encontrado solución."<<endl;
            asignacion.clear();
            return asignacion;
        }
        double minimo = alumnos[0].altura - esquis[ini];

        //Busco el esqui con el cual la altura - la talla al cuadrado sea minimo entre los esquis no descartados
        double aux;
        pos_talla=ini;


        for (int i = ini+1; i < esquis.size(); i++)
        {
            if (alumnos[0].altura- esquis[i] >= 0) // Comparo con una talla superior a la altura
            {
                aux = alumnos[0].altura - esquis[i];
                if (aux < minimo && minimo != aux) // Comparo con el que minimo actual y actualizo variable
                {
                    minimo=aux;
                    pos_talla=i;
                }
            }
        }
        //Guardo la id del alumno junto a la talla que se le ha asignado
        asignacion.push_back(make_pair(alumnos[0].id,esquis[pos_talla]));
        //Elimino al alumno y la talla de sus respectivos vectores
        eliminar_pos_vec(0,alumnos);
        eliminar_pos_vec(pos_talla,esquis);

        //Acumulo el error 
        error_cuadratico+= pow(minimo,2);
        //Incremento el numero de alumnos con esquis asignados
        it++;

    }

    //Calculo del error cuadratico medio
    string msg= "error_medio= " + to_string(error_cuadratico/num_alumnos);
    cout <<msg<<endl;
    return asignacion;
}


int main(int argc, const char *argv[])
{
    if(argc !=2)
    {
        cerr <<"Argumentos incorrectos."<<endl;
        return 1;
    }

    vector<int> esquis;
    vector<Alumno> alumnos;
    int M,N;

    if(!LeerDatos(argv[1],alumnos,esquis,N,M))
    {
        cerr <<"Error en la lectura."<<endl;
        return 2;
    }
    cout<<"Alumnos leidos:"<<endl;
    for (int i = 0 ; i < N; i++)
    {
        cout << alumnos[i].id <<" "<< alumnos[i].altura<<endl;
    }
    cout<<"Esquis que proporciona la tienda:"<<endl;
    for (int i = 0 ; i < M; i++)
    {
        cout << esquis[i]<<endl;
    }

    auto asignacion=greedy(alumnos,esquis);
    for (int i = 0 ; i < asignacion.size(); i++)
    {
        cout<< asignacion[i].first << " " << asignacion[i].second<<endl;
    }
}
