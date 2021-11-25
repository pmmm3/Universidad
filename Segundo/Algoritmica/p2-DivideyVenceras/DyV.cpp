#include <iostream>
#include <vector>
#include <list>
#include <utility> // pair

using namespace std;

void ObtenerInversiones(const vector<int> &v, list<pair<int, int>> &inversiones, int inicio, int fin)
{
    // Tu código aquí
    if(fin - inicio + 1 == 1)//Umbral
    {
        
    }
    else
    {
        //Dividir
        int medio = ((inicio + fin  )/2);
        ObtenerInversiones(v,inversiones,inicio,medio);
        ObtenerInversiones(v,inversiones,medio+1,fin);

        //Combinar
        if (v[medio] > v[medio+1])
        {
            inversiones.push_back(make_pair(medio,medio+1));
        }
        
    }
    
}

int main()
{
    list<pair<int, int>> inversiones;
    vector<int> v;

    // Inicializamos el vector de datos
    int n = 25;
    int semilla_aleatoria =1234;
    srand(semilla_aleatoria);

    //Relleno el vector aleatoriamente
    for (int i = 0 ; i < n ; ++i)
    {
        v.push_back((1 + rand() % 50)); //Del 1 al 100
    }
    cout<<endl;
    for (int i = 0 ; i < n ; ++i)
    {
        cout<<v[i]<<"  ";
    }
    // Ejecutamos el algoritmo
    ObtenerInversiones(v, inversiones, 0, v.size() - 1);

    cout << "Listado de inversiones:" << endl;
    for (auto inversion : inversiones)
    {
        cout << "(" << inversion.first << ", " << inversion.second << ")" << endl;
    }
}