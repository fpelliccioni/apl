#pragma once

#include <deque>
#include <optional>
// #include <stack>
#include <vector>

#include <apl/tokenizer/token.hpp>

struct Exec {
    // Scope sc;
    std::vector<token> tokens_;
    tokens::line allToken;
    // std::stack<token> left;      //Stack<Token> left;
    std::deque<token> left;         //Stack<Token> left;

    Exec(tokens::line ln) //, Scope sc)
        : tokens_(ln.tokens)
        , allToken(ln)
        // , sc(sc)
    {}

    std::optional<obj> exec() {
        // if (tokens_.size() > 0) Main.faulty = tokens_.get(0);
        // else Main.faulty = allToken;

        // if (sc.alphaDefined && tokens_.size() >= 2 && tokens_.get(0) instanceof OpTok && ((OpTok) tokens_.get(0)).op.equals("⍺") && tokens_.get(1) instanceof SetTok) {
        //     if (Main.debug) printlvl("skipping cuz it's ⍺←");
        //     return null;
        // }

        left.clear();
        left.insert(left.end(), tokens_.begin(), tokens_.end());         // left.addAll(tokens_);

        // if (Main.debug) {
        //     StringBuilder repr = new StringBuilder();
        //     for (Token t : tokens_) repr.append(t.toRepr()).append(" ");
        //     printlvl("NEW:");
        //     Main.printlvl++;
        //     printlvl("code:", repr);
        //     printlvl();
        // }

        reset();
        std::optional<std::vector<obj>> arr;

        while (left.size() > 0) {
            token t = left.back();
            left.pop_back();

            obj c = valueOf(t);

            // obj c;
            //TODO: not implemented yet
            // if (t instanceof NameTok && left.size() >= 2
            //     && left.peek() instanceof OpTok
            //     && ((OpTok) left.peek()).op.equals(".")
            //     && left.at(left.size() - 2) instanceof NameTok) {
            //     int ptr = left.size() - 2;

            //     while (ptr >= 2) {
            //         if (left.at(ptr - 1) instanceof OpTok
            //             && ((OpTok) left.at(ptr - 1)).op.equals(".")
            //             && left.at(ptr - 2) instanceof NameTok) ptr -= 2;
            //         else break;
            //     }

            //     std::vector<std::string> names = new std::string[(left.size() - ptr >> 1) + 1];
            //     names[names.length - 1] = ((NameTok) t).name;

            //     for (int i = names.length - 2; i >= 0; i--) {
            //         OpTok dot = (OpTok) left.pop();
            //         assert dot.op.equals(".");
            //         NameTok name = (NameTok) left.pop();
            //         names[i] = name.name;
            //     }

            //     if (Main.debug) printlvl("dotnot", Arrays.toString(names)); // todo fix (m).a (m).b0
            //     obj d = null;
            //     Settable r = sc.getVar(names[0]);
            //     for (int i = 1; i < names.length; i++) {
            //       if (r == null) {
            //           r = sc.getVar(names[i]);
            //           if (Main.debug) printlvl(":start", d, r, names[i]);
            //       } else {
            //           auto got = r.getOrThis();
            //           if (got instanceof fun) {
            //               if (Main.debug) printlvl(":fn", d, r, names[i]);
            //               if (d == null) d = got;
            //               else d = new DotBuiltin().derive(d, got);
            //               r = sc.getVar(names[i]);
            //           } else if (got instanceof APLMap) {
            //               if (Main.debug) printlvl(":map", d, r, names[i]);
            //               r = ((APLMap) got).get(names[i]);
            //           } else throw new SyntaxError("dot-chain contained non-fn/map");
            //       }
            //     }
            //     if (r != null) {
            //         if (d == null) d = r;
            //         else d = new DotBuiltin().derive(d, r.get());
            //     } else if (d == null) throw new SyntaxError("what?");
            //     c = d;
            //     if (Main.debug) printlvl(llToString());

            // } else {
                // c = valueOf(t);
            // }

            // if (is_obj(c) || type(c) == Type::gettable && (left.size() == 0 ||  !(left.at(0) instanceof SetTok))) {
            if (is_obj(c) || type(c) == Type::gettable && (left.size() == 0 || ! std::holds_alternative<tokens::set>(left.at(0)))) {
                if ( ! arr) {
                    arr = std::vector<obj>();
                }
                arr->push_back(c);
            } else {
                if (arr) {
                    if (arr->size() == 1) addS(arr->at(0));
                    //TODO: URGENT: not implemented
                    // else addS(VarArr.of(arr));
                    update(false);
                    arr = std::nullopt;
                }
                addS(c);
                update(false);
            }
        }

        if (arr) {
            if (arr->size() == 1) {
                addS(arr->front());
            } else {
                //TODO: URGENT: not implemented
                // addS(VarArr.of(*arr));
            }
        }

        update(true);

        // Main.printlvl--;

        // if (Main.debug) printlvl("END:", llToString());

        if (llSize != 1) {
            if (llSize == 0) return std::nullopt;
            // if (pollS().token != null) Main.faulty = pollS().token;
            // try to figure out what went wrong


            for (Node* cn = LN->l; cn != FN; cn = cn->l) {
                obj obj_ = cn->val;

                // if (obj_ instanceof Variable) {
                if (std::holds_alternative<variable>(obj_)) {
                    auto v = std::get<variable>(obj_);
                    // if (v.getOrThis() == v) throw new SyntaxError("Couldn't find the value of " + obj_.name, obj_);
                    if ( ! v.hasValue()) throw "Couldn't find the value of ";
                }

                //TODO: not implemented
                // // } else if (obj_ instanceof Settable) {
                // } else if (std::holds_alternative<settable>(obj_)) {
                //     // Settable settable = (Settable) obj_;
                //     if (settable.getOrThis() == obj_) throw new SyntaxError("Couldn't find the value of " + obj_, obj_);
                // }
            }

            // oh well that failed
            // throw new SyntaxError("Failed to parse expression", pollL());
            throw "Failed to parse expression";
        }
        return pollS();
    }

private:
    struct Node {
        Node* l;
        Node* r;
        char type_;
        obj val;

        Node() { }

        Node(obj val, Node* l, Node* r)
            : l(l), r(r), val(val), type_(chr(type(val)))
        {}

        obj remove() {
            l->r = r;
            r->l = l;
            return val;
        }

        std::string to_string() {
          // return hashCode()+"{"+l.hashCode()+"; "+r.hashCode()+"}\n";
        //   return val==null? "null" : val.toString();
            return ::to_string(val);
        }
    };


    int llSize;
    Node* FN;
    Node* LN;
    Node* barNode;


    // void printlvl(Object... args) {
    //     if (!Main.debug) return;
    //     Main.printdbg(sc, Main.repeat("  ", Main.printlvl), args);
    // }

