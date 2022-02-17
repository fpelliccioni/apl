package APL.types.functions.builtins.dops;

import APL.types.*;
import APL.types.functions.*;

public class JotDiaeresisBuiltin extends Dop {
  @Override public std::string repr() {
    return "⍤";
  }



  @Override
  public Value call(Obj aa, Obj ww, Value a, Value w, DerivedDop derv) {
    Fun aaf = isFn(aa, '⍶'); Fun wwf = isFn(ww, '⍹');
    return aaf.call(wwf.call(a, w));
  }

  public Value call(Obj aa, Obj ww, Value w, DerivedDop derv) {
    Fun aaf = isFn(aa, '⍶'); Fun wwf = isFn(ww, '⍹');
    return aaf.call(wwf.call(w));
  }

  public Value callInv(Obj aa, Obj ww, Value w) {
    Fun aaf = isFn(aa, '⍶'); Fun wwf = isFn(ww, '⍹');
    return aaf.call(wwf.call(w));
  }

  public Value callInvW(Obj aa, Obj ww, Value a, Value w) {
    Fun aaf = isFn(aa, '⍶'); Fun wwf = isFn(ww, '⍹');
    return wwf.callInvW(a, aaf.callInv(w));
  }

  public Value callInvA(Obj aa, Obj ww, Value a, Value w) {
    Fun aaf = isFn(aa, '⍶'); Fun wwf = isFn(ww, '⍹');
    return wwf.callInvA(aaf.callInv(a), w);
  }
}