# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
class CasillaSorpresa < Casilla
  def initialize(nombre,mazo)
    super(nombre)
    @mazo = mazo
  end
  def recibeJugador(actual,todos)
    if(jugadorCorrecto(actual, todos))
      super(actual,todos)
      sorpresa1=@mazo.Siguiente
      sorpresa1.aplicarAJugador(actual, todos)
    end
  end
   
  def toString
    cadena="Casilla: #{@nombre} \n\n"
    return cadena
  end
   public :toString
end
end