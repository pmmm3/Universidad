package gestion_veterinario;

import java.io.*;
import java.util.*;

public class Catalogo {

    Map<String, Integer> productos;
    File fil_lec;
    FileWriter fil_wr;
    Scanner teclado;
    public Catalogo()
    {
        this.fil_lec = new File("./data/catalogo.txt");
        this.CargarFichero();
    }

    private void CargarFichero() {
        this.productos = new HashMap<String, Integer>();
        try {
            teclado = new Scanner(fil_lec);

            // Linea a linea
            while (teclado.hasNextLine()) {
                String producto = teclado.nextLine();
                Integer cantidad = Integer.parseInt(teclado.nextLine());
                this.productos.put(producto, cantidad);
            }
            teclado.close();
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }

    public boolean cambiarProducto(String proc, Integer cantidad) {
        if (productos.get(proc) > cantidad) {
            productos.put(proc, productos.get(proc) - cantidad);
            CopiaSeguridad();
            return true;
        }
        return false;
    }

    public Integer getCantidad(String produc)
    {
        if(productos.containsKey(produc))
        {
            return productos.get(produc);
        }
        return null;
    }

    public Set<String> getProductos()
    {
        return productos.keySet();
    }
    private void CopiaSeguridad()
    {

        try {
            fil_wr = new FileWriter("./data/catalogo.txt", false);
            Iterator<String> it = productos.keySet().iterator();
            while (it.hasNext())
            {
                Object key = it.next();
                fil_wr.write(key + "\n" + productos.get(key).toString() + "\n" );
            }
            fil_wr.close();
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
