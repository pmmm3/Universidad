
#include <iostream>
#include <iomanip>
#include <random>
#include <thread>
#include "HoareMonitor.cpp"

using namespace std;
using namespace HM;

const int n=6;//Numero de clientes

//Aleatorio
template<  int min,  int max > int aleatorio()
{
static default_random_engine generador( (random_device())() );
static uniform_int_distribution<int> distribucion_uniforme( min, max );
return distribucion_uniforme( generador );
}

void Pelar( )
{
    // Tiempo aleatorio en pelar
    chrono::milliseconds duracion_pelar( aleatorio<20,200>() );

    // informa de que comienza a pelar
    cout << "Cliente  durmiendose en la silla para pelarse " << endl;

    // espera bloqueada mientras se pela 
    this_thread::sleep_for( duracion_pelar );

    // Cuando despierta informa de que ha terminado de pelarse
    cout << "Cliente  despertandose de la silla pelado" << endl;
}


void EsperarFueraBarberia(int i)
{
    
    chrono::milliseconds crecePelo( aleatorio<20,200>() );// Tiempo aleatorio de espera
    cout << "Al cliente " << i << " le esta creciendo el pelo...";
    this_thread::sleep_for( crecePelo );//Espera de crecePelo
    
}
class Barberia :
{
    private:
    CondVar salaEspera, //donde esperan los clientes
            cama,       //dobde duerme el barbero
            silla;      //donde cortar el pelo
    public:
        Barberia();
        void CortarPelo(int i);
        void SiguienteCliente();//Ver si en la sala de espera hay alguien y llevarlo a la silla
        void FinCliente();//Dejar la silla libre al terminar de cortar el pelo
};
// constructor
Barberia::Barberia()
{
    salaEspera  = newCondVar();
    cama        = newCondVar();
    silla       = newCondVar();
}

void Barberia::CortarPelo(int i)
{
    if(!silla.empty())// comprueba si la silla está ocupada                           
    {
        cout << "Cliente " << i << " esperando en la sala de espera." << endl;
        salaEspera.wait(); // me espero en la sala de espera
    }
    cama.signal();// aviso al barbero que estoy en la silla
    cout << "Comienza a pelar al cliente " << i << "." << endl;
    silla.wait();//Espera mientras se esta pelando
}

void Barberia::SiguienteCliente(){

    if(silla.empty())// comprueba si la silla está ocupada 
    {
    
        if(salaEspera.empty())// y la sala de espera también
        {
            cout << "Barbero duerme." << endl;
            cama.wait();
        }
        else // Si la sala de espera no esta vacia
        {
            cout << "Barbero llama a cliente de la sala de espera." << endl;
            salaEspera.signal(); // Invoca a otro cliente
        }
    }
}
void Barberia::FinCliente(){

    cout << "Barbero termina de pelar." << endl;
    silla.signal();
}



void funcion_cliente(MRef<Barberia> barb, int i)
{

    while(true)
    {
        barb->CortarPelo(i);
        EsperarFueraBarberia(i);
    }
}

void funcion_barbero(MRef<Barberia> barb)
{
    while(true){
        barb->SiguienteCliente();
        Pelar();
        barb->FinCliente();
    }
}


int main(){

    // creo monitor tipo Barberia
    MRef<Barberia> barberia = Create<Barberia>();

    // creo la hebra barbero y la lanzo
    thread hebra_barbero(funcion_barbero, barberia);

    // creo las hebras clientes y las lanzo
    thread hebra_cliente[n];
    for(int i = 0; i < n; i++)
        hebra_cliente[i] = thread(funcion_cliente, barberia, i);
    
        
    hebra_barbero.join();// esperar a que termine la hebra barbero
   
    for(int j = 0; j < n; j++) // esperar a que terminen las hebras clientes    
        hebra_cliente[j].join();
    
}
