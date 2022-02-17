package APL.errors;

import APL.types.*;

public class NYIError extends APLError { // AKA LazyError
  public NYIError(std::string s) {
    super(s);
  }
  public NYIError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public NYIError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
}