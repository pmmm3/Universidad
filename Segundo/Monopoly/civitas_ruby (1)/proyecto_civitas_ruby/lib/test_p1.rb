# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative ('tablero')
require_relative ('mazo_sorpresas')
require_relative ('casilla')
require_relative ('diario')
require_relative ('dado')
require_relative ('tipo_sorpresa')
require_relative ('tipo_casilla')
require_relative ('operaciones_juego')
require_relative ('estados_juego')
require_relative ('sorpresa')
require_relative ('civitas_juego')
require_relative ('gestor_estados') 
require_relative ('jugador')
require_relative ('vista_textual')
require_relative ('controlador')
require_relative ('operacion_inmobiliaria')
require_relative ('gestiones_inmobiliarias')
require_relative ('respuestas')
require_relative ('salidas_carcel')

module Civitas
class TestP1
  def self.main
    for i in 0...100
      puts "\n#{Dado.instance.quienEmpieza(4)}"
    end
    
  end
  def self.main2
   
   Dado.instance.setDebug(false)
   for i in 0...20
      puts "\n#{Dado.instance.tirar}"
   end
   
  end
  def self.main3
  
   Dado.instance.setDebug(false)
   
   for i in 0...100
 
      puts "\n#{Dado.instance.salgoDeLaCarcel}"
   end
  end
  def self.main4
   
   puts OperacionesJuego::COMPRAR
  end
  
  def self.main5
       a=MazoSorpresas.new
       b=SorpresaPagarCobrar.new("Te encuentras 400 en el suelo",+400)
       c=SorpresaPorJugador.new("Pagas 170 a cada jugador ", -170)
       a.alMazo(b)
       a.alMazo(c)
       a.Siguiente
       a.inhabilitarCartaEspecial(c)
       a.habilitarCartaEspecial(c)
       puts Diario.instance.leer_evento
       puts Diario.instance.leer_evento
   
 end
 
 def self.main6
   
       a=Tablero.new(3);
       b=Casilla.new('Pablo')
       c=Casilla.new('Pedro')
       d=Casilla.new('JF')
       e=Casilla.new('Raul');
       
       a.aniadeCasilla(b)
       a.aniadeCasilla(c);    
       a.aniadeCasilla(d);
       a.aniadeCasilla(e);
   
 end 
 def self.main7
   vistatext=Vista_textual.new
   nombres=Array.new
   nombres<<"Pablo"
   nombres<<"Pedro"
   nombres<<"Raul"
   nombres<<"Rodolfo"
   Dado.instance.setDebug(false)
   juego=CivitasJuego.new(nombres)
   contr=Controlador.new(juego,vistatext)
   
   contr.juega
   
 end 
 TestP1.main7
end
end