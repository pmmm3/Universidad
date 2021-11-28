

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
 * Servlet implementation class plantilla
 */
@WebServlet("/plantilla")
public class plantilla extends HttpServlet {
	private static final long serialVersionUID = 1L;
	String equipo_select;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public plantilla() {
        super();
        equipo_select="";
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		PrintWriter out  = response.getWriter();
		equipo_select = request.getParameter("equipo");
		response.setContentType("text/html; charset=utf-8");
		if (!equipo_select.equals("0"))
		{
		
		NBA nba = new NBA();
		Map<String,Integer > responseEquipos = new HashMap<String,Integer>();
		
		
		responseEquipos = nba.getEquipos();
		/*
		String equipos="";
		 Iterator it = responseEquipos.entrySet().iterator();
		 while (it.hasNext()) {
				Map.Entry e = (Map.Entry)it.next();
				equipos = equipos +(e.getKey() + " " + e.getValue()+ "<br>") ;
			}
		out.println(equipos);
		/*/
		int id_equipo = responseEquipos.get(equipo_select);
		// Buscar en el Map 
		//out.println(id_equipo);
		
		Vector<String> players_equip_select = nba.Obtener_Jugadores_Equipo(id_equipo);
		
		out.println("<p>" +equipo_select);
		for (int i = 0 ; i< players_equip_select.size();i++)
		{
			out.println(" "+ players_equip_select.get(i) + "<br>");
			
		}
		out.println("</p>");
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
