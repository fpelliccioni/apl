package APL.types;

import APL.errors.DomainError;

public abstract class Primitive extends Value {
  private static final int[] SHAPE = new int[0];
  
  public Primitive() {
    super(SHAPE, 1, 0);
  }
  
  @Override
  public final Value get(int i) {
    return this;
  }
  
  public final Value first() {
    return this;
  }
  
  @Override
  public int[] asIntArrClone() {
    throw new DomainError("Using " + this.oneliner() + " as integer array", this);
  }
  @Override
  public int[] asIntVec() {
    throw new DomainError("Using " + this.oneliner() + " as integer vector", this);
  }
  
  @Override
  public int asInt() {
    throw new DomainError("Using " + this.oneliner() + " as integer", this);
  }
  
  @Override
  public String asString() {
    throw new DomainError("Using " + this.oneliner() + " as string", this);
  }
  
  public final Value prototype() {
    Value v = safePrototype();
    if (v==null) throw new DomainError("Getting prototype of "+this, this);
    return v;
  }
  public Value safePrototype() {
    return null;
  }
  
  @Override public Value squeeze() { // primitives are already pretty squeezed
    return this;
  }
}