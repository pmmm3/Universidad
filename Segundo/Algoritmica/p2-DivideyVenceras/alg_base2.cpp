#include <iostream>
#include <vector>
#include <cstdlib> // Para el random
using namespace std;

int main()
{
    vector<int> v;
    int n = 25;
    int semilla_aleatoria =1234;
    srand(semilla_aleatoria);

    //Relleno el vector aleatoriamente
    for (int i = 0 ; i < n ; ++i)
    {
        v.push_back((1 + rand() % 50)); //Del 1 al 100
    }

    //ALgoritmo
    int inversiones=0;
    //Para la solucion voy a hacer un vector de pairs
    vector<pair<int,int>> sol;
    for(int i = 0 ; i < n -1 ; i++)
    {
        if (v[i]>v[i+1])
        {
            inversiones++;
                sol.push_back(make_pair(i,i+1));
        }
    }




    //Mostrar las soluciones
    cout<<endl;
    for (int i = 0 ; i < n ; ++i)
    {
        cout<<v[i]<<"  ";
    }
    cout <<"\nPosibles inversiones = "<<inversiones;
    for (int i = 0 ; i < inversiones; ++i)
    {
        cout <<"\n"<<sol[i].first  << "  -  "<< sol[i].second ;
    }
    cout << endl;
    return 0;
}