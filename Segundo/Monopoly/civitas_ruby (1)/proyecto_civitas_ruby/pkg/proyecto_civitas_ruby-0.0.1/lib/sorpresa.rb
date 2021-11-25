
require_relative 'jugador'
require_relative ('sorpresa')
module Civitas
  class Sorpresa
    
#    private 
#    def init()
#      @tablero=nil
#      @mazo=nil
#      @valor=-1
#    end
#    
    def initialize(texto)
      @texto=texto
#    @valor=dato
#    @mazo=mazo # Clase mazo sorpresas
#    @tipo = tipo_sorpresa # Enum TipoSopresa
#    @tablero = tablero#Clase Tablero
    end
    
    #Constructores especificos
#    def self .new_EnviarCarcel(tipo,tablero)
#      new(tipo,tablero)
#    end
#    
#    def self .new_EnviarCasilla(tipo,tablero,valor)
#      new(tipo,tablero,nil,valor)
#    end
#    def self .new_EvitarCarcel(tipo,mazo)
#      new(tipo,nil,mazo)
#    end

   
    def jugadorCorrecto ( actual, todos)
      return actual<=todos.size
    end
    
    
    def informe (actual, todos)
        msg = "\nAplicando sorpresa a: "
        msg += "Jugador: "+ todos.at(actual).getNombre()
        puts msg
        Diario.instance.ocurre_evento(msg)
    end
   
    
  
    def aplicarAJugador(actual,todos)
      informe(actual,todos)
    end
    
#    private
#    def aplicarAJugador_irACasilla(actual,todos)
#      if (self.jugadorCorrecto(actual,todos))
#        self.informe(actual, todos)
#        casilla_actual=todos.at(actual).getNumCasillaActual()
#        movimiento=@tablero.calcularTirada(casilla_actual,@valor)
#        todos.at(actual).moverACasilla(movimiento)
#        @tablero.getCasilla(@valor).recibeJugador(actual,todos) 
#        end
#    end
#    def aplicarAJugador_irCarcel(actual,todos)
#      if (self.jugadorCorrecto(actual,todos))
#        self.informe(actual, todos)
#        todos.at(actual).encarcelar(@tablero.numCasillaCarcel)
#      end
#    end
#    def aplicarAJugador_pagarCobrar(actual,todos)
#      if (self.jugadorCorrecto(actual,todos))
#        self.informe(actual, todos)
#        todos.at(actual).modificarSaldo(todos.at(actual).getSaldo()*@valor)
#      end
#    end
#    def aplicarAJugador_porCasaHotel(actual,todos)
#      if (self.jugadorCorrecto(actual,todos))
#        self.informe(actual, todos)
#        todos.at(actual).modificarSaldo(todos.at(actual).getSaldo()*@valor)
#      end
#    end
#    def aplicarAJugador_porJugador(actual,todos)
#      if (self.jugadorCorrecto(actual,todos))
#        self.informe(actual, todos)
#        sorpresa1 = Sorpresa.new(TipoSorpresa::PAGARCOBRAR,@tablero,@mazo,(@valor*-1))
#        sorpresa2 = Sorpresa.new(TipoSorpresa::PAGARCOBRAR,@tablero,@mazo,(@valor*(todos.size()-1)))
#        var = 0  
#        while var < todos.size() 
#          if actual == var
#          sorpresa2.aplicarAJugador(var,todos)
#          var +=1
#          else
#          sorpresa1.aplicarAJugador(var,todos)
#          var += 1 
#      
#          end
#        end
#        
#      end
#    end
#    def aplicarAJugador_salirCarcel(actual,todos)
#      if (self.jugadorCorrecto(actual,todos))
#        estado=false
#        self.informe(actual,todos)
#        contador=0
#        while contador < todos.size
#          if todos.at(contador).tieneSalvoconducto
#            estado=true
#          end
#          
#        end
#        if estado==false
#          # self?
#          todos.at(actual).obtenerSalvoconducto(self)
#        end
#      end
#    end
#    
#    public 
#    def salirDelMazo()
#      if (@tipo==TipoSorpresa::SALIRCARCEL)
#        @mazo.inhabilitarCartaEspecial(self)
#      end
#    end
#    
#    def toString()
#      "Texto: #{@texto}  Valor: #{@valor}  Tipo: #{@tipo} \n"
#    end
#    
#    def usada
#      if (@tipo==TipoSorpresa::SALIRCARCEL)
#        @mazo.def habilitarCartaEspecial(self)
#      end
#    end
#    
    
  private_class_method :new
  private :informe
  end
end