# encoding:utf-8
module Civitas
  class MazoSorpresas
    private 
    def init
      @sorpresas = Array.new
      @usadas=0
      @barajada=false
      @cartasEspeciales = Array.new
      @ultimaSorpresa=nil
    end
    public
    def initialize (estado=nil)
      
      if (estado==nil)
        init
        @debug=false
      else
        @debug=estado
        init
        if (estado)
          msg = "Modo debug activado en el Mazo Sorpresas"
          Diario.instance.ocurre_evento(msg)
        end
      end
     
    end
    
    def alMazo (s)
      if @barajada ==false then
        @sorpresas<<s
      end
    end
    
    def Siguiente 
      
      if ((@barajada==false)||(@sorpresas.size==@usadas)) then
        if (@debug == false) then
          @sorpresas.shuffle
        end
        @usadas=0
        @barajada=true
        
      end
      @usadas = @usadas + 1 
      @ultimaSorpresa = @sorpresas[0]
      @sorpresas.delete_at(0)
      @sorpresas<<@ultimaSorpresa
      return @ultimaSorpresa
      
 
    end
    
    
    def inhabilitarCartaEspecial (sorpresa)
#     enelmazo= @sorpresas.include?(sorpresa)
#     if (enelmazo==true)
#         
#            @sorpresas.delete(sorpresa)
#            @cartasEspeciales.push(sorpresa)
#           Diario.instance.ocurreEvento("Se ha quitado una carta del mazo")
#     end  
      for i in 0...@sorpresas.size
        if(@sorpresas[i]==sorpresa)
            a=@sorpresas[i]
            @sorpresas.delete_at(i)
            @cartasEspeciales<<a
            Diario.instance.ocurre_evento('Se ha inhabilitado una carta del mazo sorpresas y se ha añadido al de cartas especiales')
        end
      end
    end
    
    def habilitarCartaEspecial (sorpresa)
#     enelmazo= @cartasEspeciales.include?(sorpresa)
#     if (enelmazo==true)
#         
#            @cartasEspeciales.delete(sorpresa)
#            @sorpresas.push(sorpresa)
#           Diario.instance.ocurreEvento("Se ha añadido una carta del mazo")
#     end  
    for i in 0...@cartasEspeciales.size
      if(@cartasEspeciales[i]==sorpresa)
          a=@cartasEspeciales[i]
          @cartasEspeciales.delete_at(i)
          @sorpresas<<a
          Diario.instance.ocurre_evento('Se ha habilitado una carta al mazo sorpresas  de las cartas especiales')
      end
    end  
    end
    
  end
end