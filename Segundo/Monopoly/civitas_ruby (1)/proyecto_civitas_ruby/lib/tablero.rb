# encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
  

class Tablero
  require_relative ('casilla')
  attr_reader :numCasillaCarcel
    def initialize(indice)
      if(indice>=1)
        @numCasillaCarcel=indice
      else
        @numCasillaCarcel=1  
      
      end
      @casillas=Array.new
      @casillas<<Casilla.new("Salida")
 
      @porSalida=0
      @tieneJuez=false
    end
    
#    private
#    def tablero_correcto
#      
#      es_correcto = false
#      if @casillas.size > @numCasillaCarcel then
#      es_correcto = true  
#      end
#      es_correcto
#    end
    private
    def correcto(numCasilla=nil)
      if(numCasilla==nil)
       return @tieneJuez && @casillas.size > @numCasillaCarcel
      else
        
       if(@tieneJuez && @casillas.size > @numCasillaCarcel)
            return @casillas.size > numCasilla
          end   
      end
    end
 
    public
    def getPorSalida
      salida=@porSalida
      if @porSalida>0 then
    
      @porSalida=@porSalida - 1
      
      end
      
      salida
    end
    
    def aniadeCasilla (casilla)
      
      if(@casillas.size==@numCasillaCarcel)
        @casillas<<Casilla.new("Cárcel")
        @casillas<<casilla
      else
        @casillas<<casilla
      end
    end
    
    
    def aniadeJuez
      if(!@tieneJuez)
        @casillas<<CasillaJuez.new("Juez",@numCasillaCarcel)
        @tieneJuez=true
      end
      
    end
    
    
    def getCasilla (numCasilla)
      casilla=nil
      if numCasilla <= @casillas.size then
        casilla = @casillas.at(numCasilla)
      end
      return casilla
    end
    
    def nuevaPosicion (actual,tirada) 
      if correcto
        pos = actual + tirada
        pos = pos % @casillas.size
        if(pos==actual + tirada)
          return actual + tirada
        else
          @poSalida=@porSalida+1
          return pos
        end
      else
        return -1
      end
    end  
    
    
    
    def calcularTirada (origen,destino)
   
        tirada = destino - origen;
        if tirada < 0 then
          @porSalida=@porSalida+1
          tirada = tirada + @casillas.size
        end
        return tirada
    end
    
end  
end    
    
 