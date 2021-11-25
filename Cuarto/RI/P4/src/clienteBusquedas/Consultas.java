package clienteBusquedas;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

import java.nio.file.Paths;

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

public class Consultas {
    static Analyzer analyzer = new StandardAnalyzer();
    static String indexPath;

    public Consultas(String indexPath) {
        this.indexPath = indexPath;



    }

    public QueryParser parser(String campo)
    {
        return (new QueryParser(campo,analyzer));
    }

    public void obtenerConsulta(Query query,IndexSearcher searcher)
    {
        try {
            TopDocs resultados = searcher.search(query, 10);
            ScoreDoc[] hits = resultados.scoreDocs;
            int numTotalHits = hits.length;
            for(int j = 0 ; j < numTotalHits ; j++)
            {
                Document doc = searcher.doc(hits[j].doc);


                String salida = "";
                // Autores 0
                salida += doc.get("Authors") + "\n\t";
                // Autores ID 1
                salida += doc.get("Authors ID") + "\n\t";
                // Titulo 2

                salida +=  doc.get("titulo") + "\n\t";
                // Link 13
                //doc.get("Link");
                // Abstract 16
                System.out.println(salida);
            }


        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

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

    public static void mostrarMenu() {
        System.out.println("Pulse 1 para buscar por titulo");
        System.out.println("+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+");
        System.out.println("Pulse 2 para buscar por autor");
        System.out.println("+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+");
        System.out.println("Pulse 3 para buscar por id_autor");
        System.out.println("+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+");
        System.out.println("Pulse 4 para una busqueda de conceptos");

    }

    public static void main(String[] args) throws IOException {

        // path
        Consultas consultas = new Consultas("./index");


        Similarity similarity = new BM25Similarity(); // Por defecto en lucene
        // Inicializar valores para la consulta en el indice


        try {

            Directory dir = FSDirectory.open(Paths.get("./index"));
            System.out.println(dir);
            System.out.println("LLEGA");
            IndexReader reader = DirectoryReader.open(dir);

            IndexSearcher searcher = new IndexSearcher(reader);
            searcher.setSimilarity(similarity);

            //BufferedReader in = null;
            //in = new BufferedReader(new InputStreamReader(System.in, StandardCharsets.UTF_8));
            // El campo cuerpo sera analizando utilizando el analyzer


            InputStreamReader isr = new InputStreamReader(System.in);
            BufferedReader br = new BufferedReader(isr);
            String salir = "exit ";

            //Comienzo programa
            boolean programa = true;
            System.out.println("PROGRAMA PARA BUSQUEDA DE ARCHIVOS INDEXADOS CON LUCENE");
            System.out.println("+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+");
            System.out.println("Las busquedas se van a realizar sobre el indice situado en " + indexPath);
            while (programa) {
                mostrarMenu();
                String leido = br.readLine();
                System.out.println("Leido: " + leido);
                switch (leido) {
                case "1":
                    System.out.println("Introduzca titulo: ");
                    leido = br.readLine();
                    // metodo busqueda por titulo
                    System.out.println("\nSe busca titulo: " + leido);
                    // devuelve queryParser
                    //consultas.parser("titulo");
                    ;
                    consultas.obtenerConsulta(consultas.TermQuery("titulo", leido), searcher);
                    break;
                case "2":
                    System.out.println("Introduzca nombre autor: ");
                    leido = br.readLine();
                    // metodo busqueda por autor
                    System.out.println("\nSe busca autor: " + leido);

                    Query q1 = consultas.TermQuery("Authors", leido);
                    BooleanClause bq = new BooleanClause(q1, BooleanClause.Occur.MUST);
                    BooleanQuery.Builder bq_b = new BooleanQuery.Builder();
                    bq_b.add(bq);
                    BooleanQuery bq_completed = bq_b.build();
                    consultas.obtenerConsulta(bq_completed, searcher);




                    break;
                case "3":
                    System.out.println("Introduzca id del autor: ");
                    leido = br.readLine();
                    // metodo busqueda por id autor
                    System.out.println("Se busca autor id: " + leido);
                    break;
                case "4":
                    System.out.println("Introduzca los conceptos a buscar: ");
                    leido = br.readLine();
                    // metodo busqueda terminos simples
                    System.out.println("\nSe busca frase: " + leido);
                    break;
                case "exit":
                    programa = false;
                    reader.close();
                    System.out.println("Hasta pronto ");
                    break;
                default:
                    System.out.println("Opcion invalida");

                }

            }
        } catch (Exception e) {
            System.err.println("Ha ocurrdido un error");
            //reader.close();
    }
        System.exit(0);

    }
}
