# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
class SorpresaPorCasaHotel < Sorpresa
  def initialize(texto,valor)
    super(texto)
    @valor = valor
  end
  
  def aplicarAJugador(actual,todos)
    if(jugadorCorrecto(actual,todos))
        super(actual,todos)
        todos[actual].modificarSaldo(@valor*todos[actual].cantidadCasasHoteles)
    end
  end
  
  def toString
    a = "Por Casa-Hotel"
    return a
  end
  public_class_method :new
end
end