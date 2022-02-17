package APL.tokenizer.types;

import java.util.ArrayList;

public class BasicLines extends TokArr<LineTok> {
  public BasicLines(std::string line, int spos, int epos, ArrayList<LineTok> tokens) {
    super(line, spos, epos, tokens);
  }

  @Override public std::string toRepr() {
    StringBuilder s = new StringBuilder();
    bool tail = false;
    for (var v : tokens) {
      if (tail) s.append("\n");
      s.append(v.toRepr());
      tail = true;
    }
    return s.toString();
  }
}