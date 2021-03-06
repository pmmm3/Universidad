// g++ -std=c++11 -pthread -Wfatal-errors -o fumadores fumadores.cpp HoareMonitor.cpp Semaphore.cpp

#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include "HoareMonitor.cpp"

using namespace std;
using namespace HM;


const int NUMERO_DE_FUMADORES = 3;
//Aleatorio
template<  int min,  int max > int aleatorio()
{
static default_random_engine generador( (random_device())() );
static uniform_int_distribution<int> distribucion_uniforme( min, max );
return distribucion_uniforme( generador );
}

void Fumar( int num_fumador )
{
    // Tiempo aleatorio en fumar
    chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

    // informa de que comienza a fumar
    cout << "Fumador " << num_fumador << " :" << " empieza a fumar " << endl;

    // espera bloqueada mientras fuma 
    this_thread::sleep_for( duracion_fumar );

    // Cuando despierta informa de que ha terminado de fumar
    cout << "Fumador " << num_fumador << " : termina de fumar" << endl;
}


int ProducirIngrediente(){
    //Espera aleatoria de producir un ingrediente aleatorio
    chrono::milliseconds tiempo( aleatorio<20,200>() );
    this_thread::sleep_for(tiempo);

    //Devuelve el ingrediente aleatorio
    return aleatorio<0,(NUMERO_DE_FUMADORES-1)>();
}

//Monitor tipo SU
class Estanco :  
{
    private:
                        
        int mostrador; //mostrador donde se coloca el ingrediente i, si tiene valor -1 está vacío
        CondVar estanquero, fumador[NUMERO_DE_FUMADORES];
    public:
        Estanco(); // Constructor
        void ObtenerIngrediente(int i);//Espera bloqueado a que su ingrediente este disponible -- De los fumadores
        void PonerIngrediente(int i);//Espera aleatoria e ingrediente aleatorio -- Estanquero
        void EsperarRecogida();// Espera bloqueada a que este el monitor libre -- Estanquero
};

// constructor
Estanco::Estanco(){

    mostrador = -1;//El mostrador vacio al principio

    estanquero = newCondVar();
    for(int i = 0; i < 3; i++)
        fumador[i] = newCondVar();
}

void Estanco::ObtenerIngrediente(int i){
  
    if(mostrador != i) // Comprueba si su ingrediente esta en mostrador
    
        fumador[i].wait();//Espera si entra en el if
    
    mostrador = -1; // Vacia el mostrador y muestra que ha usado el ingrediente
    cout << "Ingrediente: " << i << " ha sido usado." << endl;

    estanquero.signal();// se avisa al estanquero que el mostrador está vacío
}

void Estanco::PonerIngrediente(int i){
   
    mostrador = i; // se pone el ingrediente en el mostrador
    cout << "Ingrediente " << i << " puesto en el mostrador." << endl;
    fumador[i].signal(); // se avisa al fumador i que su ingrediente está disponible
}

void Estanco::EsperarRecogida(){
    if(mostrador != -1) // Si el mostrador no esta vacio espera bloqueada
        estanquero.wait();
}

void funcion_estanquero(MRef<Estanco> monitor){
    int ingrediente;
    while(true)
    {
        // el estanquero produce un ingrediente
        ingrediente = ProducirIngrediente();
        // lo coloca en el mostrador
        monitor->PonerIngrediente(ingrediente);
        // espera a que sea recogido el ingrediente del mostrador por un fumador
        monitor->EsperarRecogida();
    }
}

void funcion_fumador(MRef<Estanco> monitor, int i){
    while(true)
    {   
        // el fumador i coge el ingrediente del mostrador
        monitor->ObtenerIngrediente(i);
        //Se pone a fumar durante un tiempo aleatorio
        Fumar(i);
    }
}

int main(){

    // creo el monitor de tipo EstancoSU
    MRef<Estanco> monitor = Create<Estanco>();


    // creo hebra_estanquero y la lanzo
    thread hebra_estanquero(funcion_estanquero, monitor);

    // creo las hebra_fumadores y las lanzo
    thread hebra_fumadores[NUMERO_DE_FUMADORES];
    for(int i = 0; i < NUMERO_DE_FUMADORES; i++)
        hebra_fumadores[i]= thread(funcion_fumador, monitor, i);
    

    //Esperar a que termine el estanquero
    hebra_estanquero.join();
    // esperar a que terminen las hebras de los fumadores
    for(int i = 0; i < NUMERO_DE_FUMADORES; i++)
        hebra_fumadores[i].join();

}
