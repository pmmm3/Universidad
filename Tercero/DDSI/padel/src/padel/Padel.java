/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package padel;

import java.sql.*;
import java.util.ArrayList;
import java.util.Scanner;

/**
 *
 * @author victo
 */
public class Padel {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        

        try (Connection conn = DriverManager.getConnection(
             // Oracle SID = orcl , find yours in tnsname.ora
            "jdbc:oracle:thin:@oracle0.ugr.es:1521/practbd.oracle0.ugr.es", "X4119634", "X4119634")) {

            if (conn != null) {
                System.out.println("Conectado!");
            }
            else
            {
                System.out.println("Error al conectar!");
            }

        /*
        Aqui empieza el código
        */

        //Definición de los querys de SQL
//EXECUTE IMMEDIATE 'DROP TABLE IF EXISTS Stock'

        String SQL_Borrar_Stock  = " begin " + " execute immediate 'drop table Stock'; " + " exception when others then null; " + " end; ";
        String SQL_Borrar_Pedido = " begin " + " execute immediate 'drop table Pedido'; " + " exception when others then null; " + " end; ";
        String SQL_Borrar_Detalle_Pedido =  " begin " + " execute immediate 'drop table Detalle_Pedido'; " + " exception when others then null; " + " end; ";
        
        String SQL_CREATE_STOCK = "CREATE TABLE Stock(Cproducto INT GENERATED BY DEFAULT ON NULL AS IDENTITY PRIMARY KEY, Cantidad INT NOT NULL)";
        String SQL_CREATE_PEDIDO = "CREATE TABLE Pedido ( Cpedido NUMBER GENERATED BY DEFAULT ON NULL AS IDENTITY PRIMARY KEY, Ccliente INT NOT NULL, Fecha_pedido DATE NOT NULL)";

        
        String SQL_CREATE_DETALLE_PEDIDO =" CREATE TABLE Detalle_Pedido ( Cpedido INT, Cproducto INT, Cantidad INT NOT NULL, FOREIGN KEY(Cpedido)  REFERENCES Pedido(Cpedido) ON DELETE CASCADE, FOREIGN KEY(Cproducto) REFERENCES Stock(Cproducto) ON DELETE CASCADE, PRIMARY KEY(Cpedido,Cproducto)) ";
        

        
        conn.setAutoCommit(false);

        //Execute

        System.out.println("INTERFAZ");

        Statement st = conn.createStatement();

        // ResultSet rs = null;
        Scanner sn = new Scanner(System.in);
        boolean salir = false;
        int opcion; //Guardaremos la opcion del usuario

        while(!salir){

            System.out.println("1. Restaurar tablas");
            System.out.println("2. Dar de alta nuevo pedido ");
            System.out.println("3. Borrar un pedido en cascada");
            System.out.println("4. Salir del programa y cerrar conexión a BD");

            System.out.println("Escribe una de las opciones");
            opcion = sn.nextInt();

            
            switch(opcion){
                case 1:
                    System.out.println("Has seleccionado la opcion 1");

                   
                    st.executeUpdate(SQL_Borrar_Detalle_Pedido);
                    st.executeUpdate(SQL_Borrar_Stock);
                    st.executeUpdate(SQL_Borrar_Pedido);
                    
                    
                    System.out.println("Tablas Borradas");
                    st.executeUpdate(SQL_CREATE_STOCK);
                    st.executeUpdate(SQL_CREATE_PEDIDO);
                    st.executeUpdate(SQL_CREATE_DETALLE_PEDIDO);
                    System.out.println("Tablas Creadas");
                    
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('0')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('1')"); 
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('2')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('3')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('4')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('5')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('6')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('7')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('8')");
                    st.executeQuery("INSERT INTO Stock (Cantidad) VALUES ('9')");
                    
                    System.out.println("10 Datos metidos en Stock");
                    conn.commit();
                    
                    
                    
                    break;
                case 2:
                    System.out.println("Has seleccionado la opcion 2");

                    //Punto 1    
                    //Entrada de datos básicos del pedido
                    System.out.println("Introduzca Codigo Cliente");
                    Scanner codigo_c = new Scanner(System.in);
                    int codigo_cliente = Integer.parseInt(codigo_c.nextLine());
                    //Guardamos el cambio
                    Savepoint antes_insertar = conn.setSavepoint("antes_insertar");

                    
                    st.executeQuery(" INSERT INTO Pedido (Ccliente , Fecha_pedido) VALUES ( '" + codigo_cliente
                            + "' , SYSDATE ) ");
                    ResultSet c_ped = st.executeQuery(" SELECT MAX(Cpedido) FROM Pedido ");
                    String c_pedido = "";
                    while (c_ped.next()) {
                        c_pedido = c_ped.getString("MAX(Cpedido)");
                    }

                    System.out.println("Se ha generado su codigo de pedido " + c_pedido);
                    
                    //Punto 2
                    int opcion_sub_menu;
                    Boolean salida_sub_menu = false;
                    Savepoint antes_de_insertar_detalle = null;

                    while (!salida_sub_menu)
                    {
                        System.out.println("1. Añadir detalle de producto");
                        System.out.println("2. Eliminar todos los detalles de producto");
                        System.out.println("3. Cancelar pedido");
                        System.out.println("4. Finalizar pedido");

                        System.out.println("Escribe una de las opciones");
                        opcion_sub_menu = sn.nextInt();
                        
                        switch(opcion_sub_menu){
                            case 1:
                            
                                antes_de_insertar_detalle = conn.setSavepoint("antes_de_insertar_detalles");
                                String cantidad = "";
                                
                                System.out.println("Introduzca el código del producto");
                                Scanner codigo_prod = new Scanner(System.in);
                                int codigo_producto = Integer.parseInt(codigo_prod.nextLine());
                                System.out.println("Introduzca la cantidad del producto");
                                Scanner cant_prod = new Scanner(System.in);
                                int cantidad_producto = Integer.parseInt(cant_prod.nextLine());
                                
                                ResultSet rs = st.executeQuery("Select Cantidad from Stock where Cproducto='"+codigo_producto+"'");
                                
                                while (rs.next()) {
                                    cantidad = rs.getString("Cantidad");
                                }
                                System.out.println("La cantidad de " + codigo_producto + " es de " + cantidad);

                                if(cantidad_producto <= Integer.parseInt(cantidad) && !cantidad.equals("")){  // Si la cantidad que el usuario pide es mayor o igual a la que se tiene en la tabla stock y existe el Cpreducto dado.           
                                    //Añadimos los detalles del pedido        
                                    st.executeQuery(" INSERT INTO Detalle_pedido (Cproducto,CPedido,Cantidad) VALUES( '"+codigo_producto+"', '"+c_pedido+"', '"+cantidad_producto+"' ) ");
                                    // Modificamos el Stock del pedido
                                    
                                    st.executeQuery(" UPDATE Stock SET Cantidad='"+ (Integer.parseInt(cantidad) - cantidad_producto)+"' WHERE Cproducto="+codigo_producto);
                                
                                }
                                else{
                                    System.out.println("Error. No tenemos stock suficiente.");
                                }

                                
                            break;
                            case 2:
                                if(antes_de_insertar_detalle!=null){
                                    conn.rollback(antes_de_insertar_detalle);
                                    conn.commit();
                                }
                            break;
                            
                            
                            case 3:
                                conn.rollback(antes_insertar);
                                conn.commit();
                                salida_sub_menu = true;
                                break;
                            case 4:
                                conn.commit();
                                salida_sub_menu=true;
                            break;
                            default:
                                System.out.println("Solo números entre 1 y 4");
                            break;
                        }
                    }
                    
                    
                    
                    
                    
                    break;
                case 3:
                    System.out.println("Has seleccionado la opcion 3");

                    ArrayList<String> codigo_producto_pedido = new ArrayList<String>();
                    ArrayList<String> cantidad_producto_pedido = new ArrayList<String>();

                    // String codigo_producto_pedido = "";
                    System.out.println("Inserte el número de pedido que desea cancelar");
                    Scanner codigo_p = new Scanner(System.in);
                    int codigo_ped = Integer.parseInt(codigo_p.nextLine());
                    // Obtenemos la cantidades de los productos antes de borrar para actualizar el stock
                    ResultSet rs_caso3 = st.executeQuery("Select Cantidad,Cproducto from Detalle_pedido where Cpedido="+codigo_ped);
                    System.out.println("Realizado el select");
                    ResultSet rsStock = null;
                    int stock_actual = 0;
                    // String cantidad_pedido;
                    

                    while (rs_caso3.next()){
                        cantidad_producto_pedido.add(rs_caso3.getString("Cantidad"));
                        codigo_producto_pedido.add(rs_caso3.getString("Cproducto"));
                    }

                    for(int i = 0; i < codigo_producto_pedido.size() ; i++){
                        // Obtenemos la cantidades de los productos del stock
                        rsStock = st.executeQuery("SELECT Cantidad FROM Stock WHERE Cproducto="+codigo_producto_pedido.get(i));
                        while (rsStock.next()) {
                            stock_actual = Integer.parseInt(rsStock.getString("Cantidad"));
                        }

                        //Actualizamos el Stock
                        st.executeQuery(" UPDATE Stock SET Cantidad='"+ (Integer.parseInt(cantidad_producto_pedido.get(i))+stock_actual) +"' WHERE Cproducto="+codigo_producto_pedido.get(i));
                        System.out.println("Añadido Stock de nuevo");
                    }
                    
                    //Borramos el pedido en cascada, En la definición de las tabla esta ON CASCADE para relaizarlo correctamente
                    if(codigo_producto_pedido.size() >0 ){
                        st.executeQuery(" DELETE FROM Pedido Where Cpedido='"+codigo_ped +"' ");
                        System.out.println("Pedido Borrado");
                    }
                    else{
                        System.out.println("No existe pedido con ese codigo");
                    }

                    //Salvamos los cambios
                    conn.commit();
                    break;
                case 4:
                    sn.close();
                    conn.close();
                    System.out.println("Cerrada la conexión");
                    salir=true;
                    break;
                default:
                    System.out.println("Solo números entre 1 y 4");
            }

        }


        } catch (SQLException e) {
            System.err.format("SQL State: %s\n%s", e.getSQLState(), e.getMessage());
        } catch (Exception e) {
            e.printStackTrace();
        }
        
    }

}