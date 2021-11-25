#encoding:utf-8
require_relative 'civitas_juego'
require_relative 'operacion_inmobiliaria'
require_relative 'operaciones_juego'
require_relative 'respuestas'
require_relative 'gestiones_inmobiliarias'
require_relative 'salidas_carcel'
require 'io/console'

module Civitas

  class Vista_textual
    attr_reader:iGestion,:iPropiedad
    private
    def mostrar_estado(estado)
      puts estado
    end

    public 
    def pausa
      print "Pulsa una tecla"
      STDIN.getch
      print "\n"
    end

    def lee_entero(max,msg1,msg2)
      ok = false
      begin
        print msg1
        cadena = gets.chomp
        begin
          if (cadena =~ /\A\d+\Z/)
            numero = cadena.to_i
            ok = true
          else
            raise IOError
          end
        rescue IOError
          puts msg2
        end
        if (ok)
          if (numero >= max)
            ok = false
          end
        end
      end while (!ok)

      return numero
    end



    def menu(titulo,lista)
      tab = "  "
      puts titulo
      index = 0
      lista.each { |l|
        puts tab + index.to_s + "-" +l.to_s
        index += 1
      }

      opcion = lee_entero(lista.length,
                          "\n"+tab+"Elige una opción: ",
                          tab+"Valor erróneo")
      return opcion
    end
    

    

    def gestionar
      lista_gestiones=[Civitas::GestionesInmobiliarias::VENDER.to_s,Civitas::GestionesInmobiliarias::HIPOTECAR.to_s,Civitas::GestionesInmobiliarias::CANCELAR_HIPOTECA.to_s,Civitas::GestionesInmobiliarias::CONSTRUIR_CASA.to_s,Civitas::GestionesInmobiliarias::CONSTRUIR_HOTEL.to_s,Civitas::GestionesInmobiliarias::TERMINAR.to_s]
      opcion=menu("¿Que deseas hacer?",lista_gestiones)
      @iGestion=opcion
      
      prop = @juegoModel.getJugadorActual.get_nombre_propiedades
      if(opcion!=5 && prop!=nil)
        indice=menu("¿Sobre que propiedad quieres realizar la gestion elegida?",prop)
      end
      @iPropiedad=indice
    end
    
    public

    def mostrarSiguienteOperacion(operacion)
      puts "Siguiente operacion #{operacion}"
    end

    def mostrarEventos
      puts Diario.instance.leer_evento until Diario.instance.eventos_pendientes
    end
    public
    def setCivitasJuego(civitas)
      @juegoModel=civitas
    end
    public 
    def actualizarVista
      a=@juegoModel.infoJugadorTexto
      b=@juegoModel.getCasillaActual.toString
      puts a+"\n"+b+"\n"
     
    end
    
    def salirCarcel() # SalidasCarcel
      lista_salidas=[Civitas::SalidasCarcel::PAGANDO.to_s,Civitas::SalidasCarcel::TIRANDO.to_s]
      opcion=menu("Elige la forma para intentar salir de la carcel",lista_salidas)
      return Civitas::SalidasCarcel::Lista_SalidasCarcel[opcion]
      
    end
    
    def comprar
      lista_respuestas=[Civitas::Respuestas::SI.to_s,Civitas::Respuestas::NO.to_s]
      opcion=menu("Desea usted comprar la calle a la que se ha llegado",lista_respuestas)
      return Civitas::Respuestas::Lista_Respuestas[opcion]
    end
 
    
    
    
    
    
    
  end

end
