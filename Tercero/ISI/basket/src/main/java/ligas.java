
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Vector;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class ligas
 */
@WebServlet("/ligas")
public class ligas extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private String liga_select;
	private String equipo_select;
	ApiBasketball stats_ACB;
	ApiBasketball stats_NBA;
	NBA iNBA;
	Scrapping iEuroliga;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ligas() {
        super();
        liga_select=equipo_select="";
        
        
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html; charset=utf-8");
		liga_select = request.getParameter("Liga");
		equipo_select = request.getParameter("Equipo");
		PrintWriter out  = response.getWriter();
		
		if (!equipo_select.equals("0"))
		{
		
			out.println(liga_select + equipo_select);
			
			// Enviare a APIS
			switch (liga_select)
			{
				case "12":
					//BD - Acceso 
					// Peticion Equipo a BD
						// Esta - Mostrar plantilla
						// No ESTA - peticion a API --> API Guardar BD
					stats_NBA = new ApiBasketball(12);
					//out.println(stats_NBA.getEquipos());
					
					Map<String,Integer > responseEquipos = new HashMap<String,Integer>();
					
					responseEquipos = stats_NBA.getEquipos();
					
					// Buscar en el Map 
					int id_equipo = responseEquipos.get(equipo_select);
					out.println(id_equipo);
					
					Vector<String> stats_equip_select = stats_NBA.Obtener_Estadisticas_Equipo_API(id_equipo);
					
					out.println("<p>" +equipo_select);
					for (int i = 0 ; i< stats_equip_select.size();i++)
					{
						out.println(" "+ stats_equip_select.get(i) + " ");
					}
					out.println("</p>");
		
					
					break;
				case "2":
						out.println("EN PROCESO DE DESARROLLO");
						break;
				case "117":
						stats_ACB = new ApiBasketball(117);
						out.println(stats_ACB.getEquipos());
						break;
				default:
						break;
				
				
			}
		}
		else
			out.println("En Desarrollo");
		
		
	}
	
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
