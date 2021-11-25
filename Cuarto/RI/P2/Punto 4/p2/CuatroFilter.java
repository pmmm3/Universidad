package p2;

import java.io.IOException;

import org.apache.lucene.analysis.CharacterUtils;
import org.apache.lucene.analysis.TokenFilter;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.tokenattributes.CharTermAttribute;

public class CuatroFilter extends TokenFilter {

    private final CharTermAttribute termAtt = addAttribute(CharTermAttribute.class);

    /** Sole constructor */
    public CuatroFilter(TokenStream in) {
        super(in);
    }

    @Override
    public final boolean incrementToken() throws IOException {
        if (input.incrementToken()) {
            if (termAtt.length() <= 3) {
                termAtt.setEmpty();
                termAtt.resizeBuffer(0);
                termAtt.setLength(0);
                // return false;
            } else {
                char[] t = termAtt.buffer();
                t[0] = t[t.length - 1];
                t[1] = t[t.length - 2];
                t[2] = t[t.length - 3];
                t[3] = t[t.length - 4];
                termAtt.resizeBuffer(4);
            }

            return true;
        } else
            return false;
    }
}
