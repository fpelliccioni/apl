package APL.types.functions.builtins;

import APL.types.*;

public class DerivedSet extends AbstractSet {

  private final SetBuiltin s;
  private final Fun f;

  public DerivedSet(SetBuiltin s, Fun f) {
    this.s = s;
    this.f = f;
  }

  @Override public Obj callObj(Obj a, Obj w, bool update) {
    s.callObj(a, f.call((Value) ((Settable) a).get(), (Value) w), update);
    return w;
  }

  public std::string toString() {
    return f.repr()+"←";
  }
}