    void update(bool end) {
        if (llSize == 1 && ! pollS()) return;
        while (llSize != 1) {
            // if (Main.debug) printlvl(llToString());

            // if (is("D!|NFN", end, false)) {
            //     // if (Main.debug) printlvl("NFN");
            //     auto w = lastVal();
            //     auto f = lastFun();
            //     auto a = lastVal();
            //     // Main.faulty = f;
            //     auto res = f.callObj(a, w);
            //     if (res == null && (left.size() > 0 || llSize > 0)) throw new SyntaxError("trying to use result of function which returned nothing", a);
            //     if (res != null) addE(res);
            //     else return;
            //     continue;
            // }

            // if (llSize >= 2 && FN->r->r->type == '@') {
            //     if (is("F@", end, true)) {
            //         // if (Main.debug) printlvl("F[]");
            //         auto f = (fun) firstObj();
            //         auto w = (Brackets) popS();
            //         addS(new DervDimFn(f, w.toInts(), sc));
            //         continue;
            //     }
            //     if (is("M@", end, true)) {
            //         // if (Main.debug) printlvl("M[]");
            //         auto f = firstMop();
            //         auto w = (Brackets) popS();
            //         addS(new DervDimMop(f, w.toInt(), sc));
            //         continue;
            //     }
            //     if (is("D@", end, true)) {
            //         // if (Main.debug) printlvl("D[]");
            //         auto f = firstDop();
            //         auto w = (Brackets) popS();
            //         addS(new DervDimDop(f, w.toInt(), sc));
            //         continue;
            //     }
            //     if (is("v@", end, true)) {
            //         // if (Main.debug) printlvl("v[]");
            //         auto f = firstVar();
            //         auto w = (Brackets) popS();
            //         addS(new Pick((Variable) f, w, sc));
            //         continue;
            //     }
            //     if (is("N@", end, true)) {
            //         // if (Main.debug) printlvl("n[]");
            //         auto a = firstVal();
            //         auto w = (Brackets) popS();
            //         addS(RShoeUBBuiltin.on(w.val, a, sc.IO, w));
            //         continue;
            //     }
            // }

            // if (is("[FM←]|FN", end, false)) {
            //     // if (Main.debug) printlvl("FN");
            //     auto w = lastVal();
            //     auto f = lastFun();
            //     // Main.faulty = f;
            //     auto res = f.callObj(w);
            //     if (res == null && (left.size() > 0 || llSize > 0)) throw new SyntaxError("trying to use result of function which returned nothing", f);
            //     if (res != null) addE(res);
            //     else return;
            //     continue;
            // }

            // if (is("#!←", end, true) || llSize == 1 && pollS().type() == Type::gettable) {
            //     auto w = firstVar();
            //     addFirst(w.get());
            // }

            // if (llSize > 2 && LN->l->l->type == '←') {

            //     if (is(new std::vector<std::string>{"D!|V←[#NFMD]","#←[#NFMDV]","D!|D←D","D!|M←M","D!|F←F","D!|N←N"}, end, false)) { // "D!|.←." to allow changing type
            //         // if (Main.debug) printlvl("N←.");
            //         auto w = lastObj();
            //         auto s = (AbstractSet) popE(); // ←
            //         auto a = popE(); // variable
            //         // Main.faulty = s;
            //         auto res = s.callObj(a, w, false);
            //         addE(res);
            //         continue;
            //     }

            //     if (is("D!|NF←N", end, false, 5)) {
            //         // if (Main.debug) printlvl("NF←.");
            //         auto w = lastVal();
            //         auto s0 = popE(); // ←
            //         if (s0 instanceof DerivedSet) throw new SyntaxError("cannot derive an already derived ←");
            //         auto s = (SetBuiltin) s0;
            //         auto f = lastFun();
            //         obj a = popE(); // variable
            //         // Main.faulty = f;
            //         obj res = s.callObj(f, a, w);
            //         if (res != null) addE(res);
            //         continue;
            //     }
            // }

            // if (llSize == 2 && is("F←", false, false)) {
            //     // if (Main.debug) printlvl("F←");
            //     auto s0 = popE(); // ←
            //     if (s0 instanceof DerivedSet) throw new SyntaxError("cannot derive an already derived ←");
            //     auto s = (SetBuiltin) s0;
            //     auto f = lastFun();
            //     addE(new DerivedSet(s, f));
            //     continue;
            // }

            // -----------------------------------------------------------------------------------------------
            if (is("!D|[FN]M", end, true)) {
                // if (Main.debug) printlvl("FM");
                auto f = firstObj();
                auto o = firstMop();
                addFirst(derive(o, f));
                continue;
            }

            // if (is("!D|[FNV]D[FNV]", end, true)) {
            //     // if (Main.debug) printlvl("FDF");
            //     auto aa = popB(); // done.removeFirst();
            //     auto  o = firstDop(); // (dop) done.removeFirst();
            //     auto ww = popB();
            //     auto aau = aa;
            //     auto wwu = ww;
            //     if (aau instanceof Settable) aau = ((Settable) aau).getOrThis();
            //     if (wwu instanceof Settable) wwu = ((Settable) wwu).getOrThis();
            //     if (aau instanceof VarArr) aau = ((VarArr) aau).get();
            //     if (wwu instanceof VarArr) wwu = ((VarArr) wwu).get();
            //     if (o instanceof DotBuiltin && aau instanceof APLMap && ww instanceof Variable) {
            //       addB(((APLMap) aau).get(Main.toAPL(((Variable) ww).name)));
            //     } else {
            //       addB(o.derive(aau, wwu));
            //     }
            //     continue;
            // }

            // -----------------------------------------------------------------------------------------------
            if (is("D!|[FN]FF", end, false)) {
                // if (Main.debug) printlvl("f g h");
                auto h = lastFun();
                auto g = lastFun();
                auto f = lastObj();
                addE(fork(f, g, h));
                continue;
            }

            // if (is("D!|NF", false, false)) {
            //     // if (Main.debug) printlvl("A f");
            //     auto f = lastFun();
            //     auto a = lastObj();
            //     addE(new Atop(a, f));
            //     continue;
            // }

            // if (is("←FF", false, false)) {
            //     // if (Main.debug) printlvl("g h");
            //     auto h = lastFun();
            //     auto g = lastObj();
            //     addE(new Atop(g, h));
            //     continue;
            // }

            // if (llSize >= 3 && pollS() instanceof JotBuiltin && FN->r->r->val instanceof DotBuiltin) {
            //     // if (Main.debug) printlvl("∘.");
            //     auto jot = popS();
            //     popS();
            //     auto fn = popS();
            //     if (fn instanceof Settable) fn = ((Settable) fn).get();
            //     if (fn instanceof VarArr) fn = ((VarArr) fn).get();
            //     auto TB = new TableBuiltin();
            //     TB.token = jot.token;
            //     addS(TB.derive(fn));
            //     continue;
            // }

            break;
        }

        if (end && llSize == 2) {
            // if (Main.debug) printlvl("g h");
            auto h = lastFun();
            auto g = lastObj();
            // if (g instanceof fun || g instanceof value) addE(new Atop(g, h));
            // else throw new SyntaxError("creating an atop with "+g.humanType(true), g);

            if (is_fun(g)) {
                addE(atop(g, h));
            } else {
                throw "creating an atop with ";
            }
        }
    }

    //TODO: not implemented yet
    // value lastVal() {
    //     auto r = popE();
    //     if (r instanceof Settable) r = ((Settable) r).get();
    //     if (r instanceof value) return (value) r;
    //     if (r instanceof VarArr) return ((VarArr) r).get();
    //     throw new SyntaxError("Expected value, got "+r, r);
    // }

    // fun lastFun() {
    obj lastFun() {
        auto r = popE();
        // if (r instanceof Settable) r = ((Settable) r).get();
        // if (r instanceof fun) return (fun) r;
        // throw new SyntaxError("Expected function, got "+r, r);

        //TODO:
        // if (r instanceof Settable) r = ((Settable) r).get();
        if (is_fun(r)) {
            return r;
        }
        throw "Expected function, got ...";
    }

