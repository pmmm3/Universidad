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
class SorpresaSalirCarcel extends Sorpresa{
    
    private MazoSorpresas mazo;
    SorpresaSalirCarcel(MazoSorpresas mazo,String texto){
        super(texto);
        this.mazo=mazo;
    }
    @Override
    public void aplicarAJugador(int actual, ArrayList<Jugador> todos){
         if(jugadorCorrecto(actual,todos)){
            informe(actual,todos);
            Boolean ok=false;
            for(int i=0; i<todos.size();i++)
              if(todos.get(i).tieneSalvoconducto())
                  ok=true;
              if(!ok){
                  todos.get(actual).obtenerSalvoconducto(this);
                  salirDelMazo();
              }
         }
    }
    void salirDelMazo(){
        mazo.inhabilitarCartaEspecial(this);
    }
    @Override
    public String toString() {
        return "Sorpresa Salir Carcel ";
    }
    void usada()
    {
        mazo.habilitarCartaEspecial(this);   
    }
    
}
