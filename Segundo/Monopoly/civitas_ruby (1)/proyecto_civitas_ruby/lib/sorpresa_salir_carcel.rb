# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
class SorpresaSalirCarcel < Sorpresa
  def initialize(texto,mazo)
    super(texto)
    @mazo = mazo
  end
  
  def aplicarAJugador(actual,todos)
    if(jugadorCorrecto(actual,todos))
      super(actual,todos)
      estado=false
      contador=0
      while contador < todos.size
        if todos.at(contador).tieneSalvoconducto
          estado=true
        end
        contador+=1
      end
      if(!estado)
        todos.at(actual).obtenerSalvoconducto(self)
        salirDelMazo
      end
    end
  end
  
  def usada 
    @mazo.habilitarCartaEspecial(self)
  end
  
  def salirDelMazo
    @mazo.inhabilitarCartaEspecial(self)
  end
 
  def toString
    a = "Salir Carcel"
    return a
  end
  public_class_method :new
end
end