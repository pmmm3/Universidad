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
public class SorpresaEspeculador extends Sorpresa {
    private int fianza;
    
    
    SorpresaEspeculador(int fianza,String texto)
    {
        super(texto);
        this.fianza=fianza;
    }
    @Override
    public void aplicarAJugador(int actual, ArrayList<Jugador> todos)
    {
        if(jugadorCorrecto(actual,todos))
        {
            informe(actual,todos);
            JugadorEspeculador js=new JugadorEspeculador(todos.get(actual),fianza);
            todos.set(actual, js);
        }
    }
    @Override
    public String toString() 
    {
        return "SorpresaEspeculador " + "fianza: " + fianza + super.toString()+ '\n';
    }
}
