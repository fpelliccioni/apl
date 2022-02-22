#pragma once

#include <array>

#include <apl/Config.hpp>
#include <apl/Helpers.hpp>

constexpr
std::array<Char*, 128> ascii_chars();

struct Char : Primitive {
    char chr;

    // static {
    //     ASCII = new Char[128];
    //     for (int i = 0; i < 128; i++) {
    //         ASCII[i] = new Char((char) i);
    //     }
    // }


    // static const Char SPACE = ASCII[' '];

    Char(char c) {
        chr = c;
    }

    static
    Char* of(char c);

    // Char upper() {
    //     return Char::of(Character.toUpperCase(chr));
    // }

    // Char lower() {
    //     return Char::of(Character.toLowerCase(chr));
    // }

    // Char swapCase() {
    //     if (Character.isUpperCase(chr)) return lower();
    //     if (Character.isLowerCase(chr)) return upper();
    //     return Char::of(chr);
    // }

    // int getCase() {
    //     return Character.isUpperCase(chr)? 1 : Character.isLowerCase(chr)? -1 : 0;
    // }

    std::string toString() {
        if (Config::quotestrings) {
            return std::string("'") + chr + "'";
        }
        return std::string(1, chr);
    }

    std::string oneliner(std::vector<int> ignored) {
        return std::string("'") + chr + "'";
    }

    virtual Value const* ofShape(std::vector<int> sh) const override;

    int compareTo(Char v) {
        // return Character.compare(chr, v.chr);
        return compare(chr, v.chr);
    }

    // virtual bool equals(Obj c) const override {
    //     return c instanceof Char && chr == ((Char) c).chr;
    // }

    virtual std::string asString() const override {
        return std::string(1, chr);
    }

    // virtual int hashCode() override {
    //     return chr;
    // }

    Value* safePrototype() override;
};

//TODO
// constexpr
// std::array<Char*, 128> ascii_chars() {
//     std::array<Char*, 128> ascii;

//     for (size_t i = 0; i < 128; ++i) {
//         ascii[i] = new Char(char(i));
//     }

//     return ascii;
// }

// constexpr std::array<Char*, 128> ASCII = ascii_chars();

constexpr std::array<Char*, 128> ASCII = {};
constexpr Char* CHAR_SPACE = ASCII[' '];

// static
Char* Char::of(char c) {
    if (c < char(128)) return ASCII[c];
    return new Char(c);
}

#include <apl/types/arrs/ChrArr.hpp>

/*virtual*/
Value const* Char::ofShape(std::vector<int> sh) const /*override*/ {
    if (sh.size() == 0 && ! Config::enclosePrimitives) {
        return this;
    }
    // assert ia == Arr.prod(sh);
    // return new ChrArr(Character.toString(chr), sh); // special because there's no quickCharArr
    return new ChrArr(std::string(1, chr), sh); // special because there's no quickCharArr
}

Value* Char::safePrototype() /*override*/ {
    return CHAR_SPACE;
}
