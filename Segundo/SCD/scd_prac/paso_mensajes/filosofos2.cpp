//Pablo Mariano Moreno Mancebo 76067676y D1
// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos ( camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------
/*
Cada filosofo pide sentarse, tambien lo hace mediante una unica llamada a una 
funcion de envio de MPI dirigida al camarero,pero en lugar de enviar un unico valor entero
ahora se ha de enviar un vector de entre 1 y 5 valores enteros. Cada filosofo escoge aleatoriamente en cada peticion de sentarse el tamaño dek vector de enteros que envia
El numero de valores que se envia es importante y se escoge aleatoriamente entre 1 y 5 

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
  int tam_vec=rand()%4;//4 por que el 0 no cuenta 
  int vec[tam_vec];
  for(int i = 0 ; i < tam_vec ; i++)
{
	vec[i]=i+1;
}
  while ( true )
  {
    cout <<"Filósofo " <<id << " solicita camarero" <<id_ten_izq <<endl;
    // ... solicitar tenedor izquierdo (completar)
    MPI_Ssend(&vec, tam_vec, MPI_INT, id_camarero, ETQ_SENTARSE , MPI_COMM_WORLD);


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
    MPI_Ssend(&vec, tam_vec, MPI_INT, id_camarero, ETQ_LEVANTARSE , MPI_COMM_WORLD);
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
    
    MPI_Status estado ;
    int etq_aceptada;
    int espacio = num_filosofos-1;
    int ocupados = 0;
  	int enteros;
    while(1)
    {
        etq_aceptada = MPI_ANY_TAG;
        if (ocupados == num_filosofos -1 )
        {
            etq_aceptada = ETQ_LEVANTARSE;
        }
        else if (ocupados == 0)
        {
            etq_aceptada = ETQ_SENTARSE;
        }
	// espera un mensaje de cualquier emisor, sin recibirlo
      MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado );

      // leer el numero de chars del mensaje
      MPI_Get_count( &estado, MPI_INT, &enteros );

      // reservar memoria dinámica para los caracteres (incluyendo 0 al final)
      int * vec = new int[enteros+1] ;
        MPI_Recv(vec, enteros, MPI_INT, estado.MPI_SOURCE, etq_aceptada, MPI_COMM_WORLD, &estado);
	
      

      // imprimir  la cadena recibida
      cout << "\nElementos recibidos : "<<enteros << endl ;
	for (int i = 0 ; i < enteros;i++)
		cout<<vec[i]<<" ";
      
	cout<<endl;
// liberar memoria dinámica ocupada por el buffer
      delete [] vec ;
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
