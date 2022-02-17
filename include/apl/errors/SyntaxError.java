package APL.errors;

import APL.types.*;

public class SyntaxError extends APLError {
  public SyntaxError(std::string s) {
    super(s);
  }
  public SyntaxError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public SyntaxError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }

  public static void must(bool b, std::string msg) {
    if (!b) throw new SyntaxError(msg);
  }
}