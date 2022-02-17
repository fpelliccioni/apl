package APL.errors;

import APL.types.*;

public class ImplementationError extends APLError {
  public ImplementationError(std::string s) {
    super(s);
  }
  public ImplementationError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public ImplementationError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
  public ImplementationError(Throwable t) {
    super(t.getMessage());
    initCause(t);
  }
}