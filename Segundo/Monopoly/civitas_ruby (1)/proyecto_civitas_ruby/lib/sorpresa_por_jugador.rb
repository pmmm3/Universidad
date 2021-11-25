# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas
class SorpresaPorJugador < Sorpresa
  def initialize(texto,valor)
    super(texto)
    @valor = valor
  end
  
  def aplicarAJugador(actual,todos)
     if(jugadorCorrecto(actual,todos))
        super(actual,todos)
        s1=SorpresaPagarCobrar.new("Pagan todos los jugadores menos el no afectado ",@valor * -1)
        var = 0  
        while var < todos.size
          if(var!=actual)
            s1.aplicarAJugador(var,todos)
          end
          var+=1
        end
        s2=SorpresaPagarCobrar.new("Recibe dinero de todos los jugadores",@valor*(todos.size-1))
        s2.aplicarAJugador(actual,todos)
    end
  end
  
  def toString
    a = "Por Jugador"
    return a
  end
  public_class_method :new
end
end