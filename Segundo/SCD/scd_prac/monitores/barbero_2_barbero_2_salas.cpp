#include "HoareMonitor.h"
#include <iostream>
#include <unistd.h>

using namespace HM;
using namespace std;
class Barberia : public HoareMonitor
{
    CondVar salaEspera[2], silla, barbero[2];
    int turno;

public:
    Barberia()
    {
        salaEspera[0] = newCondVar();
        salaEspera[1] = newCondVar();
        silla = newCondVar();
        barbero[0] = newCondVar();
        barbero[1] = newCondVar();
        turno = rand()%2;
    }

    void cortarPelo(int id_cliente)
    {
        if (!silla.empty() || !salaEspera[0].empty())
        {
            if (salaEspera[0].get_nwt() == 5)
            {
                cout << "\nEl Cliente " << id_cliente << " en sala de espera 2";
                salaEspera[1].wait();
            }
             cout << "\nEl Cliente " << id_cliente << " en sala de espera 1";
            salaEspera[0].wait();
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
                if (!salaEspera[0].empty())
                {
                    cout << "\nEl barbero" << id_barbero << " llama de la sala de espera";
                    salaEspera[0].signal();
                }
                else
                {
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
        if (!salaEspera[0].empty())
        {
            cout<<"\nSe llama a un cliente de la sala 1";
            salaEspera[0].signal();
            cout<<"\nSe desplaza a un cliente de la sala 2 a la 1";
            salaEspera[1].signal();
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
    thread hebras_cliente[15];
    thread hebra_barbero[2];
    for (int i = 0 ; i < 2; i ++)
        hebra_barbero[i]=thread(funcion_hebra_barbero, monitor, i);
    
    for (int i = 0; i < 15; i++)
        hebras_cliente[i] = thread(funcion_hebra_cliente, monitor, i);
    
    for (int i = 0 ; i < 2; i ++)
        hebra_barbero[i].join();
    for (int i = 0; i < 15; i++)
        hebras_cliente[i].join();
    return(0);
}