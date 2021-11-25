package gestion_veterinario;

import java.io.*;
import java.util.*;




enum Tipo_Log {
    CLIENTE("CLIENTE"),
    VETERINARIO("VETERINARIO"),
    VOLUNTARIO("VOLUNTARIO");

    private String nombre;

    Tipo_Log()
    {}
    Tipo_Log(String nombre)
    {
        this.nombre = nombre;
    }

    public String toString()
    {
        return nombre;
    }
}

public class Login {
    Map<String, HashMap<Tipo_Log, String>> users;
    File fil_lec;
    FileWriter fil_wr;
    Scanner teclado;

    public Login() {
        this.fil_lec = new File("./data/users.txt");
        this.CargarFichero();
    }

    public boolean ExisteUsuario(String usr) {
        return users.containsKey(usr);
    }

    public String getPass(String usr) {
        return users.get(usr).get(Tipo_Log.CLIENTE);
    }

    private void CargarFichero() {
        this.users = new HashMap<String, HashMap<Tipo_Log, String>>();
        try {
            teclado = new Scanner(fil_lec);

            //Linea a linea
            while (teclado.hasNextLine()) {
                String usr = teclado.nextLine();
                Tipo_Log tip = Tipo_Log.valueOf(teclado.nextLine());
                String password = teclado.nextLine();
                HashMap<Tipo_Log, String> arg2 = new HashMap<Tipo_Log, String>();
                arg2.put(tip, password);
                users.put(usr, arg2);
            }
            teclado.close();
        } catch (Exception ex) {
            System.out.println("Error: " + ex.getMessage());
        }
    }

    private void insertarEnFichero(String usr, Tipo_Log tip, String pass) {
        try {
            fil_wr = new FileWriter("./data/users.txt", true);

            fil_wr.write(usr + "\n" + tip.toString() + "\n" + pass + "\n");
            fil_wr.close();
        } catch (IOException e) {
            System.out.println("Error: " + e.getMessage());
        }

    }

    public void Imprimir() {
        Iterator<String> it = users.keySet().iterator();
        while (it.hasNext()) {
            Object key = it.next();
            Iterator<Tipo_Log> it2 = users.get(key).keySet().iterator();
            while (it2.hasNext()) {
                Object key2 = it2.next();
                System.out.println("Usuario: " + key + " tipo: " + users.get(key).keySet() + " password: "
                        + users.get(key).get(key2));

            }
        }
    }

    public boolean inicioSesion(String user, String pass) {
        if (ExisteUsuario(user)) {
            Iterator<Tipo_Log> it = users.get(user).keySet().iterator();
            boolean estado = false;
            while (it.hasNext()) {
                Object key2 = it.next();
                if (users.get(user).get(key2).equals(pass)) {
                    estado = true;
                }
            }
            return estado;
        } else {
            return false;
        }
    }

    public boolean Registrar(String nom, Tipo_Log tip, String pass)
    {
        if (ExisteUsuario(nom)) {
            System.out.println("El nombre de usuario ya esta registrado");
            return false;
        } else {
            this.insertarEnFichero(nom, tip, pass);
            CargarFichero();
            return true;
        }
    }

public String  getTipo(String usr)
    {
        /*
        for (Entry<Tipo_Log, String> entry : users.get(usr).entrySet()) {
            return entry.getKey().name();
        }
        */
        String a="";
        for (Tipo_Log key : users.get(usr).keySet()) {
            a = (key).name();
        }
        return a;

    }


public ArrayList<String> getVeterinarios()
{
    ArrayList<String> veterinarios = new ArrayList<String>();
    Iterator<String> it = users.keySet().iterator();
    while (it.hasNext()) {
        Object key = it.next();
        Iterator<Tipo_Log> it2 = users.get(key).keySet().iterator();
        while (it2.hasNext()) {
            Object key2 = it2.next();
            if (key2.equals(Tipo_Log.VETERINARIO)) {
                veterinarios.add(key.toString());
            }
        }
    }
    return veterinarios;
}

    public static void main(String[] args) {
        Login log = new Login();

        //log.Registrar("Sancho", Tipo_Log.CLIENTE, "padel");
        System.out.println(log.getTipo("Sancho"));
        //log.Imprimir();
    }

}

