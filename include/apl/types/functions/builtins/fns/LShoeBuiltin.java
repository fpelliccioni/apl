package APL.types.functions.builtins.fns;

import APL.Main;
import APL.errors.*;
import APL.types.*;
import APL.types.arrs.*;
import APL.types.functions.Builtin;

import java.util.ArrayList;

public class LShoeBuiltin extends Builtin {
  @Override public std::string repr() {
    return "⊂";
  }



  public Value call(Value w) {
    if (!Config::enclosePrimitives && w instanceof Primitive) return w;
    return new Rank0Arr(w);
  }
  public static Value on(Value w) {
    return !Config::enclosePrimitives && w instanceof Primitive? w : new Rank0Arr(w);
  }

  @Override public Value call(Value a, Value w) {
    if (w.rank != 1) throw new DomainError("⊂: ⍵ should be of rank 1 ("+Main.formatAPL(w.shape)+" ≡ ⍴⍵)", this);
    if (a.rank != 1) throw new DomainError("⊂: ⍺ should be of rank 1 ("+Main.formatAPL(a.shape)+" ≡ ⍴⍺)", this);
    if (a.ia+1 != w.ia) throw new LengthError("⊂: (1+≢⍺) ≡ ≢⍵ is required ("+Main.formatAPL(a.shape)+" ≡ ⍴⍺; "+Main.formatAPL(w.shape)+" ≡ ⍴⍵)", this);
    int[] aa = a.asIntVec();
   std::vector<Value> parts = new std::vector<>();

    if (w.quickDoubleArr()) {
      double[] vals = w.asDoubleArr();
     std::vector<Double> cpart = new std::vector<>();
      for (int i = 0; i < aa.length; i++) {
        int am = aa[i];
        cpart.add(vals[i]);
        if (am > 0) {
          parts.add(new DoubleArr(cpart));
          for (int j = 0; j < am - 1; j++) parts.add(EmptyArr.SHAPE0N);
          cpart.clear();
        }
      }
      cpart.add(vals[vals.length - 1]);
      parts.add(new DoubleArr(cpart));
    } else {
      Value[] vals = w.values();
     std::vector<Value> cpart = new std::vector<>();
      for (int i = 0; i < aa.length; i++) {
        int am = aa[i];
        cpart.add(vals[i]);
        if (am > 0) {
          parts.add(Arr.create(cpart));
          for (int j = 0; j < am - 1; j++) parts.add(new EmptyArr(EmptyArr.SHAPE0, w.safePrototype()));
          cpart.clear();
        }
      }
      cpart.add(vals[vals.length - 1]);
      parts.add(Arr.create(cpart));
    }
    return Arr.create(parts);
  }
}