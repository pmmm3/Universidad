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
import GUI.Dado;
public class CivitasJuego {
    private int indiceJugadorActual;
    private EstadosJuego estado;
    private Tablero tablero;
    private MazoSorpresas mazo;
    private GestorEstados gestorEstados;
    private ArrayList<Jugador> jugadores;
    private OperacionesJuego operacion;


    public CivitasJuego(ArrayList<String>nombres)
    {
        jugadores=new ArrayList();
        for(int i=0;i<nombres.size();i++)
            jugadores.add(new Jugador(nombres.get(i)));
        
        gestorEstados=new GestorEstados();
        estado=gestorEstados.estadoInicial();
        indiceJugadorActual=Dado.getInstance().quienEmpieza(jugadores.size());
        mazo=new MazoSorpresas(true);
        inicializaTablero(mazo);
        inicializaMazoSorpresas(tablero);
        
    }
    private void inicializaTablero (MazoSorpresas mazo){
        tablero=new Tablero(4);
        this.mazo=mazo;
        
        TituloPropiedad titulo1=new TituloPropiedad("Calle Esopo",80, (float) 1.22,500,800,100);
        CasillaCalle casilla1 = new CasillaCalle(titulo1);
        tablero.añadeCasilla(casilla1);
        
        TituloPropiedad titulo2= new TituloPropiedad("Calle Nueva",60, (float) 1.2,400,600,80);
        CasillaCalle casilla2 = new CasillaCalle(titulo2);
        tablero.añadeCasilla(casilla2);
        tablero.añadeJuez();
        
        TituloPropiedad titulo3=new TituloPropiedad("Calle Vieja",60, (float) 1.27,470,670,87);
        CasillaCalle casilla3 = new CasillaCalle(titulo3);
        tablero.añadeCasilla(casilla3);

        CasillaImpuesto casilla_impuesto=new CasillaImpuesto(600,"\nMulta por tropezar con la farola"); 
        tablero.añadeCasilla(casilla_impuesto);



        TituloPropiedad titulo4=new TituloPropiedad("Calle Alta",30, (float) 1.2,200,100,20) ;
        CasillaCalle casilla4 = new CasillaCalle(titulo4);
        tablero.añadeCasilla(casilla4);

        tablero.añadeCasilla(new CasillaSorpresa(mazo,"¡Sorpresaaaa!"));

        TituloPropiedad titulo5=new TituloPropiedad("Calle Baja",90, (float) 1.3,490,500,300);
        CasillaCalle casilla5 = new CasillaCalle(titulo5);
        tablero.añadeCasilla(casilla5);

        TituloPropiedad titulo6=new TituloPropiedad("Calle Guadix",70, (float) 2.6,290,710,300);
        CasillaCalle casilla6 = new CasillaCalle(titulo6);
        tablero.añadeCasilla(casilla6);

        tablero.añadeCasilla(new Casilla("Descanso"));

        TituloPropiedad titulo7=new TituloPropiedad("Acera del Darro",100, (float) 2.9,700,600,400);
        CasillaCalle casilla7 = new CasillaCalle(titulo7);
        tablero.añadeCasilla(casilla7);

        tablero.añadeCasilla(new CasillaSorpresa(mazo,"¡Sorpresaaaa!"));

        TituloPropiedad titulo8=new TituloPropiedad("Calle Puentezuelas",50, (float) 2.66,390,410,360);
        CasillaCalle casilla8 = new CasillaCalle(titulo8);
        tablero.añadeCasilla(casilla8);

        TituloPropiedad titulo9=new TituloPropiedad("Calle Horno",60, (float) 2.46,400,810,200);
        CasillaCalle casilla9 = new CasillaCalle(titulo9);
        tablero.añadeCasilla(casilla9);

        tablero.añadeCasilla(new CasillaSorpresa(mazo,"¡Sorpresaaaa!"));

        TituloPropiedad titulo10 = new TituloPropiedad("Calle Antonio Machado",90, (float) 1.3,490,500,300);
        CasillaCalle casilla10 = new CasillaCalle(titulo10);
        tablero.añadeCasilla(casilla10);

        TituloPropiedad titulo11 =new TituloPropiedad("Calle Julio Verne",180, (float) 1.45,860,1850,320);
        CasillaCalle casilla11 = new CasillaCalle(titulo11);
        tablero.añadeCasilla(casilla11);

        tablero.añadeCasilla(new CasillaSorpresa(mazo,"¡Sorpresaaaa!"));

        TituloPropiedad titulo12 =new TituloPropiedad("Avenida America",170, (float) 1.44,830,1650,310);
        CasillaCalle casilla12 = new CasillaCalle(titulo12);
        tablero.añadeCasilla(casilla12);
    }
    
    
    private void inicializaMazoSorpresas(Tablero tablero){
        
        
        mazo.alMazo(new SorpresaEspeculador(250,"\n250 de fianza"));
        mazo.alMazo(new SorpresaPorJugador(-170,"\nPagas 170 a cada jugador "));
        mazo.alMazo(new SorpresaSalirCarcel(mazo,"\nSorpresa Salir Carcel "));
        mazo.alMazo(new SorpresaPagarCobrar(400,"\nTe encuentras 400 en el suelo")); 
        mazo.alMazo(new SorpresaPagarCobrar(-500,"\nPagas 500  por exceso de velocidad"));
        mazo.alMazo(new SorpresaIrCasilla(tablero,0,"\nDe vuelta a la Salida"));
        mazo.alMazo(new SorpresaIrCasilla(tablero,4,"\nVas a la carcel por intentar hacer trampas"));
        mazo.alMazo(new SorpresaIrCasilla(tablero,9,"\nVe a la casilla de descanso"));
        mazo.alMazo(new SorpresaPorCasaHotel(200,"\nRecibes 200 por cada casa y hotel "));
        mazo.alMazo(new SorpresaPorCasaHotel(-200,"\nPagas 200 por cada casa y hotel "));
        mazo.alMazo(new SorpresaPorJugador(200,"\nRecibes 200 por cada jugador "));
        
        
        mazo.alMazo(new SorpresaIrCarcel(tablero,"\nVas a la carcel"));
    }
    private void contabilizarPasosPorSalida (Jugador jugadorActual){
        if(tablero.getPorSalida()>0)
            jugadorActual.pasaPorSalida();
    }
    private void pasarTurno(){
        indiceJugadorActual=(indiceJugadorActual + 1)%jugadores.size();

    }
    public void siguientePasoCompletado(OperacionesJuego operacion){
        estado=gestorEstados.siguienteEstado(jugadores.get(indiceJugadorActual), estado, operacion);
    }
    public boolean vender(int ip){
        return jugadores.get(indiceJugadorActual).vender(ip);
    }
    public boolean hipotecar(int ip){
        return jugadores.get(indiceJugadorActual).hipotecar(ip);
    }
    public boolean cancelarHipoteca(int ip){
        return jugadores.get(indiceJugadorActual).cancelarHipoteca(ip);
    }
    