    //TODO: not implemented yet
    // value firstVal() {
    //     auto r = popB();
    //     if (r instanceof Settable) r = ((Settable) r).get();
    //     if (r instanceof value) return (value) r;
    //     if (r instanceof VarArr) return ((VarArr) r).get();
    //     throw new SyntaxError("Expected value, got "+r, r);
    // }


    // dop firstDop() {
    obj firstDop() {
        auto r = popB();
        // if (r instanceof Settable) r = ((Settable) r).get();
        // if (r instanceof dop) return (dop) r;
        // throw new SyntaxError("Expected dop, got "+r, r);

        // if (r instanceof Settable) r = ((Settable) r).get();
        if (is_dop(r)) {
            return r;
        }
        throw "Expected dop, got ...";
    }

    obj lastObj() {
        auto r = popE();
        // if (r instanceof Settable) r = ((Settable) r).get();
        // if (r instanceof VarArr) return ((VarArr) r).get();
        return r;
    }

    obj firstObj() {
        auto r = popB();
        // if (r instanceof VarArr) return ((VarArr) r).get();
        // if (r instanceof Settable) return ((Settable) r).get();
        return r;
    }

    //TODO: implement
    // Settable firstVar() {
    //     auto r = popB();
    //     if (r instanceof Settable) return (Settable) r;
    //     throw new SyntaxError("Expected a variable, got "+r, r);
    // }

    // mop firstMop() {
    obj firstMop() {
        auto r = popB();
        // if (r instanceof Settable) r = ((Settable) r).get();
        // if (r instanceof mop) return (mop) r;
        // throw new SyntaxError("Expected mop, got "+r, r);

        // if (r instanceof Settable) r = ((Settable) r).get();
        if (is_mop(r)) {
            return r;
        }
        throw "Expected mop, got ...";
    }

    void addFirst(obj o) {
        addB(o);
    }

    obj popS() {
        llSize--;
        Node* c = FN->r;
        Node* r = c->r;
        obj res = c->val;
        FN->r = c->r;
        r->l = FN;
        return res;
    }

    obj popE() {
        llSize--;
        Node* c = LN->l;
        Node* l = c->l;
        obj r = c->val;
        LN->l = c->l;
        l->r = LN;
        return r;
    }

    obj popB() {
        llSize--;
        obj r = barNode->remove();
        barNode = barNode->r;
        return r;
    }

    void addS(obj o) {
        llSize++;
        Node* r = FN->r;
        Node* l = FN->r->l;
        // assert l == FN;
        Node* n = new Node(o, l, r);
        l->r = n;
        r->l = n;
    }

    void addE(obj o) {
        llSize++;
        Node* l = LN->l;
        Node* r = LN->l->r;
        // assert r == LN : llToString();
        Node* n = new Node(o, l, r);
        l->r = n;
        r->l = n;
    }

    void addB(obj o) {
        llSize++;
        Node* l = barNode->l;
        Node* r = barNode;
        Node* n = new Node(o, l, r);
        l->r = n;
        r->l = n;
        barNode = n;
    }

    std::optional<obj> pollS() {
        return FN->r->val;
    }

    obj pollL() {
        return LN->l->val;
    }

    void reset() {
        FN = new Node();
        LN = new Node();
        FN->r = LN;
        LN->l = FN;
        FN->l = nullptr;
        LN->r = nullptr;
    }

    std::string llToString() {
        std::string r = "[";
        Node* c = FN->r;
        bool first = true;
        while (c != LN) {
          if (first) first = false;
          else r += ", ";
          r += c->to_string();
          c = c->r;
        }
        r += "]";
        return r;
    }

    bool is(std::vector<std::string> pts, bool everythingDone, bool fromStart) {
        for (std::string pt : pts) if (is(pt, everythingDone, fromStart)) return true;
        return false;
    }

    bool is(std::string pt, bool everythingDone, bool fromStart) {
        return is(pt, everythingDone, fromStart, 4);
    }

    bool is(std::string pt, bool everythingDone, bool fromStart, int am) {
        if(!fromStart && llSize > am) return false;
        if (everythingDone && is(pt, false, fromStart)) return true;
        if (fromStart && everythingDone) {
            for (int i = 0; i < pt.length(); i++) {
                if (pt[i] == '|') {
                    return is(pt.substr(i+1), false, true);
                }
            }
        }

        int len = pt.length();
        int ptrinc = fromStart ? 1 : -1;
        bool pass = false;
        barNode = FN->r;
        Node* cn = fromStart? FN->r : LN->l;
        for (int i = fromStart ? 0 : len - 1; fromStart ? i<len : i>=0; i += ptrinc) {
            char p = pt[i];
            bool inv = false;
            if (p == '|') {
                pass = everythingDone;
                barNode = cn;
                i += ptrinc;
                p = pt[i];
            }
            if (cn==FN | cn==LN) return pass;
            if (p == '!') {
                inv = true;
                i += ptrinc;
                p = pt[i];
            }
            obj v = cn->val;
            if (p == 'v') {
                if (!(is_settable(v)) ^ inv) return false;
                cn = fromStart? cn->r : cn->l;
                continue;
            }
            if (p == '.') {
                cn = fromStart? cn->r : cn->l;
                continue;
            }

            char type = cn->type_;
            if (p == ']') { // regular guaranteed
                i--;
                bool nf = true;
                while (true) {
                char c = pt[i];
                if (c == '[') break;
                if (c==type) nf = false;
                i--;
                }
                if (nf) return false; // no inv for []s!
            } else if (p == '[') { // reverse guaranteed
                i++;
                bool nf = true;
                while (true) {
                char c = pt[i];
                if (c == ']') break;
                if (c==type) nf = false;
                i++;
                }
                if (nf) return false;
            } else {
                if ((p != type) ^ inv) return false;
            }
            cn = fromStart? cn->r : cn->l;
        }
        return true;
    }

    obj valueOf(token t) {
        obj o = valueOfRaw(t);

        // o.token = t;
        set_token(o, t);

        return o;
    }

