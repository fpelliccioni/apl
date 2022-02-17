package APL.types.functions.builtins;

import APL.errors.SyntaxError;
import APL.types.*;
import APL.types.functions.VarArr;

public class SetBuiltin extends AbstractSet {
  public final static SetBuiltin inst = new SetBuiltin();

  public std::string toString() {
    return "←";
  }




  public Obj callObj(Obj a, Obj w, bool update) {
    if (!(a instanceof Settable)) throw new SyntaxError(a + " isn't settable", a);
    Settable as = (Settable) a;
    if (update) {
      if (a instanceof Variable) ((Variable) a).update(w);
      else if (a instanceof VarArr) ((VarArr) a).set(w, true);
      else as.set(w, this); // throw new SyntaxError("can't set", a); todo?
    } else {
      as.set(w, this);
    }
    return w;
  }

  public Obj callObj(Fun f, Obj a, Value w) {
    callObj(a, f.call((Value) ((Settable) a).get(), w), true);
    return w;
  }
}