# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative ('tablero')
require_relative ('casilla')
require_relative ('gestor_estados')
require_relative ('titulo_propiedad')
require_relative ('jugador')
require_relative 'operaciones_juego'
require_relative 'casilla_calle'
require_relative 'casilla_juez'
require_relative 'casilla_impuesto'
require_relative 'casilla_sorpresa'
require_relative 'sorpresa'
require_relative 'sorpresa_ir_carcel'
require_relative 'sorpresa_ir_casilla'
require_relative 'sorpresa_pagar_cobrar'
require_relative 'sorpresa_por_casa_hotel'
require_relative 'sorpresa_por_jugador'
require_relative 'sorpresa_salir_carcel'
require_relative 'sorpresa_jugador_especulador'



module Civitas
  class CivitasJuego
    def initialize (nombres)
      
      @jugadores = Array.new
      for i in 0...nombres.size
        @jugadores<<Jugador.new(nombres[i])
      end
      @indiceJugadorActual= Dado.instance.quienEmpieza(@jugadores.size) 
      @gestorEstados = Gestor_estados.new
      @estado=@gestorEstados.estado_inicial
      @mazo = MazoSorpresas.new(false)
      inicializarTablero(@mazo)
      inicializarMazoSorpresas(@tablero)
    end
    
    #def actualizarInfo
    #  puts @jugadores.at(@indiceJugadorActual).toString
     # if @jugadores.at(@indiceJugadorActual).enBancarrota
       # self.ranking()
      #end
    #end
    private
 
    def avanzaJugador() 
      puts "Avanzando"
      jugadorActual = @jugadores.at(@indiceJugadorActual)
      posicionActual =jugadorActual.getNumCasillaActual
      tirada= Dado.instance.tirar
      posicionNueva= @tablero.nuevaPosicion(posicionActual, tirada)
      casilla = @tablero.getCasilla(posicionNueva)
      contabilizarPasosPorSalida(jugadorActual)
      jugadorActual.moverACasilla(posicionNueva)
      casilla.recibeJugador(@indiceJugadorActual,@jugadores)
      contabilizarPasosPorSalida(jugadorActual)
     
    end
    public
    def cancelarHipoteca(ip ) 
      @jugadores.at(@indiceJugadorActual).cancelarHipoteca(ip)
    end

    def comprar() 
      
    jugadorActual = @jugadores.at(@indiceJugadorActual)
    numCasillaActual = jugadorActual.getNumCasillaActual
    casilla = @tablero.getCasilla(numCasillaActual)
    titulo= casilla.getTituloPropiedad
    res = jugadorActual.comprar(titulo) 
    return res
    end
    def construirCasa(ip ) 
      @jugadores.at(@indiceJugadorActual).construirCasa(ip)
    end
    def construirHotel(ip ) 
      @jugadores.at(@indiceJugadorActual).construirHotel(ip)
    end
    private
    def contabilizarPasosPorSalida(jugadorActual ) 
      while (@tablero.getPorSalida > 0)
        jugadorActual.pasaPorSalida
      end
    end
    public
    def finalDelJuego() 
      estado=false
      contador=0
      while contador < @jugadores.size && estado==false
        if @jugadores.at(contador).enBancarrota
          
          estado=true
        end
        contador=contador+1
      end
      return estado
    end
    def getCasillaActual() 
      @tablero.getCasilla(@jugadores.at(@indiceJugadorActual).getNumCasillaActual)
    end
    def getJugadorActual() 
      @jugadores.at(@indiceJugadorActual)
    end
    def hipotecar(ip ) 
      @jugadores.at(@indiceJugadorActual).hipotecar(ip)
    end
    def infoJugadorTexto() 
      @jugadores.at(@indiceJugadorActual).toString
