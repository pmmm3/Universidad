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
public class SorpresaPorJugador extends Sorpresa{
    private int valor;

    SorpresaPorJugador(int valor,String texto)
    {
        super(texto);
        this.valor=valor;
    }
    @Override
    public void aplicarAJugador(int actual, ArrayList<Jugador> todos){
         if(jugadorCorrecto(actual,todos))
         {
            informe(actual,todos);
            SorpresaPagarCobrar a = new SorpresaPagarCobrar(valor*-1,"Pagan los demas");
            for(int i=0;i<todos.size();i++)
            {
                if(i!=actual)
                    a.aplicarAJugador(i, todos);
            }
             
            SorpresaPagarCobrar b = new SorpresaPagarCobrar(valor*(todos.size()-1)," ,y recibe dinero de los demas");
            b.aplicarAJugador(actual, todos);
        }
    }
    @Override
    public String toString() {
        return "Sorpresa Aplicar A Jugador " + "valor: " + valor + super.toString()+ '\n';
    }
}
