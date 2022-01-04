
import java.util.Vector;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/* 
 * Para la ACB usamos la api de  API-BASKETBALL
 * La idea es almacenar para equipos de la acb 
 */
public class ApiBasketball {
	 int id_l = 117;
	 String season = "2018-2019";
	 Map<String,Integer > Equipos;
	 Map<Integer,Vector<String>> Stats_teams;
	 public ApiBasketball(int id_n) {
		 id_l = id_n;
		 Equipos = new HashMap<String,Integer>();
		 Stats_teams = new HashMap<Integer,Vector<String>>();
		 Obtener_Equipos();
	 }
	 private void meterEquipo(String nombre,int id)
	 {
		 Equipos.put(nombre, id);
	 }
	 public  Map<String,Integer > getEquipos()
	 {
		 /*
		 String equipos="";
		 Iterator it = Equipos.entrySet().iterator();
		 while (it.hasNext()) {
				Map.Entry e = (Map.Entry)it.next();
				equipos = equipos +(e.getKey() + " " + e.getValue()+ "<br>") ;
			}
			*/
		 return Equipos;
	 }
	 public String getStats()
	 {
		 String equipos="";
		 Iterator it = Equipos.entrySet().iterator();
		 while (it.hasNext()) {
				Map.Entry e = (Map.Entry)it.next();
				equipos = equipos +(e.getKey() + " " + e.getValue()+ "<br>") ;
			}
		 return equipos;
	 }
	 public Vector<String> Obtener_Estadisticas_Equipo_API(int id)
	 {
		 if(!Stats_teams.containsKey(id))
		 {
		 HttpRequest request = HttpRequest.newBuilder()
					.uri(URI.create("https://api-basketball.p.rapidapi.com/statistics?season=2018-2019&league="+Integer.toString(id_l)+"&team="+Integer.toString(id)))
					.header("x-rapidapi-key", "")
					.header("x-rapidapi-host", "api-basketball.p.rapidapi.com")
					.method("GET", HttpRequest.BodyPublishers.noBody())
					.build();
		 HttpResponse<String> response_api = null;
		try {
			response_api = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.ofString());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		                                  
		// Convertir  JSON	
		JSONObject jsonObject = null;
		try {
			jsonObject = new JSONObject(response_api.body());
		} catch (JSONException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		//Leer JSON
		JSONObject jsonResponse = null;
		try {
			jsonResponse = jsonObject.getJSONObject("response");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//Subseccion
		JSONObject jsonGAMES = null;
		JSONObject jsonPOINTS= null;
		
		try {
			jsonGAMES = jsonResponse.getJSONObject("games");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			jsonPOINTS = jsonResponse.getJSONObject("points");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		// Leer de GAMES
		JSONObject PartidosGanados = null;
		try {
			PartidosGanados = jsonGAMES.getJSONObject("wins");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
			JSONObject JSON_PartidosGanadosLocal = null;
			
			try {
				JSON_PartidosGanadosLocal = PartidosGanados.getJSONObject("home");
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
				int PartidosGanadosLocal=0;
				try {
					PartidosGanadosLocal = (int)JSON_PartidosGanadosLocal.get("total");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			JSONObject PartidosGanadosVisitante= null;
			
			try {
				PartidosGanadosVisitante = PartidosGanados.getJSONObject("away");
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
				int PartidosGanadosV=0;
				try {
					PartidosGanadosV = (int)PartidosGanadosVisitante.get("total");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			
		JSONObject PartidosPerdidos = null;
		try {
			PartidosPerdidos = jsonGAMES.getJSONObject("loses");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
			JSONObject JSON_PartidosPerdidosLocal = null;
			try {
				JSON_PartidosPerdidosLocal = PartidosPerdidos.getJSONObject("home");
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
				int PartidosPerdidosLocal=0;
				try {
					PartidosPerdidosLocal = (int)JSON_PartidosPerdidosLocal.get("total");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			JSONObject JSON_PartidosPerdidosVisitante= null;
			try {
				JSON_PartidosPerdidosVisitante = PartidosPerdidos.getJSONObject("away");
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
				int PartidosPerdidosVisitante=0;
				try {
					PartidosPerdidosVisitante = (int)JSON_PartidosPerdidosVisitante.get("total");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		
		
		
		
		
		
		
		
		// Leer de POINTS
		int puntosFavor=0;
		try {
			puntosFavor = (int) jsonPOINTS.getJSONObject("for").getJSONObject("total").get("all");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		int puntosEncontra=0;
		try {
			puntosEncontra = (int) jsonPOINTS.getJSONObject("against").getJSONObject("total").get("all");
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Vector<String> Equipo_ID_STATS = new Vector();
		Equipo_ID_STATS.add(Integer.toString(PartidosGanadosLocal));
		System.out.println("Partidos Ganados como local "+PartidosGanadosLocal);
		Equipo_ID_STATS.add(Integer.toString(PartidosGanadosV));
		System.out.println("Partidos Ganados como visitante "+PartidosGanadosV);
		Equipo_ID_STATS.add(Integer.toString(PartidosPerdidosLocal));
		System.out.println("Partidos Perdidos como local "+PartidosPerdidosLocal);
		Equipo_ID_STATS.add(Integer.toString(PartidosPerdidosVisitante));
		System.out.println("Partidos Perdidos como visitante "+PartidosPerdidosVisitante);
		Equipo_ID_STATS.add(Integer.toString(puntosFavor));
		System.out.println("Puntos a favor "+puntosFavor);
		Equipo_ID_STATS.add(Integer.toString(puntosEncontra));
		System.out.println("Puntos encontra "+puntosEncontra);
		Stats_teams.put(id, Equipo_ID_STATS);	
		return Equipo_ID_STATS;
		 }
		 return null;
	 }
	 
	 private void Obtener_Equipos()
	 {
		 System.out.println("ASD");
		 //Peticion
			HttpRequest request = HttpRequest.newBuilder()
					.uri(URI.create("https://api-basketball.p.rapidapi.com/teams?league="+Integer.toString(id_l)+"&season=2018-2019"))
					.header("x-rapidapi-key", "26accdcb0amsh1e38f58b994dd82p15bd79jsn4c4afa3cb0a2")
					.header("x-rapidapi-host", "api-basketball.p.rapidapi.com")
					.method("GET", HttpRequest.BodyPublishers.noBody())
					.build();
			HttpResponse<String> response_api = null;
			try {
				response_api = HttpClient.newHttpClient().send(request, HttpResponse.BodyHandlers.ofString());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
					// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println(response_api.body());
		// Convertir  JSON	
			JSONObject jsonObject = null;
			try {
				jsonObject = new JSONObject(response_api.body());
			} catch (JSONException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			JSONArray jsonArray = null;
			try {
				jsonArray = jsonObject.getJSONArray("response");
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
				
			
			
			int tam = 0;
			try {
				tam = (int) jsonObject.get("results");
			} catch (JSONException e) {
					// TODO Auto-generated catch block
				e.printStackTrace();
			}
			for(int i = 0; i < tam;i++) {
				JSONObject equipoJSON = null;
				try {
					equipoJSON = jsonArray.getJSONObject(i);
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				try {
					this.meterEquipo(equipoJSON.getString("name"),equipoJSON.getInt("id"));
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}	
				
			
	 }
		 
	 
	 
}


