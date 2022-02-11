#include <vector>
#include <iostream>
#include <ranges>
// #include <__ranges/ta>
#include <unordered_map>

#include <apl/tokenizer/tokenizer.hpp>

void printdbg(tokens::basic_lines lines) {
    // std::string p;
    std::cout << lines.to_repr() << std::endl;
    // std::cout << lines.to_tree(p) << std::endl;
    // StringBuilder r = new StringBuilder();
    // if (args.length > 0) r.append(args[0]);
    // for (int i = 1; i < args.length; i++) r.append(" ").append(args[i]);
    // sc.sys.println(r.toString());
}

using Obj = void*;

enum class EType {
    all
};

template <std::ranges::range R>
constexpr
auto to_vector(R&& r) {
    using elem_t = std::decay_t<std::ranges::range_value_t<R>>;
    return std::vector<elem_t>{r.begin(), r.end()};
}

template <std::ranges::range R>
constexpr
auto subList(R&& r, size_t fromIndex, size_t toIndex) {
    using elem_t = std::decay_t<std::ranges::range_value_t<R>>;
    return std::vector<elem_t>{r.begin() + fromIndex, r.begin() + toIndex};
}


Obj exec(tokens::line s) { //, Scope sc) {
    // Obj val = new Exec(s, sc).exec();
    Obj val = Exec(s).exec();
    // if (val instanceof Settable) val = ((Settable) val).get();
    return val;
}

Value vexec(tokens::line s) { //, Scope sc) {
    Obj val = Main.exec(s, sc);
    if (val instanceof Value) return (Value) val;
    throw new SyntaxError("expected array, got " + val.humanType(true), s);
  }


Obj execLines(tokens::array<tokens::line> lines) {          //, Scope sc) {
    Obj res = nullptr;
    std::unordered_map<EType, tokens::line> eGuards;

    try {
        for (auto ln : lines.tokens) {
            // auto tokens = std::views::all(ln.tokens);
            auto tokens = ln.tokens;

            int guardPos = ln.colonPos();
            int eguardPos = ln.eguardPos();

            // if (guardPos != -1 && eguardPos != -1) throw new SyntaxError("both : and :: found in line");
            if (guardPos != -1 && eguardPos != -1) throw "both : and :: found in line";

            // bool endAfter = tokens.size() > 1 && tokens.at(0) instanceof SetTok;
            bool endAfter = tokens.size() > 1 && std::holds_alternative<tokens::set>(tokens.front());

            // if (endAfter) tokens = tokens.subList(1, tokens.size());
            // if (endAfter) tokens = tokens | std::views::drop(2);
            if (endAfter) {
                // tokens = to_vector(std::ranges::drop_view{tokens, 1});
                tokens = subList(tokens, 1, tokens.size());
            } else if (guardPos != -1) {
                // if (guardPos == tokens.size()-1) throw new SyntaxError("Guard without success expression");
                // if (tokens.at(guardPos+1) instanceof SetTok) endAfter = true;

                if (guardPos == tokens.size()-1) throw "Guard without success expression";
                if (std::holds_alternative<tokens::set>(tokens.at(guardPos+1))) endAfter = true;

            } else if (eguardPos != -1) {
                // if (eguardPos == tokens.size()-1) throw new SyntaxError("Error guard without success expression");
                if (eguardPos == tokens.size()-1) throw "Error guard without success expression";
            }

            if (guardPos != -1) {
                // auto guard = LineTok.inherit(tokens.subList(0, guardPos));
                // auto guard = tokens::line::inherit(to_vector(std::ranges::take_view{tokens, guardPos}));
                auto guard = tokens::line::inherit(subList(tokens, 0, guardPos));

                // if (bool(vexec(guard, sc))) {
                if (bool(vexec(guard))) {
                    // auto expr = LineTok.inherit(tokens.subList(guardPos+(endAfter? 2 : 1), tokens.size()));
                    auto expr = tokens::line::inherit(subList(tokens, guardPos+(endAfter? 2 : 1), tokens.size()));
                    // res = exec(expr, sc);
                    res = exec(expr);

                    if (endAfter) return res;
                }
            } else if (eguardPos != -1) {
                // auto guard = LineTok.inherit(tokens.subList(0, eguardPos));
                auto guard = tokens::line::inherit(subList(tokens, 0, eguardPos));
                // Value r = vexec(guard, sc);
                Value r = vexec(guard);
                EType t;
                if (r.equals(Num.ZERO)) t = EType.all;
                else throw new DomainError("guard "+r+" not supported", guard);
                auto expr = LineTok.inherit(tokens.subList(eguardPos+(endAfter? 2 : 1), tokens.size()));
                eGuards.put(t, expr);
            } else {
                // res = exec(endAfter? LineTok.inherit(tokens) : ln, sc);
                res = exec(endAfter ? tokens::line::inherit(tokens) : ln);
                if (endAfter) return res;
            }
        }
        if (res instanceof Settable) return ((Settable) res).get();
    } catch (Throwable e) {
        for (Map.Entry<EType, LineTok> entry : eGuards.entrySet()) {
            EType t = entry.getKey();
            // if (t == EType.all) return vexec(entry.getValue(), sc);
            if (t == EType.all) return vexec(entry.getValue());
        }
        throw e;
    }
    return res;
}

int main() {
    std::string s = "∧/⊃=⊢";
    auto t = tokenizer::tokenize(s);
    std::cout << "tokens: " << t.tokens.size() << std::endl;
    printdbg(t);
    // return execLines(t, sc);

}