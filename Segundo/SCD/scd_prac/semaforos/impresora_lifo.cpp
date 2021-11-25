#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"

using namespace std;
using namespace SEM;

//**********************************************************************
// variables compartidas

const int num_items = 40, // número de items
    tam_vec = 10;         // tamaño del buffer
int posicion = 0;

unsigned cont_prod[num_items] = {0}, // contadores de verificación: producidos
    cont_cons[num_items] = {0};      // contadores de verificación: consumidos

Semaphore puede_producir = tam_vec,
          puede_consumir = 0,
          impresora = 0,
          productor = 0,
          exclusionMutua = 1;

int v_intermedio[tam_vec];

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato()
{
   static int contador = 0;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 100>()));

   // cout << "producido: " << contador << endl
   //      << flush;

   cont_prod[contador]++;
   return contador++;
}
//----------------------------------------------------------------------

void consumir_dato(unsigned dato)
{
   assert(dato < num_items);
   cont_cons[dato]++;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 100>()));

   // cout << "                  consumido: " << dato << endl;
}

//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true;
   cout << "comprobando contadores ....";
   for (unsigned i = 0; i < num_items; i++)
   {
      if (cont_prod[i] != 1)
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl;
         ok = false;
      }
      if (cont_cons[i] != 1)
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl;
         ok = false;
      }
   }
   if (ok)
      cout << endl
           << flush << "solución (aparentemente) correcta." << endl
           << flush;
}

//----------------------------------------------------------------------

void funcion_hebra_impresora()
{
   while (true)
   {
      // Esperar
      impresora.sem_wait();
      // Mostrar los elementos actuales
      sem_wait(exclusionMutua);
      cout << "## Elementos " << posicion << endl;
      char c;
      cin >> c;
      sem_signal(exclusionMutua);
      // Avisar al productor
      productor.sem_signal();
   }
}

void funcion_hebra_productora()
{
   for (unsigned i = 0; i < num_items; i++)
   {
      int dato = producir_dato();

      sem_wait(puede_producir);
      sem_wait(exclusionMutua);

      v_intermedio[posicion] = dato;
      posicion++;

      cout << "producido: " << dato << endl
           << flush;

      sem_signal(exclusionMutua);
      sem_signal(puede_consumir);

      if (dato % 5 == 0)
      {
         impresora.sem_signal();
         productor.sem_wait();
      }
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora()
{

   for (unsigned i = 0; i < num_items; i++)
   {
      int dato;
      sem_wait(puede_consumir);
      sem_wait(exclusionMutua);

      posicion--;
      dato = v_intermedio[posicion];

      cout << "                  consumido: " << dato << endl;

      sem_signal(exclusionMutua);
      sem_signal(puede_producir);
      consumir_dato(dato);
   }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush;

   thread hebra_productora(funcion_hebra_productora),
       hebra_consumidora(funcion_hebra_consumidora),
       hebra_impresora(funcion_hebra_impresora);

   hebra_productora.join();
   hebra_consumidora.join();

   test_contadores();
   hebra_impresora.join();
}
