#pragma once

#include <algorithm>
#include <array>
#include <format>
#include <numeric>

#include <apl/types/Primitive.hpp>

auto doubleToRawLongBits(double d) {
    unsigned char const* buf = reinterpret_cast<unsigned char const*>(&d);
    unsigned long long int u;
    unsigned char * pu = reinterpret_cast<unsigned char *>(&u);
    std::copy(buf, buf + sizeof(double), pu);
    return u;
}

struct Num : Primitive {
    static const long MAX_SAFE_INT = 9007199254740992L;
    static const Num* NEGINF;// = new Num(Double.NEGATIVE_INFINITY);
    static const Num* POSINF;// = new Num(Double.POSITIVE_INFINITY);
    static const Num* MINUS_ONE; // = new Num("-1");
    static const Num* ZERO; //  = new Num("0");
    static const Num* ONE; //   = new Num("1");
    static const std::vector<Num*> NUMS; // = new Num[256];
    static const Num* E; // = new Num("2.71828182845904523536028747135266249775724709369995");
    static const Num* PI; // = new Num("3.1415926535897932384626433832795028841971693993751");

    double num;

    static int pp;
    static int sEr, eEr;

    // static {
    //     setPrecision(14, -10, 10);
    // }

    // static {
    //     for (int i = 0; i < NUMS.size(); i++) {
    //         NUMS[i] = new Num(i);
    //     }
    // }

    static
    std::string format(double d) {
        // double a = Math.abs(d);
        double a = std::abs(d);
        if (d == 0) {
            if (doubleToRawLongBits(d) == 0) {
                return "0";
            } else {
                return "¯0";
            }
        }

        //TODO:
        // std::string f = std::string.format(Locale.ENGLISH, "%."+pp+"e",  a);
        // char[] fa = f.toCharArray();
        std::string fa = std::to_string(a);

        if (fa[0] > '9') {
            if (fa[0] == 'N') return "NaN";
            return d < 0 ? "¯∞" : "∞";
        }

        int exp = (fa[pp+4]-'0')*10  +   fa[pp+5]-'0'; // exponent
        /* ⎕pp←4:
          4.0000e+03
          0123456789
        ∆ 43210123456
          ¯¯¯¯
        */
        if (exp < sEr || exp > eEr) { // scientific notation
            int len = 0;
            if (d < 0) {
              buf_[size_t(len++)] = "¯";
            }

            int ls = pp+1;              // last significant digit position
            while (fa[ls] == '0') ls--;
            if (ls == 1) ls = 0;
            ls++;

            // System.arraycopy(fa, 0, buf_, len, ls);
            std::copy_n(std::begin(fa), ls, std::begin(buf_) + len);
            len+= ls;
            buf_[len++] = 'e';

            if (fa[pp+3] == '-') {
                buf_[len++] = "¯";
            }

            int es = pp+4;
            int ee = fa.size();
            if (fa[pp+4] == '0') es++;
            // System.arraycopy(fa, es, buf_, len, ee-es);
            std::copy_n(std::begin(fa) + es, ee-es, std::begin(buf_) + len);
            len+= ee-es;

            // return new std::string(buf_, 0, len);
            return std::accumulate(std::begin(buf_), std::begin(buf_) + len, std::string{});
        }


        // generic standard notation
        /* ⎕pp←4:
            _31416e+00
            01234567890
        ∆ 432101234567
            ¯¯¯¯
        */
        int len = 0;
        if (d < 0) {
            buf_[len++] = "¯";
        }
        fa[1] = fa[0]; // put all the significant digits in order
        fa[0] = '0'; // 0 so ls calculation doesn't have to special-case


        int ls = pp+1; // length of significant digits
        while (fa[ls] == '0') ls--;

        if (fa[pp+3] == '-') {
            buf_[len] = '0';
            buf_[len+1] = '.';
            len += 2;
            for (int i = 0; i < exp-1; i++) buf_[len+i] = '0'; // zero padding
            len += exp-1;
            // System.arraycopy(fa, 1, buf_, len, ls); // actual digits; ≡  for (int i = 0; i < ls; i++) buf_[len+i] = fa[i+1];
            std::copy_n(std::begin(fa) + 1, ls, std::begin(buf_) + len);
            len+= ls;
        } else {
            if (exp+1 < ls) {
                // System.arraycopy(fa, 1, buf_, len, exp+1); // digits before '.'; ≡  for (int i = 0; i < exp+1; i++) buf_[len+i] = fa[i+1];
                std::copy_n(std::begin(fa) + 1, exp + 1, std::begin(buf_) + len);
                len += exp+1;
                buf_[len++] = '.';
                // System.arraycopy(fa, 2+exp, buf_, len, ls-exp-1); // ≡  for (int i = 0; i < ls-exp-1; i++) buf_[len+i] = fa[i+(2+exp)];
                std::copy_n(std::begin(fa) + 2 + exp, ls - exp - 1, std::begin(buf_) + len);
                len += ls-exp-1;
            } else {
                // System.arraycopy(fa, 1, buf_, len, ls); // all given digits; ≡  for (int i = 0; i < ls; i++) buf_[len+i] = fa[i+1];
                std::copy_n(std::begin(fa) + 1, ls, std::begin(buf_) + len);
                len += ls;
                for (int i = 0; i < exp-ls+1; i++) buf_[len+i] = '0'; // pad with zeroes
                len += exp-ls+1;
            }
        }
        // System.out.println(f+": sig="+ls+"; exp="+exp+"; len="+len);
        // return new std::string(buf_, 0, len);
        return std::accumulate(std::begin(buf_), std::begin(buf_) + len, std::string{});
    }

