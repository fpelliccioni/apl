#pragma once

enum class Type {
    array,
    var,
    nul,
    gettable,
    fn,
    mop,
    dop,
    set,
    dim,
};

char chr(Type x) {
    switch (x) {
        case Type::array:
          return 'N';
        case Type::var:
          return 'V';
        case Type::nul:
          return 'V';
        case Type::gettable:
          return '#';
        case Type::fn:
          return 'F';
        case Type::mop:
          return 'M';
        case Type::dop:
          return 'D';
        case Type::set:
          return '<';   // return '←';
        case Type::dim:
          return '@';
    }
}
