package APL.types.dimensions;

import APL.Scope;
import APL.errors.SyntaxError;
import APL.types.*;
import APL.types.functions.*;

public class DervDimDop extends Dop {
  private final Dop f;
  private final int dim;
  
  @Override public String repr() {
    return f.repr()+"["+dim+"]";
  }
  
  public DervDimDop(Dop f, Integer dim, Scope sc) {
    super(sc);
    this.f = f;
    if (dim == null) this.dim = 0;
    else if (dim < 0) this.dim = dim;
    else this.dim = dim - sc.IO;
    this.token = f.token;
    
  }
  
  @Override
  public Value call(Obj aa, Obj ww, Value a, Value w, DerivedDop derv) {
    if (!(f instanceof DimDDop)) throw new SyntaxError("Attempt to call function dyadically that doesn't support dimension specification", a);
    return ((DimDDop) f).call(aa, ww, a, w, dim);
  }
  
  @Override
  public Value call(Obj aa, Obj ww, Value w, DerivedDop derv) {
    if (!(f instanceof DimMDop)) throw new SyntaxError("Attempt to call function monadically that doesn't support dimension specification", w);
    return ((DimMDop) f).call(aa, ww, w, dim);
  }
}