    obj valueOfRaw(token t) {
        if (std::holds_alternative<tokens::op>(t)) {
            std::string_view op = std::get<tokens::op>(t).op_;

            // size_t c_size = utf8_char_size(raw.substr(i));
            // if (c_size == 0) {
            //     throw "UTF8 encoding error";
            // }
            // auto c = raw.substr(i, c_size);
            // std::cout << "c: " << c << std::endl;

            // ***
            if (op == "∧") {
                // return new AndBuiltin();
                return and_builtin();
            } else {
                // throw new NYIError("no built-in " + ((OpTok) t).op + " defined in exec", t);
                throw "no built-in defined in exec";
            }




            // switch (t1.op.charAt(0)) {
                // slashes: / - reduce; ⌿ - replicate; \ - reduce (r[3]←(r[2] ← (r[1]←a) f b) f c); ⍀ - extend
                // in Dyalog but not at least partially implemented: ⊆⌹→  &⌶⌺

                // fns
                // else if (op == "+") return new PlusBuiltin();
                // else if (op == "-") return new MinusBuiltin();
                // else if (op == "×") return new MulBuiltin();
                // else if (op == "÷") return new DivBuiltin();
                // else if (op == "*") return new StarBuiltin();
                // else if (op == "⍟") return new LogBuiltin();
                // else if (op == "√") return new RootBuiltin();
                // else if (op == "⌈") return new CeilingBuiltin();
                // else if (op == "⌊") return new FloorBuiltin();
                // else if (op == "|") return new StileBuiltin();


                // else if (op == "∨") return new OrBuiltin();
                // else if (op == "⍲") return new NandBuiltin(sc);
                // else if (op == "⍱") return new NorBuiltin(sc);
                // else if (op == "⊥") return new UTackBuiltin();
                // else if (op == "⊤") return new DTackBuiltin();
                // else if (op == "~") return new TildeBuiltin();
                // else if (op == "○") return new TrigBuiltin();
                // else if (op == "!") return new ExclBuiltin();

                // else if (op == "∊") return new EpsilonBuiltin();
                // else if (op == "⍷") return new FindBuiltin();
                // else if (op == "⊂") return new LShoeBuiltin();
                // else if (op == "⊇") return new RShoeUBBuiltin(sc);

                // ***
                // else if (op == "⊃") return new RShoeBuiltin(sc);

                // else if (op == "∪") return new DShoeBuiltin();
                // else if (op == "∩") return new UShoeBuiltin();
                // else if (op == "⌷") return new SquadBuiltin(sc);
                // else if (op == "⍳") return new IotaBuiltin(sc);
                // else if (op == "⍸") return new IotaUBBuiltin(sc);
                // else if (op == "⍴") return new RhoBuiltin();
                // else if (op == ",") return new CatBuiltin();
                // else if (op == "≢") return new TallyBuiltin();
                // else if (op == "≡") return new DepthBuiltin();

                // ***
                // else if (op == "⊢") return new RTackBuiltin();

                // else if (op == "⊣") return new LTackBuiltin();
                // else if (op == "↑") return new UpArrowBuiltin();
                // else if (op == "↓") return new DownArrowBuiltin();
                // else if (op == "?") return new RandBuiltin(sc);
                // else if (op == "⍪") return new CommaBarBuiltin();
                // else if (op == "⍉") return new TransposeBuiltin();
                // else if (op == "⊖") return new FlipBuiltin();
                // else if (op == "⌽") return new ReverseBuiltin();

                // else if (op == "…") return new EllipsisBuiltin();
                // else if (op == "⍮") return new SemiUBBuiltin();
                // else if (op == "⍕") return new FormatBuiltin();
                // else if (op == "⍎") return new EvalBuiltin(sc);
                // else if (op == "⍋") return new GradeUpBuiltin(sc);
                // else if (op == "⍒") return new GradeDownBuiltin(sc);
                // else if (op == "⌿") return new ReplicateBuiltin();
                // else if (op == "⍀") return new ExpandBuiltin();
                // else if (op == "⍧") return new LShoeStileBuiltin();
                // else if (op == "%") return new MergeBuiltin(sc);

                // comparisons
                // else if (op == "<") return new LTBuiltin();
                // else if (op == "≤") return new LEBuiltin();

                // ***
                // else if (op == "=") return new EQBuiltin();

                // else if (op == "≥") return new GEBuiltin();
                // else if (op == ">") return new GTBuiltin();
                // else if (op == "≠") return new NEBuiltin();

                // mops

                // ***
                // else if (op == "/") return new ReduceBuiltin();

                // else if (op == "\\")return new ScanBuiltin();
                // else if (op == "¨") return new EachBuiltin();
                // else if (op == "⍨") return new SelfieBuiltin();
                // else if (op == "⌾") return new TableBuiltin();
                // else if (op == "⌸") return new KeyBuiltin(sc);
                // else if (op == "⍁") return new ObliqueBuiltin();
                // else if (op == "⍩")
                // else if (op == "ᐵ") return new EachLeft();
                // else if (op == "ᑈ") return new EachRight();

                // dops
                // else if (op == "∘") return new JotBuiltin();
                // else if (op == "⍛") return new JotUBBuiltin();
                // else if (op == ".") return new DotBuiltin();
                // else if (op == "⍣") return new RepeatBuiltin(sc);
                // else if (op == "⍡") return new CRepeatBuiltin(sc);
                // else if (op == "⍤") return new JotDiaeresisBuiltin();
                // else if (op == "⍥") return new OverBuiltin();
                // else if (op == "⍢") return new DualBuiltin();
                // else if (op == "@") return new AtBuiltin(sc);
                // else if (op == "⍫") return new ObverseBuiltin();

                // else if (op == "⍬") return new DoubleArr(DoubleArr.EMPTY);
                // else if (op == "⎕") return new Quad(sc);
                // else if (op == "⍞") return new QuoteQuad(sc);
                // else if (op == "⍺") Obj o = sc.get("⍺"); if(o == null) throw new SyntaxError("No ⍺ found", t); return o;
                // else if (op == "⍵")     o = sc.get("⍵"); if(o == null) throw new SyntaxError("No ⍵ found", t); return o;
                // else if (op == "∇")     o = sc.get("∇"); if(o == null) throw new SyntaxError("No ∇ found", t); return o;
                // else if (op == "⍶")     o = sc.get("⍶"); if(o == null) throw new SyntaxError("No ⍶ found", t); return o;
                // else if (op == "⍹")     o = sc.get("⍹"); if(o == null) throw new SyntaxError("No ⍹ found", t); return o;
            // }
        }
        throw "Unknown type: ...";

        //TODO: not implemented yet
        // if (t instanceof NumTok) return ((NumTok) t).num;
        // if (t instanceof ChrTok) return ((ChrTok) t).val;
        // if (t instanceof StrTok) return ((StrTok) t).val;
        // if (t instanceof SetTok) return SetBuiltin.inst;
        // if (t instanceof NameTok) return sc.getVar(((NameTok) t).name);
        // if (t instanceof tokens::line) return Main.rexec((tokens::line) t, sc);
        // if (t instanceof ParenTok) {
        //   List<tokens::line> ts = ((ParenTok) t).tokens;
        //   int size = ts.size();
        //   if (size == 0) return new StrMap();
        //   tokens::line fst = ts.get(0);
        //   if (size==1 && fst.colonPos()==-1) {
        //     if (((ParenTok) t).hasDmd) return new Shape1Arr(Main.vexec(ts.get(0), sc));
        //     return Main.rexec(ts.get(0), sc);
        //   }
        //   if (fst.tokens != null && fst.colonPos() != -1) { // map constants
        //     Scope nsc = new Scope(sc);
        //     StrMap res = new StrMap(nsc);
        //     for (tokens::line ct : ts) {
        //       Token name = ct.tokens.get(0);
        //       if (ct.colonPos() ==-1) throw new SyntaxError("expected a colon in expression", ct.tokens.get(0));
        //       if (ct.colonPos() != 1) throw new SyntaxError("expected : to be the 2nd token in parenthesis", ct.tokens.get(ct.colonPos()));
        //       std::string key;
        //       if (name instanceof NameTok) key = ((NameTok) name).name;
        //       else if (name instanceof StrTok) key = ((StrTok) name).parsed;
        //       else if (name instanceof ChrTok) key = ((ChrTok) name).parsed;
        //       else throw new SyntaxError("expected a key name, got " + name.toRepr(), name);
        //       List<Token> tokens = ct.tokens.subList(2, ct.tokens.size());

        //       Obj val = Main.exec(tokens::line.inherit(tokens), nsc);
        //       res.setStr(key, val);
        //     }
        //     return res;
        //   } else { // array
        //     Obj fo = Main.exec(fst, sc);
        //     if (fo instanceof value) { // value array
        //       value[] vs = new value[size];
        //       for (int i = 0; i < ts.size(); i++) {
        //         Obj o = i==0? fo : Main.exec(ts.get(i), sc);
        //         if (!(o instanceof value)) throw new DomainError("⋄-array contained " + o.humanType(true), o);
        //         vs[i] = (value) o;
        //       }
        //       return Arr.create(vs);
        //     } else if (fo instanceof fun) { // function array
        //       Obj[] os = new Obj[size];
        //       for (int i = 0; i < ts.size(); i++) {
        //         Obj o = i==0? fo : Main.exec(ts.get(i), sc);
        //         if (!(o instanceof fun)) throw new DomainError("function array contained " + o.humanType(true), o);
        //         os[i] = o;
        //       }
        //       return new FunArr(os);
        //     } else throw new DomainError("⋄-array contained " + fo.humanType(true), fo);
        //   }
        // }
        // if (t instanceof DfnTok) return UserDefined.of((DfnTok) t, sc);
        // if (t instanceof BracketTok) return Brackets.of((BracketTok) t, sc);
        // if (t instanceof BacktickTok) return new ArrFun((BacktickTok) t, sc);
        // if (t instanceof BigTok) return ((BigTok) t).val;
        // if (t instanceof ScopeTok) return new StrMap(sc);
        // throw new NYIError("Unknown type: " + t.toRepr(), t);
    }

};


