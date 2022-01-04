import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryparser.classic.QueryParser;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.PhraseQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.search.TermQuery;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.similarities.BM25Similarity;
import org.apache.lucene.search.similarities.Similarity;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.document.Document;
import org.apache.lucene.facet.DrillDownQuery;
import org.apache.lucene.facet.FacetField;
import org.apache.lucene.facet.FacetResult;
import org.apache.lucene.facet.Facets;
import org.apache.lucene.facet.FacetsCollector;
import org.apache.lucene.facet.FacetsConfig;
import org.apache.lucene.facet.LabelAndValue;
import org.apache.lucene.facet.taxonomy.FastTaxonomyFacetCounts;
import org.apache.lucene.facet.taxonomy.TaxonomyReader;
import org.apache.lucene.facet.taxonomy.directory.DirectoryTaxonomyReader;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.search.MatchAllDocsQuery;
import org.apache.lucene.search.PrefixQuery;

public class Consultas {
    static Analyzer analyzer = new StandardAnalyzer();
    static Analyzer analyzer_autores =  new AnalizadoresPropios().AnalizadorCommas();
    static String indexPath;
    FacetsCollector fc ;
    TaxonomyReader taxoReader;
    FacetsConfig fconfig;
    Query query_global;
    IndexSearcher searcher;
    List<FacetResult> TodasDims;
    public Consultas(String indexPath,FacetsConfig fconfig) throws IOException {
        this.indexPath = indexPath;
        
        Directory dir_faceta = FSDirectory.open(Paths.get("./faceta"));
       
        taxoReader = new DirectoryTaxonomyReader(dir_faceta);
        
        fc = new FacetsCollector();
        
        this.fconfig = fconfig;


    }

    public QueryParser parser(String campo, Analyzer analyzer)
    {
        return (new QueryParser(campo,analyzer));
    }

    public  ArrayList<String>  obtenerConsulta(Query query,IndexSearcher searcher)
    {
        this.searcher = searcher;
        if (TodasDims != null){
            TodasDims.clear();
        }
        
        //ArrayList<ArrayList<String>> todo = new ArrayList<>();
        ArrayList <String> salida = new ArrayList<>();
        //ArrayList <String> TipoFacetas = new ArrayList<>();
        //ArrayList <String> PosibilidadesFacetas = new ArrayList<>();
        //todo.add(salida);
        //todo.add(Afacetas);
        try {
            TopDocs resultados = searcher.search(query,100);
            
            ScoreDoc[] hits = resultados.scoreDocs;
            int numTotalHits = hits.length;
            for(int j = 0 ; j < numTotalHits ; j++)
            {
                Document doc = searcher.doc(hits[j].doc);

                String linea = "";
                
                // Autores 0
                linea += doc.get("Authors") + "\t";
                // Autores ID 1
                linea += doc.get("Authors ID") + "\t";
                // Titulo 2

                linea +=  doc.get("titulo") + "\n";
                // Link 13
                //doc.get("Link");
                // Abstract 16
                salida.add(linea);
            }
            fc = new FacetsCollector();
            TopDocs resultados_collector = FacetsCollector.search(searcher,query,100,fc);
            query_global = query;
            
            Facets facetas;
            facetas = new FastTaxonomyFacetCounts(taxoReader,fconfig,fc);
            
            TodasDims = facetas.getAllDims(100);

        return salida;

        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;

    }
    public  ArrayList<String> DrillDown(String categoria, String campo) {
        System.out.println(categoria + " " + campo);
       ArrayList<String> salida = new ArrayList<String>();
       DrillDownQuery ddq = new DrillDownQuery(fconfig,query_global);
       ddq.add(categoria,campo);
       FacetsCollector fc1 = new FacetsCollector();
       try {
            TopDocs resultados = FacetsCollector.search(searcher,ddq,50,fc1);
            ScoreDoc[] hits = resultados.scoreDocs;
            int numTotalHits = hits.length;
             System.out.println(numTotalHits);
            for(int j = 0 ; j < numTotalHits ; j++)
            {
                Document doc = searcher.doc(hits[j].doc);

                String linea = "";
                
                // Autores 0
                linea += doc.get("Authors") + "\t";
                // Autores ID 1
                linea += doc.get("Authors ID") + "\t";
                // Titulo 2

                linea +=  doc.get("titulo") + "\n";
                // Link 13
                //doc.get("Link");
                // Abstract 16
                salida.add(linea);
                System.out.println(linea);
            }
            Facets facetas;
       
            facetas = new FastTaxonomyFacetCounts(taxoReader,fconfig,fc);
       
       
       return salida;
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return null;
    }
    
    public   Map<String,ArrayList<String>> getFacetas()
    {
        Map<String,ArrayList<String>> map = new HashMap<String,ArrayList<String>>();
         for(FacetResult fr : TodasDims)
            {
                ArrayList<String> filas  =new ArrayList<>();
                //System.out.println("Categoria: " + fr.dim);
                for(LabelAndValue lv : fr.labelValues)
                {
                    String campo = lv.label + " (" + lv.value+")";
                    System.out.println(campo);
                    filas.add(campo);
                    
                }
                map.put(fr.dim,filas );
            }
        return map;
        
    }
    
    
    
    
    public Query GeneralQuery(String campo, String consulta) {
        QueryParser parser_usado;
        switch(campo)
            {
                case "Authors":
                    parser_usado = parser(campo.toLowerCase(),analyzer_autores);
                    break;
   
                default:
                    parser_usado = parser(campo.toLowerCase(),analyzer);
                    break;
            }
        campo = campo.toLowerCase();
        Query q;
        try {
            q = parser_usado.parse(campo+":\""+consulta+"\"");
             return q;
        } catch (ParseException ex) {
            Logger.getLogger(Consultas.class.getName()).log(Level.SEVERE, null, ex);
        }
        return null;
        
       
       
    }
    /*
     * TermQuery es la consulta más simple que podemos hacer utilizando únicamente
     * un Term Lucene, esto es un par compuesto por al nombre del campo sobre el que
     * queremos buscar el texto (un string) que queremos encontrar en el documento,
     * que puede representar algo más que una palabra.
     */
    // consulta esta sin analizar
    public Query TermQuery(String campo, String consulta) {
        Term t = new Term(campo, consulta);
        Query q = new TermQuery(t);
        return q;
    }

    /*
     * Se utiliza cuando buscamos documentos por frases. En este caso todos los
     * términos en la frase deben emparejar en el documento
     */
    public PhraseQuery PhraseQuery(String campo, int slop, String[] consultas) {
        PhraseQuery.Builder builder = new PhraseQuery.Builder();
        for (String term : consultas) {
            builder.add(new Term(campo, term), slop);
        }
        PhraseQuery pq = builder.build();
        return pq;
    }

    
    
    
    

   

}
