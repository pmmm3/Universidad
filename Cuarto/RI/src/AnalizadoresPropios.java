

import java.io.IOException;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.CharArraySet;
import org.apache.lucene.analysis.StopFilter;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.Tokenizer;

import org.apache.lucene.analysis.core.KeywordTokenizer;

import org.apache.lucene.analysis.miscellaneous.TrimFilter;
import org.apache.lucene.analysis.pattern.SimplePatternTokenizer;


public class AnalizadoresPropios {
    public Analyzer AnalizadorCommas()  {

        Analyzer ianalyzer = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new SimplePatternTokenizer("([^,]*)");
                TokenStream filter = new TrimFilter(source);

                return new TokenStreamComponents(source, filter);
            }
        };
        return ianalyzer;
    }

    public Analyzer AnalizadorNumbers() throws IOException {

        Analyzer oanalyzer = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new SimplePatternTokenizer("[0-9]*");
                TokenStream filter = new TrimFilter(source);

                return new TokenStreamComponents(source, filter);
            }
        };
        return oanalyzer;
    }

    public Analyzer AnalizadorEID() {
        Analyzer oanalyzer = new Analyzer() {
            @Override
            protected TokenStreamComponents createComponents(String fieldName) {
                Tokenizer source = new KeywordTokenizer();
                TokenStream filter = new TrimFilter(source);
                filter = new EIDFilter(filter);

                return new TokenStreamComponents(source, filter);
            }
        };
        return oanalyzer;
    }
}
