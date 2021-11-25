package Ejercicio3;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
// Editado por Pablo Mariano Moreno Mancebo , 2020
//
import java.io.BufferedReader;
import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;

public class YodafyClienteTCP {

	public static void main(String[] args) {
		//Cambio a String
		String buferEnvio;
		String buferRecepcion;
		//int bytesLeidos=0;

		// Nombre del host donde se ejecuta el servidor:
		String host="localhost";
		// Puerto en el que espera el servidor:
		int port=8989;

		// Socket para la conexión TCP
		Socket socketServicio = null;

		boolean estado = true;


		try {
			// Creamos un socket que se conecte a "hist" y "port":
			//////////////////////////////////////////////////////
			// socketServicio= ... (Completar)
			socketServicio = new Socket(host, port);
			//////////////////////////////////////////////////////

			// InputStream inputStream = socketServicio.getInputStream();
			// OutputStream outputStream = socketServicio.getOutputStream();

			BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
			PrintWriter outPrinter = new PrintWriter(socketServicio.getOutputStream(), true);
			// Si queremos enviar una cadena de caracteres por un OutputStream, hay que pasarla primero
			// a un array de bytes:
			//Al ser un string no hace falta el getbytes
			buferEnvio="Al monte del volcán debes ir sin demora";

			do {
				// Enviamos el array por el outputStream;
				outPrinter.println(buferEnvio);
				buferRecepcion = inReader.readLine();
				System.out.println(buferRecepcion);
				try {
					Thread.sleep(1000);
				} catch (Exception e) {
					System.out.println(e);
				}
			} while (estado == true);


			socketServicio.close();
			//////////////////////////////////////////////////////

			// Excepciones:
		} catch (UnknownHostException e) {
			System.err.println("Error: Nombre de host no encontrado.");
		} catch (IOException e) {
			System.err.println("Error de entrada/salida al abrir el socket.");
		}
	}
}
