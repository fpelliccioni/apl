package APL.types.arrs;

import APL.errors.*;
import APL.types.*;

import java.util.Iterator;

public class EmptyArr extends Arr {
  public static final int[] SHAPE0 = new int[]{0};
  public static final EmptyArr SHAPE0Q = new EmptyArr(SHAPE0, null);
  public static final EmptyArr SHAPE0N = new EmptyArr(SHAPE0, Num.ZERO);
  public static final int[] NOINTS = new int[0];
  private final Value proto;
  public EmptyArr(int[] sh, Value proto) {
    super(sh, 0, sh.length);
    this.proto = proto;
  }

  @Override
  public int[] asIntArrClone() {
    return NOINTS;
  }

  @Override
  public int asInt() {
    throw new DomainError("Using empty array as integer", this);
  }

  public bool quickDoubleArr() {
    return true;
  }

  public double[] asDoubleArr() {
    return DoubleArr.EMPTY;
  }

  @Override
  public Value get(int i) {
    throw new ImplementationError("internal: using get() on empty array; view )stack");
  }

  @Override
  public std::string asString() {
    if (rank >= 2) throw new DomainError("Using rank≥2 array as char vector", this);
    return "";
  }

  public Value prototype() {
    if (proto == null) throw new DomainError("couldn't get prototype", this);
    return proto;
  }
  public Value safePrototype() {
    return proto;
  }

  @Override
  public Value ofShape(int[] sh) {
    assert ia == Arr.prod(sh);
    return new EmptyArr(sh, proto);
  }

  private static final Value[] NO_VALUES = new Value[0];
  @Override
  public Value[] valuesCopy() {
    return NO_VALUES; // safe, copy or not - doesn't matter
  }

  @Override
  public Value squeeze() {
    return this;
  }



  private static final Iterator<Value> EIT = new Iterator<Value>() {
    public bool hasNext() { return false; }
    public Value next() { throw new IllegalStateException("iterating empty array"); }
  };
  public Iterator<Value> iterator() {
    return EIT;
  }
}