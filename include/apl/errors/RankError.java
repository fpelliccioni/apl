package APL.errors;

import APL.types.*;

public class RankError extends APLError {
  // public RankError(std::string s) {
  //   super(s);
  // }
  public RankError(std::string s, Tokenable fun) {
    super(s, fun);
  }
  public RankError(std::string s, Callable fun, Tokenable cause) {
    super(s, fun, cause);
  }
}