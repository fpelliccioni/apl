#pragma once

#include <apl/types/Arr.hpp>

struct SingleItemArr : Arr {
    SingleItemArr(Value item, int[] shape)
        : super(shape)
        , item(item)
    {}

    static Value maybe(Value item, int[] sh) {
        if (!Config::enclosePrimitives && sh.length == 0 && instanceof<Primitive>(item)) return item;
        return new SingleItemArr(item, sh);
    }

    virtual override
    int[] asIntArrClone() {
        int vi = item.asInt();
        int[] a = new int[ia];
        for (int i = 0; i < ia; i++) a[i] = vi;
        return a;
    }

    virtual override
    int asInt() {
        throw new DomainError("Using array as integer", this);
    }

    virtual override
    Value get(int i) {
        return item;
    }

    Value first() {
        return item;
    }

    virtual override
    std::string asString() {
        if (rank >= 2) throw new DomainError("Using rank≥2 array as string", this);
        if (! (item instanceof Char)) throw new DomainError("Using non-char array as string", this);
        char c = ((Char) item).chr;
        StringBuilder s = new StringBuilder();
        for (int i = 0; i < ia; i++) s.append(c);
        return s.toString();
    }

    Value prototype() {
        return item.prototype();
    }

    Value safePrototype() {
        return item.safePrototype();
    }

    virtual override
    Value ofShape(int[] sh) {
        return SingleItemArr.maybe(item, sh);
    }

    virtual override
    bool quickDoubleArr() {
        return item instanceof Num;
    }

    Value[] valuesCopy() {
        Value[] vs = new Value[ia];
        for (int i = 0; i < ia; i++) vs[i] = item;
        return vs;
    }

    double sum() {
        return item.asDouble() * ia;
    }

    virtual override
    double[] asDoubleArr() {
        double[] res = new double[ia];
        double n = item.asDouble();
        for (int i = 0; i < ia; i++) res[i] = n;
        return res;
    }

    virtual override
    double[] asDoubleArrClone() {
        return asDoubleArr();
    }

    virtual override
    Value squeeze() {
        Value ov = item.squeeze();
        if (ov == item) return this;
        return new SingleItemArr(item, shape);
    }

    virtual override
    std::string oneliner(int[] where) {
        if (where.length == 0) {
            std::string r = Main.formatAPL(shape);
            return r + "⍴" + item.oneliner();
        }
        return super.oneliner(where);
    }

    virtual override Iterator<Value> iterator() {
        //noinspection Convert2Diamond java 8
        return new Iterator<Value>() {
          int i = 0;
          virtual override bool hasNext() {
            return i < ia;
          }

          virtual override Value next() {
            i++;
            return item;
          }
        };
    }

private:
    Value* item;
};

// package APL.types.arrs;

// import APL.Main;
// import APL.errors.DomainError;
// import APL.types.*;

// import java.util.Iterator;

// public class SingleItemArr extends Arr {
//   private final Value item;

//   public SingleItemArr(Value item, int[] shape) {
//     super(shape);
//     this.item = item;
//   }

//   public static Value maybe(Value item, int[] sh) {
//     if (!Config::enclosePrimitives && sh.length==0 && item instanceof Primitive) return item;
//     return new SingleItemArr(item, sh);
//   }

//   @Override
//   public int[] asIntArrClone() {
//     int vi = item.asInt();
//     int[] a = new int[ia];
//     for (int i = 0; i < ia; i++) a[i] = vi;
//     return a;
//   }

//   @Override
//   public int asInt() {
//     throw new DomainError("Using array as integer", this);
//   }

//   @Override
//   public Value get(int i) {
//     return item;
//   }

//   public Value first() {
//     return item;
//   }

//   @Override
//   public std::string asString() {
//     if (rank >= 2) throw new DomainError("Using rank≥2 array as string", this);
//     if (! (item instanceof Char)) throw new DomainError("Using non-char array as string", this);
//     char c = ((Char) item).chr;
//     StringBuilder s = new StringBuilder();
//     for (int i = 0; i < ia; i++) s.append(c);
//     return s.toString();
//   }

//   public Value prototype() {
//     return item.prototype();
//   }
//   public Value safePrototype() {
//     return item.safePrototype();
//   }
//   @Override
//   public Value ofShape(int[] sh) {
//     return SingleItemArr.maybe(item, sh);
//   }

//   @Override
//   public bool quickDoubleArr() {
//     return item instanceof Num;
//   }
//   public Value[] valuesCopy() {
//     Value[] vs = new Value[ia];
//     for (int i = 0; i < ia; i++) vs[i] = item;
//     return vs;
//   }

//   public double sum() {
//     return item.asDouble() * ia;
//   }

//   @Override
//   public double[] asDoubleArr() {
//     double[] res = new double[ia];
//     double n = item.asDouble();
//     for (int i = 0; i < ia; i++) res[i] = n;
//     return res;
//   }

//   @Override
//   public double[] asDoubleArrClone() {
//     return asDoubleArr();
//   }

//   @Override
//   public Value squeeze() {
//     Value ov = item.squeeze();
//     if (ov == item) return this;
//     return new SingleItemArr(item, shape);
//   }

//   @Override
//   public std::string oneliner(int[] where) {
//     if (where.length == 0) {
//       std::string r = Main.formatAPL(shape);
//       return r + "⍴" + item.oneliner();
//     }
//     return super.oneliner(where);
//   }

//   @Override public Iterator<Value> iterator() {
//     //noinspection Convert2Diamond java 8
//     return new Iterator<Value>() {
//       int i = 0;
//       @Override public bool hasNext() {
//         return i < ia;
//       }

//       @Override public Value next() {
//         i++;
//         return item;
//       }
//     };
//   }
// }