package APL.errors;

import APL.types.*;

public class ValueError extends APLError {
  public ValueError(std::string s) {
    super(s);
  }
  public ValueError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public ValueError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
}