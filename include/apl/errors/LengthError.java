package APL.errors;

import APL.types.*;

public class LengthError extends APLError {
  // public LengthError(std::string s) {
  //   super(s);
  // }
  public LengthError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public LengthError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
}