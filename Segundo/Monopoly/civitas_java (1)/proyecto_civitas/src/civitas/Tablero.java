/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package civitas;

import java.util.ArrayList;

/**
 *
 * @author pc
 */
public class Tablero
{
    private int numCasillaCarcel;
    private ArrayList <Casilla> casillas;
    private int porSalida;
    private boolean tieneJuez;
    
    Tablero (int pos_carcel)
    {
        if (pos_carcel >=1)
            numCasillaCarcel = pos_carcel;
        else
            numCasillaCarcel = 1;
        
        casillas=new ArrayList();
          
        Casilla salida = new Casilla ("Salida");
        casillas.add(salida);
        porSalida=0;
        tieneJuez=false;
        
    }
    
    
    private Boolean correcto()
    {
        Boolean es_correcto = false;
        
        if ((casillas.size() > numCasillaCarcel)&&tieneJuez)
        {
            es_correcto = true;
        }
        return es_correcto;
    }
    private Boolean correcto(int numCasilla)
    {
        Boolean es_correcto = false;
        
        if (this.correcto() && numCasilla <= casillas.size())
        {
            es_correcto = true;
        }
        return es_correcto;
    }
    
    int getCarcel (){
        return numCasillaCarcel;
    }
    
    int getPorSalida()
    {
        int aux = porSalida;
        if (porSalida > 0)
        {
            porSalida = porSalida - 1;
        }    
        return aux;
    }
    
    void añadeCasilla (Casilla casilla)
    {
        if (casillas.size()== numCasillaCarcel)
        {
            Casilla carcel = new Casilla ("Cárcel");
            casillas.add(carcel);
        }
        casillas.add(casilla);
        
    }
    void añadeJuez()
    {
        if (tieneJuez==false){
            Casilla juez = new Casilla ("Juez");
            casillas.add(juez);
            tieneJuez=true;
        }
    }
    Casilla getCasilla (int numCasilla)
    {
        Casilla casilla = null;
        if (correcto(numCasilla))
        {
            casilla = casillas.get(numCasilla);
        }
        return casilla;
    }
    int nuevaPosicion (int actual, int tirada)
    {
        if(correcto()){
            int pos1=actual+tirada;
            int pos2=(pos1)%casillas.size();
            if(pos1==pos2)
                return pos1;
            else 
            {
                porSalida++;
                return pos2;
            }
        }
        else
            return -1;
    }
    
    int calcularTirada (int origen, int destino)
    {
        int tirada;
        tirada = destino - origen;
        if (tirada <0){
            porSalida++;
            tirada = tirada + casillas.size();
        }
        return tirada;
    }
}