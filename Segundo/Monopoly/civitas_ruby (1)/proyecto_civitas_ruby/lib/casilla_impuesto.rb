# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas
class CasillaImpuesto < Casilla
  def initialize(nombre,valor)
    super(nombre)
    @importe = valor
  end
  
  def recibeJugador(actual,todos)
    if(jugadorCorrecto(actual,todos))
      super(actual,todos)
      todos[actual].pagaImpuesto(@importe)
    end
  end
  
  def toString
    cadena="\nCasilla: #{@nombre}  Importe: #{@importe} \n\n"
    return cadena
  end
  public :toString
end
end