    public boolean construirCasa(int ip){
        return jugadores.get(indiceJugadorActual).construirCasa(ip);
    }
    
    public boolean construirHotel(int ip){
        return jugadores.get(indiceJugadorActual).construirHotel(ip);
    }
    
    public boolean salirCarcelPagando(){
        return jugadores.get(indiceJugadorActual).salirCarcelPagando();
    }
    
    public boolean salirCarcelTirando(){
        return jugadores.get(indiceJugadorActual).salirCarcelTirando();
    }
    public boolean finalDelJuego(){
        Boolean ok=false;
        for(int i=0; i<jugadores.size();i++){
           if(jugadores.get(i).enBancarrota())
               ok=true;
        }
        return ok;
    }
    
    
    public ArrayList<Jugador> ranking(){
        ArrayList<Jugador> lista=jugadores;
        lista.sort((o1,o2) -> o1.compareTo(o2));
        Collections.reverse(lista);
        return lista;
    }
    public Casilla getCasillaActual(){
        return tablero.getCasilla(getJugadorActual().getNumCasillaActual());
    }
    
    public Jugador getJugadorActual(){
        return jugadores.get(indiceJugadorActual);
    }
    
    private void avanzaJugador(){
        Jugador jugadorActual=getJugadorActual();
        int posicionActual=jugadorActual.getNumCasillaActual();
        int tirada=Dado.getInstance().tirar();
        int posicionNueva=tablero.nuevaPosicion(posicionActual, tirada);
        Casilla casilla=tablero.getCasilla(posicionNueva);
        this.contabilizarPasosPorSalida(jugadorActual);
        jugadorActual.moverACasilla(posicionNueva);
        casilla.recibeJugador(indiceJugadorActual, jugadores);
        this.contabilizarPasosPorSalida(jugadorActual);
    }
    public OperacionesJuego siguientePaso(){
        Jugador jugadorActual=jugadores.get(indiceJugadorActual);
        OperacionesJuego ope=gestorEstados.operacionesPermitidas(jugadorActual, estado);
        if(ope==OperacionesJuego.PASARTURNO){
            pasarTurno();
            siguientePasoCompletado(ope);
        }
        else if(ope==OperacionesJuego.AVANZAR){
            avanzaJugador();
            siguientePasoCompletado(ope);
        }
        
        return ope;
    }
    
   
    public boolean comprar(){
        Jugador jugadorActual=jugadores.get(indiceJugadorActual);
        int numCasillaActual=jugadorActual.getNumCasillaActual();
        Casilla casilla=tablero.getCasilla(numCasillaActual);
        TituloPropiedad titulo=((CasillaCalle)casilla).getTituloPropiedad();
        boolean res=jugadorActual.comprar(titulo);
        return res;
    }
    
    
    
    
     public String infoJugadorTexto(){
        return jugadores.get(indiceJugadorActual).toString();
    }
}
