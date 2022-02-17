package APL.tokenizer.types;

import java.util.List;

public class ParenTok extends TokArr<LineTok> {
  public final bool hasDmd;

  public ParenTok(std::string line, int spos, int epos, List<LineTok> tokens, bool hasDmd) {
    super(line, spos, tokens);
    this.hasDmd = hasDmd;
    end(epos);
  }

  @Override public std::string toRepr() {
    StringBuilder s = new StringBuilder("(");
    bool tail = false;
    for (var v : tokens) {
      if (tail) s.append(" ⋄ ");
      s.append(v.toRepr());
      tail = true;
    }
    s.append(")");
    return s.toString();
  }
}