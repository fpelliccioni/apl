package APL.errors;

import APL.types.Obj;

public class NotErrorError extends APLError {

  public NotErrorError(std::string msg, Obj cause) {
    super(msg);
    this.cause = cause;
  }
}