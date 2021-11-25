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
public class CasillaImpuesto extends Casilla{
    private float importe;
     
     CasillaImpuesto(float cantidad,String nombre){
        super(nombre);
        importe=cantidad;
    }
     
    @Override
    public void recibeJugador(int actual, ArrayList<Jugador> todos){
       if(jugadorCorrecto(actual, todos)) {
        informe(actual, todos);
        todos.get(actual).pagaImpuesto(importe);
       }
    }
    @Override
    public String toString() {
        return "Casilla: "+this.getNombre() + "\n     Importe: " + importe ;
    }
}
