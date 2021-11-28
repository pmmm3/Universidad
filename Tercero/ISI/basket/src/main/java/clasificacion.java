

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Vector;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class clasificacion
 */
@WebServlet("/clasificacion")
public class clasificacion extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private String liga_select;
	private String temp_select;
	Scrapping iEuroliga;
    /**
     * @see HttpServlet#HttpServlet()
     */
    public clasificacion() {
        super();
        liga_select="";
        iEuroliga=null;
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.setContentType("text/html; charset=utf-8");
		PrintWriter out  = response.getWriter();
		
		liga_select = request.getParameter("Liga");
		temp_select = request.getParameter("Temporada");
		
		out.println("<table class='tclass'>");
		switch (liga_select)
		{
		case "0":
			break;
		case "1":
			out.print("<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"styles/index.css\"></head>");
			out.println("<tr><th>Posicion</th><th>Nombre</th><th>PJ</th><th>PG</th><th>PP</th><th>%PG</th></tr>");
			iEuroliga = new Scrapping(temp_select);
			Vector<Vector<String>> clasificacion = iEuroliga.obtenerClasificacion();
			
			int pos=1;
			for (Vector<String> fila : clasificacion)
			{
				out.println("<tr>");
				out.println("<td>" + (pos++) + "</td>");
				for (String stats : fila) {
					out.println("<td>" + stats + "</td>");
				}
				out.println("</tr>");
			}
				
			break;
		default: 
			break;
		}
		out.println("</table>");
			
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
