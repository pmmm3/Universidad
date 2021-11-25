# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
class SorpresaIrCasilla < Sorpresa
  def initialize(texto,tablero,valor)
    super(texto)
    @tablero = tablero
    @valor = valor
  end
  
  def aplicarAJugador(actual,todos)
      if(jugadorCorrecto(actual,todos))
        super(actual,todos)
        casilla_actual=todos[actual].getNumCasillaActual
        tirada=@tablero.calcularTirada(casilla_actual,@valor)
        nueva_pos=@tablero.nuevaPosicion(casilla_actual,tirada)
        todos[actual].moverACasilla(nueva_pos)
        @tablero.getCasilla(nueva_pos).recibeJugador(actual, todos)
      end
  end
  
  def toString
    msg = "Ir Casilla"
    return msg
  end
  public_class_method :new
end
end