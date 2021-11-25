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
public class TituloPropiedad {
    
    //Atributos de clase
    private static float factorInteresHipoteca = (float) 1.1;
    
    private float alquilerBase;
    private float factorRevalorizacion;
    private float hipotecaBase;
    private boolean hipotecado;
    private String nombre;
    private int numCasas;
    private int numHoteles;
    private float precioCompra;
    private float precioEdificar;
    private Jugador propietario;
    
    /*
    
    nombre, precio base de alquiler, factor de revalorización, precio base de hipoteca, precio de
compra y precio por edificar. Debes tener en cuenta que todos los títulos de propiedad
comienzan existiendo sin propietario, casas ni hoteles y sin hipotecar.
    */
    TituloPropiedad(String nom,float alquiler_base, float factor,
                    float base_hipoteca,float precio_compra,
                    float precio_edificar)
    {
        nombre=nom;
        alquilerBase=alquiler_base;
        factorRevalorizacion=factor;
        hipotecaBase=base_hipoteca;
        precioCompra=precio_compra;
        precioEdificar=precio_edificar;
        numCasas=0;
        numHoteles=0;
        propietario=null;
        hipotecado=false;
    }
    @Override
    public String toString ()
    {
        String aB=Float.toString(alquilerBase);
        String fI =Float.toString(factorInteresHipoteca);
        String fR=Float.toString(factorRevalorizacion);
        String hB=Float.toString(hipotecaBase);
        String hip=Boolean.toString(hipotecado);
        String nC=Integer.toString(numCasas);
        String nH=Integer.toString(numHoteles);
        String pC=Float.toString(precioCompra);
        String pD=Float.toString(precioEdificar);
        
        String todo="\n"+nombre+"\nAlquiler base: "+ aB + "\nFactor Interes Hipoteca : ";
        todo+=  fI + "\nfactorRevalorizacion: "+fR + "\nHipoteca: " +hB ;
        todo+="\nEstado hipoteca: "+hip+"\nCasas: "+nC+"\nHoteles: "+"\n "+nH;
        todo+="\nPrecio Compra: "+pC+"\nPrecio Edificar: "+pD+". ";
        
        return todo;
        
    }
    public String getNombre()
    {
        return nombre;
    }
    boolean tienePropietario()
    {
        boolean estado=false;
        if (propietario!=null){
            estado=true;
        }
        return estado;
    }
    public Jugador getPropietario()
    {
        return propietario;
    }
    public int getNumCasas(){
        return numCasas;
    }
    public int getNumHoteles(){
        return numHoteles;
    }
    public float getPrecioAlquiler()
    {
        float precio;
        
        precio = (float) (alquilerBase*(1+(numCasas*0.5)+(numHoteles*2.5)));
        //PrecioAlquiler=AlquilerBase*(1+(NumCasas*0.5)+(NumHoteles*2.5))
        if (propietario.isEncarcelado()||hipotecado)
        {
            precio = 0;
        }
        
        return precio;
    }
    boolean cancelarHipoteca(Jugador jugador){
        boolean estado = false;
        if (esEsteElPropietario(jugador)&&hipotecado)
        {
            estado=true;
            propietario.paga(getImporteCancelarHipoteca());
            hipotecado=false;
        }
        return estado;
    }
    public float getImporteCancelarHipoteca()
    {
        return  (float)(getImporteHipoteca()*factorInteresHipoteca);
    }
    
    boolean hipotecar(Jugador jugador)
    {
        boolean estado = false;
        
        if (esEsteElPropietario(jugador)==true&&hipotecado==false)
        {
            jugador.recibe(getImporteHipoteca());
            hipotecado=true;
            estado =true;
        }
        
        return estado;
        
    }
    public boolean getHipotecado(){
        return hipotecado;
    }
    void tramitarAlquiler(Jugador jugador)
    {
        if (tienePropietario() && esEsteElPropietario(jugador)==false)
        {
            float alquiler = getPrecioAlquiler();
            jugador.pagaAlquiler(alquiler);
            propietario.recibe(alquiler);
        }
    }
    private boolean propietarioEncarcelado()
    {
        boolean estado = false;
            if (propietario.isEncarcelado())
            {
                estado=true;
            }
        return estado;  
    }

    private float getImporteHipoteca() {
        float CantidadRecibida;
        CantidadRecibida=(float) (hipotecaBase*(1+(numCasas*0.5)+(numHoteles*2.5)));
        return CantidadRecibida;
    }
    int cantidadCasasHoteles(){
        return (numCasas+numHoteles);
    }
    boolean derruirCasas(int n,Jugador jugador)
    {
        boolean estado = false;
        if (esEsteElPropietario(jugador)&& numCasas >= n )
        {
            numCasas=numCasas-n;
            estado = true;
        }
        return estado;
    }
    public  float getPrecioVenta(){
        float precio;
        precio = precioCompra +(numCasas+5*numHoteles)*precioEdificar*factorRevalorizacion;
        return precio;
    }
    
    boolean construirCasa(Jugador jugador)
    {
        boolean estado=false;
        if ((esEsteElPropietario(jugador))&& numCasas<jugador.getCasasMax())
        {
            jugador.paga(precioEdificar);
            estado=true;
            numCasas++;
            
        }
        return estado;
    }
    boolean construirHotel(Jugador jugador)
    {
        boolean estado=false;
        if (esEsteElPropietario(jugador))
        {
            if (numHoteles<jugador.getCasasPorHotel())
                
                jugador.paga(precioEdificar*5);
                estado=true;
                numHoteles++;
//                numCasas=numCasas-4;
                
        }
        return estado;
    }
    
    private boolean esEsteElPropietario(Jugador jugador)
    {
        return propietario==jugador;
    }
    boolean comprar(Jugador jugador)
    {
        if(tienePropietario())
            return false;
        else{
            propietario=jugador;
            propietario.paga(precioCompra);
            return true;
        }
    }
    boolean vender(Jugador jugador)
    {
        if(esEsteElPropietario(jugador)){
            propietario.recibe(getPrecioVenta());
            propietario=null;
            numCasas=0;
            numHoteles=0;
            return true;
        }
        else
            return false;
    }
    void actualizaPropietarioPorConversion(Jugador jugador)
    {
        propietario=jugador;
    }
    public float getPrecioCompra()
    {
        return precioCompra;
    }
    public float getPrecioEdificar()
    {
        return precioEdificar;
    }
    public void setPropietario(JugadorEspeculador js)
    {
        propietario=js;
    }
}
