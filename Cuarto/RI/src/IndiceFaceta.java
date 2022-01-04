

import java.io.File;
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
import org.apache.lucene.analysis.miscellaneous.PerFieldAnalyzerWrapper;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.analysis.standard.UAX29URLEmailAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.TextField;
import org.apache.lucene.facet.FacetField;
import org.apache.lucene.facet.FacetsConfig;
import org.apache.lucene.facet.taxonomy.directory.DirectoryTaxonomyWriter;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.search.similarities.ClassicSimilarity;
import org.apache.lucene.search.similarities.Similarity;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;

public class IndiceFaceta{
    String indexPath = "./index";
    String facetaPath = "./faceta";
    String docPath = "./csv";
    FacetsConfig fconfig;
    boolean create = true;
    private IndexWriter writer;
    private DirectoryTaxonomyWriter taxoWriter;
    IndiceFaceta() throws IOException {
         fconfig = new FacetsConfig();
         System.out.println(separador());
         System.out.println("\tAñadiendo varios documentos a un índice Lucene");
         System.out.println(separador());

        // Analizador a utilizar

        Analyzer analyzer_por_defecto = new StandardAnalyzer();
        Map<String, Analyzer> analizadores = new HashMap<>();
        analizadores.put("Titulo", new StandardAnalyzer());
        analizadores.put("Link", new UAX29URLEmailAnalyzer());
        analizadores.put("Authors", new AnalizadoresPropios().AnalizadorCommas());
        analizadores.put("Authors ID", new AnalizadoresPropios().AnalizadorNumbers());
        analizadores.put("IndexKeyword", new StandardAnalyzer());
        analizadores.put("Authro Keyword", new StandardAnalyzer());
        analizadores.put("Affiliations", new StandardAnalyzer());
        analizadores.put("EID", new AnalizadoresPropios().AnalizadorEID());

        PerFieldAnalyzerWrapper analyzer = new PerFieldAnalyzerWrapper(analyzer_por_defecto, analizadores);
        // Medida de Similitud ( modelo de recuperacion) BM25

        Similarity similarity = new ClassicSimilarity();


        

        // Creamos el indice

        configurarIndice(analyzer, similarity);

        // Insertamos los documentos

        indexarDocumentos();

        // Cerramos el indice
        System.out.println(analizadores.toString());
        //this.close();
    }
    public static void main(String[] args) throws IOException {

        IndiceFaceta index = new IndiceFaceta();
        

        }
    
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



    private void configurarIndice(Analyzer analyzer, Similarity similarity) throws IOException {
        IndexWriterConfig iwc = new IndexWriterConfig(analyzer);
        iwc.setSimilarity(similarity);

        // Crea un nuevo indice y si no inserta a uno existente
        iwc.setOpenMode(IndexWriterConfig.OpenMode.CREATE);
        // iwc.setOpenMode(IndexWriterConfig.OpenMode.CREATE_OR_APPEND);

        // Localizacion del indice
        Directory dir = FSDirectory.open(Paths.get(indexPath));
        Directory taxoDir = FSDirectory.open(Paths.get(facetaPath));
        // Creamos el indice

        writer = new IndexWriter(dir, iwc);
        taxoWriter = new DirectoryTaxonomyWriter(taxoDir);

    }
    public FacetsConfig getFconfig()
    {
        return fconfig;
    }

    private void indexarDocumentos() throws IOException {

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
                        try{
                        // Autores 0
                        doc.add(new TextField("Authors", fila[0], Field.Store.YES));
                        // Autores ID 1
                        doc.add(new TextField("Authors ID", fila[1], Field.Store.YES));
                        // Titulo 2

                        doc.add(new TextField("titulo", fila[2], Field.Store.YES)); // por defecto no se almacena
                        // Link 13
                        doc.add(new TextField("Link", fila[13], Field.Store.NO));
                        // Abstract 16

                        // Authro Keyword 17
                        doc.add(new TextField("Authro Keyword", fila[17], Field.Store.YES));
                        // IndexKeyword 18
                        doc.add(new TextField("IndexKeyword", fila[18], Field.Store.YES));
                        // EID
                        doc.add(new TextField("EID", fila[23], Field.Store.YES));
                        
                        
                        doc.add(new FacetField("Year" , fila[3] ));
                        fconfig.setHierarchical("Year", true);
                        doc.add(new FacetField("Document Type" , fila[19] ));
                        fconfig.setHierarchical("Document Type", true);
                        
                        doc.add(new FacetField("Affiliations" , fila[14].substring(0, 200) ));
                        fconfig.setHierarchical("Affiliations", true);
                        }
                        catch(Exception e)
                        {
                            
                        }
                        
                        
                        writer.addDocument(fconfig.build(taxoWriter,doc));
                        

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
            taxoWriter.close();
        } catch (IOException e) {
            System.err.println("Error cerrando el indice");
        }
    }

}
