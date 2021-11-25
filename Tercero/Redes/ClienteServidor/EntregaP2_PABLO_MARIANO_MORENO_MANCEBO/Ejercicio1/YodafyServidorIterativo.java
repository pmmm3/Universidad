package Ejercicio1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
// Editado por Pablo Mariano Moreno Mancebo , 2020
//
public class YodafyServidorIterativo {

	public static void main(String[] args) {

		// Puerto de escucha
		int port=8989;
		// array de bytes auxiliar para recibir o enviar datos.
		//byte []buffer=new byte[256];
		// Número de bytes leídos
		//int bytesLeidos = 0;


		ServerSocket socketServidor;

		try {
			// Abrimos el socket en modo pasivo, escuchando el en puerto indicado por "port"
			//////////////////////////////////////////////////
			// ...serverSocket=... (completar)

			System.out.println("Abriendo el puerto " + port);
			socketServidor = new ServerSocket(port);
			System.out.println("El puerto "+port+" abierto correctamente");
			//////////////////////////////////////////////////

			// Mientras ... siempre!
			do {
				// Aceptamos una nueva conexión con accept()
				Socket socketConexion = null;
				try {
					socketConexion = socketServidor.accept();
				} catch (IOException e) {
					System.out.println("Error: no se pudo aceptar la conexión solicitada");
				}

				// Creamos un objeto de la clase ProcesadorYodafy, pasándole como
				// argumento el nuevo socket, para que realice el procesamiento
				// Este esquema permite que se puedan usar hebras más fácilmente.
				ProcesadorYodafy procesador=new ProcesadorYodafy(socketConexion);
				procesador.procesa();

			} while (true);

		} catch (IOException e) {
			System.err.println("Error al escuchar en el puerto "+port);
		}

	}

}
