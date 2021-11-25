/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;
import GUI.Dado;
public class Jugador implements Comparable<Jugador> {
    
    protected static int CasasMax=4;
    protected static int CasasPorHotel=4;
    protected boolean encarcelado;
    protected static int HotelesMax=4;
    private String nombre;
    private int numCasillaActual;
    protected static float PasoPorSalida=1000;
    protected static float PrecioLibertad=200;
    private boolean puedeComprar;
    protected float saldo;
    static float SaldoInicial=7500;
    protected ArrayList<TituloPropiedad> propiedades;
    protected SorpresaSalirCarcel salvoconducto;
    protected boolean especulador;
    

    public Jugador(String nom){
        nombre=nom;
        encarcelado=false;
        numCasillaActual=0;
        puedeComprar=true;
        saldo=7500;
        propiedades=new ArrayList<>();
        salvoconducto=null;
        especulador=false;    
    }
    protected Jugador(Jugador otro){
        this.nombre=otro.nombre;
        this.encarcelado=otro.encarcelado;
        this.numCasillaActual=otro.numCasillaActual;
        this.puedeComprar=otro.puedeComprar;
        this.saldo=otro.saldo;
        this.salvoconducto=otro.salvoconducto;
        this.propiedades=otro.propiedades;
        this.especulador=otro.especulador;
    }
    public boolean getEspeculador()
    {
        return especulador;
    }
    @Override
    public String toString() {
        String aux= "\nJugador: ";
        aux+= "\nNombre= " + nombre ;
        aux+= "\nEncarcelado= " + encarcelado ;
        aux+= "\nNumCasillaActual= " + numCasillaActual;
        aux+= "\nPuedeComprar= " + puedeComprar ;
        aux+= "\nSaldo= " + saldo;
        aux+= "\nPropiedades= " + propiedades.toString();
        aux+= "\nSalvoconducto= " + salvoconducto +"\n";
        return aux;
    }
    @Override
    public int compareTo(Jugador otro){

        return Float.compare(this.saldo, otro.saldo);
    }
    boolean comprar(TituloPropiedad titulo){
       boolean result=false;
       if(encarcelado)
           return result;
       if(puedeComprar){
           float precio=titulo.getPrecioCompra();
           if(puedoGastar(precio)){
              result=titulo.comprar(this);
              if(result){
                  propiedades.add(titulo);
                  Diario.getInstance().ocurreEvento("El jugador "+nombre+"compra la propiedad "+titulo.getNombre());
              }
              puedeComprar=false;
           }
       }
       
       return result;
       
    }
    boolean construirHotel(int ip){
        boolean result=false;
        if(encarcelado)
            return result;
       
        if(this.existeLaPropiedad(ip))
        {
            TituloPropiedad propiedad=propiedades.get(ip);
            boolean puedoEdificarHotel=this.puedoEdificarHotel(propiedad);
            float precio=propiedad.getPrecioEdificar();
            if(puedoGastar(precio) && propiedad.getNumHoteles()<this.getHotelesMax() && propiedad.getNumCasas()>=this.getCasasPorHotel()){
               puedoEdificarHotel=true;
            }
            if(puedoEdificarHotel)
            {
               result=propiedad.construirHotel(this);
               propiedad.derruirCasas(CasasPorHotel, this);
               Diario.getInstance().ocurreEvento("El jugador "+nombre+" construye hotel en la propiedad "+propiedades.get(ip).getNombre());
           }
        }

        return result; 
    }
    boolean construirCasa(int ip){
       boolean result=false;
       boolean puedoEdificarCasa=false;
       
        if(encarcelado)
           return result;
        else
        {
            if(existeLaPropiedad(ip)){
                TituloPropiedad propiedad=propiedades.get(ip);
                if(puedoEdificarCasa(propiedad))
                {
                    result=propiedad.construirCasa(this);
                    if(result)
                        Diario.getInstance().ocurreEvento("El jugador "+nombre+" construye casa en la propiedad "+propiedades.get(ip).getNombre());
                }
              
            }
        }
        return result;
       
    }
    
    public String getNombre() {
        return nombre;
    }
    int getNumCasillaActual(){
        return numCasillaActual;
    }
    private void perderSalvoconducto (){
        salvoconducto.usada();
        salvoconducto=null;
    }
    int cantidadCasasHoteles(){
        int contador=0;
        for(int i=0; i<propiedades.size();i++)
        {
            contador+=propiedades.get(i).cantidadCasasHoteles();
        }
       return contador;
   }
    public float getSaldo()
    {
        return saldo;
    }
    protected Boolean existeLaPropiedad(int ip){
       return ip<=propiedades.size();
   }
    boolean tieneSalvoconducto(){
       return salvoconducto!=null;
    }
    boolean obtenerSalvoconducto(SorpresaSalirCarcel s){
       if(encarcelado)
           return false;
       else{
           salvoconducto=s;
           return true;     
       }
    }
    boolean hipotecar(int ip){
       boolean result=false;
       if(encarcelado)
           return result;
       
       if(existeLaPropiedad(ip)){
           TituloPropiedad propiedad=propiedades.get(ip);
           result=propiedad.hipotecar(this);
           if(result)
            Diario.getInstance().ocurreEvento("El jugador "+nombre+" hipoteca la propiedad "+propiedades.get(ip).getNombre());
       }

       return result;
   }
    public boolean isEncarcelado() {
        return encarcelado;
    }
    protected boolean debeSerEncarcelado(){
        boolean estado=false;
        if(isEncarcelado())
            estado=false;
        else
            if(!tieneSalvoconducto())
                estado=true;
            else
            {
                perderSalvoconducto();
                estado=false;
                Diario.getInstance().ocurreEvento("El jugador "+nombre +" se libra de la cárcel"); 
            }
        return estado;
           
   }
    boolean modificarSaldo(float cantidad){
        
        saldo+=cantidad;
        Diario.getInstance().ocurreEvento("Se ha modificado el sueldo del jugador "+nombre);
        return true;
    }
    

