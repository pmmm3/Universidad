package p2;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;

import java.io.IOException;
import java.io.StringReader;
import java.io.BufferedReader;

import org.apache.lucene.analysis.Tokenizer;
import org.apache.lucene.analysis.commongrams.CommonGramsFilter;
import org.apache.lucene.analysis.es.SpanishAnalyzer;
import org.apache.lucene.analysis.ngram.EdgeNGramTokenFilter;
import org.apache.lucene.analysis.ngram.NGramTokenFilter;
import org.apache.lucene.analysis.shingle.ShingleFilter;
import org.apache.lucene.analysis.snowball.SnowballFilter;
import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.LowerCaseFilter;
import org.apache.lucene.analysis.StopFilter;
import org.apache.lucene.analysis.standard.StandardFilter;
import org.apache.lucene.analysis.standard.StandardTokenizer;
import org.apache.lucene.util.CharsRef;
import org.apache.lucene.analysis.synonym.SynonymGraphFilter;
import org.apache.lucene.analysis.synonym.SynonymGraphFilterFactory;
import org.apache.lucene.analysis.synonym.SynonymMap;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.tokenattributes.CharTermAttribute;
import org.apache.lucene.analysis.tokenattributes.OffsetAttribute;
import org.tartarus.snowball.ext.EnglishStemmer;
import org.tartarus.snowball.ext.SpanishStemmer;
import org.apache.lucene.analysis.CharArraySet;

public class main {
    public static void tokenizeString(Analyzer analyzer, String string) {
        try {
            TokenStream stream = analyzer.tokenStream(null, new StringReader(string));
            OffsetAttribute offsetAtt = stream.addAttribute(OffsetAttribute.class);
            CharTermAttribute cAtt = stream.addAttribute(CharTermAttribute.class);

            stream.reset();
            while (stream.incrementToken()) {
                System.out.println(
                        cAtt.toString() + " :[" + offsetAtt.startOffset() + " , " + offsetAtt.endOffset() + "]");

            }
            stream.end();

        } catch (IOException e) {
            System.err.println("Error en el tokenizeString");
        }
    }

    public static void punto4() {
        String texto = "azucar sol pelicula bar submarino caja raton usb ";
        System.out.println("\n************************************************************************");
        System.out.println("\tNuestro Token Filter");
        System.out.println("************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out.println(" se quede únicamente con los últimos 4 caracteres: ");

        /*
         * StopFilter, Snowball-Filter, ShingleFilter, EdgeNGramCommonFilter,
         * NGramTokenFilter, Com-monGramsFilter, SynonymFilter
         */
        Analyzer analyzer = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new CuatroFilter(source);
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(analyzer, texto);
    }

    public static void punto2() {
        String texto = "PROBANDO: esto_es_un; programa con español dentro y tíldes";

        System.out.println("\n************************************************************************");
        System.out.println("\tProbando los Token Filter");
        System.out.println("************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out
                .println("Tokenizar utilizando un StandardTokenizer, sigue las reglas de segmentación para Unicode: ");

        /*
         * StopFilter, Snowball-Filter, ShingleFilter, EdgeNGramCommonFilter,
         * NGramTokenFilter, Com-monGramsFilter, SynonymFilter
         */
        Analyzer anStandardFilter = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new StandardFilter(source);
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anStandardFilter, texto);
        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);

        System.out.println("************************************************************************\n");
        System.out.println("Convertir a minúscula, LowerCaseFilter : ");

        Analyzer anLowerCase = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new LowerCaseFilter(source);
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anLowerCase, texto);
        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out.println("Eliminar palabras vacías, StopFilter");

        /*
         * ShingleFilter, EdgeNGramCommonFilter, NGramTokenFilter, Com-monGramsFilter,
         * SynonymFilter
         */

