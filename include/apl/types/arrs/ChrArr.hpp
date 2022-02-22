#pragma once

#include <apl/types/Arr.hpp>
#include <apl/types/Char.hpp>

struct ChrArr : Arr {
    std::string s;

    ChrArr(std::string s)
        : Arr(std::vector<int>{ int(s.size()) }, s.size(), 1)
        , s(s)
    {}

    ChrArr(std::string s, std::vector<int> sh)
        : Arr(sh, s.size(), sh.size())
        , s(s)
    {
        // assert Config::enclosePrimitives || sh.size() != 0;
    }

    // ChrArr(std::vector<char> arr, std::vector<int> sh) {
    //   this(new std::string(arr), sh);
    // }

    // ChrArr(std::vector<char> arr) {
    //   this(new std::string(arr));
    // }

    virtual std::vector<int> asIntArrClone() const override {
        // throw new DomainError("Using character array as integer array", this);
        throw "Using character array as integer array";
    }

    virtual int asInt() const override {
        // throw new DomainError("Using character array as integer", this);
        throw "Using character array as integer";
    }

    virtual Value const* get(int i) const override {
      return Char::of(s[i]);
    }

    virtual Value const* first() const override {
        if (ia > 0) return Char::of(s[0]);
        return CHAR_SPACE;
    }

    virtual std::string asString() const override {
        if (rank > 1) {
            //TODO
            // throw new DomainError("Using rank "+rank+" character array as string", this);
            throw "Using rank ... character array as string";
        }
        return s;
    }

    Value* prototype() override {
        return CHAR_SPACE;
    }

    Value* safePrototype() override {
        return CHAR_SPACE;
    }

    virtual Value const* ofShape(std::vector<int> sh) const override {
        if (sh.size() == 0 && !Config::enclosePrimitives) return get(0);
        return new ChrArr(s, sh);
    }

    virtual Value const* squeeze() const override {
        return this;
    }

    // virtual override
    // int hashCode() {
    //   if (hash == 0) {
    //     for (char c : s.toCharArray()) {
    //       hash = hash*31 + c;
    //     }
    //     hash = shapeHash(hash);
    //   }
    //   return hash;
    // }
};





// package APL.types.arrs;

// import APL.Main;
// import APL.errors.DomainError;
// import APL.types.*;

// public class ChrArr extends Arr {
//   public std::string s;

//   public ChrArr(std::string s) {
//     super(new int[]{s.length()}, s.length(), 1);
//     this.s = s;
//   }
//   public ChrArr(std::string s, int[] sh) {
//     super(sh, s.length(), sh.length);
//     assert Config::enclosePrimitives || sh.length != 0;
//     this.s = s;
//   }

//   public ChrArr(char[] arr, int[] sh) {
//     this(new std::string(arr), sh);
//   }
//   public ChrArr(char[] arr) {
//     this(new std::string(arr));
//   }


//   @Override
//   public int[] asIntArrClone() {
//     throw new DomainError("Using character array as integer array", this);
//   }

//   @Override
//   public int asInt() {
//     throw new DomainError("Using character array as integer", this);
//   }

//   @Override
//   public Value get(int i) {
//     return Char::of(s.charAt(i));
//   }

//   @Override public Value first() {
//     if (ia > 0) return Char::of(s.charAt(0));
//     return CHAR_SPACE;
//   }
//   @Override
//   public std::string asString() {
//     if (rank > 1) throw new DomainError("Using rank "+rank+" character array as string", this);
//     return s;
//   }

//   public Value prototype() {
//     return CHAR_SPACE;
//   }
//   public Value safePrototype() {
//     return CHAR_SPACE;
//   }

//   @Override
//   public Value ofShape(int[] sh) {
//     if (sh.length==0 && !Config::enclosePrimitives) return get(0);
//     return new ChrArr(s, sh);
//   }

//   @Override
//   public Value squeeze() {
//     return this;
//   }

//   @Override
//   public int hashCode() {
//     if (hash == 0) {
//       for (char c : s.toCharArray()) {
//         hash = hash*31 + c;
//       }
//       hash = shapeHash(hash);
//     }
//     return hash;
//   }
// }