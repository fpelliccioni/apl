#pragma once

#include <string_view>
#include <variant>

#include <apl/types/functions/builtins/fns/and_builtin.hpp>
#include <apl/types/fun.hpp>
#include <apl/types/value.hpp>
#include <apl/types/functions/dop.hpp>
#include <apl/types/functions/mop.hpp>
#include <apl/types/functions/derived_mop.hpp>
#include <apl/types/functions/trains/fork.hpp>
#include <apl/types/functions/trains/atop.hpp>
#include <apl/types/variable_def.hpp>

#include <apl/type.hpp>

#include <apl/types/obj_fwd.hpp>

#include <apl/tokenizer/token.hpp>

bool is_obj(obj x) {
    // return type()==Type.array || type() == Type.var;
    return false;
}

Type type(obj x) {
    return std::visit([](auto&& arg) {
        return arg.type();
    }, x);
}

std::string to_string(obj x) {
    return std::visit([](auto&& arg) {
        return arg.to_string();
    }, x);
}

// derived_mop derive(mop m, obj o) {
derived_mop derive(obj m, obj o) {
    return derived_mop(o, m);
}


bool is_fun(obj x) {
    return
        // std::holds_alternative<shell>(x) ||
        // std::holds_alternative<nc>(x) ||
        // std::holds_alternative<big>(x) ||
        // std::holds_alternative<dr>(x) ||
        // std::holds_alternative<deriv_dim_fn>(x) ||
        // std::holds_alternative<builtin>(x) ||
        // std::holds_alternative<derived_dop>(x) ||
        // std::holds_alternative<fun_arr>(x) ||
        // std::holds_alternative<binda>(x) ||
        // std::holds_alternative<rshoebuiltin>(x) ||
        // std::holds_alternative<dfn>(x) ||
        std::holds_alternative<derived_mop>(x) ||
        std::holds_alternative<atop>(x) ||
        std::holds_alternative<fork>(x);
}

bool is_dop(obj x) {
    return false;
        // DervDimDop
        // AtBuiltin
        // CRepeatBuiltin
        // DotBuiltin
        // DualBuiltin
        // JotBuiltin
        // JotDiaeresisBuiltin
        // JotUBBuiltin
        // ObverseBuiltin
        // OverBuiltin
        // RepeatBuiltin
        // Ddop


    // return
    //     // std::holds_alternative<shell>(x) ||
    //     // std::holds_alternative<nc>(x) ||
    //     // std::holds_alternative<big>(x) ||
    //     // std::holds_alternative<dr>(x) ||
    //     // std::holds_alternative<deriv_dim_fn>(x) ||
    //     // std::holds_alternative<builtin>(x) ||
    //     // std::holds_alternative<derived_dop>(x) ||
    //     // std::holds_alternative<fun_arr>(x) ||
    //     // std::holds_alternative<binda>(x) ||
    //     // std::holds_alternative<rshoebuiltin>(x) ||
    //     // std::holds_alternative<dfn>(x) ||
    //     std::holds_alternative<derived_mop>(x) ||
    //     std::holds_alternative<atop>(x) ||
    //     std::holds_alternative<fork>(x);
}

bool is_mop(obj x) {
    // ProfilerOp
    // DervDimMop
    // EachBuiltin
    // EachLeft
    // EachRight
    // InvertBuiltin
    // KeyBuiltin
    // ObliqueBuiltin
    // ReduceBuiltin
    // ScanBuiltin
    // SelfieBuiltin
    // TableBuiltin
    // Dmop

    return false;
    // return
    //     // std::holds_alternative<shell>(x) ||
    //     // std::holds_alternative<nc>(x) ||
    //     // std::holds_alternative<big>(x) ||
    //     // std::holds_alternative<dr>(x) ||
    //     // std::holds_alternative<deriv_dim_fn>(x) ||
    //     // std::holds_alternative<builtin>(x) ||
    //     // std::holds_alternative<derived_dop>(x) ||
    //     // std::holds_alternative<fun_arr>(x) ||
    //     // std::holds_alternative<binda>(x) ||
    //     // std::holds_alternative<rshoebuiltin>(x) ||
    //     // std::holds_alternative<dfn>(x) ||
    //     std::holds_alternative<derived_mop>(x) ||
    //     std::holds_alternative<atop>(x) ||
    //     std::holds_alternative<fork>(x);
}

bool is_settable(obj x) {
    return false;
}


void set_token(obj o, token t) {
    //TODO
}



// package APL.types;

// import APL.*;
// import APL.errors.NYIError;
// import APL.tokenizer.Token;
// import APL.types.dimensions.*;
// import APL.types.functions.*;

// public abstract class Obj implements Tokenable {
//   public Token token;

//   public boolean isObj() {
//     return type()==Type.array || type() == Type.var;
//   }
//   abstract public Type type();
//   public boolean equals(Obj o) {
//     return false;
//   }

//   public String humanType(boolean article) {

//     if (this instanceof Arr     )return article? "an array"     : "array";
//     if (this instanceof Char    )return article? "a character"  : "character";
//     if (this instanceof Num     )return article? "a number"     : "number";
//     if (this instanceof APLMap  )return article? "a map"        : "map";
//     if (this instanceof Fun     )return article? "a function"   : "function";
//     if (this instanceof Null    )return article? "javanull"     : "javanull";
//     if (this instanceof Brackets)return article? "brackets"     : "brackets";
//     if (this instanceof VarArr  )return article? "a vararr"     : "vararr";
//     if (this instanceof Variable)return article? "a variable"   : "variable";
//     if (this instanceof Pick    )return article? "an array item": "array item";
//     if (this instanceof Mop     )return article? "monadic operator" : "a monadic operator";
//     if (this instanceof Dop     )return article? "dyadic operator" : "a dyadic operator";
//     if (this instanceof ArrFun  )return article? "an arrayified function": "arrayified function";
//     if (this instanceof APLMap.MapPointer)return article? "a map item": "map item";
//     if (this instanceof BigValue)return article? "a biginteger" : "biginteger";
//     return "some type that dzaima hasn't named in Obj.humanType ಠ_ಠ (class = "+getClass()+")";
//   }

//   @Override
//   public boolean equals(Object obj) {
//     return obj instanceof Obj && equals((Obj) obj);
//   }

//   public String name() {
//     return toString();
//   }

//   @Override
//   public String toString() {
//     return humanType(false);
//   }

//   @Override
//   public int hashCode() {
//     throw new NYIError("hash not supported for "+this, this);
//   }

//   final protected int actualHashCode() {
//     return super.hashCode();
//   }

//   @Override
//   public Token getToken() {
//     return token;
//   }
// }