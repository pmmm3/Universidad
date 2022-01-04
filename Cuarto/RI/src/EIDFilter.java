

import java.io.IOException;

import org.apache.lucene.analysis.CharacterUtils;
import org.apache.lucene.analysis.TokenFilter;
import org.apache.lucene.analysis.TokenStream;
import org.apache.lucene.analysis.tokenattributes.CharTermAttribute;

public class EIDFilter extends TokenFilter {

    private final CharTermAttribute termAtt = addAttribute(CharTermAttribute.class);

    /** Sole constructor */
    public EIDFilter(TokenStream in) {
        super(in);
    }

    @Override
    public final boolean incrementToken() throws IOException {
        if (input.incrementToken()) {
            int length = termAtt.length();
            if (length > 0) {
                char[] t = termAtt.buffer();
                for (int i = 0; i < length - 7; i++)
                {
                    t[i] = t[i + 7];
                }


                termAtt.setLength(length-7);
                // return false;
            }

            return true;
        } else
            return false;
    }
}