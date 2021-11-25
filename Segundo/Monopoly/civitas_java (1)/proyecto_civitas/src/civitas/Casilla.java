/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author pc
 */
import java.util.ArrayList;
public class Casilla{
    private String nombre;

 
    public Casilla(String nombre){
        
        this.nombre= nombre;
    
    }
    public String getNombre() {
        
        return nombre;
    }
    public void setCasilla(String nombre){
        
        this.nombre= nombre;
    
    }
    public void informe (int actual, ArrayList<Jugador> todos){
        String msg;
        msg=("Nombre: "+todos.get(actual).getNombre()+" en la Casilla "+toString());
        Diario.getInstance().ocurreEvento(msg);
    }
    @Override
    public String toString() {
        return "Casilla Descanso" + "\n      Nombre : " + nombre + '\n';
    }
    
    public boolean jugadorCorrecto(int actual, ArrayList<Jugador> todos){
        return actual<=todos.size();
    }
    public void recibeJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual,todos))
        informe(actual,todos);
    }
}