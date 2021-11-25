# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas

class JugadorEspeculador < Jugador
  @@FactorEspeculador = 2
  def initialize(jugador,fianza)
    jugador_copia(jugador)
    @fianza = fianza
    
    @especulador = true
    
  end
=begin 
  def self.copia(jugador,fianza)
    nuevo_jugador = new(fianza)
    super(jugador)
    puts nuevo_jugador.inspect
    actualiza_propietario_por_conversion
    return nuevo_jugador
  end

  def actualiza_propietario_por_conversion
    for i in 0..@propiedades.size
      @propiedades[i].set_propietario(self)
    end
  end
=end
  
  def debeSerEncarcelado
    resultado = false
    if (super)
      if(!puede_pagar_fianza)
        resultado = true
      end
    end
    return resultado
  end
  
  def puede_pagar_fianza
    puedePagar = false
    if(@saldo >= @fianza)
      modificarSaldo(-@fianza)
      puedePagar = true
    end
    return puedePagar
  end
  
  def puedoEdificarCasa(propiedad)
    if(@encarcelado)
      return false
    end
    if(propiedad.numCasas < (@@CasasMax * @@FactorEspeculador))
      return @saldo >= propiedad.precioEdificar
    else
      return false
    end
  end
  
  def puedoEdificarHotel(propiedad)
    if(@encarcelado)
      return false
    end
    if(propiedad.numHoteles< (@@HotelesMax * @@FactorEspeculador) && propiedad.numCasas >=4)
      return @saldo >= propiedad.precioEdificar
    else
      return false
    end
  end
  
  def pagaImpuesto(cantidad)
    if(@encarcelado)
      return false
    else
      return paga(cantidad/@@FactorEspeculador)
    end
  end
  
  
  
  def getCasasMax
    return (@@CasasMax * @@FactorEspeculador)
  end
  
  def getHotelesMax
    return (@@HotelesMax * @@FactorEspeculador)
  end
  
  def to_string
    a= "JugadorEspeculador{fianza= #{@fianza} , nombre= #{@nombre}, saldo= #{@saldo},encarcelado = #{@encarcelado}, numCasillaActual=  #{@numCasillaActual}, puedeComprar= #{@puedeComprar}, salvoconducto= #{@salvoconducto}, propiedades= "
    for i in 0...@propiedades.size
      a = a + @propiedades[i].nombre
    end
    a = a + "}\n"
    return a
  end
  
  def construirCasa(ip)
    result = false
    puedoEdificarCasa = false
    if(@encarcelado)
      return result
    else
      if (existeLaPropiedad(ip))
        propiedad = @propiedades[ip]
         
        if (puedoEdificarCasa(propiedad))
          result = propiedad.construirCasa(self)
          if (result)
            Diario.instance.ocurre_evento("El jugador #{@nombre} construye una casa en la propiedad "+ @propiedades[ip].nombre)
          end
        end
      end
    end
    return result
  end
  
  def construir_hotel(ip)
    result = false
    if(@encarcelado)
      return result
    end
    
    if(existeLaPropiedad(ip))
      propiedad = @propiedades[ip]
      puedo_EdificarHotel = puedoEdificarHotel(propiedad)
      precio = propiedad.precioEdificar
      if(puedoGastar(precio) && propiedad.numHoteles < @@HotelesMax && propiedad.numCasas >= @@CasasPorHotel)
        puedo_EdificarHotel = true
      end
      if(puedo_EdificarHotel)
        result = propiedad.construirHotel(self)
        propiedad.derruirCasas(@@CasasPorHotel,self)
        Diario.instance.ocurre_evento("El jugador #{@nombre} construye hotel en la propiedad "+ @propiedades[ip].nombre)
      end
    end
    
  end
  
end

end