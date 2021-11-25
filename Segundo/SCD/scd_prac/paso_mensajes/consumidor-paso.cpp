/*
For jose:
$ mpicxx consumidor-paso.cpp -o consumidor-paso
$ mpirun --host "localhost:3" -np 3 ./consumidor-paso
*/
#include <mpi.h>
#include <iostream>
#include <unistd.h>

using namespace std;

const int ID_BUFFER = 0;
const int ETQ_PRODUCIR = 1, ETQ_CONSUMIR = 2;

void buffer()
{
    int dato, etq_aceptada;
    int vector[4];
    int pos=0;
    MPI_Status status;
    while (1)
    {
        etq_aceptada = MPI_ANY_TAG;
        if (pos == 4)
        {
            etq_aceptada = ETQ_CONSUMIR;
        }
        else if (pos == 0)
        {
            etq_aceptada = ETQ_PRODUCIR;
        }
        cout << "[BUFFER] Tiene " << pos << " elementos y etq=" << etq_aceptada << endl;
        MPI_Recv(&dato, 1, MPI_INT, MPI_ANY_SOURCE, etq_aceptada, MPI_COMM_WORLD, &status);
        if (status.MPI_TAG == ETQ_PRODUCIR)
        {
            cout << "[BUFFER] Mete " << dato << endl;
            vector[pos] = dato;
            pos++;
        }
        else
        {
            pos--;
            dato = vector[pos];
            cout << "[BUFFER] Saca " << dato << endl;
            MPI_Send(&dato, 1, MPI_INT, status.MPI_SOURCE, ETQ_CONSUMIR, MPI_COMM_WORLD);
        }
    }
}

void productor(int mi_id)
{
    int dato;
    while (1)
    {
        dato = rand() % 20;
        cout << "[PROD " << mi_id << "] Va a enviar " << dato << endl;
        MPI_Ssend(&dato, 1, MPI_INT, ID_BUFFER, ETQ_PRODUCIR, MPI_COMM_WORLD);
        sleep(rand() % 3);
    }
}

void consumidor(int mi_id)
{
    int dato;
    MPI_Status status;
    while (1)
    {
        cout << "[CONS " << mi_id << "] Espera recibir" << endl;
        MPI_Send(&dato, 1, MPI_INT, ID_BUFFER, ETQ_CONSUMIR, MPI_COMM_WORLD);
        MPI_Recv(&dato, 1, MPI_INT, ID_BUFFER, ETQ_CONSUMIR, MPI_COMM_WORLD, &status);
        cout << "[CONS " << mi_id << "] Recibe " << dato << endl;
        sleep(rand() % 3);
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int mi_id, tam;
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_id);
    MPI_Comm_size(MPI_COMM_WORLD, &tam);

    if (tam != 5)
    {
        if (mi_id == 0)
        {
            cerr << "Numero procesos invalido" << endl;
        }
    }
    else
    {
        if (mi_id == ID_BUFFER)
        {
            buffer();
        }
        else if (mi_id < 3)
        {
            productor(mi_id);
        }
        else
        {
            consumidor(mi_id);
        }
    }

    MPI_Finalize();
}