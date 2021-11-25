/**
 * @author Pablo Mariano Moreno Mancebo
 *
 */
package gestion_veterinario;

import java.io.*;
import java.net.*;
import java.util.*;






/**
 * @brief Clase ServerTCP la cual hereda de Thread para procesar mas de un
 *        cliente
 */
public class SecVeterinario extends Thread{
    private Socket socketServicio;
    Login login;
    Catalogo catalogo;
    String anfitrion;
    int puerto;
    public SecVeterinario(Socket socketConexion)
    {
        // Nombre del host donde se ejecuta el servidor:
        String anfitrion = "localhost";
        // Puerto en el que espera el servidor:
        int puerto = 8989;

        // Socket para la conexión TCP
        socketServicio = socketConexion;
        this.catalogo = new Catalogo();
        this.login = new Login();
    }
    public void run()
    {
        String usuario_dentro = "";
        try{
            BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
            PrintWriter outPrint = new PrintWriter(socketServicio.getOutputStream(), true);

            //socketServicio = new Socket(anfitrion, puerto);

            int opc_menu_login;
            do
            {
                opc_menu_login = Integer.parseInt(inReader.readLine());
            } while (opc_menu_login < 0 && opc_menu_login > 2);
            switch (opc_menu_login) {
                case 1:
                    boolean estado_login = false;
                    String user;
                    do {
                        user = inReader.readLine();
                        String pass = inReader.readLine();
                        estado_login = login.inicioSesion(user, pass);
                        outPrint.println(estado_login);
                    } while (!estado_login);
                    usuario_dentro = user;
                    break;
                case 2:
                    boolean estado_registro = false;
                    do {
                        String user2 = inReader.readLine();
                        Tipo_Log tip = Tipo_Log.valueOf(inReader.readLine());
                        String pass = inReader.readLine();

                        estado_registro = login.Registrar(user2, tip, pass);
                        outPrint.println(estado_registro);
                    } while (!estado_registro);
                    break;
            }
            if (!usuario_dentro.equals(""))
            {
                System.out.println("Atendiendo al usuario "+ usuario_dentro);
                Tipo_Log tipo_dentro = Tipo_Log.valueOf(login.getTipo(usuario_dentro));
                outPrint.println(tipo_dentro);
                switch(tipo_dentro)
                {
                    case CLIENTE:

                        int opc_cliente;

                        ArrayList<String> veterinarios_disponibles = login.getVeterinarios();

                        do
                        {
                            opc_cliente = Integer.parseInt(inReader.readLine());
                        } while (opc_cliente < 0 && opc_cliente > 4);
                        switch (opc_cliente)
                        {
                            case 1:
                                //Nombre del animal
                                String nom_animal = null;
                                do
                                {
                                    nom_animal = inReader.readLine();
                                } while (nom_animal.equals(null));
                                String nom_veterinario = null;

                                int elec_veterinario;
                                do {
                                    elec_veterinario = Integer.parseInt(inReader.readLine());
                                } while (elec_veterinario < 0);
                                switch(elec_veterinario)
                                {
                                    case 1:
                                        //Nombre del veterinario
                                        do{
                                            nom_veterinario = inReader.readLine();
                                        } while (nom_veterinario.equals(null));

                                        //Compruebo que esta disponible
                                        boolean disponible_veterinario = false;
                                        for (String i : veterinarios_disponibles)
                                        {
                                            if (i.equals(nom_veterinario)) {
                                                disponible_veterinario = true;
                                            }
                                        }
                                        //Devuelvo el resultado de la consulta
                                        outPrint.println(disponible_veterinario);
                                        break;
                                    default:
                                        if (veterinarios_disponibles.isEmpty()) {
                                        System.out.println("No hay veterinarios disponibles");
                                        outPrint.println(false);
                                        } else {
                                            outPrint.println(true);
                                        }
                                        break;
                            }
                                break;
                            case 2:
                                String nom_animal2 = null;
                                do {
                                    nom_animal2 = inReader.readLine();
                                } while (nom_animal2.equals(null));

                                if (veterinarios_disponibles.isEmpty())
                                {
                                    System.out.println("No hay veterinarios disponibles");
                                    outPrint.println(false);
                                }
                                else
                                {
                                    outPrint.println(true);
                                }
                                break;
                            case 3:
                                Set<String> productos = catalogo.getProductos();
                                Iterator<String> it_catalogo = productos.iterator();
                                while (it_catalogo.hasNext())
                                {
                                    outPrint.println(it_catalogo.next());
                                }
                                outPrint.println("FIN");

                                String produc_escogido = inReader.readLine();
                                int cantidad_prod = Integer.parseInt(inReader.readLine());
                                outPrint.println(catalogo.cambiarProducto(produc_escogido, cantidad_prod));
                                break;
                            case 4:
                                // Sin implementar
                                break;
                            case 5:
                                // Sin implementar
                                break;
                            default:
                                break;
                        }

                        break;
                    case VETERINARIO:
                        // Sin implementar

                        break;
                    case VOLUNTARIO:
                        // Sin implementar
                        break;

                }
            }



        }catch (IOException e) {
            System.err.println("Error: no se pudo establecer la conexión");
        }
    }
}
