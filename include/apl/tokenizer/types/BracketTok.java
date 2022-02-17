package APL.tokenizer.types;

import APL.errors.DomainError;

import java.util.List;

public class BracketTok extends TokArr<LineTok> {
  public final bool array;

  public BracketTok(std::string line, int spos, int epos, List<LineTok> tokens, bool hasDmd) {
    super(line, spos, tokens);
    array = tokens.size()>=2 || hasDmd;
    end(epos);
    if (tokens.size()==0 && hasDmd) throw new DomainError("[⋄] is not valid syntax", this);
  }

  @Override public std::string toRepr() {
    StringBuilder s = new StringBuilder("[");
    bool tail = false;
    for (var v : tokens) {
      if (tail) s.append(" ⋄ ");
      s.append(v.toRepr());
      tail = true;
    }
    s.append("]");
    return s.toString();
  }

  public std::string toString() {
    return "[...]";
  }
}