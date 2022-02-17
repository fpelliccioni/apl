#pragma once

class Obj { //implements Tokenable
public:
    Token token;

    bool isObj() {
        return type()==Type.array || type() == Type.var;
    }

    virtual Type type() = 0;

    bool equals(Obj o) {
       return false;
    }

    std::string humanType(bool article) {
        // if (Add* v = dynamic_cast<Add*>(n)) {
        //   auto x = v->evaluate();
        // }

        if (dynamic_cast<Arr*>(*this))      return article? "an array"     : "array";
        if (dynamic_cast<Char*>(*this))     return article? "a character"  : "character";
        if (dynamic_cast<Num*>(*this))      return article? "a number"     : "number";
        if (dynamic_cast<APLMap*>(*this))   return article? "a map"        : "map";
        if (dynamic_cast<Fun*>(*this))      return article? "a function"   : "function";
        if (dynamic_cast<Null*>(*this))     return article? "javanull"     : "javanull";
        if (dynamic_cast<Brackets*>(*this)) return article? "brackets"     : "brackets";
        if (dynamic_cast<VarArr*>(*this))   return article? "a vararr"     : "vararr";
        if (dynamic_cast<Variable*>(*this)) return article? "a variable"   : "variable";
        if (dynamic_cast<Pick*>(*this))     return article? "an array item": "array item";
        if (dynamic_cast<Mop*>(*this))      return article? "monadic operator" : "a monadic operator";
        if (dynamic_cast<Dop*>(*this))      return article? "dyadic operator" : "a dyadic operator";
        if (dynamic_cast<ArrFun*>(*this))   return article? "an arrayified function": "arrayified function";
        if (dynamic_cast<APLMap.MapPointer*>(*this)) return article? "a map item": "map item";
        if (dynamic_cast<BigValue*>(*this)) return article? "a biginteger" : "biginteger";
        return "some type that dzaima hasn't named in Obj.humanType ಠ_ಠ (class = "+getClass()+")";
    }

    bool equals(Object obj) override {
      return obj instanceof Obj && equals((Obj) obj);
    }

    std::string name() {
      return toString();
    }

    std::string toString() override {
      return humanType(false);
    }

    Token getToken() override {
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