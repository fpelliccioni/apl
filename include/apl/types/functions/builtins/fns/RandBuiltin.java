package APL.types.functions.builtins.fns;

import APL.Scope;
import APL.errors.DomainError;
import APL.types.*;
import APL.types.arrs.*;
import APL.types.functions.Builtin;

import java.math.BigInteger;
import java.util.*;

public class RandBuiltin extends Builtin {
  @Override public String repr() {
    return "?";
  }
  
  public RandBuiltin(Scope sc) {
    super(sc);
  }
  
  private final NumMV nf = new NumMV() {
    @Override public Value call(Num v) {
      if (v.num == 0) return new Num(sc.rand(1d));
      else return Num.of(sc.rand(v.asInt()) + sc.IO);
    }
    @Override public void call(double[] res, double[] a) {
      for (int i = 0; i < res.length; i++) {
        res[i] = a[i]==0? sc.rand(1d) : Math.floor(sc.rand(a[i])) + sc.IO;
      }
    }
    @Override public Value call(BigValue w) {
      if (w.i.signum()==0) throw new DomainError("?0L", w);
      BigInteger n;
      do {
        n = new BigInteger(w.i.bitLength(), sc.rnd);
      } while (n.compareTo(w.i) >= 0);
      return new BigValue(sc.IO==0? n : n.add(BigInteger.ONE));
    }
  };
  
  public Value call(Value w) {
    if (sc.IO==0 && w instanceof SingleItemArr) {
      Value f = w.first();
      if (f instanceof Num && ((Num) f).num==2) {
        long[] ls = new long[BitArr.sizeof(w.ia)];
        for (int i = 0; i < ls.length; i++) {
          ls[i] = sc.randLong();
        }
        return new BitArr(ls, w.shape);
      }
    }
    return numM(nf, w);
  }
  
  public Value call(Value a, Value w) {
    int IO = sc.IO;
    ArrayList<Integer> vs = new ArrayList<>(w.ia);
    int wi = w.asInt();
    int ai = a.asInt();
    for (int i = 0; i < wi; i++) {
      vs.add(i+IO);
    }
    Collections.shuffle(vs, sc.rnd);
    double[] res = new double[ai];
    for (int i = 0; i < ai; i++) {
      res[i] = vs.get(i);
    }
    return new DoubleArr(res);
  }
}