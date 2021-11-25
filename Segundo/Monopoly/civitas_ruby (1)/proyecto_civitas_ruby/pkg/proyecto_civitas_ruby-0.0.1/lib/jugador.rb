# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


module Civitas
  class Jugador
    include Comparable
    attr_reader :nombre,:numCasillaActual,:HotelesMax,:CasasMax,:CasasPorHotel,:propiedades,:puedeComprar,:saldo,:encarcelado,:valor,:salvoconducto,:especulador
    

    def initialize(nom)
      @nombre=nom
      @encarcelado=false
      @numCasillaActual=0
      @puedeComprar=true
      @saldo=7500
      @propiedades=Array.new
      @salvoconducto=nil
      @@CasasMax=4
      @@CasasPorHotel=4
      @@HotelesMax=4
      @@PasoPorSalida=1000
      @@PrecioLibertad=200
      @@SaldoInicial=7500
      @especulador = false
    end
    def jugador_copia(otro)
      @nombre = otro.nombre
      @encarcelado=otro.encarcelado
      @numCasillaActual=otro.numCasillaActual
      @puedeComprar=otro.puedeComprar
      @saldo=otro.saldo
      @salvoconducto= otro.salvoconducto
      @propiedades=otro.propiedades
      for i in @propiedades
        i.actualiza_propietario_por_conversion(self)  
      end
      @especulador = otro.especulador
  end
    def self.copia(otro)
      @nombre = otro.getNombre
      @encarcelado=otro.isEncarcelado
      @numCasillaActual=otro.getNumCasillaActual
      @puedeComprar=otro.getPuedeComprar
      @saldo=otro.getSaldo
      @salvoconducto= otro.salvoconducto
      @propiedades=otro.propiedades   
    end

    def from(p)

      init(p.salvoconducto,p.isEncarcelado,p.nombre,p.numCasillaActual,p.saldo,p.puedeComprar)
      @propiedades = p.propiedades
    end

    def init(salvo,carcel,nombre,casilla,saldo,compra)

      @salvoconducto=[]
      isEncarcelado=carcel
      @nombre=nombre
      @numCasillaActual=casilla
      @saldo=saldo
      @puedeComprar=compra
    end

    

    def cancelarHipoteca(ip)
      result = false
      if (@encarcelado)
        return result
      end
      if (existeLaPropiedad(ip))
        propiedad = @propiedades.at(ip)
        cantidad = propiedad.getImporteCancelarHipoteca
        puedoGastar= puedoGastar(cantidad);
        if (puedoGastar)
          result = propiedad.cancelarHipoteca(self)
          if result
            Diario.instance.ocurre_evento("El jugador "+@nombre+" cancela la hipoteca de la propiedad "+ip.to_s)
          end

        end
      end
      return result


    end



    def cantidadCasasHoteles() 
      cont=0
      for i in 0...@propiedades.size
        cont=cont+@propiedades[i].cantidad_casas_hoteles
      end
      return cont
    end
    def <=>(otro)
    @valor<=>otro.valor
    end
