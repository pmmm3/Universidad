/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;
import java.util.ArrayList;

/**
 *
 * @author pc
 */
public class CasillaCalle extends Casilla {
    
    private TituloPropiedad tituloPropiedad;
    
    CasillaCalle(TituloPropiedad titulo){
        super(titulo.getNombre());
        tituloPropiedad=titulo;
    }
    
    @Override
     public void recibeJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual,todos)){
            informe(actual,todos);
            Jugador jugador=todos.get(actual);
            
            if(!tituloPropiedad.tienePropietario())
                jugador.puedeComprarCasilla();
            else{
                tituloPropiedad.tramitarAlquiler(jugador);
                }
        }
    }
    TituloPropiedad getTituloPropiedad(){
        return tituloPropiedad;
    }
    @Override
    public String toString() {
        return "Casilla: "+ this.getNombre() +"\n      TituloPropiedad: " + tituloPropiedad.toString();
    }
     
}
