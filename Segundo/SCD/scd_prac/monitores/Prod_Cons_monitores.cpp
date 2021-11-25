#include "HoareMonitor.h"
#include <unistd.h> // Para los sleep
using namespace HM;

class Buffer : public HoareMonitor{
    private:
    int datos[10],pos;
    CondVar puedoE,puedoL;

    public:
    Buffer()
    {
        pos=0;
        puedoE=newCondVar();
        puedoL=newCondVar();
    }
    void poner(int x)
    {
        if (pos==10)
        {
            cout<<"\nBuffer lleno";
            puedoE.wait();
        }
        datos[pos]=x;
        cout<<"\nIntroducido: "<<x;
        pos++;
        puedoL.signal();
    }
    int quitar()
    {
        if (pos==0)
        {
            cout <<"\nNo hay nada que quitar.";
            puedoL.wait();
        }
        pos--;
        cout <<"\n\t\tConsumido: "<<datos[pos];
        puedoE.signal();
        return datos[pos];
    }
    

};


void funcion_hebra_productor(MRef<Buffer> buffer)
{
    while(1)
    {
        int dato = rand()%10;
        buffer->poner(dato);
        sleep(rand()%3);
        
    }
}
void funcion_hebra_consumidor(MRef<Buffer> buffer)
{
    while(1)
    {
        int dato = buffer->quitar();
        sleep(rand()%3);
        
    }
}
int main()
{
    MRef<Buffer> monitor = Create<Buffer>();
    thread hebra_productor(funcion_hebra_productor,monitor),
           hebra_consumidor(funcion_hebra_consumidor,monitor);
    hebra_productor.join();
    hebra_consumidor.join();
}
