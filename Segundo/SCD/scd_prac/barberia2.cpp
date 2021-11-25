#include <iostream>
#include <iomanip>
#include <random>
#include <unistd.h> 
#include "HoareMonitor.h"

using namespace std ;
using namespace HM ;
const int excluido=4;
class Barberia: public HoareMonitor{
    private:
        CondVar sala_espera;
        CondVar silla;
        CondVar barbero;
	int indice_cliente_silla;
	int contador;
	
    public:
        Barberia()
        {
            sala_espera = newCondVar();
            silla = newCondVar();
            barbero = newCondVar();
	indice_cliente_silla=-1;
	contador=0;
        }
        int cortarPelo(int i)
        {
	    contador++;
	    if (contador==excluido)
		return excluido;
	    else{
		    if(!silla.empty())
		    {
		        cout << "\nEl cliente "<<i<<" a la sala de espera.";
		        sala_espera.wait();
		    }
		    cout<<"\nAvisando al barbero";
		    barbero.signal();
		    cout<<"\nEn la silla se ha sentado el cliente"<<i;
		    indice_cliente_silla=i;
		    silla.wait();
		    return -7;
		}

        }
        void finCliente()
        {
            cout<<"\nEl barbero ha terminado de pelar.";
            silla.signal();
        }
        int siguienteCliente()
        {
            if (silla.empty())
            {
                if(!sala_espera.empty())
                {
                    cout<<"\nEl barbero llama a un cliente de la sala de espera.";
                    sala_espera.signal();
		    
                }
                else
                {
                    cout<<"\nEl barbero espera dormido a que haya clientes.";
                    barbero.wait();
                }
            }
	    
	    return indice_cliente_silla;
        }
};
void funcion_hebra_barbero(MRef <Barberia> barberia)
{
    int i;
    while(1)
    {
        i=barberia->siguienteCliente();
	if(i!=-1)
        	cout<<"\nCortando el pelo a "<<i;
        sleep(rand()%3);//Cortar pelo
        barberia->finCliente();
    }
}
void funcion_hebra_cliente(MRef <Barberia> barberia, int i)
{
int pos;
    while(1)
    {
        pos=barberia->cortarPelo(i);
	if(pos !=excluido)
	{

		cout<<"\nAl cliente "<<i<<" le esta creciendo el pelo.";
		sleep(rand()%3);
	}
	else
	 cout<<"\nDISCULPEN SOY EL EXCLUIDO";
    }
}
int main()
{
    MRef<Barberia> monitor = Create<Barberia>();
    thread hebra_barbero(funcion_hebra_barbero, monitor),
         hebra_cliente[10];
    for(int i = 0 ; i <10 ; i++)(
        hebra_cliente[i]=thread(funcion_hebra_cliente, monitor,i));
       

    for(int i = 0 ; i <10 ; i++)
        hebra_cliente[i].join();
    hebra_barbero.join();
    return(0);
    return(0);
}
