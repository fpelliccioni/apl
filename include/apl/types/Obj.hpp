#pragma once

#include <apl/Type.hpp>
#include <apl/tokenizer/Token.hpp>

class Arr;
class Char;
class Num;
class APLMap;
class Fun;
class Null;
class Brackets;
class VarArr;
class Variable;
class Pick;
class Mop;
class Dop;
class ArrFun;
class APLMap;
class BigValue;

class Obj { //implements Tokenable
public:
    Token* token;

    bool isObj() {
        return type()==Type::array || type() == Type::var;
    }

    virtual Type type() const = 0;

    //TODO
    // bool equals(Obj o) {
    //    return false;
    // }

    std::string humanType(bool article) const;

    //TODO
    // bool equals(Object obj) const {
    //     return obj instanceof Obj && equals((Obj) obj);
    // }

    virtual std::string name() const {
        return toString();
    }

    virtual std::string toString() const {
        return humanType(false);
    }

    Token const* getToken() const {
        return token;
    }


    // @Override
    // public int hashCode() {
    //   throw new NYIError("hash not supported for "+this, this);
    // }

    // final protected int actualHashCode() {
    //   return super.hashCode();
    // }

};