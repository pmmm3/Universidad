// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------
/*

2 modos (Camarero)
- modo 0  sólo permito que se sienten
- modo 1 funcionamiento normal

* Empieza en modo 0 y cuando hay 4 sentados pasa a modo 1
* Cuando se queda la mesa vacia volvemos al modo 0


*/

#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_filosofos = 5 ,
   id_camarero=10,
   num_procesos  = 2*num_filosofos +1,
   ETQ_SENTARSE=1,
   ETQ_LEVANTARSE=2;


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

// ---------------------------------------------------------------------

void funcion_filosofos( int id )
{
  int nproc= num_procesos -1;
  int id_ten_izq = (id+1)              %  nproc, //id. tenedor izq.
      id_ten_der = (id+nproc-1) % nproc; //id. tenedor der.
//    if ( id == 0)
//    {
//       dato = id_ten_izq;
//       id_ten_izq=id_ten_der;
//       id_ten_der=dato;
//    }
  while ( true )
  {
    cout <<"Filósofo " <<id << " solicita camarero" <<id_ten_izq <<endl;
    // ... solicitar tenedor izquierdo (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_SENTARSE , MPI_COMM_WORLD);


    cout <<"Filósofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
    // ... solicitar tenedor izquierdo (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_ten_izq, 9 , MPI_COMM_WORLD);
    cout <<"Filósofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
    // ... solicitar tenedor derecho (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_ten_der, 9 , MPI_COMM_WORLD);
    cout <<"Filósofo " <<id <<" comienza a comer" <<endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );

    cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
    // ... soltar el tenedor izquierdo (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_ten_izq, 9 , MPI_COMM_WORLD);
    cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
    // ... soltar el tenedor derecho (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_ten_der, 9 , MPI_COMM_WORLD);
    cout << "Filosofo " << id << " comienza a pensar" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );


    cout <<"Filósofo " <<id << " da camarero" <<id_ten_izq <<endl;
    // ... solicitar tenedor izquierdo (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_LEVANTARSE , MPI_COMM_WORLD);
 }
}
// ---------------------------------------------------------------------

void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones
 
  while ( true )
  {
     // ...... recibir petición de cualquier filósofo (completar)
     MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE,9, MPI_COMM_WORLD, &estado);
     // ...... guardar en 'id_filosofo' el id. del emisor (completar)
     id_filosofo=estado.MPI_SOURCE;

     cout <<"Ten. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;

     // ...... recibir liberación de filósofo 'id_filosofo' (completar)
     MPI_Recv(&valor, 1, MPI_INT, id_filosofo, 9, MPI_COMM_WORLD, &estado);
     cout <<"Ten. "<< id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
  }
}


void Camarero ()
{
    int solicitud;
    MPI_Status estado ;
    int etq_aceptada;
    int espacio = num_filosofos-1;
    int ocupados = 0;
    int modo = 0 ;
    while(1)
    {
        etq_aceptada = MPI_ANY_TAG;

        //Modo 0
        if (ocupados < 4 && modo==0)
        {
            cout<<"\nModo 0 activado";
            etq_aceptada = ETQ_LEVANTARSE;
        }
        else
        {
            //Modo normal
            modo=1;
            cout <<"\nModo normal : sitios ocupados = "<<ocupados;
            if (ocupados == num_filosofos -1 )
            {
                etq_aceptada = ETQ_LEVANTARSE;
            }
            else if (ocupados == 0)
            {
                etq_aceptada = ETQ_SENTARSE;
                cout<<"\nSe realiza un cambio de modo\n";
                modo=0;
            }
        }
        



        //Modo normal
        if (ocupados == num_filosofos -1 )
        {
            etq_aceptada = ETQ_LEVANTARSE;
        }
        else if (ocupados == 0)
        {
            etq_aceptada = ETQ_SENTARSE;
        }





        MPI_Recv(&solicitud, 1, MPI_INT, MPI_ANY_SOURCE, etq_aceptada, MPI_COMM_WORLD, &estado);
        if (estado.MPI_TAG == ETQ_LEVANTARSE)
        {
            ocupados--;
        }
        else
        {
            ocupados++;
        }
        
    }
}
// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
       if (id_propio==id_camarero)
       {
           Camarero();
       }
       else
       {
           // ejecutar la función correspondiente a 'id_propio'
        if ( id_propio % 2 == 0 )          // si es par
         funcion_filosofos( id_propio ); //   es un filósofo
        else                               // si es impar
         funcion_tenedores( id_propio ); //   es un tenedor
   }
       }
       
        
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
