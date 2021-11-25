#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

int x,y,z;
int v1[8];
int v2[8];

Semaphore process2=0;
Semaphore espera_x=0;
Semaphore process3=0;
Semaphore espera_y=0;

void funcion_hebra_p1()
{
    for (int i = 0 ; i < 8 ; ++i)
    {
        x=v1[i];
        sem_signal(process2);
        sem_wait(espera_x);
    }
}
void funcion_hebra_p2()
{
    for (int i = 0 ; i < 8 ; ++i)
    {
        sem_wait(process2);
        y=v2[i]+x;
        sem_signal(espera_x);
        if(i%2==0)
        {
            sem_signal(process3);
            sem_wait(espera_y);
        }
    }
}
void funcion_hebra_p3()
{
    z=0;
    for (int i = 0 ; i < 4 ; ++i)
    {
        sem_wait(process3);
        z=z+y;
        sem_signal(espera_y);
    }
}
//----------------------------------------------------------------------
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

int main()
{
    
    for (int j = 0 ; j < 8 ; ++j)
    {
        v1[j] =aleatorio<1,5>();
        v2[j] =aleatorio<1,5>();
    }
    cout<<"\nV1: \n";
    for (int j = 0 ; j < 8 ; ++j)
    {
        cout<<v1[j]<<" ";
    }
    cout<<"\nV2: \n";
    for (int j = 0 ; j < 8 ; ++j)
    {
        cout<<v2[j]<<" ";
    }


    thread hebra_p1(funcion_hebra_p1),
           hebra_p2(funcion_hebra_p2),
           hebra_p3(funcion_hebra_p3);
    hebra_p1.join();
    hebra_p2.join();
    hebra_p3.join();
    cout<< "\nValor de z: "<< z<<endl;
    return (0);
}