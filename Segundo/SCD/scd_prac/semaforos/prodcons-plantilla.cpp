#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

//**********************************************************************
// variables compartidas


int pos=0;

const int num_items = 40 ,   // número de items
	       tam_vec   = 10 ;   // tamaño del buffer
int buffer[tam_vec];
//Semaforos lifo
Semaphore mutex1 =1;
Semaphore producir=tam_vec;
Semaphore consumir=0;
//Semaforos fifo
Semaphore mutex2=1;
Semaphore producir_fifo=tam_vec;
Semaphore consumir_fifo=0;
int buffer2[tam_vec];
int ini_fifo=0;
int fin_fifo=0;

unsigned  cont_prod[num_items] = {0}, // contadores de verificación: producidos
          cont_cons[num_items] = {0}; // contadores de verificación: consumidos


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "producido: " << contador << endl << flush ;

   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}
void test_contadores2()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------
//Lifo
void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato() ;
      sem_wait(producir);
      sem_wait(mutex1);
      buffer[pos]=dato;
      pos++;
      sem_signal(mutex1);
      sem_signal(consumir);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      sem_wait(consumir);
      sem_wait(mutex1);
      int dato ;
      pos--;
      dato= buffer[pos];
      
      sem_signal(mutex1);
      sem_signal(producir);
      consumir_dato( dato ) ;

    }
}
//----------------------------------------------------------------------

//Fifo
void  funcion_hebra_productora_fifo(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato() ;
      sem_wait(producir_fifo);
      sem_wait(mutex2);
      buffer2[ini_fifo]=dato;
      ini_fifo=(ini_fifo+1)%tam_vec;
      sem_signal(mutex2);
      sem_signal(consumir_fifo);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora_fifo(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      sem_wait(consumir_fifo);
      sem_wait(mutex2);
      int dato ;
     
      dato= buffer2[fin_fifo];
      fin_fifo=(fin_fifo+1)%tam_vec;
      sem_signal(mutex2);
      sem_signal(producir_fifo);
      consumir_dato( dato ) ;

    }
}

//----------------------------------------------------------------------
int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   //thread hebra_productora ( funcion_hebra_productora_fifo ),
   //     hebra_consumidora( funcion_hebra_consumidora_fifo );
   thread hebra_productora ( funcion_hebra_productora ),
        hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}