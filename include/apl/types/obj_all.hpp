#pragma once

#include <string_view>
#include <variant>

#include <apl/type.hpp>

class and_builtin;
using builtin = std::variant<
    and_builtin
    >;

class variable;
using settable = std::variant<
    variable
    >;


class derived_mop;
class fork;
class atop;
using fun = std::variant<
    derived_mop,
    fork,
    atop
    >;

class brackets;
class dop;
class mop;
class abstract_set;
using callable = std::variant<
    fun,
    brackets,
    dop,
    mop,
    abstract_set
    >;


class value;
using obj = std::variant<
    callable,
    settable,
    value
    >;

// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------

struct derived_mop { //extends Fun {
    obj& aa;
    obj& op;    //mop

    // derived_mop(obj& o, mop& op)
    derived_mop(obj& o, obj& op)
        // : aa(o), op(op), token(op.token)    //TODO
        : aa(o), op(op)
    {}

    std::string repr() const;

    std::string to_string() const {
        return repr();
    }
};


// --------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------


bool is_obj(obj x);
Type type(obj x);
std::string to_string(obj x);

bool is_fun(obj x);
bool is_dop(obj x);
bool is_mop(obj x);
bool is_settable(obj x);


// TODO: each hierarchy has to be another variant
