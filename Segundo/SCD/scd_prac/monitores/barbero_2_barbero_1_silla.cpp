#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h> 
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;
class Barberia : public HoareMonitor
{
    CondVar salaEspera, silla, barbero[2];
    int turno;

public:
    Barberia()
    {
        salaEspera = newCondVar();
        silla = newCondVar();
        barbero[0] = newCondVar();
        barbero[1] = newCondVar();
        turno = rand()%2;
    }
    void cortarPelo(int id_cliente)
    {
        if (!silla.empty() || !salaEspera.empty())
        {
            cout << "\nEl Cliente " << id_cliente << " en sala de espera";
            salaEspera.wait();
        }
        cout << "\nEl Cliente "<< id_cliente << " avisa al barbero " << turno;
        barbero[turno].signal();
        cout << "\nEl Cliente " << id_cliente << " se sienta en la silla";
        silla.wait();
    }
    void siguienteCliente(int id_barbero)
    {
        if (turno != id_barbero)
        {
            cout << "\nEl barbero" << id_barbero << " se duerme hasta su turno";
            barbero[id_barbero].wait();
        }
        else
        {

            if (silla.empty())
            {
                if (!salaEspera.empty())
                {
                    cout << "\nEl barbero" << id_barbero << " llama de la sala de espera";
                    salaEspera.signal();
                }
                else{
                    cout << "\nEl barbero" << id_barbero << " se duerme hasta que haya clientes";
                    barbero[id_barbero].wait();
                }
            }
        }

        cout << "\nEl barbero"  << id_barbero << " se dispone a pelar";
    }
    void finCliente(int id_barbero)
    {
        cout<<"\nEl barbero ha terminado de pelar.";
        silla.signal();
        turno = (turno + 1) % 2;
        if (!salaEspera.empty())
        {
            salaEspera.signal();
        }
    }
};
void funcion_hebra_barbero(MRef <Barberia> barberia, int i)
{
    while(1)
    {
        barberia->siguienteCliente(i);
        cout<<"\nCortando el pelo";
        sleep(rand()%3);//Cortar pelo
        barberia->finCliente(i);
    }
}
void funcion_hebra_cliente(MRef <Barberia> barberia, int i)
{
    while(1)
    {
        barberia->cortarPelo(i);
        cout<<"\nAl cliente "<<i<<" le esta creciendo el pelo.";
        sleep(rand()%3);
    }
}
int main()
{
    MRef<Barberia> monitor = Create<Barberia>();
    thread hebras_cliente[5];
    thread hebra_barbero[2];
    for (int i = 0 ; i < 2; i ++)
        hebra_barbero[i]=thread(funcion_hebra_barbero, monitor, i);
    
    for (int i = 0; i < 5; i++)
        hebras_cliente[i] = thread(funcion_hebra_cliente, monitor, i);
    
    for (int i = 0 ; i < 2; i ++)
        hebra_barbero[i].join();
    for (int i = 0; i < 5; i++)
        hebras_cliente[i].join();
    return(0);
}