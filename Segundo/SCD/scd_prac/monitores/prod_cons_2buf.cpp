#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h> 
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;
class monitorSU : public HoareMonitor{
    private:
        CondVar puedoProducir_par,
                puedoProducir_impar,
                puedoConsumir;
        int v1[10];
        int pos1;
        int v2[10];
        int pos2;
    public:
        monitorSU()
        {
            pos1=pos2=0;
            puedoConsumir=newCondVar();
            puedoProducir_par=newCondVar();
            puedoProducir_impar=newCondVar();

        }
        void ColocarDato(int num_prod ,int dato)
        {
            if (num_prod%2==0)
            {
                if (pos2==10)
                {
                    
                    cout<<"\nBuffer 2 esta lleno.";
                    puedoProducir_par.wait();
                }
                cout<<"\nIntroducido el dato "<<dato<<" en el Buffer 2"<<" por el productor "<<num_prod;
                v2[pos2]=dato;
                pos2++;
                puedoConsumir.signal();
            }
            else
            {
                if (pos1==10)
                {
                    cout<<"\nBuffer 1 esta lleno.";
                    puedoProducir_impar.wait();
                }
                cout<<"\nIntroducido el dato "<<dato<<" en el buffer 1"<<" por el productor "<<num_prod;
                v1[pos1]=dato;
                pos1++;
                puedoConsumir.signal();
            }
            
        }
        int quitarDato(int i)
        {
            if(pos1==0&&pos2==0){
                cout<<"\nNo hay nada para consumir para el consumidor "<<i;
                puedoConsumir.wait();
            }
            if (pos1 > 0)
            {
                pos1--;
                cout <<"\n\t\tConsumido: "<<v1[pos1]<<" por el consumidor "<<i;
                puedoProducir_impar.signal();
                return v1[pos1];
            }
            else 
            {
                pos2--;
                cout <<"\n\t\tConsumido: "<<v2[pos2]<<" por el consumidor "<<i;
                puedoProducir_par.signal();
                return v2[pos2];
            }
        }



};
void funcion_hebra_productor(MRef<monitorSU> monitorSU,int i)
{
    while(1)
    {
        int dato = rand()%10;
        monitorSU->ColocarDato(i,dato);
        sleep(rand()%3);
        
    }
}
void funcion_hebra_consumidor(MRef<monitorSU> monitorSU,int i)
{
    while(1)
    {
        int dato = monitorSU->quitarDato(i);
        sleep(rand()%3);
        
    }
}
int main()
{
    MRef<monitorSU> monitor = Create<monitorSU>();

    thread hebras_productoras[4],
           hebras_consumidoras[4];
    for (int i = 0 ; i < 4 ; i ++)
    {
        hebras_consumidoras[i]=thread(funcion_hebra_consumidor,monitor,i);
        hebras_productoras[i]=thread(funcion_hebra_productor,monitor,i);
    }

    for (int i = 0 ; i < 4 ; i ++)
    {
        hebras_productoras[i].join();
        hebras_consumidoras[i].join();
    }
}
