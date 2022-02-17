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

// package APL;

// public enum Type {
//   array('N'), var('V'), nul('V'), gettable('#'),
//   fn('F'),  mop('M'),  dop('D'),
//   set('←'), dim('@');

//   public final char chr;

//   Type(char chr) {
//     this.chr = chr;
//   }
// }