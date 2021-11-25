#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h> 
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;
const int num_fumadores=3;
class Estanco: public HoareMonitor
{
    private:
        CondVar mostrador,clientes[num_fumadores];
        int ingrediente_mostrador;

    public:
        Estanco()
        {
            for (int i = 0 ; i < num_fumadores ; i++){
                clientes[i]=newCondVar();
            }
            mostrador=newCondVar();
            ingrediente_mostrador=-1;
        }
        void ponerIngrediente(int x)
        {
            ingrediente_mostrador=x;
            cout << "\nIngrediente " << x << " en el mostrador";
            cout << "\nMostrador lleno";
            clientes[x].signal();
            
        }
        void ObtenerIngrediente(int i)
        {
            if(ingrediente_mostrador != i)
            {
                clientes[i].wait();
            }
            cout<<"\nSe retira el ingrediente "<<i<<" del mostrador.";
            cout<<"\nMostrador Vacio";
            ingrediente_mostrador=-1;
            mostrador.signal();
        }
        void esperarRecogidaIngrediente()
        {
            if (ingrediente_mostrador != -1)
                mostrador.wait();
        }

};


// función que simula la acción de fumar, como un retardo aleatorio de la hebra.
// recibe como parámetro el numero de fumador
void fumar( int num_fum )
{
    cout << "Fumador número " << num_fum << ": comienza a fumar." << endl;
    sleep(rand()%3);
    cout << "Fumador número " << num_fum << ": termina de fumar." << endl;
}

int ProducirIngrediente()
{
    cout<<"\nProduciendo ingredientes..."<<endl;
    sleep(rand()%3);
    return (rand()%3);
}

void funcion_hebra_estanquero( MRef<Estanco> estanco)
{
    while (1)
    {
        int ingrediente = ProducirIngrediente();
        estanco->ponerIngrediente(ingrediente);
        //cout <<"\nEn el mostrador esta el ingrediente: "<<ingrediente;
        //ingrediente_mostrador=ingrediente;
        //Se le hace un signal al fumador que necesite ese ingrediente
        //sem_signal(ingr_disp[ingrediente_mostrador]);
        estanco->esperarRecogidaIngrediente();
    }
    
}

void funcion_hebra_fumador(MRef<Estanco> estanco,int num_fum )
{
    while (1)
    {
        estanco->ObtenerIngrediente(num_fum);
        fumar(num_fum);
    }
    
}
int main()
{
    MRef<Estanco> estanco = Create<Estanco>();
    thread hebra_estanco(funcion_hebra_estanquero,estanco);
    
    thread clientes[3];
    for (int i=0 ; i < 3 ; ++i)
        clientes[i]=thread(funcion_hebra_fumador,estanco,i);
    
    hebra_estanco.join();
    for (int i=0 ; i < 3 ; ++i)
        clientes[i].join();
    return 0;
}