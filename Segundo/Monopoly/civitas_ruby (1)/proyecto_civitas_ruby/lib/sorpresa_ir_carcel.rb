# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas
class SorpresaIrCarcel < Sorpresa
  def initialize(texto,tablero)
    super(texto)
    @tablero=tablero
  end
  
  def aplicarAJugador(actual,todos)
    if(jugadorCorrecto(actual,todos))
      super(actual,todos)
      todos[actual].encarcelar(4) 
    end
  end
  
  def toString
    msg = "Ir self.existe_la_propiedad(ipCarcel"
    return msg
  end
  
  public_class_method :new
end
end