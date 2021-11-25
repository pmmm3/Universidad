/**
 * @author Pablo Mariano Moreno Mancebo
 *
 */
package gestion_veterinario;

import java.net.*;
import java.util.*;



import java.io.*;

/**
 * Clase para el Cliente TCP Se encarga de la conexión del cliente al Servidor
 * del Veterianario
 */
public class ClienteTCP {

    public static void main(String[] args) {
        {

            // Nombre del host donde se ejecuta el servidor:
            String anfitrion = "localhost";
            // Puerto en el que espera el servidor:
            int puerto = 8989;

            // Socket para la conexión TCP
            Socket socketServicio = null;

            // Entrada de teclado
            Scanner teclado = new Scanner(System.in);

            //Flags
            //boolean estado = false;
            try {
                //Conecto al Servidor
                socketServicio = new Socket(anfitrion, puerto);

                //Buffers de lectura y escritura
                BufferedReader inReader = new BufferedReader(new InputStreamReader(socketServicio.getInputStream()));
                PrintWriter outPrint = new PrintWriter(socketServicio.getOutputStream(), true);

                System.out.println("*** Conectado correctamente al servidor ***");

                //Menu de login
                int opc_menu_login;
                do {
                    System.out.println("*** Login ***\n\t1. Iniciar Sesion\n\t2. Registrarme\n\n Escoga una opción: ");
                    opc_menu_login = teclado.nextInt();
                    if (opc_menu_login > 0 && opc_menu_login <= 2) {
                        outPrint.println(Integer.toString(opc_menu_login));
                    } else {
                        System.err.println("X Opcion no valida X");
                    }
                } while (opc_menu_login < 0 && opc_menu_login > 2);

                //Posibilidades del Login

                switch (opc_menu_login) {
                    case 1:
                        boolean estado_login = false;
                        do {
                            //Inicio de Sesion
                            //Entrada de datos + envio
                            System.out.println("Introduce tu nombre de usuario: ");
                            outPrint.println(teclado.next());
                            System.out.println("Introduce tu contraseña: ");
                            outPrint.println(teclado.next());

                            //Recibir la respuesta del servidor
                            boolean inicio_sesion = Boolean.parseBoolean(inReader.readLine());

                            if (inicio_sesion) {
                                System.out.println("Datos correctos");
                                estado_login = true;
                            } else {
                                System.out.println("Datos incorrectos");
                            }
                        } while (!estado_login);
                        break;
                    case 2:
                        //Registro
                        boolean estado_registro = false;
                        do {
                            System.out.println("Introduce un nuevo usuario: ");
                            outPrint.println(teclado.next());

                            System.out.println("Introduce tipo [CLIENTE,VETERINARIO,VOLUNTARIO]: ");
                            outPrint.println(teclado.next());

                            System.out.println("Introduce una contraseña: ");
                            outPrint.println(teclado.next());

                            estado_registro = Boolean.parseBoolean(inReader.readLine());
                            if (estado_registro) {
                                System.out.println("Registrado correctamente");
                            } else {
                                System.out.println("Ya existe ese usuario");
                            }

                        } while (!estado_registro);

                        break;
                    default:
                        break;
                }

                Tipo_Log tipo_dentro = Tipo_Log.valueOf(inReader.readLine());

                switch (tipo_dentro) {
                    case CLIENTE:
                        int opc_cliente;
                        do {
                            System.out.println("*** Motivo de la Consulta ***" + "\n\t1. Pedir Cita"
                                    + "\n\t2. Servicio de Urgencias"
                                    + "\n\t3. Comprar productos "
                                    + "\n\t4. Solicitar Monta - No implementado");
                            opc_cliente = teclado.nextInt();
                            if (opc_cliente > 0 && opc_cliente <= 4) {
                                outPrint.println(Integer.toString(opc_cliente));
                            } else {
                                System.err.println("X Opcion no valida X");
                            }
                        } while (opc_cliente < 0 && opc_cliente > 4);
                        switch (opc_cliente) {
                            case 1:
                                System.out.println("Introduce el nombre de la mascota: ");
                                String nom_animal = teclado.next();
                                outPrint.println(nom_animal);

                                int elec_veterinario;
                                do {
                                    System.out.println("Elección de veterinario: " + "\n\t1. Elegir veterinario"
                                            + "\n\t2. Quiero ser atendido cuanto antes");
                                    elec_veterinario = teclado.nextInt();

                                } while (elec_veterinario < 1);
                                outPrint.println(elec_veterinario);
                                switch (elec_veterinario) {
                                    case 1:
                                        System.out.println("Introduce el veterinario que desee: ");
                                        String nom_vet = teclado.next();
                                        outPrint.println(nom_vet);

                                        boolean estado_veterinario = Boolean.parseBoolean(inReader.readLine());
                                        if (!estado_veterinario) {
                                            System.out.println("El veterinario solicitado no esta disponible");
                                        } else {
                                            System.out.println("Escogido el veterinario correctamente");
                                        }
                                        break;
                                    default:
                                        estado_veterinario = Boolean.parseBoolean(inReader.readLine());
                                        if (!estado_veterinario) {
                                            System.out.println("No hay veterinarios disponibles");
                                        } else {
                                            System.out.println("Consultando  su cita");
                                        }
                                        break;
                                }

                                break;
                            case 2:
                                System.out.println("Introduce el nombre de la mascota: ");
                                String nom_animal2 = teclado.next();
                                outPrint.println(nom_animal2);

                                Boolean estado_veterinario = Boolean.parseBoolean(inReader.readLine());
                                if (!estado_veterinario) {
                                    System.out.println("No hay veterinarios disponibles");
                                } else {
                                    System.out.println("Consultando  su cita");
                                }

                                break;
                            case 3:
                                //Compra
                                Set<String> productos = new HashSet<String>();
                                String recibo;
                                do {
                                    recibo = inReader.readLine();
                                    if (!recibo.equals("FIN")) {
                                        productos.add(recibo);
                                    }
                                } while (!recibo.equals("FIN"));

                                Iterator<String> it_catalogo = productos.iterator();
                                String lista = "";
                                while (it_catalogo.hasNext()) {
                                    lista += it_catalogo.next() + " ";
                                }
                                System.out.println("Productos: ");
                                System.out.println(lista);
                                String producto_deseado="";
                                do
                                {
                                    System.out.println("Introduce el producto que desee: ");
                                    producto_deseado = teclado.next();
                                } while (!producto_deseado.equals("") && !productos.contains(producto_deseado));

                                System.out.println("Introduce la cantidad deseada: ");
                                int cantidad_producto = teclado.nextInt();
                                outPrint.println(producto_deseado);
                                outPrint.println(cantidad_producto);
                                boolean resultado_catalogo = Boolean.parseBoolean(inReader.readLine());
                                if ( resultado_catalogo)
                                {
                                    System.out.println("Compra con exito");

                                }
                                else
                                {
                                    System.out.println("Error en la compra");
                                }
                            case 4:
                                // Sin implementar
                                //Publicar Monta
                                break;
                        }

                        break;
                    case VETERINARIO:
                        //Sin implementar
                        /*
                         * 4.1 Atender citas 4.2 Atender montas
                         */
                        break;
                    case VOLUNTARIO:
                        // Sin implementar
                        /*
                         * 5.1 Pedir cita con preferencia
                         * 5.2 Comprar productos con descuento aplicado
                         * 5.3 Acoger perro
                         * 5.4 Devolver perro
                         * 5.5 Aportar dinero para alimentos y medicinas a otros perros
                         */
                        break;

                }

                teclado.close();
                socketServicio.close();
            } catch (UnknownHostException e) {
                System.err.println("Error: equipo desconocido");
            } catch (IOException e) {
                System.err.println("Error: no se pudo establecer la conexión");
            }
        }
    }
}