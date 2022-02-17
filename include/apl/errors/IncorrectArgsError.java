package APL.errors;

import APL.types.*;

public class IncorrectArgsError extends APLError {
  public IncorrectArgsError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
}