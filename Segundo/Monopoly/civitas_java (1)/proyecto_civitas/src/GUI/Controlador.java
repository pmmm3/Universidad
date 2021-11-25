/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package GUI;
//import civitas.Casilla;
import civitas.CivitasJuego;
//import civitas.Diario;
import civitas.GestionesInmobiliarias;
//import civitas.Jugador;
import civitas.OperacionesJuego;
import civitas.OperacionInmobiliaria;
import civitas.SalidasCarcel;
//import civitas.TituloPropiedad;

/**
 *
 * @author pc
 */
//import GUI.Respuestas;
//
//import static java.lang.System.exit;
//import java.util.ArrayList;
//import java.util.Arrays;
//import java.util.Scanner;
public class Controlador {
    private CivitasJuego juego;
    private CivitasView vista;
    
    
    public Controlador(CivitasJuego juego,CivitasView vista){
        this.juego=juego;
        this.vista=vista;
    }
    public void juega(){
        vista.setCivitasJuego(juego);
        while(!juego.finalDelJuego())
        {
            
            OperacionesJuego oper=juego.siguientePaso();
            
            vista.actualizarVista();
            
            
            vista.mostrarSiguienteOperacion(oper);
            
            if (oper != civitas.OperacionesJuego.PASARTURNO)
                vista.mostrarEventos();
            
            if(!juego.finalDelJuego())
            {
                switch(oper){
                    case COMPRAR: 
                        Respuestas opc_respuesta;
                        opc_respuesta=vista.comprar();
                        if(opc_respuesta == Respuestas.SI)
                            juego.comprar();

                        juego.siguientePasoCompletado(oper);
                        break;
                    case GESTIONAR:
                        if(juego.getJugadorActual().getPropiedades().isEmpty()==false)
                        {
                            vista.gestionar();
                            GestionesInmobiliarias c_gestion = GestionesInmobiliarias.values()[vista.getGestion()];

                            int i_prop = vista.getPropiedad();
                            OperacionInmobiliaria tarea=new OperacionInmobiliaria(c_gestion,i_prop);
                            switch(tarea.getGestion())
                            {
                                case VENDER:
                                    if(juego.getJugadorActual().getNombrePropiedades()!=null)
                                    {
                                        juego.vender(i_prop);
                                    }
                                    break;
                                case HIPOTECAR:
                                    if(juego.getJugadorActual().getNombrePropiedades()!=null)
                                        juego.hipotecar(i_prop);
                                    break;
                                case CANCELAR_HIPOTECA:
                                    if(juego.getJugadorActual().getNombrePropiedades()!=null)
                                        juego.cancelarHipoteca(i_prop);
                                    break;
                                case CONSTRUIR_CASA:
                                    juego.construirCasa(i_prop);
                                    break;
                                case CONSTRUIR_HOTEL:
                                    juego.construirHotel(i_prop);
                                    break;
                                default:
                                    juego.siguientePasoCompletado(oper);

                                break;
                            }
                        }
                        else
                            juego.siguientePasoCompletado(oper);
                        break;
                    case SALIRCARCEL:
                        SalidasCarcel salida=vista.salirCarcel();
                        switch(salida)
                        {
                            case PAGANDO:
                                juego.salirCarcelPagando();
                                break;
                            case TIRANDO:
                                juego.salirCarcelTirando();
                                break;
                        }
                    
                }
            }
            else
            {

                vista.actualizarVista();
            }
            
        }
    }
   
}