#    def compareTo(otro)#1 if self>other; 0 if self==other; -1 if self<other
#      
#      
#      if (@saldo > otro.getSaldo)
#        valor=1
#      
#      else
#        if @saldo == otro.getSaldo()
#          valor=0
#        else
#          valor=-1
#        end
#      end
#      
#      @valor <=> otro.getSaldo)
#      return valor
#    end

    def comprar(titulo ) 
      result = false
      if (@encarcelado)
        return result
      end

      if (@puedeComprar)
        precio = titulo.precioCompra
        if (puedoGastar(precio))
          result = titulo.comprar(self)
          if (result)
            @propiedades.push(titulo)
            Diario.instance.ocurre_evento("El jugador "+@nombre+ " compra la propiedad "+titulo.toString())
          end
          @puedeComprar=false
        end

      end

      return result
    end

    def construirCasa(ip ) 
      result = false
      if @encarcelado
        return result
      else
        if existeLaPropiedad(ip)

        propiedad= @propiedades.at(ip)
       
          if (puedoEdificarCasa(propiedad))
            result=propiedad.construirCasa(self)
            if (result)
               Diario.instance.ocurre_evento("El jugador "+@nombre+ " construye casa en la propiedad "+ip.to_s)
            end
          end
        end
      end
    end

    def construirHotel(ip ) 
      result = false
      if @encarcelado
        return result
      end
      if existeLaPropiedad(ip)

        propiedad= @propiedades.at(ip)
        puedoEdificarHotel = puedoEdificarHotel(propiedad)
        precio=propiedad.precioEdificar
        if puedoEdificarHotel

        result= propiedad.construirHotel(self)
        propiedad.derruirCasas( @@CasasPorHotel, self)

        Diario.instance.ocurre_evento("El jugador "+@nombre+ " construye hotel en la propiedad "+ip.to_s)



        end
      end
      return result
    end

    def debeSerEncarcelado() 
      estado=false
      if (@encarcelado)
        estado=false

      else
        if tieneSalvoconducto()==false
          estado=true
        else
          perderSalvoConducto
          estado=false
          Diario.instance.ocurre_evento("El jugador se libra de la carcel")
        end
      end





      return estado
    end

    def enBancarrota() 

      estado=true
      if @saldo >=0
        estado=false
      end
      return estado

    end

    def encarcelar(numCasillaCarcel) 


      if debeSerEncarcelado
        @encarcelado=true
        moverACasilla(numCasillaCarcel)
        Diario.instance.ocurre_evento("Jugador encarcelado")

      end


      return @encarcelado
    end

    private
    def existeLaPropiedad(ip)
      return ip<=@propiedades.size
    end
    public
    def getCasasMax()
      @@CasasMax
    end
    private
    def getCasasPorHotel()
      @@CasasPorHotel
    end
    public
    def getHotelesMax()
      return @@HotelesMax
    end

    public 
    def getNombre()
      return @nombre
    end 
    

    def getNumCasillaActual()
      return @numCasillaActual
    end
    private 
    def getPrecioLibertad() 
      return @@PrecioLibertad
    end

    def getPremioPasoSalida() 
      return @@PasoPorSalida
    end

    public
    def getPropiedades() #: TituloPropiedad[1..*]
      return @propiedades
    end
    def get_nombre_propiedades
      nombres=Array.new
      for i in 0...@propiedades.size
        nombres<<@propiedades[i].nombre
      end
      return nombres
    end

    def getPuedeComprar() 
      return @puedeComprar
    end

    def getSaldo() 
      return @saldo
    end

    def hipotecar(ip )
     result = false
     if (@encarcelado)
       return result
     end
     if (existeLaPropiedad(ip))
        propiedad = @propiedades.at(ip)
        result = propiedad.hipotecar(self)
        if result
          Diario.instance.ocurre_evento("El jugador "+@nombre+ " hipoteca la propiedad "+ip.to_s)
        end
     end

     return result
    end 

    def isEncarcelado() 
      return @encarcelado
    end

    def modificarSaldo(cantidad )
      estado=true

      @saldo=@saldo+cantidad
      Diario.instance.ocurre_evento('Se ha modificado el saldo del jugador')
      return estado
    end

    
    def moverACasilla(numCasilla ) 
      estado=false
      if !@encarcelado
        @numCasillaActual=numCasilla
        @puedeComprar=false
        msg=@nombre + " desplazado a #{numCasilla}"
        Diario.instance.ocurre_evento(msg)
        estado=true
      end
      return estado
    end

    def obtenerSalvoconducto(sorpresa) 
      estado = false
        if (@encarcelado==false)
          @salvoconducto=sorpresa
          estado=true
        end

      return estado
    end
    def paga(cantidad ) 
      return estado=modificarSaldo(cantidad * (-1))
    end

    def pagaAlquiler(cantidad) 
      estado=false
      if @encarcelado
        estado=false
      else
        estado=paga(cantidad)
      end
      return estado
    end

    def pagaImpuesto(cantidad )
      estado=false
      if @encarcelado
        estado=false
      else
        estado=paga(cantidad)
      end
      return estado
    end

    def pasaPorSalida() 
      estado=true
      modificarSaldo(@@PasoPorSalida)
 
      Diario.instance.ocurre_evento("El jugador ha pasado por la salida")
      return estado
    end
    private
    def perderSalvoConducto() 
      @salvoconducto.usada
      @salvoconducto=nil
    end
    public
    def puedeComprarCasilla() 
      if(@encarcelado)
        @puedeComprar=false
      else
        @puedeComprar=true
      end
      return @puedeComprar
    end
    private
    def puedeSalirCarcelPagando() 
      estado = false
      if @saldo >= @@PrecioLibertad
        estado=true
      end
      return estado
    end
    def puedoEdificarCasa(propiedad ) 
      estado=false
     
        if((propiedad.numCasas<=@@CasasMax)&&!@encarcelado)
          if puedoGastar(propiedad.precioEdificar ) 
            estado=true
          end
        end

     
      return estado
    end
    def puedoEdificarHotel(propiedad ) 
      if(@encarcelado)
        return false
      else
        
      if(propiedad.numHoteles<=@@HotelesMax && propiedad.numCasas==4)
        return @saldo>=propiedad.precioEdificar
      else
        return false
      end
    end
      end


    def puedoGastar(precio ) 
      estado=false
      if @encarcelado==false
        if(@saldo >= precio)
          estado=true
        end
      end
      return estado
    end
    public
    def recibe(cantidad ) 
      estado=false
      if @encarcelado
        estado=false
      else
        estado=modificarSaldo(cantidad)
      end
      return estado
    end
    def salirCarcelPagando() 
      estado=false
        if (@encarcelado)
          if puedeSalirCarcelPagando
            paga(@@PrecioLibertad)
            estado=true
            @encarcelado=false
            msg=@nombre +" : El jugador ha pagado por salir de la carcel"
            Diario.instance.ocurre_evento(msg)
          end
        end
      return estado
    end
    def salirCarcelTirando() 
      estado=false
      if Dado.instance.salgoDeLaCarcel
        @encarcelado=false
        Diario.instance.ocurre_evento("El jugador ha salido de la carcel con el dado")
        estado=true
      end

      return estado
    end
    def tieneAlgoQueGestionar() 
      return @propiedades!=nil
    end
    def tieneSalvoconducto() 
      estado=false
        if @salvoconducto!=nil
          estado=true
        end
      return estado
    end
    def toString() 
      aux="\nJugador:
          nombre:"+ @nombre+"
          encarcelado: "+@encarcelado.to_s+"
          saldo: "+@saldo.to_s+"
          casilla actual:"+ @numcasillaActual.to_s+"\n"
      aux2="Propiedades= "
      for i in 0...@propiedades.size
        aux2=aux2+@propiedades[i].nombre
      end
      return aux+aux2
    end
    def vender(ip ) 
      estado=false
      if @encarcelado ==false
        if existeLaPropiedad(ip) 
          estado=@propiedades[ip].vender(self) #self.instance
          if (estado)
           Diario.instance.ocurre_evento("La propiedad "+@propiedades[ip].nombre+" ha sido vendida por el jugador #{@nombre}")
           @propiedades.delete_at(ip) 
          end
        end

      end
      return estado
    end 
  end
end

