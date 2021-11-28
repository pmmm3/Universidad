

import java.io.IOException;
import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Vector;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class NBA {
	int league = 0; //standard
	Map<String,Integer > Equipos;
	Map<Integer,Vector<String>> Jugadores;
	public NBA() {
		 Equipos = new HashMap<String,Integer>();
		 Jugadores = new HashMap<Integer,Vector<String>>();
		 Obtener_Equipos_Api();
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
	 Vector<String> Obtener_Jugadores_Equipo(int id_team)
	 {
		 Vector<String> jugadores_equipo = new Vector<String>();
		 HttpRequest request = HttpRequest.newBuilder()
					.uri(URI.create("https://api-nba-v1.p.rapidapi.com/players/teamId/"+Integer.toString(id_team)))
					.header("x-rapidapi-key", "360809f858msh80877f3455ec74ep1cd698jsn4661358865a9")
					.header("x-rapidapi-host", "api-nba-v1.p.rapidapi.com")
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
					// API JSON 
						JSONObject jsonApi = null;
						try {
							jsonApi = jsonObject.getJSONObject("api");
						} catch (JSONException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					// Teams
						JSONArray jsonPlayers = null;
						try {
							jsonPlayers = jsonApi.getJSONArray("players");
						} catch (JSONException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
						
					int tam = jsonPlayers.length();
					for (int i = 0 ; i < tam ; i++)
					{
						JSONObject jugadorJSON = null;
						try {
							jugadorJSON = jsonPlayers.getJSONObject(i);
						} catch (JSONException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						try {
							String msg = (jugadorJSON.getString("firstName")+" " +jugadorJSON.getString("lastName"));
							jugadores_equipo.add(msg);
							//System.out.println(msg);
						} catch (JSONException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						
						
						
					}
		 return jugadores_equipo;
		 
	 }
	 
	 private void Obtener_Equipos_Api()
	 {
		//Peticion
		 HttpRequest request = HttpRequest.newBuilder()
					.uri(URI.create("https://api-nba-v1.p.rapidapi.com/teams/league/standard"))
					.header("x-rapidapi-key", "360809f858msh80877f3455ec74ep1cd698jsn4661358865a9")
					.header("x-rapidapi-host", "api-nba-v1.p.rapidapi.com")
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
		// System.out.println(response_api.body());
		// Convertir  JSON	
			JSONObject jsonObject = null;
			try {
				jsonObject = new JSONObject(response_api.body());
			} catch (JSONException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		// API JSON 
			JSONObject jsonApi = null;
			try {
				jsonApi = jsonObject.getJSONObject("api");
			} catch (JSONException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		// Teams
			JSONArray jsonTeams = null;
			try {
				jsonTeams = jsonApi.getJSONArray("teams");
			} catch (JSONException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
		int tam = jsonTeams.length();
		for (int i = 0 ; i < tam ; i++)
		{
			JSONObject equipoJSON = null;
			try {
				equipoJSON = jsonTeams.getJSONObject(i);
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			try {
				Equipos.put(equipoJSON.getString("nickname"),equipoJSON.getInt("teamId"));
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
			
	 }
	 
	 
}
