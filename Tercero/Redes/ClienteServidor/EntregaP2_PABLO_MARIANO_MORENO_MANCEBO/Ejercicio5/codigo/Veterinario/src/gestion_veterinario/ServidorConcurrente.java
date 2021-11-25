package gestion_veterinario;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServidorConcurrente {
    public static void main(String[] args) {
        // Puerto en el que espera el servidor:
        int puerto = 8989;

        // Socket para la conexión TCP
        ServerSocket socketServidor;
        try {
            System.out.println("Abriendo el puerto " + puerto);
            socketServidor = new ServerSocket(puerto);
            System.out.println("El puerto " + puerto + " abierto correctamente");
            do {
                Socket socketConexion = null;
                try {
                    socketConexion = socketServidor.accept(); //Espera hasta aceptar conexion
                } catch (IOException e) {
                    System.out.println("ERROR: no se pudo aceptar la conexion solicitada.");
                }

                SecVeterinario procesador = new SecVeterinario(socketConexion);
                procesador.run();
            } while (true);

        } catch (IOException e) {
            System.err.println("Error al escuchar en el puerto " + puerto);
        }

    }
}
