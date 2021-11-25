# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
#require_relative 'diario'
#require_relative 'tipo_casilla'
#require_relative 'titulo_propiedad'
#require_relative 'mazo_sorpresas'
#require_relative 'sorpresa'
module Civitas
 class Casilla
   
    def initialize(nombre)
      @nombre= nombre
    end
    public
    def getNombre
      return @nombre
    end
    
    def getTituloPropiedad()
      return @tituloPropiedad 
    end
    public
    def jugadorCorrecto(actual,todos)
      return actual<=todos.size
    end
    private
    def informe( actual,todos)
      if jugadorCorrecto(actual,todos) then
        msg= "Nombre: "+todos.at(actual).getNombre()+"en la casilla"+ toString()
        Diario.instance.ocurre_evento(msg)
      end
    end
    
  public
  def toString
    msg="\n\nCasilla:\n\tNombre:  #{@nombre}\n\n"
    return msg
  end
  
  def recibeJugador (actual,todos)
    informe(actual,todos)
#    if (@tipo == TipoCasilla::SORPRESA)
#      recibeJugador_sorpresa(actual,todos)
#      
#    else
#      if (@tipo == TipoCasilla::JUEZ)
#      recibeJugador_juez(actual , todos )
#      
#      else
#        
#        if (@tipo == TipoCasilla::IMPUESTO)
#        recibeJugador_impuesto(actual , todos ) 
#        else
#          if (@tipo == TipoCasilla::CALLE)
#          recibeJugador_calle( actual,todos)
#          else
#            informe(actual,todos)
#          end          
#          
#        end      
#      end    
    
      
  end
    
    
    
    
    
    
    

  
#  def recibeJugador_calle( actual,todos)
#    if jugadorCorrecto(actual,todos)
#      informe(actual,todos)
#      jugador=todos.at(actual)
#      if (@tituloPropiedad.tienePropietario()==false)
#        jugador.puedeComprarCasilla
#      else
#        @tituloPropiedad.tramitarAlquiler(jugador)
#        
#        
#      end
#    end
#  end
#  def recibeJugador_sorpresa( actual,todos)
#    if jugadorCorrecto(actual,todos)
#      sorpresa = @mazo.Siguiente 
#      informe(actual,todos)
#      sorpresa.aplicarAJugador(actual,todos)
#      
#    end
#  end
#  def recibeJugador_impuesto(actual , todos ) 
#    if jugadorCorrecto(actual,todos)
#      informe(actual,todos)
#      todos.at(actual).pagaImpuesto(@importe )
#    end
#  end
#  def recibeJugador_juez(actual , todos )
#    if jugadorCorrecto(actual,todos)
#      informe(actual,todos)
#      todos.at(actual).encarcelar(@carcel) 
#    end
#    
#  end 
  

  
 private :informe   
 end
end
