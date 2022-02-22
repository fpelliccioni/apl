#pragma once

#include <cassert>
#include <string>

struct Token { //implements Tokenable
    static const int EPOS_DEF = -12345;

    std::string raw;
    int spos; // incl
    int epos; // excl


    Token(std::string raw, int spos, int epos)
        : raw(raw)
        , spos(spos)
        , epos(epos)
    {}

    Token const& getToken() const {
        return *this;
    }

    std::string toTree(std::string& p) const {
        // std::string className = this.getClass().getCanonicalName(); //TODO
        std::string className = "TODO";
        p += "  ";
        return p + className + ' ' + std::to_string(spos) + '-' + std::to_string(epos) + '\n';
    }

    virtual std::string toRepr() const = 0;

    std::string source() const {
        return raw.substr(spos, epos);
    }

protected:
    Token(std::string raw, int spos)
        : raw(raw)
        , spos(spos)
        , epos(EPOS_DEF)
    {
    }

    void end(int i) {
        assert(epos == EPOS_DEF);
        epos = i;
    }
};