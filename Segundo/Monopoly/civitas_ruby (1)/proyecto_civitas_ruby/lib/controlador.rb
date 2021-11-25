# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require_relative 'civitas_juego'
require_relative 'operaciones_juego'
require_relative 'operacion_inmobiliaria'
require_relative 'gestiones_inmobiliarias'
require_relative 'salidas_carcel'
require_relative 'respuestas'

module Civitas
  class Controlador
    def initialize(juego,vista)
      @juego=juego
      @vista=vista
    end
    
    def juega()
      
      @vista.setCivitasJuego(@juego)
     
      while ( !@juego.finalDelJuego )
        operacion = @juego.siguientePaso
        @vista.actualizarVista
        @vista.pausa

        
        @vista.mostrarSiguienteOperacion(operacion)

        if (operacion != Civitas::OperacionesJuego::PASAR_TURNO)
          @vista.mostrarEventos
        end
        
       
        if (!@juego.finalDelJuego)
          case operacion
            when OperacionesJuego::COMPRAR
              if @vista.comprar == Respuestas::SI
                @juego.comprar
              end
              @juego.siguientePasoCompletado(operacion)
              
            
            when OperacionesJuego::GESTIONAR
              
              @vista.gestionar
              
              lista=[Civitas::GestionesInmobiliarias::VENDER,Civitas::GestionesInmobiliarias::HIPOTECAR,Civitas::GestionesInmobiliarias::CANCELAR_HIPOTECA,Civitas::GestionesInmobiliarias::CONSTRUIR_CASA,Civitas::GestionesInmobiliarias::CONSTRUIR_HOTEL,Civitas::GestionesInmobiliarias::TERMINAR]
              oi=Civitas::OperacionInmobiliaria.new(lista[@vista.iGestion], @vista.iPropiedad)
              
              case lista[@vista.iGestion]
                  when GestionesInmobiliarias::VENDER
                    if(@juego.getJugadorActual.get_nombre_propiedades!=nil)
                      @juego.vender(oi.getNumPropiedad)
                    end
                  when GestionesInmobiliarias::HIPOTECAR 
                    if(@juego.getJugadorActual.get_nombre_propiedades!=nil)
                      @juego.hipotecar(oi.getNumPropiedad)
                    end
                  when GestionesInmobiliarias::CANCELAR_HIPOTECA
                    if(@juego.getJugadorActual.get_nombre_propiedades!=nil)
                      @juego.cancelarHipoteca(oi.getNumPropiedad)
                    end
                  when GestionesInmobiliarias::CONSTRUIR_CASA
                    @juego.construirCasa(oi.getNumPropiedad)
                  when GestionesInmobiliarias::CONSTRUIR_HOTEL
                    @juego.construirHotel(oi.getNumPropiedad)
                  else
                    @juego.siguientePasoCompletado(operacion)
                
              end
              
          
          
          when   Civitas::OperacionesJuego::SALIR_CARCEL
              turn=@vista.salirCarcel
              case turn
                when SalidasCarcel::PAGANDO
                  @juego.salirCarcelPagando
                when SalidasCarcel::TIRANDO
                  @juego.salirCarcelTirando
              end
              @juego.siguientePasoCompletado(operacion)
              
            
            else
              list_aux=Array.new
              list_aux=@juego.ranking
              list_aux.reverse
              for i in 0...list_aux.size
                puts list_aux[i].nombre+"\n"
              end
            
          end
          
 
            
        end
          
          
          
      end
        
        
    end
      
  end
end


