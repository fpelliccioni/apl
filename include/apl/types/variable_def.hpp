#pragma onde

#include <apl/types/obj.hpp>
// #include <apl/types/obj_fwd.hpp>
#include <apl/types/variable.hpp>

Type variable::type() const {
    // return v ? type(v) : Type::var;          //TODO
    return Type::var;
}

obj variable::getOrThis() const {
    // if ( ! v) return this;
    // return v;
    return variable{};   //TODO
}

bool variable::hasValue() const {
    // if ( ! v) return false;
    // return true;
    return false;   //TODO
}

std::string variable::to_string() const {
    // if (Main.debug) return v == null? "var:"+name : "var:"+v;
    // return v == null? "var:"+name : v.toString();
    return "";  // TODO
}

