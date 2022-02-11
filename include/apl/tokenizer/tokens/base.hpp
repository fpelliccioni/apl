#pragma once

#include <format>
#include <string>
#include <string_view>

namespace tokens {

struct base { //implements Tokenable  TODO: use Concept?
    std::string_view raw;
    int spos; // incl
    int epos; // excl
    static constexpr int EPOS_DEF = -12345;

    base(std::string_view raw, int spos)
        : raw(raw), spos(spos), epos(EPOS_DEF)
    {}

    base(std::string_view raw, int spos, int epos)
        : raw(raw), spos(spos), epos(epos)
    {}

    void end(int i) {
        // assert epos == EPOS_DEF;
        epos = i;
    }

    // /*@Override*/ Token getToken() {
    //     return this;
    // }

    // std::string to_tree(std::string& p, std::string_view class_name) const {
    //     p += "  ";
    //     return p;
    //     // return std::format("{}{} {}-{}\n", p, class_name, spos, epos);
    //     // return p + class_name + ' ' + spos + '-' + epos + '\n';
    // }

    // abstract String toRepr();

    std::string_view source() const {
        return raw.substr(spos, epos - spos);
    }
};

} // namespace tokens

// class Token { //implements Tokenable  TODO: use Concept?
//   public final String raw;
//   public final int spos; // incl
//   public       int epos; // excl
//   public static final int EPOS_DEF = -12345;
//   protected Token(String raw, int spos) {
//     this.raw = raw;
//     this.spos = spos;
//     epos = EPOS_DEF;
//   }

//   public Token(String raw, int spos, int epos) {
//     this.raw = raw;
//     this.spos = spos;
//     this.epos = epos;
//   }

//   protected void end(int i) {
//     assert epos == EPOS_DEF;
//     epos = i;
//   }

//   @Override public Token getToken() {
//     return this;
//   }
//   public String toTree(String p) {
//     p+= "  ";
//     return p + this.getClass().getCanonicalName() + ' '+ spos + '-' + epos + '\n';
//   }
//   public abstract String toRepr();

//   public String source() {
//     return raw.substring(spos, epos);
//   }
// }