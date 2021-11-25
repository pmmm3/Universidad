# encoding: utf-8

class TituloPropiedad


  def initialize (nombre,precioAlquiler,factorRevalorizacion,precioHipoteca,precioCompra,precioEdificar)
    @nombre=nombre
    @alquilerBase=precioAlquiler
    @factorRevalorizacion=factorRevalorizacion
    @hipotecaBase=precioHipoteca
    @precioCompra=precioCompra
    @precioEdificar=precioEdificar
    @propietario=nil
    @numCasas=0
    @numHoteles=0
    @hipotecado=false
    @@factorInteresesHipoteca = 1.1
  end
  attr_reader:numCasas
  attr_reader:numHoteles
  attr_reader:nombre
  attr_reader:hipotecado
  attr_reader:precioCompra
  attr_reader:precioEdificar
  attr_reader:propietario
  
  def actualizaPropietarioPorConversion (jugador)
    @propietario = jugador
  end
  def setPropietario(jugador)
    @propietario = jugador
  end
  def cancelarHipoteca(jugador )
    #estado=false
    #if (self.esEsteElPropietario(jugador) && @hipotecado==true)
    #        @estado=true
    #        @propietario.paga(self.getImporteCancelarHipoteca)
    #        @hipotecado=false
    #end
    
    #estado
    
    
    result = false
    if (@hipotecado)
      if (esEsteElPropietario(jugador))
         result=true
         @propietario.paga(getImporteCancelarHipoteca)
         @hipotecado=false
      end
    end
    return result
  end
  
  
  def cantidadCasasHoteles()
    return @numCasas+@numHoteles
  end
  
  def comprar(jugador)
    result=false
    if (!tienePropietario)
        
      @propietario=jugador
      @propietario.paga(@precioCompra)
      result = true
            
    end
    return result
  end
  
  def construirCasa(jugador) 
   
    estado=false
    if (esEsteElPropietario(jugador))
        
      if(@numCasas < jugador.getCasasMax)
        @propietario.paga(@precioEdificar)
        estado=true;
        @numCasas=@numCasas+1
      end
    end
    return estado
  end
  def construirHotel(jugador) 
   
    estado=false
    if (esEsteElPropietario(jugador))
       if( @numHoteles < jugador.getHotelesMax)
        @propietario.paga(@precioEdificar*5)
        estado=true;
        @numHoteles=@numHoteles+1
      end
    end
    return estado
  end
  def derruirCasas(n,jugador)
    estado = false
    if (esEsteElPropietario(jugador)&& n >= @numCasas) 
      @numCasas=@numCasas-n
      estado = true
    end
    return estado
  end
  
  private 
  def esEsteElPropietario(jugador)
    return @propietario.equal?(jugador) 
  end
  
  public
  
  
  def getImporteCancelarHipoteca()
    return (getImporteHipoteca * @@factorInteresesHipoteca)
  end
  
  private
  def getImporteHipoteca()
    cantidad_recibida=(@hipotecaBase*(1+(@numCasas*0.5)+(@numHoteles*2.5)))
    return cantidad_recibida
  end
  
  def getPrecioAlquiler
    precio= @alquilerBase*(1+(@numCasas*0.5)+(@numHoteles*2.5))
    if (@propietario.isEncarcelado()||@hipotecado)
        precio = 0;
    end
        
    return precio;
  end
  def getPrecioVenta

    precio = @precioCompra+(@numCasas+5*@numHoteles)*@precioEdificar*@factorRevalorizacion
    return precio
  end
  
  public
  def hipotecar (jugador)
    estado = false
        
    if (esEsteElPropietario(jugador)&&@hipotecado==false)
        
        jugador.recibe(getImporteHipoteca)
        @hipotecado=true
        estado =true
    end
        
    return estado

  end
  
  private
  def propietarioEncarcelado()
    estado = false
        if (@propietario.isEncarcelado())
            
          estado=true
        end
      return estado
  end
  
  public
  def tienePropietario()
    return @propietario != nil
  end
  
  def toString
     msg = "
 Nombre: #{@nombre}
 Alquiler base: #{@alquilerBase}
 Número casas: #{ @numCasas}
 Número hoteles: #{@numHoteles}
 Precio compra: #{@precioCompra}"
 return msg
  end
  def tramitarAlquiler(jugador)
    if (@propietario && esEsteElPropietario(jugador)==false)
        
      alquiler = getPrecioAlquiler
      jugador.pagaAlquiler(alquiler)
      @propietario.recibe(alquiler)
    end
  end
  def vender (jugador)
    estado=false    
    if (esEsteElPropietario(jugador))
      @propietario.recibe(getPrecioVenta)
      @propietario=nil
      @numCasas=0
      @numHoteles=0
      estado = true
    end   
    return estado
  end
end
