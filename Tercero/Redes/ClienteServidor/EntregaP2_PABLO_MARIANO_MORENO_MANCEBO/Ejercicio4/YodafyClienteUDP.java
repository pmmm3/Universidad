package Ejercicio4;

//
// YodafyServidorIterativo
// (CC) jjramos, 2012
//
import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
//import java.net.Socket;
//import java.net.SocketException;
import java.net.UnknownHostException;

public class YodafyClienteUDP {

	public static void main(String[] args) {
		InetAddress direccion;
		DatagramPacket paquete;
		DatagramSocket socketServicio;
		byte []buferEnvio;
		//byte []buferRecepcion=new byte[256];
		//int bytesLeidos=0;

		// Nombre del host donde se ejecuta el servidor:
		//String host="localhost";
		// Puerto en el que espera el servidor:
		int port=8989;

		

		try {

			// Creamos un socket que se conecte a "hist" y "port":
			//////////////////////////////////////////////////////
			// socketServicio= ... (Completar)
			socketServicio = new DatagramSocket();
			direccion = InetAddress.getByName("localhost");


			//////////////////////////////////////////////////////

			//InputStream inputStream = socketServicio.getInputStream();
			//OutputStream outputStream = socketServicio.getOutputStream();

			// Si queremos enviar una cadena de caracteres por un OutputStream, hay que pasarla primero
			// a un array de bytes:
			buferEnvio="Al monte del volcán debes ir sin demora".getBytes();

			// Enviamos el array por el outputStream;
			//////////////////////////////////////////////////////
			// ... .write ... (Completar)
			paquete = new DatagramPacket(buferEnvio, buferEnvio.length, direccion, port);
			socketServicio.send(paquete);
			//////////////////////////////////////////////////////

			// Aunque le indiquemos a TCP que queremos enviar varios arrays de bytes, sólo
			// los enviará efectivamente cuando considere que tiene suficientes datos que enviar...
			// Podemos usar "flush()" para obligar a TCP a que no espere para hacer el envío:
			//////////////////////////////////////////////////////
			// ... .flush(); (Completar)
			//////////////////////////////////////////////////////

			// Leemos la respuesta del servidor. Para ello le pasamos un array de bytes, que intentará
			// rellenar. El método "read(...)" devolverá el número de bytes leídos.
			//////////////////////////////////////////////////////
			// bytesLeidos ... .read... buferRecepcion ; (Completar)

			socketServicio.receive(paquete);
			//////////////////////////////////////////////////////

			// MOstremos la cadena de caracteres recibidos:
			String s_paquete = new String(paquete.getData());
			System.out.println(s_paquete);

			// System.out.println("Recibido: ");
			// for(int i=0;i<bytesLeidos;i++){
			// 	System.out.print((char)buferRecepcion[i]);
			// }

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
