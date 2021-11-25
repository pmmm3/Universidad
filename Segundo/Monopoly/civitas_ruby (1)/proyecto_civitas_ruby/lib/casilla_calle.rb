# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas
class CasillaCalle < Casilla
  
  
  def initialize(nombre,titulo)
    super(nombre)
    @tituloPropiedad=titulo
  end
  def recibeJugador(actual,todos)
    if(jugadorCorrecto(actual, todos))
      super(actual,todos)
      jugador=todos.at(actual)
      
      if(@tituloPropiedad.tienePropietario()==false)
        jugador.puedeComprarCasilla
      else
        @tituloPropiedad.tramitarAlquiler(jugador)
      end
    end
  end
  public
  def getTituloPropiedad()
    return @tituloPropiedad 
  end
  
  public
  def toString
    msg="\n\nCasilla: #{@nombre}"  + @tituloPropiedad.toString +  "\n\n"
    return msg
  end
  
end
end