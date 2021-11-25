package p1;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.text.Normalizer;
import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.LinkedHashMap;

import com.uwyn.jhighlight.tools.StringUtils;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.LinkedList;
import org.apache.tika.Tika;
import org.apache.tika.exception.TikaException;
import org.apache.tika.language.detect.LanguageResult;
import org.apache.tika.metadata.Metadata;
import org.apache.tika.sax.BodyContentHandler;

import org.apache.tika.parser.ParseContext;
import org.apache.tika.parser.AutoDetectParser;
import org.apache.tika.langdetect.OptimaizeLangDetector;
import org.apache.tika.language.detect.LanguageDetector;

import org.apache.tika.sax.Link;
import org.apache.tika.sax.LinkContentHandler;
import org.apache.tika.sax.TeeContentHandler;

public class parser_archivos {

    HashMap<String, Integer> conteoPalabras;
    String path;
    public File archivo;
    InputStream is; // stream de bytes del que lee el parser
    Metadata meta; // parámetro tanto de entrada como de salida, y es utilizado para representar
                   // los metadatos del documento
    BodyContentHandler ch; // stream de datos es escrito en el handler en formato estructurado, XHTML
    ParseContext parserContext; /*
                                 * modificar el comportamiento de ContentHandler indicando información del
                                 * contexto concreto sobre el vamos a trabajar
                                 */
    AutoDetectParser parser;
    String tipo;
    static Tika tika = new Tika();
    List<Link> enlaces;
    String text;

    public parser_archivos(String path) throws IOException, TikaException, Exception {
        this.path = path;
        enlaces = new ArrayList<Link>();
        archivo = new File(path);
        conteoPalabras = new HashMap<String, Integer>();
        text = "";
        try {
            is = new FileInputStream(archivo); // open stream
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();

        }
        meta = new Metadata();
        ch = new BodyContentHandler();
        LinkContentHandler linkHandler = new LinkContentHandler();
        TeeContentHandler teeHandler = new TeeContentHandler(linkHandler, ch);

        parserContext = new ParseContext();
        parser = new AutoDetectParser();

        try {
            parser.parse(is, teeHandler, meta, parserContext); // parse
            enlaces = linkHandler.getLinks();
        } finally {
            is.close(); // close stream
        }
        // Para que texto tenga valor
        getLanguage();
    }

    public String getName() {
        String name = archivo.getName();
        final int lastPeriodPos = name.lastIndexOf('.');
        if (lastPeriodPos <= 0) {

            return name;
        } else {

            return name.substring(0, lastPeriodPos);
        }

    }

    public String getTipo() {
        return meta.get(Metadata.CONTENT_TYPE);
    }

    public String getEncoding() {
        return meta.get(Metadata.CONTENT_ENCODING);
    }

    public List<Link> getEnlaces() {
        // LinkContentHandler linkHandler = new LinkContentHandler();
        // enlaces = linkHandler.getLinks();
        return enlaces;
    }

    public String getLanguage() {
        if (text == "")
        {
            try {
                text = tika.parseToString(archivo);
            } catch (IOException | TikaException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
            LanguageDetector identifier;
            try {
                identifier = new OptimaizeLangDetector().loadModels();
                LanguageResult resultado = identifier.detect(text);
                return resultado.getLanguage();
            } catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            return null;



    }

    public String getTexto() {

        return text;
    }

    public void LimpiarTexto() {
        // El String de normal no es iterable, lo pasamos array de String
        String[] texto_aux = text.split("\\s");

        for (String palabra : texto_aux) {
            String cadenaNormalize = Normalizer.normalize(palabra, Normalizer.Form.NFD);
            String cadenaSinAcentos = cadenaNormalize.replaceAll("[^\\p{ASCII}]", "");
            String cadenaSinPuntos = cadenaSinAcentos.replaceAll("[\\p{Punct}]", "");
            String minuscula = org.apache.commons.lang3.StringUtils.lowerCase(cadenaSinPuntos);
            if (conteoPalabras.containsKey(minuscula)) {
                int num = conteoPalabras.get(minuscula) + 1;
                conteoPalabras.put(minuscula, num);
            } else
                conteoPalabras.put(minuscula, 1);

        }
        ordenarHashPorValor();

    }

    // https://www.geeksforgeeks.org/sorting-a-hashmap-according-to-values/
    private void ordenarHashPorValor() {

        // Creamos una lista para almacenar el hash
        // Map entry devuelve el par del hash
        List<Map.Entry<String, Integer>> lista_aux;
        lista_aux = new LinkedList<Map.Entry<String, Integer>>(conteoPalabras.entrySet());

        // Ordenamos la lista
        Collections.sort(lista_aux, (i1, i2) -> i2.getValue().compareTo(i1.getValue()));

        // Volcamos en hashmap
        HashMap<String, Integer> temp = new LinkedHashMap<String, Integer>();
        for (Map.Entry<String, Integer> aa : lista_aux) {
            temp.put(aa.getKey(), aa.getValue());
        }
        conteoPalabras = temp;
    }

    public String imprimirCSV() {
        LimpiarTexto();
        String CSV = "";
        for (String clave : conteoPalabras.keySet()) {
            int valor = conteoPalabras.get(clave);
            CSV += (clave + ";" + valor + "\n");
        }
        return CSV;
    }
}
