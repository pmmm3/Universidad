#include <iostream>
#include <thread>
#include <chrono>
#include<mutex>
#include<random>
#include <unistd.h> //Para el sleep()
#include <stdlib.h> // necesario para random(), srandom()
#include <time.h> // necesario para time()
#include "Semaphore.h" // incluye tipo 'Semaphore'

using namespace std ; // permite acortar la notación (abc en lugar de std::abc)
using namespace SEM ; // permite usar 'Semaphore' en lugar de 'SEM::Semaphore'


Semaphore mostr_vacio =1;//{ 1 si mostrador vacío, 0 si ocupado }
Semaphore ingr_disp[3] = {0,0,0};//{ 1 si el ingrediente i esta disponible en el mostrador, 0 si no}
Semaphore terminar_fumar = 1;
int ingrediente_mostrador;
//*****************************************************************************
//*****************************************************************************
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}
// función que simula la acción de fumar, como un retardo aleatorio de la hebra.
// recibe como parámetro el numero de fumador
void fumar( int num_fum )
{
    cout << "Fumador número " << num_fum << ": comienza a fumar." << endl;
    this_thread::sleep_for( chrono::milliseconds( aleatorio<50,200>() ));
    cout << "Fumador número " << num_fum << ": termina de fumar." << endl;
}

int Producir()
{
    cout<<"\nProduciendo ingredientes..."<<endl;
    sleep(rand()%3);
    return (aleatorio<0,2>());
}

//*****************************************************************************
//*****************************************************************************
void funcion_hebra_estanquero( )
{
    while (1)
    {
        sem_wait(terminar_fumar);
        int ingrediente = Producir();
        sem_wait(mostr_vacio);
        cout <<"\nEn el mostrador esta el ingrediente: "<<ingrediente;
        ingrediente_mostrador=ingrediente;
        //Se le hace un signal al fumador que necesite ese ingrediente
        sem_signal(ingr_disp[ingrediente_mostrador]);

    }
    
}

void funcion_hebra_fumador( int num_fum )
{
    while (1)
    {
        sem_wait(ingr_disp[num_fum]);//Espera a su ingrediente
        cout<<"\nSe retira el ingrediente "<<num_fum<<" del mostrador.";
        int elemento = ingrediente_mostrador;
        ingrediente_mostrador=-1;
        sem_signal(mostr_vacio);
        fumar(elemento);
        sem_signal(terminar_fumar);
    }
    
}
int main()
{
    thread estanco(funcion_hebra_estanquero);
    
    thread clientes[3];
    for (int i=0 ; i < 3 ; ++i)
        clientes[i]=thread(funcion_hebra_fumador,i);
    
    estanco.join();
    for (int i=0 ; i < 3 ; ++i)
        clientes[i].join();
    return 0;
}