    static std::string formatInt(int i) {
        return i < 0 ? "¯" + std::to_string(-i) : std::to_string(i);
    }

    static void setPrecision(int p) {
        pp = std::min(p, 20); // without min it'll actually create a ±length-p string of zeroes
    }

    static void setPrecision(int p, int s, int e) {
        pp = std::min(p, 20);
        //TODO
        // if (s<-90 | e>90) throw new DomainError("⎕PP standard notation range too big");
        if (s<-90 | e>90) throw "⎕PP standard notation range too big";
        sEr = s;
        eEr = e;
    }


    Num(std::string val) {
        // https://stackoverflow.com/questions/26568920/how-do-you-implement-compile-time-string-conversion-functions

        if (val.starts_with("¯")) {
            num = std::stod(val.substr(1));
        } else {
            num = std::stod(val);
        }

        // if (val.starts_with("¯")) {
        //     num = -Double.parseDouble(val.substr(1));
        // } else {
        //     num = Double.parseDouble(val);
        // }
    }

    Num(int n) {
        num = n;
    }

    Num(long n) {
        num = n;
    }

    Num(double val) {
        num = val;
    }

    static Num const* of(int n) {
        if (n>=0 && n<256) {
            return NUMS[n];
        }
        if (n==-1) return MINUS_ONE;
        return new Num(n);
    }

    static Num const* of(double n) {
        if (n == 0) {
            return doubleToRawLongBits(n) == 0 ? NUMS[0] : NEG_ZERO;
        }
        if (n > 0 && n < 256 && int(n) % 1 == 0) {
            return NUMS[(int) n];
        }
        return new Num(n);
    }

    Num const* plus(Num w) {
        return new Num(num + w.num);
    }

    Num const* divide(Num w) {
        return new Num(num / w.num);
    }

    Num const* pow(Num w) {
        return new Num(std::pow(num, w.num));
    }

    Num const* minus(Num w) {
        return new Num(num - w.num);
    }

