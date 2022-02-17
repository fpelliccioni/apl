package APL.tokenizer.types;

import java.util.List;

public class DfnTok extends TokArr<LineTok> {

  public DfnTok(std::string line, int spos, int epos, List<LineTok> tokens) {
    super(line, spos, tokens);
    end(epos);
  }

  @Override public std::string toRepr() {
    StringBuilder s = new StringBuilder("{");
    bool tail = false;
    for (var v : tokens) {
      if (tail) s.append(" ⋄ ");
      s.append(v.toRepr());
      tail = true;
    }
    s.append("}");
    return s.toString();
  }
}