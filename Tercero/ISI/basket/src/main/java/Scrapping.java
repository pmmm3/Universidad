

import java.io.IOException;
import java.util.Vector;

import org.jsoup.Connection.Response;
import org.jsoup.Jsoup;
import org.jsoup.nodes.*;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class Scrapping {
	String Temporada;
	String url;
	Scrapping(String Temp)
	{
		Temporada=Temp;
		url= "https://www.mundodeportivo.com/resultados/baloncesto/euroliga/clasificacion/"+Temporada;
	}
	public static int getStatusConnectionCode(String url) {
		
	    Response response = null;
		
	    try {
		response = Jsoup.connect(url).userAgent("Mozilla/5.0").timeout(100000).ignoreHttpErrors(true).execute();
	    } catch (IOException ex) {
		System.out.println("Excepción al obtener el Status Code: " + ex.getMessage());
	    }
	    return response.statusCode();
	}
	public static Document getHtmlDocument(String url) {

	    Document doc = null;
		try {
		    doc = Jsoup.connect(url).userAgent("Mozilla/5.0").timeout(100000).get();
		    } catch (IOException ex) {
			System.out.println("Excepción al obtener el HTML de la página" + ex.getMessage());
		    }
	    return doc;
	}
	
	
	
	public  Vector<Vector<String>> obtenerClasificacion() {
		Vector<Vector<String>> todo=new Vector<Vector<String>>();
		// Compruebo si me da un 200 al hacer la petición
		 if (getStatusConnectionCode(url) == 200) {
			 
			// Obtengo el HTML de la web en un objeto Document
	            Document document = getHtmlDocument(url);
	         // Busco todas las entradas que estan dentro de: 
	            Elements entradas = document.select("tbody > tr").not(".table-header");
	            //System.out.println(tbody);
	            //Elements entradas = (tbody).children();
	            
	            //System.out.println("Número de entradas en la página: "+entradas.size()+"\n");
	            
	            for (Element elem : entradas) {
	            	Vector<String> sol = new Vector<String>();
	                String nombre_Equipo = elem.getElementsByTag("a").text();
	                sol.add(nombre_Equipo);
	                Elements stats = elem.getElementsByClass("tval text-center");
	                for (Element i : stats) {
	                	String pj = i.text();
	                	//System.out.print(" "+pj+ " ");
	                	sol.add(pj);
	                }
	                //System.out.println("");
	                todo.add(sol);
	                
	           
					
	                // Con el método "text()" obtengo el contenido que hay dentro de las etiquetas HTML
	                // Con el método "toString()" obtengo todo el HTML con etiquetas incluidas
	            }
			 
	            
			 
			 
		 }
		 else
	         System.out.println("El Status Code no es OK es: "+getStatusConnectionCode(url));
		 return todo;
		 }
	
}
