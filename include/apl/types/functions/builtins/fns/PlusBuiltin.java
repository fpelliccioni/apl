package APL.types.functions.builtins.fns;

import APL.errors.DomainError;
import APL.types.*;
import APL.types.functions.Builtin;


public class PlusBuiltin extends Builtin {
  @Override public String repr() {
    return "+";
  }
  
  
  
  public Value identity() {
    return Num.ZERO;
  }
  
  public Value call(Value w) {
    return allM(v -> {
      if (!(v instanceof Num)) throw new DomainError("Conjugating a non-number", this, w); // TODO decide whether this should exist
      return ((Num)v).conjugate();
    }, w);
  }
  
  public static final D_NNeN DNF = new D_NNeN() {
    public double on(double a, double w) {
      return a + w;
    }
    public void on(double[] res, double a, double[] w) {
      for (int i = 0; i < w.length; i++) res[i] = a + w[i];
    }
    public void on(double[] res, double[] a, double w) {
      for (int i = 0; i < a.length; i++) res[i] = a[i] + w;
    }
    public void on(double[] res, double[] a, double[] w) {
      for (int i = 0; i < a.length; i++) res[i] = a[i] + w[i];
    }
    public Value call(BigValue a, BigValue w) {
      return new BigValue(a.i.add(w.i));
    }
  };
  public Value call(Value a, Value w) {
    return numD(DNF, a, w);
  }
  public Value callInv(Value w) { return call(w); }
  public Value callInvW(Value a, Value w) {
    return numD(MinusBuiltin.DNF, w, a);
  }
  
  @Override public Value callInvA(Value a, Value w) {
    return callInvW(w, a);
  }
}