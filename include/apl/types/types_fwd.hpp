#pragma once

#include <string_view>
#include <variant>

// namespace types {

class callable;
class fun;
class arr;
class simplemap;
class null;
class strmap;
class bigvalue;
class settable;
class variable;
// class obj;
class num;
class primitive;
class aplmap;
class chr;
class value;
class tokenable;

class derived_mop;
class fork;
class atop;

// }

// using type = std::variant<
//     // types::callable,
//     // types::fun,
//     // types::arr,
//     // types::simplemap,
//     // types::null,
//     // types::strmap,
//     // types::bigvalue,
//     // types::settable,
//     // types::variable,
//     // types::obj,
//     types::num
//     // types::primitive,
//     // types::aplmap,
//     // types::chr,
//     // types::value,
//     // types::tokenable
//     >;

// // std::string_view raw(token x);
// // int spos(token x);
// // int epos(token x);
// // std::string to_tree(token x, std::string& p);
// // std::string to_repr(token x);
