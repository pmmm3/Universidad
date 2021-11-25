package p1;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.List;
import org.apache.tika.sax.Link;
import org.apache.tika.sax.BodyContentHandler;
import org.apache.poi.ss.formula.functions.T;
//import org.xml.sax.*;
import org.apache.tika.Tika;
import org.apache.tika.detect.AutoDetectReader;
import org.apache.tika.exception.TikaException;
import org.apache.tika.metadata.Metadata;
import org.apache.tika.parser.AutoDetectParser;
import org.apache.tika.parser.ParseContext;
import org.apache.tika.langdetect.OptimaizeLangDetector;
import org.apache.tika.language.detect.LanguageDetector;
import org.apache.tika.language.detect.LanguageResult;

public class p1 {

	public static void imprimirDatos(ArrayList<parser_archivos> archivos) throws IOException, TikaException, Exception {

		// array donde meteremos todos los paths de la carpeta

		System.out.println("Estamos buscando en la carpeta");
		System.out.println(
				"-----------------------------------------------------------------------------------------------------------");
		System.out.println("|\tNOMBRE\t|\tTIPO FICHERO\t\t\t|\tCODIFICACION\t|\tIDIOMA\t|");
		System.out.println(
				"-----------------------------------------------------------------------------------------------------------");

		for (parser_archivos i : archivos) {
			System.out.println(" + " + i.getName() + "\t|\t" + i.getTipo() + "\t|\t" + i.getEncoding() + "\t\t|\t"
					+ i.getLanguage() + "\t|\t");
		}
		System.out.println(
				"-----------------------------------------------------------------------------------------------------------");

	}

	public static void mostrarEnlaces(ArrayList<parser_archivos> archivos) {
		System.out.println("\nEnlaces:");
		System.out.println(
				"-----------------------------------------------------------------------------------------------------------");

		for (parser_archivos i : archivos) {
			System.out.println("\nEnlaces de :" + i.getName() + "\n");
			List<Link> enlaces = i.getEnlaces();
			for (Link j : enlaces) {
				System.out.println(" + " + j.getText());
			}
			System.out.println(
					"-----------------------------------------------------------------------------------------------------------");
		}

	}

	public static void generar(ArrayList<parser_archivos> archivos) throws IOException {

		// System.out.println(archivos.get(0).LimpiarTexto());
		BufferedWriter bw;
		for (parser_archivos i : archivos) {
			String path_aux = "./csv/" + i.getName() + ".csv";
			File archivo_nuevo = new File(path_aux);

			bw = new BufferedWriter(new FileWriter(archivo_nuevo));
			bw.write(i.imprimirCSV());

			bw.close();
		}
		
		

	}

	public static void main(String[] args) throws TikaException, Exception {
		System.out.println("\nCargando datos....\n");

		// Creacion del Menu
		boolean bucle = true;

		// cargar archivos
		String aux = args[0] + "/";
		File carpeta = new File(aux);
		String[] paths = carpeta.list();
		ArrayList<parser_archivos> archivos = new ArrayList<>();
		if (paths == null || paths.length == 0) {
			System.out.println("No hay ningun documento en la carpeta " + aux);
			System.exit(-1);

		} else {

			for (int i = 0; i < paths.length; i++) {
				String act = aux + paths[i];
				parser_archivos archivo_nuevo = new parser_archivos(act);
				archivos.add(archivo_nuevo);
			}

		}

		while (bucle) {

			Scanner entrada = new Scanner(System.in);
			System.out.println("\nELIJA LA OPCION DE QUE DESEE:");
			System.out.println("-d: Tabla con informacion de los ficheros.");
			System.out.println("-l: Enlaces extraidos de los documentos");
			System.out.println("-t Generacion archivos CSV de frecuencia de palabras");
			System.out.println("-s para salir");
			String option = entrada.next();
			System.out.println("\n");
			switch (option) {

			case "-d":
				imprimirDatos(archivos);
				break;
			case "-l":
				mostrarEnlaces(archivos);
				break;
			case "-t":
				generar(archivos);
				break;
			case "-s":
				bucle = false;
				break;
			default:
				System.out.println("Tecla incorrecta por favor vuelva a pulsa alguna de las opciones indicadas");

			}

		}

		System.exit(0);
	}

}
