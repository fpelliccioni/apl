// #include <apl/tokenizer/token_all.hpp>
#include <apl/tokenizer/token.hpp>

#include <vector>
#include <iostream>

int main() {

    std::vector<token> tokens = {
        tokens::colon{"this is a colon", 0, 0},
        tokens::dcolon{"this is a Dcolon", 0, 0},
        // tokens::diamond{"this is a diamond", 0},
        // tokens::err{"this is an err", 0, 0},
        // tokens::name{"this is a name", 0, 0, "somename"},
        // tokens::operator{"this is an op", 0, 0, "+"},
        // tokens::scope{"this is a scope", 0, 0},
        // tokens::semi{"this is a semi", 0, 0},
        // tokens::set{"this is a set", 0, 0}
    };

    std::string p;
    for (auto& t: tokens) {
        std::cout << raw(t) << std::endl;
        std::cout << class_name(t) << std::endl;
        std::cout << to_tree(t, p);
        std::cout << to_repr(t) << std::endl;
    }

    tokens::line l1("this is a bracket", 0, 0, tokens);
    std::cout << to_tree(l1, p);


    // tokens::bracket b1("this is a bracket", 0, 0, tokens, false);
    // std::cout << to_tree(b1, p);
    // tokens::bracket b2("this is a bracket", 0, 0, tokens, true);
    // std::cout << to_tree(b2, p);

    // tokens::array arr("this is an array", 0, tokens);
    // std::cout << to_tree(arr, p);
}