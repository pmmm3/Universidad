# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require 'singleton'
require_relative 'diario'
module Civitas
  class Dado
    include Singleton
    
    
  
    def initialize
      @random = Random.new
      @debug = false
      @ultimoResultado=1
      @@SalidaCarcel = 5
    end
    
    attr_reader   :ultimoResultado
    
    def tirar
      salida = 1
      if @debug==false then
        salida = 1+rand(6).to_i 
      end
      
      return @ultimoResultado=salida
      
    end
    
     def salgoDeLaCarcel 
    
       a=tirar
      return a>=5
        
      end
      
     
     
     def quienEmpieza (n)     
        return salida = rand(n).to_i      
     end
     
     def setDebug (d)
     
         @debug=d;
         msg="El dado en estado debug = true"
         if (@debug ==false) then
         
            msg=("El dado en estado debug = false")
         end
         Diario.instance.ocurre_evento(msg)
        
     end
     
     
     
  end
end