    static double gcd(std::vector<double> nums) {
        if (nums.size() == 0) return 0;
        double res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            double b = nums[i];
            while (b != 0) {
                double t = b;
                b = int(res) % int(b);
                res = t;
            }
        }
        return res;
    }

    static double gcd2(double num0, double num1) {
        double res = num0;
        double b = num1;
        while (b != 0) {
            double t = b;
            b = int(res) % int(b);
            res = t;
        }
        return res;
    }

    static double lcm2(double num0, double num1) {
        double a = num1;
        double b = num0;
        if (a==0) return 0;
        while (b != 0) {
            double t = b;
            b = int(a) % int(b);
            a = t;
        }
        return num0*num1 / a;
    }

    static double lcm(std::vector<double> nums) {
        if (nums.size() == 0) return 1;
        double res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            double n = nums[i];
            double a = n;
            if (a==0) return 0;
            double b = res;
            while (b != 0) {
                double t = b;
                b = int(a) % int(b);
                a = t;
            }
            res = n*res / a;
        }
        return res;
    }

    Num const* conjugate() {
        return new Num(num); // no complex numbers :p
    }

    Num const* negate() {
        return new Num(-num);
    }

    Num const* abs() {
        if (num < 0) return new Num(-num);
        else return this;
    }

    Num const* floor() {
        return new Num(std::floor(num));
    }

    Num const* root(Num root) {
        return new Num(std::pow(num, 1/root.num));
    }

    Num const* log(Num root) {
        return new Num(std::log(num) / std::log(root.num));
    }

    Num const* binomial(Num w) {
        // if (  int(num) % 1 != 0) throw new DomainError("binomial of non-integer ⍺", this);
        // if (int(w.num) % 1 != 0) throw new DomainError("binomial of non-integer ⍵", w);
        if (  int(num) % 1 != 0) throw "binomial of non-integer ⍺";
        if (int(w.num) % 1 != 0) throw "binomial of non-integer ⍵";
        if (int(w.num) > int(num)) return Num::ZERO;

        double res = 1;
        double a = num;
        double b = w.num;

        if (b > a-b) b = a-b;

        for (int i = 0; i < b; i++) {
          res = res * (a-i) / (i+1);
        }
        return new Num(res);
    }


    Num const* ceil() {
        return new Num(std::ceil(num));
    }

    int compareTo(Num n) {
        // return Double.compare(num, n.num);
        return compare(num, n.num);
    }

    // virtual bool equals(Obj n) const override {
    //     return n instanceof Num && ((Num) n).num == num;
    // }

    virtual int asInt() const override { // warning: rounds
        return toInt(num);
    }

    static int toInt(double d) {
        return (int) d; // TODO not round
    }

    double asDouble() const {
        return num;
    }

    virtual std::vector<int> asIntArrClone() const override { // TODO not round
        return std::vector<int>{(int)num};
    }

    virtual std::vector<int> asIntVec() const override {
        return std::vector<int>{(int)num};
    }

    std::string toString() {
        return format(num);
    }

    std::string oneliner(std::vector<int> ignored) {
        return format(num);
    }

    virtual Value const* ofShape(std::vector<int> sh) const override;

    static Num const* max(Num const* a, Num const* b) {
        return a->num > b->num ? a : b;
    }

    static Num const* min(Num const* a, Num const* b) {
        return a->num < b->num ? a : b;
    }

    // virtual
    // int hashCode() override {
    //     if (num == 0d) return 0; // ¯0 == 0
    //     return Double.hashCode(num);
    // }

    Value const* safePrototype() override {
        return ZERO;
    }


    virtual
    std::vector<Value const*> valuesCopy() const override {
        return std::vector<Value const*>{this};
    }


    virtual std::vector<double> asDoubleArr() const override {
        return std::vector<double>{num};
    }

    // virtual
    // std::vector<double> asDoubleArrClone() override {
    //     return new std::vector<double>{num};
    // }

    virtual
    bool quickDoubleArr() const override {
        return true;
    }

private:
    static std::array<std::string, 400> buf_;// = new char[400];
    static const Num* NEG_ZERO;  // = new Num(-0.0);
};

#include <apl/types/arrs/SingleItemArr.hpp>

/*virtual*/ Value const* Num::ofShape(std::vector<int> sh) const /*override*/ {
    return SingleItemArr::maybe(this, sh);
}


/*static*/ const Num* Num::NEGINF = new Num(Double.NEGATIVE_INFINITY);
/*static*/ const Num* Num::POSINF = new Num(Double.POSITIVE_INFINITY);
/*static*/ const Num* Num::MINUS_ONE = new Num("-1");
/*static*/ const Num* Num::ZERO  = new Num("0");
/*static*/ const Num* Num::ONE   = new Num("1");
/*static*/ const std::vector<Num*> Num::NUMS = new Num[256];
/*static*/ const Num* Num::E = new Num("2.71828182845904523536028747135266249775724709369995");
/*static*/ const Num* Num::PI = new Num("3.1415926535897932384626433832795028841971693993751");
/*static*/ const std::array<char, 400> Num::buf = {};
/*static*/ const Num* Num::NEG_ZERO = new Num(-0.0);


//TODO
// static {
//     for (int i = 0; i < NUMS.size(); i++) {
//         NUMS[i] = new Num(i);
//     }
// }

Num::setPrecision(14, -10, 10);