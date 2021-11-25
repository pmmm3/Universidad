package Ejercicio2;

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
		Socket socketServicio=null;

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

			// Enviamos el array por el outputStream;
			//////////////////////////////////////////////////////
			// ... .write ... (Completar)

			//outputStream.write(buferEnvio, 0, buferEnvio.length);
			outPrinter.println(buferEnvio);

			//////////////////////////////////////////////////////

			// Aunque le indiquemos a TCP que queremos enviar varios arrays de bytes, sólo
			// los enviará efectivamente cuando considere que tiene suficientes datos que enviar...
			// Podemos usar "flush()" para obligar a TCP a que no espere para hacer el envío:
			//////////////////////////////////////////////////////
			// ... .flush(); (Completar)

			//No es nececsario
			//outputStream.flush();



			//////////////////////////////////////////////////////

			// Leemos la respuesta del servidor. Para ello le pasamos un array de bytes, que intentará
			// rellenar. El método "read(...)" devolverá el número de bytes leídos.
			//////////////////////////////////////////////////////
			// bytesLeidos ... .read... buferRecepcion ; (Completar)

			//bytesLeidos = inputStream.read(buferRecepcion, 0, bytesLeidos);
			buferRecepcion = inReader.readLine();
			//////////////////////////////////////////////////////

			// MOstremos la cadena de caracteres recibidos:
			System.out.println(buferRecepcion);

			// Una vez terminado el servicio, cerramos el socket (automáticamente se cierran
			// el inpuStream  y el outputStream)
			//////////////////////////////////////////////////////
			// ... close(); (Completar)
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
