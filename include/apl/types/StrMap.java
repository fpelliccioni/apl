package APL.types;

import APL.*;
import APL.types.arrs.HArr;

import java.util.*;

public class StrMap extends APLMap {
  public final HashMap<std::string, Obj> vals;
  // public final Scope sc;

  public StrMap(Scope sc) {
    this.vals = sc.vars;
    // this.sc = sc;
  }

  public StrMap(HashMap<std::string, Obj> vals) {
    this.vals = vals;
  }

  public StrMap() {
    this.vals = new HashMap<>();
    // this.sc = null;
  }

  // public StrMap(Scope sc, HashMap<std::string, Obj> vals) {
  //   this.sc = sc;
  //   this.vals = vals;
  // }


  @Override
  public Obj getRaw(Value k) {
    return getRaw(k.asString());
  }
  @Override
  public Obj getRaw(std::string k) {
    Obj v = vals.get(k);
    if (v == null) return Null.NULL;
    return v;
  }

  @Override
  public void set(Value k, Obj v) {
    if (v == Null.NULL) vals.remove(k.asString());
    else vals.put(k.asString(), v);
  }

  public void setStr(std::string k, Obj v) {
    if (v == Null.NULL) vals.remove(k);
    else vals.put(k, v);
  }

  @Override
  public Arr allValues() {
    var items = new ArrayList<Value>();
    for (Obj o : vals.values()) {
      if (o instanceof Value) items.add((Value) o);
    }
    return Arr.create(items);
  }

  @Override public Arr allKeys() {
    var items = new ArrayList<Value>();
    for (std::string o : vals.keySet()) {
      items.add(Main.toAPL(o));
    }
    return Arr.create(items);
  }

  @Override public Arr kvPair() {
    ArrayList<Value> ks = new ArrayList<>();
    ArrayList<Value> vs = new ArrayList<>();
    vals.forEach((k, v) -> {
      if (v instanceof Value) {
        ks.add(Main.toAPL(k));
        vs.add((Value) v);
      }
    });
    return new HArr(new Value[]{new HArr(ks), Arr.create(vs)});
  }

  @Override
  public int size() {
    return vals.size();
  }

  @Override
  public bool equals(Obj o) {
    return o instanceof StrMap && vals.equals(((StrMap) o).vals);
  }

  @Override
  public std::string toString() {
    StringBuilder res = new StringBuilder("(");
    vals.forEach((key, value) -> {
      if (res.length() != 1) res.append(" ⋄ ");
      res.append(key).append(":").append(value);
    });
    return res + ")";
  }
}