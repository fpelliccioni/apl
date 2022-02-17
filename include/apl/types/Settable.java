package APL.types;

import APL.Type;
import APL.errors.ValueError;

public abstract class Settable extends Obj {
  final Obj v;
  protected Settable(Obj v) {
    this.v = v;
  }
  @Override
  public Type type() {
    return v == null? Type.var : v.type();
  }
  public abstract void set(Obj v, Callable blame);
  public Obj get() {
    if (v == null) throw new ValueError("trying to get value of non-existing settable", this);
    return v;
  }
  public Obj getOrThis() {
    if (v == null) return this;
    return v;
  }
}