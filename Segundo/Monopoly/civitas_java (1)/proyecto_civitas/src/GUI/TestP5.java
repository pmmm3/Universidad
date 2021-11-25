/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;
import civitas.CivitasJuego;
import java.util.ArrayList;

/**
 *
 * @author pc
 */
public class TestP5 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        CivitasView vista = new CivitasView ();
        Dado.createInstance(vista);
        Dado.getInstance().setDebug(false);
        CapturaNombres capnom= new CapturaNombres(vista,true);
        ArrayList<String>nombres;
        nombres=capnom.getNombres();
        CivitasJuego juego=new CivitasJuego(nombres);
        Controlador controlador=new Controlador(juego,vista);
        controlador.juega();
//        vista.setCivitasJuego(juego);
//        vista.actualizarVista();
    }
    
}
