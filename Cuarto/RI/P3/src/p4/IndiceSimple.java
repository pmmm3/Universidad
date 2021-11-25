package p4;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.opencsv.CSVReader;
import org.apache.lucene.document.Field;
import org.apache.commons.io.FilenameUtils;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.core.KeywordAnalyzer;
import org.apache.lucene.analysis.core.SimpleAnalyzer;
import org.apache.lucene.analysis.core.WhitespaceAnalyzer;
import org.apache.lucene.analysis.miscellaneous.PerFieldAnalyzerWrapper;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.analysis.standard.UAX29URLEmailAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.search.similarities.ClassicSimilarity;
import org.apache.lucene.search.similarities.Similarity;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

public class IndiceSimple {
    String indexPath = "./index";
    String docPath = "./csv";

    boolean create = true;

    IndiceSimple() {

    }

    private IndexWriter writer;

    private static String separador() {
        int tam = 78;
        String inicio = "|";
        String fin = "|";
        String mitad = "";
        for (int i = 0; i < tam; i++) {
            mitad += "-";
        }
        return inicio + mitad + fin;
    }

    public static void main(String[] args) throws IOException {
        System.out.println(separador());
        System.out.println("\tAñadiendo varios documentos a un índice Lucene");
        System.out.println(separador());

        // Analizador a utilizar

        Analyzer analyzer_por_defecto = new KeywordAnalyzer();
        Map<String, Analyzer> analizadores = new HashMap<>();
        analizadores.put("Link", new UAX29URLEmailAnalyzer());
        analizadores.put("Authors", new SimpleAnalyzer());
        analizadores.put("Author(s) ID", new StandardAnalyzer());
        analizadores.put("Affiliations", new StandardAnalyzer());
        analizadores.put("Link", new StandardAnalyzer());

        PerFieldAnalyzerWrapper analyzer = new PerFieldAnalyzerWrapper(analyzer_por_defecto, analizadores);
        // Medida de Similitud ( modelo de recuperacion) BM25

        Similarity similarity = new ClassicSimilarity();

        // Constructor

        IndiceSimple baseline = new IndiceSimple();

        // Creamos el indice

        baseline.configurarIndice(analyzer, similarity);

        // Insertamos los documentos

        baseline.indexarDocumentos();

        // Cerramos el indice

        baseline.close();

    }

    public void configurarIndice(Analyzer analyzer, Similarity similarity) throws IOException {
        IndexWriterConfig iwc = new IndexWriterConfig(analyzer);
        iwc.setSimilarity(similarity);

        // Crea un nuevo indice y si no inserta a uno existente
        iwc.setOpenMode(IndexWriterConfig.OpenMode.CREATE);
        // iwc.setOpenMode(IndexWriterConfig.OpenMode.CREATE_OR_APPEND);

        // Localizacion del indice
        Directory dir = FSDirectory.open(Paths.get(indexPath));

        // Creamos el indice

        writer = new IndexWriter(dir, iwc);

    }

    public void indexarDocumentos() throws IOException {

        // Para cada documento csv de la carpeta "csv"

        File carpeta = new File(docPath);

        for (File file : carpeta.listFiles()) {

            if (!file.isDirectory() && FilenameUtils.getExtension(file.getName()).equals("csv")) {
                System.out.println(file.getName());
                // leemos el csv

                try (CSVReader reader = new CSVReader(new FileReader(docPath + "/" + file.getName()))) {

                    List<String[]> r = reader.readAll();
                    for (int i = 1; i < r.size(); i++) {
                        String[] fila = r.get(i);
                        // Creamos el documento Lucene

                        Document doc = new Document();
                        System.out.println("Indexando la fila : ");
                        // Autores 0
                        doc.add(new TextField("Authors", fila[0], Field.Store.YES));
                        // Autores ID 1
                        doc.add(new TextField("Authors ID", fila[1], Field.Store.YES));
                        // Titulo 2
                        System.out.println(fila[2]);
                        doc.add(new TextField("titulo", fila[2], Field.Store.YES)); // por defecto no se almacena
                        // Link 13
                        doc.add(new TextField("Link", fila[13], Field.Store.NO));
                        // Abstract 16

                        // Authro Keyword 17

                        // IndexKeyword 18

                        writer.addDocument(doc);

                    }
                    // Authors,Author(s) ID,Title,Year,Source title,Volume,Issue,Art. No.,Page
                    // start,Page end,Page count,Cited by,DOI,Link,Affiliations,Authors with
                    // affiliations,Abstract,Author Keywords,Index Keywords,Document
                    // Type,Publication Stage,Open Access,Source,EID
                }

            }
        }
    }

    public void close() {
        try {
            writer.commit();
            writer.close();
        } catch (IOException e) {
            System.err.println("Error cerrando el indice");
        }
    }

}
