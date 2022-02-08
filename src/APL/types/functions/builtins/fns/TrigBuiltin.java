package APL.types.functions.builtins.fns;

import APL.errors.*;
import APL.types.*;
import APL.types.functions.Builtin;

public class TrigBuiltin extends Builtin {
  @Override public String repr() {
    return "○";
  }
  
  
  
  private static final NumMV NF = new NumMV() {
    public Value call(Num w) {
      return new Num(w.num * Math.PI);
    }
    public void call(double[] res, double[] a) {
      for (int i = 0; i < a.length; i++) res[i] = a[i] * Math.PI;
    }
  };
  private static final NumMV NFi = new NumMV() {
    public Value call(Num w) {
      return new Num(w.num / Math.PI);
    }
    public void call(double[] res, double[] a) {
      for (int i = 0; i < a.length; i++) res[i] = a[i] / Math.PI;
    }
  };
  
  public Value call(Value w) {
    return numM(NF, w);
  }
  public Value callInv(Value w) {
    return numM(NFi, w);
  }
  
  static final D_NNeN DNF = new D_NNeN() {
    @Override public double on(double a, double w) {
      switch((int) a) {
        case  1: return Math.sin(w);
        case  2: return Math.cos(w);
        case  3: return Math.tan(w);
        case  4: return Math.sqrt(w*w + 1);
        case  5: return Math.sinh(w);
        case  6: return Math.cosh(w);
        case  7: return Math.tanh(w);
        case  8: return Double.NaN; // pointless
        case  9: return w; // pointless
        case 10: return Math.abs(w); // pointless
        case 11: return 0; // also pointless
        case 12: throw new DomainError("what even is phase");
      
        case  0: return Math.sqrt(1-w*w); //Num.ONE.minus(n.pow(Num.TWO)).root(Num.TWO);
        case  -1: return Math.asin(w);
        case  -2: return Math.acos(w);
        case  -3: return Math.atan(w);
        case  -4: return Math.sqrt(w*w-1);
        case  -5: throw new NYIError("inverse hyperbolic functions"); // return Math.asinh(w);
        case  -6: throw new NYIError("inverse hyperbolic functions"); // return Math.acosh(w);
        case  -7: throw new NYIError("inverse hyperbolic functions"); // return Math.atanh(w);
        case  -8: return Double.NaN; // pooointleeeessssss
        case  -9: return w; // again, pointless pointless pointless
        case -10: return w;
        case -11: throw new DomainError("no complex numbers :/");
        case -12: throw new DomainError("no complex numbers no idea why this is even special-cased");
      }
      throw new DomainError("○: ⍺ is out of bounds");
    }
  };
  public Value call(Value a, Value w) {
    return numD(DNF, a, w);
  }
  
  
  static final D_NNeN DNFi = new D_NNeN() {
    @Override public double on(double a, double w) {
      switch((int) a) {
        case  1: return Math.asin(w);
        case  2: return Math.acos(w);
        case  3: return Math.atan(w);
        
        case -1: return Math.sin(w);
        case -2: return Math.cos(w);
        case -3: return Math.tan(w);
      }
      throw new DomainError("○⍣¯1: ⍵ must be in (+,-)1…3");
    }
  };
  public Value callInvW(Value a, Value w) {
    return numD(DNFi, a, w);
  }
}