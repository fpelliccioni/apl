#pragma once

#include <string_view>
#include <variant>

#include <apl/types/types_fwd.hpp>
#include <apl/type.hpp>

using obj = std::variant<
    and_builtin,
    variable,
    derived_mop,
    fork,
    atop
    >;

bool is_obj(obj x);
Type type(obj x);
std::string to_string(obj x);

bool is_fun(obj x);
bool is_dop(obj x);
bool is_mop(obj x);
bool is_settable(obj x);


// TODO: each hierarchy has to be another variant
