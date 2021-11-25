# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


require_relative 'jugador_especulador'

module Civitas
  
class SorpresaJugadorEspeculador < Sorpresa
  def initialize(texto,fianza)
    super(texto)
    @fianza = fianza
  end
  
  def aplicar_a_jugador(actual,todos)
    if(jugador_correcto(actual,todos))
      super(actual,todos)
      js = JugadorEspeculador.new(todos[actual],@fianza)
      todos[actual] = js
    end
   end
   
  def toString
    a = "SorpresaEspeculador{fianza= #{@fianza} }";
    return a
  end
  public_class_method :new
end
end