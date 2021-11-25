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


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

 int
    num_filosofos = 6 ,
    id_camarero=6,
    num_procesos  = num_filosofos + 1,
    ETQ_SENTARSE=1,
    ETQ_CogerTENEDOR=9,
    ETQ_SoltarTENEDOR=8,
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
//  int nproc= num_procesos -1;
//   int id_ten_izq = (id+1)              %  nproc, //id. tenedor izq.
//       id_ten_der = (id+nproc-1) % nproc; //id. tenedor der.
// //    if ( id == 0)
//    {
//       dato = id_ten_izq;
//       id_ten_izq=id_ten_der;
//       id_ten_der=dato;
//    }
  while ( true )
  {
    // cout <<"Filósofo " <<id << " solicita camarero" <<endl;
    // // ... solicitar tenedor izquierdo (completar)
    // MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_SENTARSE , MPI_COMM_WORLD);


    // cout <<"Filósofo " <<id << " solicita ten. izq."  <<endl;
    // // ... solicitar tenedor izquierdo (completar)
    // MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_CogerTENEDOR , MPI_COMM_WORLD);
    sleep(rand()%3);
    cout <<"Filósofo " <<id <<" solicita tenedores "  <<endl;
    // ... solicitar tenedor derecho (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_CogerTENEDOR , MPI_COMM_WORLD);
    cout <<"Filósofo " <<id <<" comienza a comer " <<endl ;
    //sleep_for( milliseconds( aleatorio<10,100>() ) );

    cout <<"Filósofo " <<id <<" suelta tenedores "  <<endl;
    // ... soltar el tenedor izquierdo (completar)
    MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_SoltarTENEDOR , MPI_COMM_WORLD);
    // cout<< "Filósofo " <<id <<" suelta ten. der. "  <<endl;
    // // ... soltar el tenedor derecho (completar)
    // MPI_Ssend(&id, 1, MPI_INT, id_ten_der, ETQ_SoltarTENEDOR , MPI_COMM_WORLD);
    cout << "Filosofo " << id << " comienza a pensar" << endl;
    sleep_for( milliseconds( aleatorio<10,100>() ) );


    // cout <<"Filósofo " <<id << " da camarero" <<endl;
    // // ... solicitar tenedor izquierdo (completar)
    // MPI_Ssend(&id, 1, MPI_INT, id_camarero, ETQ_LEVANTARSE , MPI_COMM_WORLD);
 }
}
// ---------------------------------------------------------------------

// void funcion_tenedores( int id )
// {
//   int valor, id_filosofo ;  // valor recibido, identificador del filósofo
//   MPI_Status estado ;       // metadatos de las dos recepciones
 
//   while ( true )
//   {
//      // ...... recibir petición de cualquier filósofo (completar)
//      MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE,9, MPI_COMM_WORLD, &estado);
//      // ...... guardar en 'id_filosofo' el id. del emisor (completar)
//      id_filosofo=estado.MPI_SOURCE;

//      cout <<"Ten. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;

//      // ...... recibir liberación de filósofo 'id_filosofo' (completar)
//      MPI_Recv(&valor, 1, MPI_INT, id_filosofo, 9, MPI_COMM_WORLD, &estado);
//      cout <<"Ten. "<< id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
//   }
// }


void Camarero ()
{
    int tenedores= 5;
    int solicitud;
    MPI_Status estado ;
    int etq_aceptada;
    int espacio = num_filosofos-1;
    int ocupados = 0;
    while(1)
    {
        // etq_aceptada = MPI_ANY_TAG;
        // if (ocupados == num_filosofos -1 )
        // {
        //     etq_aceptada = ETQ_LEVANTARSE;
        // }
        // else if (ocupados == 0)
        // {
        //     etq_aceptada = ETQ_SENTARSE;
        // }
        // MPI_Recv(&solicitud, 1, MPI_INT, MPI_ANY_SOURCE, etq_aceptada, MPI_COMM_WORLD, &estado);
        // if (estado.MPI_TAG == ETQ_LEVANTARSE)
        // {
        //     ocupados--;
        // }
        // else
        // {
        //     ocupados++;
        // }

        // ...... recibir petición de cualquier filósofo (completar)
        cout << "TENEDORES = "<<tenedores<<endl;
        if (tenedores >=2)
        {
            MPI_Recv(&solicitud, 1, MPI_INT, MPI_ANY_SOURCE,ETQ_CogerTENEDOR, MPI_COMM_WORLD, &estado);
            tenedores=tenedores-2;
            //cout << "TENEDORES = "<<tenedores<<endl;
        }
        else
        {
            MPI_Recv(&solicitud, 1, MPI_INT, MPI_ANY_SOURCE,ETQ_SoltarTENEDOR, MPI_COMM_WORLD, &estado);
            //cout << "TENEDORES = "<<tenedores<<endl;
            tenedores=tenedores+2;
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
        //    // ejecutar la función correspondiente a 'id_propio'
        // if ( id_propio % 2 == 0 )          // si es par
        funcion_filosofos( id_propio ); //   es un filósofo
        // else                               // si es impar
        //  funcion_tenedores( id_propio ); //   es un tenedor
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
