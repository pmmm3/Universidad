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
public class CasillaSorpresa extends Casilla {
    private Sorpresa sorpresa;
    private MazoSorpresas mazo;
    
    CasillaSorpresa(MazoSorpresas mazo,String nombre){
        super(nombre);
        this.mazo=mazo;
    }
    @Override
    public void recibeJugador(int actual, ArrayList<Jugador> todos){
        if(jugadorCorrecto(actual,todos)){
            sorpresa=mazo.siguiente();
            informe(actual,todos);
            sorpresa.aplicarAJugador(actual, todos);
            
        }
    }
    @Override
    public String toString() {
        return "Casilla Sorpresa: "+ sorpresa + "\nMazo: " + mazo ;
    }
}