#      if @jugadores.at(@indiceJugadorActual).enBancarrota
#        ranking()
#      end
    end
    private
    def inicializarMazoSorpresas(tablero ) 
      
   
    @mazo.alMazo(SorpresaJugadorEspeculador.new("250 de fianza", 250))
    @mazo.alMazo(SorpresaPorJugador.new("Pagas 170 a cada jugador ", -170))
    @mazo.alMazo(SorpresaSalirCarcel.new("Sorpresa salir carcel", @mazo))
    @mazo.alMazo(SorpresaPagarCobrar.new("Te encuentras 400 en el suelo",+400))
    @mazo.alMazo(SorpresaPagarCobrar.new("Pagas 500 euros por exceso de velocidad",-500))
    @mazo.alMazo(SorpresaIrCasilla.new("Avanza hasta la casilla Salida", tablero, 0))
    @mazo.alMazo(SorpresaIrCasilla.new("Vas a la carcel por intentar hacer trampas", tablero, 4))
    @mazo.alMazo(SorpresaIrCasilla.new("Ve a la casilla de descanso", tablero,9)) 
    @mazo.alMazo(SorpresaPorCasaHotel.new("Recibes 200 por cada casa y hotel", +200))
    @mazo.alMazo(SorpresaPorCasaHotel.new("Pagas 200 por cada casa y hotel", -200))
    @mazo.alMazo(SorpresaPorJugador.new("Recibes 200 de cada jugador ", +200))
    
    
    @mazo.alMazo(SorpresaIrCarcel.new("Vas a la carcel",tablero))
    end
    def inicializarTablero(mazo ) 
      
      
      @tablero=Tablero.new(4)
      @mazo=mazo
      
      titulo1=TituloPropiedad.new("Casilla1 : Esopo",80,1.22,500,800,100)
      casilla1 = CasillaCalle.new("Esopo",titulo1)
      @tablero.aniadeCasilla(casilla1)
      
      titulo2=TituloPropiedad.new("Casilla2 : Nueva",60,1.2,400,600,80)
      casilla2 = CasillaCalle.new("Calle Nueva",titulo2)
      @tablero.aniadeCasilla(casilla2)
      
      @tablero.aniadeJuez
      
      titulo3=TituloPropiedad.new("Casilla3 : Vieja",60,1.27,470,670,87)
      casilla3 = CasillaCalle.new("Calle Vieja",titulo3)
      @tablero.aniadeCasilla(casilla3)
      
      casilla_impuesto=CasillaImpuesto.new("Multa por tropezar con la farola",600)
      @tablero.aniadeCasilla(casilla_impuesto)
      

      
      titulo4=TituloPropiedad.new("Casilla4 : Alta",30,1.2,200,100,20)
      casilla4 = CasillaCalle.new("Calle Alta",titulo4)
      @tablero.aniadeCasilla(casilla4)
      
      @tablero.aniadeCasilla(CasillaSorpresa.new("¡Sorpresaaaa!",@mazo))
      
      titulo5=TituloPropiedad.new("casilla5: Baja",90,1.3,490,500,300)
      casilla5 = CasillaCalle.new("Calle Baja",titulo5)
      @tablero.aniadeCasilla(casilla5)
      
      titulo6=TituloPropiedad.new("casilla6: Guadix",70,2.6,290,710,300)
      casilla6 = CasillaCalle.new("Calle Guadix",titulo6)
      @tablero.aniadeCasilla(casilla6)
      
      @tablero.aniadeCasilla(Casilla.new("Descanso"))
      
      titulo7=TituloPropiedad.new("casilla7: Darro",100,2.9,700,600,400)
      casilla7 = CasillaCalle.new("Acera del Darro",titulo7)
      @tablero.aniadeCasilla(casilla7)
      
      @tablero.aniadeCasilla(CasillaSorpresa.new("¡Sorpresaaaa!",@mazo))
      
      titulo8=TituloPropiedad.new("casilla8:Puentezuelas",50,2.66,390,410,360)
      casilla8 = CasillaCalle.new("Calle Puentezuelas",titulo8)
      @tablero.aniadeCasilla(casilla8)
      
      titulo9=TituloPropiedad.new("casilla9:Horno",60,2.46,400,810,200)
      casilla9 = CasillaCalle.new("Calle Horno",titulo9)
      @tablero.aniadeCasilla(casilla9)
      
      @tablero.aniadeCasilla(CasillaSorpresa.new("¡Sorpresaaaa!",@mazo))
      
      titulo10=TituloPropiedad.new("casilla10:Antonio Machado",90,1.3,490,500,300)
      casilla10 = CasillaCalle.new("Calle Antonio Machado",titulo10)
      @tablero.aniadeCasilla(casilla10)
      
      titulo11=TituloPropiedad.new("casilla11:Julio Verne",180,1.45,860,1850,320)
      casilla11 = CasillaCalle.new("Calle Julio Verne",titulo11)
      @tablero.aniadeCasilla(casilla11)
      
      @tablero.aniadeCasilla(CasillaSorpresa.new("¡Sorpresaaaa!",@mazo))
      
      titulo12=TituloPropiedad.new("casilla12:America",170,1.44,830,1650,310)
      casilla12 = CasillaCalle.new("Avenida America",titulo12)
      @tablero.aniadeCasilla(casilla12)
      
      
    end
    def pasarTurno()
      @indiceJugadorActual=(@indiceJugadorActual + 1)%@jugadores.size
    end
    public
    def ranking() 
      orden=[]
      for i in 0...@jugadores.size
        orden<<@jugadores[i]
      end
      orden.sort
      return orden
      #@jugadores=@jugadores.sort { |a,b| a.compareTo(b) }
      
    end
    public
    def salirCarcelPagando() 
       @jugadores.at(@indiceJugadorActual).salirCarcelPagando
    end
    def salirCarcelTirando() 
      @jugadores.at(@indiceJugadorActual).salirCarcelTirando
    
    end
    def siguientePaso() 
      jugadorActual = @jugadores.at(@indiceJugadorActual)
      operacion = @gestorEstados.operaciones_permitidas(jugadorActual, @estado)

      if (operacion == Civitas::OperacionesJuego::PASAR_TURNO)
        pasarTurno()
        siguientePasoCompletado(operacion ) 

       else if (operacion == Civitas::OperacionesJuego::AVANZAR)

        avanzaJugador() 
        siguientePasoCompletado(operacion ) 

       end
     
      end
      return operacion
    end
    def siguientePasoCompletado(operacion ) 
      @estado= @gestorEstados.siguiente_estado(@jugadores.at(@indiceJugadorActual),@estado,operacion)
    end

    def vender(ip) 
      return @jugadores[@indiceJugadorActual].vender(ip)

    end

  end
end