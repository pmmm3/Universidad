/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

/**
 *
 * @author pc
 */
class JugadorEspeculador extends Jugador  {
    private static int FactorEspeculador=2;
    private int fianza;
    
    JugadorEspeculador(Jugador jugador, int f){
        super(jugador);
        especulador=true;
        fianza=f;
        actualizaPropietarioPorConversion();
    }
    private void actualizaPropietarioPorConversion()
    {
        for(int i=0;i<super.propiedades.size();i++)
        {
            propiedades.get(i).setPropietario(this);
        }
    }
    private boolean puedePagarFianza(){
        boolean puedePagar = false;
        
        if(saldo>=fianza){
            modificarSaldo(-(this.fianza));
            puedePagar = true;
        }
        
        return puedePagar;
    }
    @Override
    protected boolean debeSerEncarcelado(){
        boolean resultado = false;
        if(super.debeSerEncarcelado() ){
            if(!puedePagarFianza())
            resultado = true;
        }
        
        return resultado;
    }
    private boolean puedoEdificarCasa(TituloPropiedad propiedad){
        if(encarcelado)
            return false;
   
        if(propiedad.getNumCasas()< getCasasMax())
        return saldo>=propiedad.getPrecioEdificar();
        else
            return false;
    }
    private boolean puedoEdificarHotel(TituloPropiedad propiedad){
        if(encarcelado)
            return false;
        else
        {
            if(propiedad.getNumHoteles()<getHotelesMax() && propiedad.getNumCasas()>=4)
                return saldo>=propiedad.getPrecioEdificar();
            else
               return false;      
        }
           
    }
    @Override
    boolean pagaImpuesto(float cantidad){
        if(encarcelado)
            return false;
       
        else
            return paga(cantidad/FactorEspeculador);
                    
    }
    @Override
    protected int getCasasMax(){
        return CasasMax*FactorEspeculador;
    }
   
    @Override
    protected int getHotelesMax(){
        return HotelesMax*FactorEspeculador;
    }
    @Override
    public String toString() {
        return "JugadorEspeculador: "+ this.getNombre() + "\n\tfianza : " + fianza +"\n\tencarcelado: " + super.encarcelado  + "\n\tnumCasillaActual=" + this.getNumCasillaActual() + "\n\tpuedeComprar=" + this.getPuedeComprar() + "\n\tsaldo=" + saldo + "\n\tpropiedades=" + propiedades.toString() + "\n\tsalvoconducto=" + super.salvoconducto +"\n";
    }
    @Override
    boolean construirCasa(int ip)
    {
        boolean result=false;
        boolean puedoEdificarCasa=false;

        if(encarcelado)
            return result;
        else{
            boolean existe=this.existeLaPropiedad(ip);
            if(existe)
            {
                TituloPropiedad propiedad=propiedades.get(ip);
                puedoEdificarCasa=this.puedoEdificarCasa(propiedad);
                if(puedoEdificarCasa)
                {
                    result=propiedad.construirCasa(this);
                    if(result)
                        Diario.getInstance().ocurreEvento("El jugador "+this.getNombre()+" construye casa en la propiedad "+propiedades.get(ip).getNombre());
                }

            }
        }
        return result;
       
    }
    @Override
    boolean construirHotel(int ip){
        boolean result=false;
        if(encarcelado)
            return result;

        if(this.existeLaPropiedad(ip))
        {
            TituloPropiedad propiedad=propiedades.get(ip);
            boolean puedoEdificarHotel=this.puedoEdificarHotel(propiedad);
            float precio=propiedad.getPrecioEdificar();
            if(puedoGastar(precio) && propiedad.getNumHoteles()<this.getHotelesMax() && propiedad.getNumCasas()>=this.getCasasPorHotel())
            {
                puedoEdificarHotel=true;
            }
            if(puedoEdificarHotel)
            {
                result=propiedad.construirHotel(this);
                propiedad.derruirCasas(CasasPorHotel, this);
                Diario.getInstance().ocurreEvento("El jugador "+this.getNombre()+" construye hotel en la propiedad "+propiedades.get(ip).getNombre());
            }
        }


       return result; 
    }
    
}
