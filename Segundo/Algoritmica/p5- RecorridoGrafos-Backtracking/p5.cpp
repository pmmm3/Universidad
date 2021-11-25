/*
    Compilar y ejecutar: g++ -O2 -o ejecutable p5.cpp; ./ejecutable
*/
/*
Dado un conjunto de n enteros, necesitamos decidir si puede ser descompuesto en dos
subconjuntos disjuntos cuyos elementos sumen la misma cantidad. Resolver el problema
mediante una técnica de exploración en grafos.

*/

#include <iostream>
#include <vector>

using namespace std;

const int SIN_DECIDIR = 0;
const int TODOS_PROBADOS = 3;

bool SonIguales(const vector<int> &secuencia, const vector<int> &sol)
{
    int s1 = 0, s2 = 0;
    for (int i = 0; i < secuencia.size(); i++)
    {
        (sol[i] == 1) ? s1 += secuencia[i] : s2 += secuencia[i];
    }
    return (s1 == s2);
}

vector<int> Backtracking(const vector<int> &secuencia)
{
    // En el vector sol[i] =
    //  0 -> No se ha elegido conjunto
    //  1 -> Se ha metido en el conjunto 1
    //  2 -> Se ha metido en el conjunto 2
    //  3 -> Se ha probado tanto en el conjunto 1 como en el el 2
    vector<int> sol(secuencia.size(), SIN_DECIDIR);
    int pos = 0;
    while (pos >= 0)
    {
        sol[pos]++;
        if (sol[pos] == TODOS_PROBADOS)
        {
            // Si se han probado todas las opciones, realizamos la vuelta atrás
            sol[pos] = SIN_DECIDIR;
            pos--;
        }
        else
        {
            // Si estamos en la última posición, se trata de una posible solución
            if (pos == secuencia.size() - 1)
            {
                // Si hemos alcanzado el objetivo, devolvemos la solución,
                // sino, continuamos probando con el siguiente valor
                if (SonIguales(secuencia, sol))
                {
                    return sol;
                }
            }
            else
            {
                // Si no es solución, pasamos a probar con el siguiente valor
                pos++;
            }
        }
    }
    // No hemos encontrado solución, vector vacío
    return vector<int>();
}

void pintar(const vector<int> &secuencia,string aux="v")
{
    if(secuencia.empty())
    {
        cout<<aux+": No se ha encontrado solucion."<<endl;
    }
    else{
        for (int i = 0; i < secuencia.size(); i++)
            cout << aux+"[" << i << "] = " << secuencia[i] << endl;
        cout << endl;
    }
   
}
int main()
{
    int aux;
    int opc;
    vector<int> v_aux;
    vector<int> sol ;
    cout<<"Seleccionar opcion: \n\t1-Pruebas variadas\n\t2-Introducir secuencia"<<endl;
    cin >>opc;
    while (opc != 1 && opc != 2)
    {
        cout<<"Seleccionar opcion: \n\t1-Pruebas variadas\n\t2-Introducir secuencia"<<endl;
        cin >>opc;
    }
    switch (opc)
    {
        case 1:
            cout << "\nSolución 1:" << endl;
            v_aux={5, -3, 0, 2};
            pintar(v_aux,"v1");
            sol= Backtracking(v_aux);
            pintar(sol,"sol");

            cout << "Solución 2:" << endl;
            v_aux={5, 3, 0, 2};
            pintar(v_aux,"v2");
            sol = Backtracking(v_aux);
            pintar(sol,"sol");

            cout << "Solución 3:" << endl;
            v_aux={5, 4, 0, 2};
            pintar(v_aux,"v3");
            sol = Backtracking(v_aux);
            pintar(sol,"sol");
            break;
        case 2:
            v_aux.clear();
            cout <<"Introduce cantidad de numeros a leer: ";
            cin >> aux;
            cout <<endl;
            for (int i = 0 ; i < aux;i++)
            {
                cout<<"Introduce numero: ";
                cin>>opc;
                v_aux.push_back(opc);
                cout<<endl;
            }

            cout << "\nSolución :" << endl;
            pintar(v_aux,"v1");
            sol= Backtracking(v_aux);
            pintar(sol,"sol");
            break;
    }
    return 0;
}