// // package APL;

// // import APL.errors.*;
// // import APL.tokenizer.Token;
// // import APL.tokenizer.types.*;
// // import APL.types.*;
// // import APL.types.arrs.*;
// // import APL.types.dimensions.*;
// // import APL.types.functions.*;
// // import APL.types.functions.builtins.AbstractSet;
// // import APL.types.functions.builtins.*;
// // import APL.types.functions.builtins.dops.*;
// // import APL.types.functions.builtins.fns.*;
// // import APL.types.functions.builtins.mops.*;
// // import APL.types.functions.trains.*;
// // import APL.types.functions.userDefined.UserDefined;

// // import java.util.*;


// struct Exec {
//     Exec(tokens::line ln) //, Scope sc)
//         : tokens(ln.tokens)
//         , allToken(ln)
//         // , sc(sc)
//     {}

//     Obj exec() {
//       if (tokens.size() > 0) Main.faulty = tokens.get(0);
//       else Main.faulty = allToken;

//       if (sc.alphaDefined && tokens.size() >= 2 && tokens.get(0) instanceof OpTok && ((OpTok) tokens.get(0)).op.equals("⍺") && tokens.get(1) instanceof SetTok) {
//         if (Main.debug) printlvl("skipping cuz it's ⍺←");
//         return null;
//       }
//       left = new Stack<>();
//       left.addAll(tokens);
//       if (Main.debug) {
//         StringBuilder repr = new StringBuilder();
//         for (Token t : tokens) repr.append(t.toRepr()).append(" ");
//         printlvl("NEW:");
//         Main.printlvl++;
//         printlvl("code:", repr);
//         printlvl();
//       }
//       reset();
//       ArrayList<Obj> arr = null;
//       while (left.size() > 0) {
//         Token t = left.pop();
//         Obj c;
//         if (t instanceof NameTok && left.size() >= 2
//           && left.peek() instanceof OpTok
//           && ((OpTok) left.peek()).op.equals(".")
//           && left.at(left.size() - 2) instanceof NameTok) {
//           int ptr = left.size() - 2;
//           while (ptr >= 2) {
//             if (left.at(ptr - 1) instanceof OpTok
//               && ((OpTok) left.at(ptr - 1)).op.equals(".")
//               && left.at(ptr - 2) instanceof NameTok) ptr -= 2;
//             else break;
//           }
//           std::vector<std::string> names = new std::string[(left.size() - ptr >> 1) + 1];
//           names[names.length - 1] = ((NameTok) t).name;
//           for (int i = names.length - 2; i >= 0; i--) {
//             OpTok dot = (OpTok) left.pop();
//             assert dot.op.equals(".");
//             NameTok name = (NameTok) left.pop();
//             names[i] = name.name;
//           }

//           if (Main.debug) printlvl("dotnot", Arrays.toString(names)); // todo fix (m).a (m).b0
//           Obj d = null;
//           Settable r = sc.getVar(names[0]);
//           for (int i = 1; i < names.length; i++) {
//             if (r == null) {
//               r = sc.getVar(names[i]);
//               if (Main.debug) printlvl(":start", d, r, names[i]);
//             } else {
//               auto got = r->getOrThis();
//               if (got instanceof fun) {
//                 if (Main.debug) printlvl(":fn", d, r, names[i]);
//                 if (d == null) d = got;
//                 else d = new DotBuiltin().derive(d, got);
//                 r = sc.getVar(names[i]);
//               } else if (got instanceof APLMap) {
//                 if (Main.debug) printlvl(":map", d, r, names[i]);
//                 r = ((APLMap) got).get(names[i]);
//               } else throw new SyntaxError("dot-chain contained non-fn/map");
//             }
//           }
//           if (r != null) {
//             if (d == null) d = r;
//             else d = new DotBuiltin().derive(d, r->get());
//           } else if (d == null) throw new SyntaxError("what?");
//           c = d;
//           if (Main.debug) printlvl(llToString());

//         } else {
//           c = valueOf(t);
//         }
//         if (c.isObj() || c.type() == Type::gettable && (left.size() == 0 || !(left.at(0) instanceof SetTok))) {
//           if (arr == null) arr = new ArrayList<>();
//           arr.add(c);
//         } else {
//           if (arr != null) {
//             if (arr.size() == 1) addS(arr.get(0));
//             else addS(VarArr.of(arr));
//             update(false);
//             arr = null;
//           }
//           addS(c);
//           update(false);
//         }
//       }
//       if (arr != null) {
//         if (arr.size() == 1) addS(arr.get(0));
//         else addS(VarArr.of(arr));
//       }
//       update(true);


//       Main.printlvl--;
//       if (Main.debug) printlvl("END:", llToString());
//       if (llSize != 1) {
//         if (llSize == 0) return null;
//         if (pollS().token != null) Main.faulty = pollS().token;
//         // try to figure out what went wrong


//         for (Node* cn = LN->l; cn != FN; cn = cn.l) {
//           Obj obj = cn.val;
//           if (obj instanceof Variable) {
//             Variable vobj = (Variable) obj;
//             if (vobj.getOrThis() == obj) throw new SyntaxError("Couldn't find the value of " + vobj.name, obj);
//           } else if (obj instanceof Settable) {
//             Settable settable = (Settable) obj;
//             if (settable.getOrThis() == obj) throw new SyntaxError("Couldn't find the value of " + obj, obj);
//           }
//         }

//         // oh well that failed
//         throw new SyntaxError("Failed to parse expression", pollL());
//       }
//       return pollS();
//     }

// private:
//     static class Node {
//       Node l, r;
//       char type;
//       Obj val;
//       Node() { }
//       Node(Obj val, Node l, Node r) {
//         this.l = l;
//         this.r = r;
//         this.val = val;
//         type = val.type().chr;
//       }
//       Obj remove() {
//         l.r = r;
//         r->l = l;
//         return val;
//       }
//       public std::string toString() {
//         // return hashCode()+"{"+l.hashCode()+"; "+r->hashCode()+"}\n";
//         return val==null? "null" : val.toString();
//       }
//     }

