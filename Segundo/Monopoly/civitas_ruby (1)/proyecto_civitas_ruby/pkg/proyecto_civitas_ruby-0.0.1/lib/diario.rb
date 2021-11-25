require 'singleton'
module Civitas
  class Diario
    
    include Singleton
    #private solo si queremos quitar lo de singleton y que haga lo mismo
    # @@instance=nil
    
    # def self .crear_instancia
    #  if @@instance ==nil
    #    @@instance = Diario.new
    #  end
    #end
    
    #def self .getInstancia
    #  return @@instance
    #end
  
    
    #private # solo si queremos quitar lo de singleton y que haga lo mismo
    def initialize
      @eventos = []
    end
    public
    def ocurre_evento(e)
      @eventos << e
    end

    def eventos_pendientes
      return (@eventos.length > 0)
    end

    def leer_evento
      e = @eventos.shift
      return e
    end

  end
end