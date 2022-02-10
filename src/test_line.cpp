// #include <apl/tokenizer/token_all.hpp>
#include <apl/tokenizer/token.hpp>

#include <vector>
#include <iostream>

int main() {

    std::vector<token> tokens = {
        types::colon{"this is a colon", 0, 0},
        types::dcolon{"this is a Dcolon", 0, 0},
        // types::diamond{"this is a diamond", 0},
        // types::err{"this is an err", 0, 0},
        // types::name{"this is a name", 0, 0, "somename"},
        // types::op{"this is an op", 0, 0, "+"},
        // types::scope{"this is a scope", 0, 0},
        // types::semi{"this is a semi", 0, 0},
        // types::set{"this is a set", 0, 0}
    };

    std::string p;
    for (auto& t: tokens) {
        std::cout << raw(t) << std::endl;
        std::cout << class_name(t) << std::endl;
        std::cout << to_tree(t, p);
        std::cout << to_repr(t) << std::endl;
    }

    types::line l1("this is a bracket", 0, 0, tokens);
    std::cout << to_tree(l1, p);


    // types::bracket b1("this is a bracket", 0, 0, tokens, false);
    // std::cout << to_tree(b1, p);
    // types::bracket b2("this is a bracket", 0, 0, tokens, true);
    // std::cout << to_tree(b2, p);

    // types::array arr("this is an array", 0, tokens);
    // std::cout << to_tree(arr, p);
}