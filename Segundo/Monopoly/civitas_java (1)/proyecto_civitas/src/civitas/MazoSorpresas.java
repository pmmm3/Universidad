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
import java.util.Collections;
class MazoSorpresas {
    private ArrayList<Sorpresa> sorpresas;
    private boolean barajada;
    private int usadas;
    private boolean debug;
    private ArrayList<Sorpresa> cartasEspeciales;
    private Sorpresa ultimaSorpresa;
    
    private void init(){
        sorpresas=new ArrayList();
        cartasEspeciales=new ArrayList();
        barajada=false;
        usadas=0;
    }
    MazoSorpresas(){
        init();
        debug=false;   
    }
    MazoSorpresas(boolean estado){
        debug=estado;
        init();
        if(estado)
            Diario.getInstance().ocurreEvento("Debug activado en mazo sorpresa");   
    }
    void alMazo (Sorpresa s)
    {
        if (barajada==false)
        {
            sorpresas.add(s);
        }
    }
    Sorpresa siguiente(){
        if((!barajada||usadas==sorpresas.size())&& !debug){
            Collections.shuffle(sorpresas);
            usadas=0;
            barajada=true;
        }
         usadas++;
         Sorpresa a=sorpresas.get(0);
         sorpresas.remove(0);
         sorpresas.add(a);
         ultimaSorpresa=a;
         return ultimaSorpresa;
    }
    void inhabilitarCartaEspecial (Sorpresa sorpresa)
    {
        if (sorpresas.contains(sorpresa))
        {   
            sorpresas.remove(sorpresa);
            cartasEspeciales.add(sorpresa);
            Diario.getInstance().ocurreEvento("Se ha quitado una carta del mazo");
        }
    }
    void habilitarCartaEspecial(Sorpresa sorpresa)
    {
        if (cartasEspeciales.contains(sorpresa))
        {   
            cartasEspeciales.remove(sorpresa);
            sorpresas.add(sorpresa);
            Diario.getInstance().ocurreEvento("Se ha añadido una carta del mazo");
        }
    }
    
}
