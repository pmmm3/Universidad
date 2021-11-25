# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
class CasillaJuez < Casilla
  def initialize(nombre,carcel)
    super(nombre)
    @carcel = carcel
  end
  
  def recibeJugador(actual,todos)
    if(jugadorCorrecto(actual,todos))
      super(actual,todos)
      todos[actual].encarcelar(@carcel)
    end
  end
  
  def toString
    cadena="\nCasilla: #{@nombre} \n\n"
    return cadena
  end
  public :toString

end
end