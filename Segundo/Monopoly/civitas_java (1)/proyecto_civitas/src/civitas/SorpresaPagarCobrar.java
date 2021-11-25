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
public class SorpresaPagarCobrar extends Sorpresa {
    private int valor;
    SorpresaPagarCobrar(int valor,String texto){
         super(texto);
         this.valor=valor;
    }
    @Override
    public void aplicarAJugador(int actual, ArrayList<Jugador> todos){ 
        if(jugadorCorrecto(actual,todos))
        {
            informe(actual,todos);
            todos.get(actual).modificarSaldo(valor);
        }
    }
    @Override
    public String toString() {
        return "Sorpresa Pagar Cobrar: " + "valor: " + valor +super.toString() +'\n';
    }
}