//     void printlvl(Object... args) {
//       if (!Main.debug) return;
//       Main.printdbg(sc, Main.repeat("  ", Main.printlvl), args);
//     }

//     void update(bool end) {
//       if (llSize == 1 && pollS() == null) return;
//       while (llSize != 1) {
//         if (Main.debug) printlvl(llToString());
//         if (is("D!|NFN", end, false)) {
//           if (Main.debug) printlvl("NFN");
//           var w = lastVal();
//           var f = lastFun();
//           var a = lastVal();
//           Main.faulty = f;
//           var res = f.callObj(a, w);
//           if (res == null && (left.size() > 0 || llSize > 0)) throw new SyntaxError("trying to use result of function which returned nothing", a);
//           if (res != null) addE(res);
//           else return;
//           continue;
//         }
//         if (llSize >= 2 && FN->r->r->type == '@') {
//           if (is("F@", end, true)) {
//             if (Main.debug) printlvl("F[]");
//             var f = (fun) firstObj();
//             var w = (Brackets) popS();
//             addS(new DervDimFn(f, w.toInts(), sc));
//             continue;
//           }
//           if (is("M@", end, true)) {
//             if (Main.debug) printlvl("M[]");
//             var f = firstMop();
//             var w = (Brackets) popS();
//             addS(new DervDimMop(f, w.toInt(), sc));
//             continue;
//           }
//           if (is("D@", end, true)) {
//             if (Main.debug) printlvl("D[]");
//             var f = firstDop();
//             var w = (Brackets) popS();
//             addS(new DervDimDop(f, w.toInt(), sc));
//             continue;
//           }
//           if (is("v@", end, true)) {
//             if (Main.debug) printlvl("v[]");
//             var f = firstVar();
//             var w = (Brackets) popS();
//             addS(new Pick((Variable) f, w, sc));
//             continue;
//           }
//           if (is("N@", end, true)) {
//             if (Main.debug) printlvl("n[]");
//             var a = firstVal();
//             var w = (Brackets) popS();
//             addS(RShoeUBBuiltin.on(w.val, a, sc.IO, w));
//             continue;
//           }
//         }
//         if (is("[FM←]|FN", end, false)) {
//           if (Main.debug) printlvl("FN");
//           var w = lastVal();
//           var f = lastFun();
//           Main.faulty = f;
//           var res = f.callObj(w);
//           if (res == null && (left.size() > 0 || llSize > 0)) throw new SyntaxError("trying to use result of function which returned nothing", f);
//           if (res != null) addE(res);
//           else return;
//           continue;
//         }
//         if (is("#!←", end, true) || llSize == 1 && pollS().type() == Type::gettable) {
//           var w = firstVar();
//           addFirst(w.get());
//         }

//         if (llSize>2 && LN->l.l.type=='←') {
//           if (is(new std::vector<std::string>{"D!|V←[#NFMD]","#←[#NFMDV]","D!|D←D","D!|M←M","D!|F←F","D!|N←N"}, end, false)) { // "D!|.←." to allow changing type
//             if (Main.debug) printlvl("N←.");
//             var w = lastObj();
//             var s = (AbstractSet) popE(); // ←
//             var a = popE(); // variable
//             Main.faulty = s;
//             var res = s.callObj(a, w, false);
//             addE(res);
//             continue;
//           }
//           if (is("D!|NF←N", end, false, 5)) {
//             if (Main.debug) printlvl("NF←.");
//             var w = lastVal();
//             var s0 = popE(); // ←
//             if (s0 instanceof DerivedSet) throw new SyntaxError("cannot derive an already derived ←");
//             var s = (SetBuiltin) s0;
//             var f = lastFun();
//             Obj a = popE(); // variable
//             Main.faulty = f;
//             Obj res = s.callObj(f, a, w);
//             if (res != null) addE(res);
//             continue;
//           }
//         }

//         if (llSize == 2 && is("F←", false, false)) {
//           if (Main.debug) printlvl("F←");
//           var s0 = popE(); // ←
//           if (s0 instanceof DerivedSet) throw new SyntaxError("cannot derive an already derived ←");
//           var s = (SetBuiltin) s0;
//           var f = lastFun();
//           addE(new DerivedSet(s, f));
//           continue;
//         }

//         if (is("!D|[FN]M", end, true)) {
//           if (Main.debug) printlvl("FM");
//           var f = firstObj();
//           var o = firstMop();
//           addFirst(o.derive(f));
//           continue;
//         }
//         if (is("!D|[FNV]D[FNV]", end, true)) {
//           if (Main.debug) printlvl("FDF");
//           var aa = popB(); // done.removeFirst();
//           var  o = firstDop(); // (dop) done.removeFirst();
//           var ww = popB();
//           var aau = aa;
//           var wwu = ww;
//           if (aau instanceof Settable) aau = ((Settable) aau).getOrThis();
//           if (wwu instanceof Settable) wwu = ((Settable) wwu).getOrThis();
//           if (aau instanceof VarArr) aau = ((VarArr) aau).get();
//           if (wwu instanceof VarArr) wwu = ((VarArr) wwu).get();
//           if (o instanceof DotBuiltin && aau instanceof APLMap && ww instanceof Variable) {
//             addB(((APLMap) aau).get(Main.toAPL(((Variable) ww).name)));
//           } else {
//             addB(o.derive(aau, wwu));
//           }
//           continue;
//         }
//         if (is("D!|[FN]FF", end, false)) {
//           if (Main.debug) printlvl("f g h");
//           var h = lastFun();
//           var g = lastFun();
//           var f = lastObj();
//           addE(new Fork(f, g, h));
//           continue;
//         }
//         if (is("D!|NF", false, false)) {
//           if (Main.debug) printlvl("A f");
//           var f = lastFun();
//           var a = lastObj();
//           addE(new Atop(a, f));
//           continue;
//         }
//         if (is("←FF", false, false)) {
//           if (Main.debug) printlvl("g h");
//           var h = lastFun();
//           var g = lastObj();
//           addE(new Atop(g, h));
//           continue;
//         }
//         if (llSize >= 3 && pollS() instanceof JotBuiltin && FN->r.r.val instanceof DotBuiltin) {
//           if (Main.debug) printlvl("∘.");
//           var jot = popS();
//           popS();
//           var fn = popS();
//           if (fn instanceof Settable) fn = ((Settable) fn).get();
//           if (fn instanceof VarArr) fn = ((VarArr) fn).get();
//           var TB = new TableBuiltin();
//           TB.token = jot.token;
//           addS(TB.derive(fn));
//           continue;
//         }
//         break;
//       }
//       if (end && llSize == 2) {
//         if (Main.debug) printlvl("g h");
//         var h = lastFun();
//         var g = lastObj();
//         if (g instanceof fun || g instanceof value) addE(new Atop(g, h));
//         else throw new SyntaxError("creating an atop with "+g.humanType(true), g);
//       }
//     }

//     value lastVal() {
//         var r = popE();
//         if (r instanceof Settable) r = ((Settable) r).get();
//         if (r instanceof value) return (value) r;
//         if (r instanceof VarArr) return ((VarArr) r).get();
//         throw new SyntaxError("Expected value, got "+r, r);
//     }

//     fun lastFun() {
//         var r = popE();
//         if (r instanceof Settable) r = ((Settable) r).get();
//         if (r instanceof fun) return (fun) r;
//         throw new SyntaxError("Expected function, got "+r, r);
//     }

