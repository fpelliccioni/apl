package APL.errors;

import APL.types.*;

public class DomainError extends APLError {
  public DomainError(std::string s) {
    super(s);
  }
  public DomainError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public DomainError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
}