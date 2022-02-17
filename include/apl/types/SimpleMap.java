package APL.types;

import APL.errors.SyntaxError;

public abstract class SimpleMap extends APLMap {
  @Override public Obj getRaw(Value k) {
    return getv(k.asString());
  }

  public abstract Obj getv(std::string s);
  public abstract void setv(std::string s, Obj v);

  @Override public void set(Value k, Obj v) {
    setv(k.asString(), v);
  }

  @Override public Arr allValues() {
    throw new SyntaxError("getting list of values of "+name());
  }

  @Override public Arr allKeys() {
    throw new SyntaxError("getting list of keys of "+name());
  }

  @Override public Arr kvPair() {
    throw new SyntaxError("getting entries of "+name());
  }

  @Override public int size() {
    throw new SyntaxError("getting size of "+name());
  }
}