//     value firstVal() {
//         var r = popB();
//         if (r instanceof Settable) r = ((Settable) r).get();
//         if (r instanceof value) return (value) r;
//         if (r instanceof VarArr) return ((VarArr) r).get();
//         throw new SyntaxError("Expected value, got "+r, r);
//     }

//     dop firstDop() {
//         var r = popB();
//         if (r instanceof Settable) r = ((Settable) r).get();
//         if (r instanceof dop) return (dop) r;
//         throw new SyntaxError("Expected dop, got "+r, r);
//     }

//     Obj lastObj() {
//         var r = popE();
//         if (r instanceof Settable) r = ((Settable) r).get();
//         if (r instanceof VarArr) return ((VarArr) r).get();
//         return r;
//     }

//     Obj firstObj() {
//         var r = popB();
//         if (r instanceof VarArr) return ((VarArr) r).get();
//         if (r instanceof Settable) return ((Settable) r).get();
//         return r;
//     }

//     Settable firstVar() {
//         var r = popB();
//         if (r instanceof Settable) return (Settable) r;
//         throw new SyntaxError("Expected a variable, got "+r, r);
//     }

//     mop firstMop() {
//       var r = popB();
//       if (r instanceof Settable) r = ((Settable) r).get();
//       if (r instanceof mop) return (mop) r;
//       throw new SyntaxError("Expected mop, got "+r, r);
//     }

//     void addFirst(Obj o) {
//       addB(o);
//     }

//     Obj popS() {
//       llSize--;
//       Node c = FN->r;
//       Node r = c.r;
//       Obj res = c.val;
//       FN->r = c.r;
//       r.l = FN;
//       return res;
//     }

//     Obj popE() {
//       llSize--;
//       Node c = LN->l;
//       Node l = c.l;
//       Obj r = c.val;
//       LN->l = c.l;
//       l.r = LN;
//       return r;
//     }

//     Obj popB() {
//       llSize--;
//       Obj r = barNode.remove();
//       barNode = barNode.r;
//       return r;
//     }

//     void addS(Obj o) {
//         llSize++;
//         Node r = FN->r;
//         Node l = FN->r.l;
//         assert l == FN;
//         Node n = new Node(o, l, r);
//         l.r = n;
//         r.l = n;
//     }

//     void addE(Obj o) {
//         llSize++;
//         Node l = LN->l;
//         Node r = LN->l.r;
//         assert r == LN : llToString();
//         Node n = new Node(o, l, r);
//         l.r = n;
//         r.l = n;
//     }

//     void addB(Obj o) {
//         llSize++;
//         Node l = barNode.l;
//         Node r = barNode;
//         Node n = new Node(o, l, r);
//         l.r = n;
//         r.l = n;
//         barNode = n;
//     }

//     Obj pollS() {
//         return FN->r.val;
//     }

//     Obj pollL() {
//         return LN->l.val;
//     }

//     void reset() {
//       FN = new Node();
//       LN = new Node();
//       FN->r = LN;
//       LN->l = FN;
//       FN->l = LN->r = null;
//     }

//     std::string llToString() {
//       StringBuilder r = new StringBuilder("[");
//       Node c = FN->r;
//       bool first = true;
//       while (c != LN) {
//         if (first) first = false;
//         else r.append(", ");
//         r.append(c);
//         c = c.r;
//       }
//       return r.append("]").toString();
//     }

//     bool is(std::vector<std::string> pts, bool everythingDone, bool fromStart) {
//       for (std::string pt : pts) if (is(pt, everythingDone, fromStart)) return true;
//       return false;
//     }

//     bool is(std::string pt, bool everythingDone, bool fromStart) {
//       return is(pt, everythingDone, fromStart, 4);
//     }

//     bool is(std::string pt, bool everythingDone, bool fromStart, int am) {
//       if(!fromStart && llSize > am) return false;
//       if (everythingDone && is(pt, false, fromStart)) return true;
//       if (fromStart && everythingDone) {
//         for (int i = 0; i < pt.length(); i++) {
//           if (pt.charAt(i) == '|') return is(pt.substring(i+1), false, true);
//         }
//       }
//       int len = pt.length();
//       int ptrinc = fromStart ? 1 : -1;
//       bool pass = false;
//       barNode = FN->r;
//       Node cn = fromStart? FN->r : LN->l;
//       for (int i = fromStart ? 0 : len - 1; fromStart ? i<len : i>=0; i += ptrinc) {
//         char p = pt.charAt(i);
//         bool inv = false;
//         if (p == '|') {
//           pass = everythingDone;
//           barNode = cn;
//           i += ptrinc;
//           p = pt.charAt(i);
//         }
//         if (cn==FN | cn==LN) return pass;
//         if (p == '!') {
//           inv = true;
//           i += ptrinc;
//           p = pt.charAt(i);
//         }
//         Obj v = cn.val;
//         if (p == 'v') {
//           if (!(v instanceof Settable) ^ inv) return false;
//           cn = fromStart? cn.r : cn.l;
//           continue;
//         }
//         if (p == '.') {
//           cn = fromStart? cn.r : cn.l;
//           continue;
//         }

//         char type = cn.type;
//         if (p == ']') { // regular guaranteed
//           i--;
//           bool nf = true;
//           while (true) {
//             char c = pt.charAt(i);
//             if (c == '[') break;
//             if (c==type) nf = false;
//             i--;
//           }
//           if (nf) return false; // no inv for []s!
//         } else if (p == '[') { // reverse guaranteed
//           i++;
//           bool nf = true;
//           while (true) {
//             char c = pt.charAt(i);
//             if (c == ']') break;
//             if (c==type) nf = false;
//             i++;
//           }
//           if (nf) return false;
//         } else {
//           if (p!=type ^ inv) return false;
//         }
//         cn = fromStart? cn.r : cn.l;
//       }
//       return true;
//     }


//     Obj valueOf(Token t) {
//       Obj o = valueOfRaw(t);
//       o.token = t;
//       return o;
//     }

//     Obj valueOfRaw(Token t) {
//       if (t instanceof OpTok) {
//         OpTok t1 = (OpTok) t;
//         switch (t1.op.charAt(0)) {
//           // slashes: / - reduce; ⌿ - replicate; \ - reduce (r[3]←(r[2] ← (r[1]←a) f b) f c); ⍀ - extend
//           // in Dyalog but not at least partially implemented: ⊆⌹→  &⌶⌺
//           // fns
//           case '+': return new PlusBuiltin();
//           case '-': return new MinusBuiltin();
//           case '×': return new MulBuiltin();
//           case '÷': return new DivBuiltin();
//           case '*': return new StarBuiltin();
//           case '⍟': return new LogBuiltin();
//           case '√': return new RootBuiltin();
//           case '⌈': return new CeilingBuiltin();
//           case '⌊': return new FloorBuiltin();
//           case '|': return new StileBuiltin();
//           case '∧': return new AndBuiltin();
//           case '∨': return new OrBuiltin();
//           case '⍲': return new NandBuiltin(sc);
//           case '⍱': return new NorBuiltin(sc);
//           case '⊥': return new UTackBuiltin();
//           case '⊤': return new DTackBuiltin();
//           case '~': return new TildeBuiltin();
//           case '○': return new TrigBuiltin();
//           case '!': return new ExclBuiltin();