        Analyzer anStopFilter = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new StopFilter(source, SpanishAnalyzer.getDefaultStopSet());
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anStopFilter, texto);

        String texto2 = "solo solos solitos solidos solido sol";
        String texto3 = "estudios estudiar estudiantes estudiamos estudias estudiarás";
        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto3);
        System.out.println("************************************************************************\n");
        System.out.println("Snowball");

        /*
         * Snowball-Filter, ShingleFilter, EdgeNGramCommonFilter, NGramTokenFilter,
         * Com-monGramsFilter, SynonymFilter
         */
        // https://stackoverflow.com/questions/9412981/what-is-the-key-word-snowball-mean-in-elastic-search/40781785
        Analyzer anSnowball = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new SnowballFilter(source, new SpanishStemmer());
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anSnowball, texto3);
        String texto4 = "please divide this sentence into shingles";
        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto4);
        System.out.println("************************************************************************\n");
        System.out.println("ShingleFilter");
        // For example, the sentence "please divide this sentence into shingles" might
        // be tokenized into shingles "please divide", "divide this", "this sentence",
        // "sentence into", and "into shingles".
        /*
         * ShingleFilter, EdgeNGramCommonFilter, NGramTokenFilter, Com-monGramsFilter,
         * SynonymFilter
         */

        Analyzer anShingle = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new ShingleFilter(source);
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anShingle, texto4);
        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out.println("EdgeNGramCommonFilter");

        /*
         * EdgeNGramCommonFilter, NGramTokenFilter, Com-monGramsFilter, SynonymFilter
         */

        Analyzer anEdgeNGramCommonFilter = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new EdgeNGramTokenFilter(source, 1, 3);
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anEdgeNGramCommonFilter, texto);

        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out.println("NGramCommonFilter");

        /*
         * , NGramTokenFilter, Com-monGramsFilter, SynonymFilter
         */

        Analyzer anNGramCommonFilter = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new StandardTokenizer();
                TokenStream result = new NGramTokenFilter(source);
                return new TokenStreamComponents(source, result);
            }
        };
        tokenizeString(anNGramCommonFilter, texto);

        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out.println(
                "Com-monGramsFilter : https://github.com/mazyvan/most-common-spanish-words/blob/master/most-common-spanish-words.txt");

        /*
         * , , , SynonymFilter
         */
        ///
        File archivo = null;
        FileReader fr = null;
        BufferedReader br = null;
        CharArraySet common_spanish = new CharArraySet(19936, false);

        archivo = new File("./txt/spanish.txt");
        try {
            fr = new FileReader(archivo);
            br = new BufferedReader(fr);

            // Lectura del fichero
            String linea;
            while ((linea = br.readLine()) != null)
                common_spanish.add(linea);
            //

            Analyzer anCommonGramsFilter = new Analyzer() {
                @Override
                protected TokenStreamComponents createComponents(String fieldName) {
                    Tokenizer source = new StandardTokenizer();
                    TokenStream result = new CommonGramsFilter(source, common_spanish);
                    return new TokenStreamComponents(source, result);
                }
            };
            tokenizeString(anCommonGramsFilter, texto);
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

        texto = "Jose Pepe Anton Juan";
        System.out.println("\n************************************************************************\n");
        System.out.println("Texto original :\n\t" + texto);
        System.out.println("************************************************************************\n");
        System.out.println("SynonymGraphFilter");

        SynonymMap.Builder builder = new SynonymMap.Builder(true);
        CharsRef jose = new CharsRef("Jose");
        CharsRef pepe = new CharsRef("Pepe");
        CharsRef antonio = new CharsRef("Antonio");
        CharsRef anton = new CharsRef("Anton");
        builder.add(pepe, jose, true);
        builder.add(anton, antonio, true);
        SynonymMap map;
        try {
            map = builder.build();
            Analyzer anSynonymFilter = new Analyzer() {
                @Override
                protected TokenStreamComponents createComponents(String fieldName) {
                    Tokenizer source = new StandardTokenizer();
                    TokenStream result = new SynonymGraphFilter(source, map, false);
                    return new TokenStreamComponents(source, result);
                }
            };
            tokenizeString(anSynonymFilter, texto);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }

    public static void main(String[] args) throws IOException {
        punto4();
    }

}