    boolean pagaAlquiler(float cantidad) {
        if(encarcelado)
           return false;
        else
           return paga(cantidad);
    }

    boolean paga(float cantidad) {
        return modificarSaldo(cantidad*-1);
    }
    boolean recibe(float cantidad){
        if(encarcelado)
            return false;
        else 
        {
            return modificarSaldo(cantidad); 
        }
    }
    private boolean puedoEdificarCasa(TituloPropiedad propiedad){
        if(encarcelado)
            return false;
   
        if(propiedad.getNumCasas()<=CasasMax)
        return saldo>=propiedad.getPrecioEdificar();
        else
            return false;
          
    }
    
   
    private boolean puedoEdificarHotel(TituloPropiedad propiedad){
        if(encarcelado)
            return false;
        else
        {
            if(propiedad.getNumHoteles()<=HotelesMax && propiedad.getNumCasas()==CasasMax)
                return saldo>=propiedad.getPrecioEdificar();
            else
                return false;      
        }
           
    }

    boolean puedeComprarCasilla() {
        puedeComprar= !encarcelado;
        return puedeComprar;
    }
    
    boolean vender(int ip)
    {
        boolean estado = false;
        if ((!encarcelado)&&(existeLaPropiedad(ip)))
        {
            estado=propiedades.get(ip).vender(this);
            if (estado)
            {
                String msg="La propiedad "+ propiedades.get(ip).getNombre() +" ha sido vendida.";
                Diario.getInstance().ocurreEvento(msg);
                propiedades.remove(ip);
            }
        }
        return estado;
    }
    
    
    boolean pagaImpuesto(float cantidad) {
        if(encarcelado)
            return false;
        else
            return paga(cantidad);
    }
    protected boolean puedoGastar (float precio){
       if(encarcelado)
            return false;
       else
            return saldo>=precio;
   }
    boolean encarcelar(int numCasillaCarcel) {
        if(debeSerEncarcelado())
        {
            encarcelado=true;
            moverACasilla(numCasillaCarcel);
            Diario.getInstance().ocurreEvento("Jugador encarcelado: "+nombre);
        } 
        return encarcelado;
    }

    boolean tieneAlgoQueGestionar() {
        return propiedades!=null;
    }
    boolean moverACasilla(int numCasilla){
        boolean estado=false;
        if(!encarcelado){
           numCasillaActual=numCasilla;
           puedeComprar=false; 
           Diario.getInstance().ocurreEvento("El jugador "+ nombre + " desplazado a: "+ Float.toString(numCasillaActual));
           estado= true;
        }
        return estado;
   }
    
    private Boolean puedeSalirCarcelPagando(){
        return saldo>=PrecioLibertad;
    }
    boolean pasaPorSalida(){
        modificarSaldo(PasoPorSalida);
        Diario.getInstance().ocurreEvento("El jugador "+nombre+" pasa por la casilla Salida");
        return true;
    }
    boolean salirCarcelPagando(){
        boolean estado=false;
        if(encarcelado && puedeSalirCarcelPagando()){
           paga(PrecioLibertad);
           encarcelado=false;
           Diario.getInstance().ocurreEvento("El jugador "+nombre+" ha salido de la carcel pagando");
           estado= true;
        }
       
        return estado;
    }
    boolean salirCarcelTirando(){
        if(Dado.getInstance().salgoDeLaCarcel()){
            encarcelado=false;
            Diario.getInstance().ocurreEvento("El jugador "+nombre+" ha salido de la carcel tirando");
            return true;
        }
        else
            return false;
    }
    boolean enBancarrota(){
       return saldo<=0;
    }
    protected int getCasasMax(){
       return CasasMax;
    }
   
    int getCasasPorHotel(){
        return CasasPorHotel;
    }
   
    protected int getHotelesMax(){
        return HotelesMax;
    }
    public ArrayList<String> getNombrePropiedades(){
       ArrayList<String> aux = new ArrayList<>();
       
       for(int i=0;i<propiedades.size();i++)
           aux.add(propiedades.get(i).getNombre());
       
       return aux;
       
    }
    private float getPrecioLibertad(){
        return PrecioLibertad;
    }
   
    private float getPremioPasoSalida(){
        return PasoPorSalida;
    }
    public ArrayList<TituloPropiedad> getPropiedades(){
        return propiedades;
    }
   
    boolean getPuedeComprar(){
        return puedeComprar;
    }
    boolean cancelarHipoteca(int ip){
        boolean result=false;
        if(encarcelado)
            return result;
       
        if(existeLaPropiedad(ip)){
            TituloPropiedad propiedad=propiedades.get(ip);
            float cantidad=propiedad.getImporteCancelarHipoteca();
            boolean puedoGastar=puedoGastar(cantidad);
            
            if(puedoGastar){
                result=propiedad.cancelarHipoteca(this);

                if(result)
                  Diario.getInstance().ocurreEvento("El jugador "+nombre+" cancela la hipoteca de la propiedad "+propiedades.get(ip).getNombre());
                
            }
        }
        
        return result;
       
       
   }
}