//           case '∊': return new EpsilonBuiltin();
//           case '⍷': return new FindBuiltin();
//           case '⊂': return new LShoeBuiltin();
//           case '⊇': return new RShoeUBBuiltin(sc);
//           case '⊃': return new RShoeBuiltin(sc);
//           case '∪': return new DShoeBuiltin();
//           case '∩': return new UShoeBuiltin();
//           case '⌷': return new SquadBuiltin(sc);
//           case '⍳': return new IotaBuiltin(sc);
//           case '⍸': return new IotaUBBuiltin(sc);
//           case '⍴': return new RhoBuiltin();
//           case ',': return new CatBuiltin();
//           case '≢': return new TallyBuiltin();
//           case '≡': return new DepthBuiltin();
//           case '⊢': return new RTackBuiltin();
//           case '⊣': return new LTackBuiltin();
//           case '↑': return new UpArrowBuiltin();
//           case '↓': return new DownArrowBuiltin();
//           case '?': return new RandBuiltin(sc);
//           case '⍪': return new CommaBarBuiltin();
//           case '⍉': return new TransposeBuiltin();
//           case '⊖': return new FlipBuiltin();
//           case '⌽': return new ReverseBuiltin();

//           case '…': return new EllipsisBuiltin();
//           case '⍮': return new SemiUBBuiltin();
//           case '⍕': return new FormatBuiltin();
//           case '⍎': return new EvalBuiltin(sc);
//           case '⍋': return new GradeUpBuiltin(sc);
//           case '⍒': return new GradeDownBuiltin(sc);
//           case '⌿': return new ReplicateBuiltin();
//           case '⍀': return new ExpandBuiltin();
//           case '⍧': return new LShoeStileBuiltin();
//           case '%': return new MergeBuiltin(sc);

//           // comparisons
//           case '<': return new LTBuiltin();
//           case '≤': return new LEBuiltin();
//           case '=': return new EQBuiltin();
//           case '≥': return new GEBuiltin();
//           case '>': return new GTBuiltin();
//           case '≠': return new NEBuiltin();

//           // mops
//           case '/': return new ReduceBuiltin();
//           case '\\':return new ScanBuiltin();
//           case '¨': return new EachBuiltin();
//           case '⍨': return new SelfieBuiltin();
//           case '⌾': return new TableBuiltin();
//           case '⌸': return new KeyBuiltin(sc);
//           case '⍁': return new ObliqueBuiltin();
//           case '⍩':
//           case 'ᐵ': return new EachLeft();
//           case 'ᑈ': return new EachRight();

//           // dops
//           case '∘': return new JotBuiltin();
//           case '⍛': return new JotUBBuiltin();
//           case '.': return new DotBuiltin();
//           case '⍣': return new RepeatBuiltin(sc);
//           case '⍡': return new CRepeatBuiltin(sc);
//           case '⍤': return new JotDiaeresisBuiltin();
//           case '⍥': return new OverBuiltin();
//           case '⍢': return new DualBuiltin();
//           case '@': return new AtBuiltin(sc);
//           case '⍫': return new ObverseBuiltin();


//           case '⍬': return new DoubleArr(DoubleArr.EMPTY);
//           case '⎕': return new Quad(sc);
//           case '⍞': return new QuoteQuad(sc);
//           case '⍺': Obj o = sc.get("⍺"); if(o == null) throw new SyntaxError("No ⍺ found", t); return o;
//           case '⍵':     o = sc.get("⍵"); if(o == null) throw new SyntaxError("No ⍵ found", t); return o;
//           case '∇':     o = sc.get("∇"); if(o == null) throw new SyntaxError("No ∇ found", t); return o;
//           case '⍶':     o = sc.get("⍶"); if(o == null) throw new SyntaxError("No ⍶ found", t); return o;
//           case '⍹':     o = sc.get("⍹"); if(o == null) throw new SyntaxError("No ⍹ found", t); return o;
//           default: throw new NYIError("no built-in " + ((OpTok) t).op + " defined in exec", t);
//         }
//       }
//       if (t instanceof NumTok) return ((NumTok) t).num;
//       if (t instanceof ChrTok) return ((ChrTok) t).val;
//       if (t instanceof StrTok) return ((StrTok) t).val;
//       if (t instanceof SetTok) return SetBuiltin.inst;
//       if (t instanceof NameTok) return sc.getVar(((NameTok) t).name);
//       if (t instanceof tokens::line) return Main.rexec((tokens::line) t, sc);
//       if (t instanceof ParenTok) {
//         List<tokens::line> ts = ((ParenTok) t).tokens;
//         int size = ts.size();
//         if (size == 0) return new StrMap();
//         tokens::line fst = ts.get(0);
//         if (size==1 && fst.colonPos()==-1) {
//           if (((ParenTok) t).hasDmd) return new Shape1Arr(Main.vexec(ts.get(0), sc));
//           return Main.rexec(ts.get(0), sc);
//         }
//         if (fst.tokens != null && fst.colonPos() != -1) { // map constants
//           Scope nsc = new Scope(sc);
//           StrMap res = new StrMap(nsc);
//           for (tokens::line ct : ts) {
//             Token name = ct.tokens.get(0);
//             if (ct.colonPos() ==-1) throw new SyntaxError("expected a colon in expression", ct.tokens.get(0));
//             if (ct.colonPos() != 1) throw new SyntaxError("expected : to be the 2nd token in parenthesis", ct.tokens.get(ct.colonPos()));
//             std::string key;
//             if (name instanceof NameTok) key = ((NameTok) name).name;
//             else if (name instanceof StrTok) key = ((StrTok) name).parsed;
//             else if (name instanceof ChrTok) key = ((ChrTok) name).parsed;
//             else throw new SyntaxError("expected a key name, got " + name.toRepr(), name);
//             List<Token> tokens = ct.tokens.subList(2, ct.tokens.size());

//             Obj val = Main.exec(tokens::line.inherit(tokens), nsc);
//             res.setStr(key, val);
//           }
//           return res;
//         } else { // array
//           Obj fo = Main.exec(fst, sc);
//           if (fo instanceof value) { // value array
//             value[] vs = new value[size];
//             for (int i = 0; i < ts.size(); i++) {
//               Obj o = i==0? fo : Main.exec(ts.get(i), sc);
//               if (!(o instanceof value)) throw new DomainError("⋄-array contained " + o.humanType(true), o);
//               vs[i] = (value) o;
//             }
//             return Arr.create(vs);
//           } else if (fo instanceof fun) { // function array
//             Obj[] os = new Obj[size];
//             for (int i = 0; i < ts.size(); i++) {
//               Obj o = i==0? fo : Main.exec(ts.get(i), sc);
//               if (!(o instanceof fun)) throw new DomainError("function array contained " + o.humanType(true), o);
//               os[i] = o;
//             }
//             return new FunArr(os);
//           } else throw new DomainError("⋄-array contained " + fo.humanType(true), fo);
//         }
//       }
//       if (t instanceof DfnTok) return UserDefined.of((DfnTok) t, sc);
//       if (t instanceof BracketTok) return Brackets.of((BracketTok) t, sc);
//       if (t instanceof BacktickTok) return new ArrFun((BacktickTok) t, sc);
//       if (t instanceof BigTok) return ((BigTok) t).val;
//       if (t instanceof ScopeTok) return new StrMap(sc);
//       throw new NYIError("Unknown type: " + t.toRepr(), t);
//     }

//     Scope sc;
//     List<Token> tokens;
//     tokens::line allToken;
//     Stack<Token> left;
//     int llSize;
//     Node FN, LN;
//     Node barNode;
// };
