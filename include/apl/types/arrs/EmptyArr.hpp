#pragma once

#include <apl/types/Arr.hpp>

struct EmptyArr : Arr {
    static int[] SHAPE0 = new int[]{0};
    static EmptyArr SHAPE0Q = new EmptyArr(SHAPE0, null);
    static EmptyArr SHAPE0N = new EmptyArr(SHAPE0, Num.ZERO);
    static int[] NOINTS = new int[0];

    EmptyArr(int[] sh, Value proto)
        : Arr(sh, 0, sh.length)
        , proto(proto)
    {}

    virtual int[] asIntArrClone() const override {
        return NOINTS;
    }

    virtual int asInt() override {
        throw new DomainError("Using empty array as integer", this);
    }

    bool quickDoubleArr() {
        return true;
    }

    double[] asDoubleArr() {
        return DoubleArr.EMPTY;
    }


    virtual Value const* get(int i) const override {
        throw new ImplementationError("internal: using get() on empty array; view )stack");
    }

    virtual std::string asString() override {
        if (rank >= 2) throw new DomainError("Using rank≥2 array as char vector", this);
        return "";
    }

    Value* prototype() {
        if (proto == null) throw new DomainError("couldn't get prototype", this);
        return proto;
    }

    Value* safePrototype() override {
        return proto;
    }

    virtual Value const* ofShape(std::vector<int> sh) const override {
        assert ia == Arr.prod(sh);
        return new EmptyArr(sh, proto);
    }

    virtual Value[] valuesCopy() override {
        return NO_VALUES; // safe, copy or not - doesn't matter
    }

    virtual Value* squeeze() const override {
        return this;
    }

    Iterator<Value> iterator() {
        return EIT;
    }

private:
    static
    Iterator<Value> EIT = new Iterator<Value>() {
        public bool hasNext() { return false; }
        public Value next() { throw new IllegalStateException("iterating empty array"); }
    };

    Value proto;
    static Value[] NO_VALUES = new Value[0];
};

// public class EmptyArr extends Arr {
//   public static final int[] SHAPE0 = new int[]{0};
//   public static final EmptyArr SHAPE0Q = new EmptyArr(SHAPE0, null);
//   public static final EmptyArr SHAPE0N = new EmptyArr(SHAPE0, Num.ZERO);
//   public static final int[] NOINTS = new int[0];
//   private final Value proto;
//   public EmptyArr(int[] sh, Value proto) {
//     super(sh, 0, sh.length);
//     this.proto = proto;
//   }

//   virtual override
//   public int[] asIntArrClone() {
//     return NOINTS;
//   }

//   virtual override
//   public int asInt() {
//     throw new DomainError("Using empty array as integer", this);
//   }

//   public bool quickDoubleArr() {
//     return true;
//   }

//   public double[] asDoubleArr() {
//     return DoubleArr.EMPTY;
//   }

//   virtual override
//   public Value get(int i) {
//     throw new ImplementationError("internal: using get() on empty array; view )stack");
//   }

//   virtual override
//   public std::string asString() {
//     if (rank >= 2) throw new DomainError("Using rank≥2 array as char vector", this);
//     return "";
//   }

//   public Value prototype() {
//     if (proto == null) throw new DomainError("couldn't get prototype", this);
//     return proto;
//   }
//   public Value safePrototype() {
//     return proto;
//   }

//   virtual override
//   public Value ofShape(int[] sh) {
//     assert ia == Arr.prod(sh);
//     return new EmptyArr(sh, proto);
//   }

//   private static final Value[] NO_VALUES = new Value[0];
//   virtual override
//   public Value[] valuesCopy() {
//     return NO_VALUES; // safe, copy or not - doesn't matter
//   }

//   virtual override
//   public Value squeeze() {
//     return this;
//   }



//   private static final Iterator<Value> EIT = new Iterator<Value>() {
//     public bool hasNext() { return false; }
//     public Value next() { throw new IllegalStateException("iterating empty array"); }
//   };
//   public Iterator<Value> iterator() {
//     return EIT;
//   }
// }