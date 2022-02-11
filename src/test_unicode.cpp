#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>

#include <apl/helpers/unicode.hpp>

// static constexpr char validNames[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_∆";

void print_int(std::string_view lit) {
    for (char c : lit) {
        std::cout << (int) (unsigned char)c << '|';
    }
    std::cout << std::endl;
}


int main() {
    // constexpr std::string_view ops[] = {
    //     "_",
    //     "∆",
    // };


    constexpr std::string_view ops[] = {
        "⍺",
        "⍳",
        "⍴",
        "⍵",
        "!",
        "%",
        "*",
        "+",
        ",",
        "-",
        ".",
        "/",
        "<",
        "=",
        ">",
        "?",
        "@",
        "\\",
        "^",
        "|",
        "~",
        "⍬",
        "⊢",
        "⊣",
        "⌷",
        "¨",
        "⍨",
        "⌿",
        "⍀",
        "≤",
        "≥",
        "≠",
        "∨",
        "∧",
        "÷",
        "×",
        "∊",
        "↑",
        "↓",
        "○",
        "⌈",
        "⌊",
        "∇",
        "∘",
        "⊂",
        "⊃",
        "∩",
        "∪",
        "⊥",
        "⊤",
        "⍱",
        "⍲",
        "⍒",
        "⍋",
        "⍉",
        "⌽",
        "⊖",
        "⍟",
        "⌹",
        "⍕",
        "⍎",
        "⍫",
        "⍪",
        "≡",
        "≢",
        "⍷",
        "→",
        "⎕",
        "⍞",
        "⍣",
        "⍶",
        "⍸",
        "⍹",
        "⌸",
        "⌺",
        "⍇",
        "⍢",
        "⍤",
        "⍁",
        "⍂",
        "⊆",
        "⊇",
        "⊙",
        "⌾",
        "⌻",
        "⌼",
        "⍃",
        "⍄",
        "⍅",
        "⍆",
        "⍈",
        "⍊",
        "⍌",
        "⍍",
        "⍏",
        "⍐",
        "⍑",
        "⍓",
        "⍔",
        "⍖",
        "⍗",
        "⍘",
        "⍚",
        "⍛",
        "⍜",
        "⍠",
        "⍡",
        "⍥",
        "⍦",
        "⍧",
        "⍩",
        "⍭",
        "⍮",
        "⍯",
        "⍰",
        "√",
        "‽",
        "⊗",
        "ϼ",
        "∍",
        "⋾",
        "…",
        "ᑈ",
        "ᐵ"};

    // for (auto op : ops) {
    //     std::cout << op << " - " << op.size() << " - ";
    //     print_int(op);
    // }


    constexpr std::string_view test_str = "∧/⊃=⊢";
    std::cout << test_str << " - " << test_str.size() << std::endl;
    print_int(test_str);

    size_t i = 0;
    while (i < test_str.size()) {
        auto c = test_str[i];
        auto s = utf8_char_size(test_str.substr(i));
        if (s == 0) {
            std::cout << "UTF8 error\n";
            break;
        }
        auto utf8_chr = test_str.substr(i, s);


        auto it = std::find(std::begin(ops), std::end(ops), utf8_chr);
        if (it != std::end(ops)) {
            std::cout << utf8_chr << " found" << std::endl;
        } else {
            std::cout << utf8_chr << " NOT found" << std::endl;
        }

        // std::cout << "i: " << i << " - size: " << s << std::endl;
        i += s;
    }


    // std::cout << test_str << " - " << test_str.size() << std::endl;
    // print_int(test_str);

    // // std::cout << "0b11100010 <= 0b01111111: " << (uint8_t(0b11100010) <= 0b01111111) << std::endl;


    // size_t i = 0;
    // while (i < test_str.size()) {
    //     auto c = test_str[i];
    //     auto s = utf8_char_size(test_str.substr(i));
    //     std::cout << "i: " << i << " - size: " << s << std::endl;
    //     ++i;
    // }




    // char x = 0b01111111;
    // std::cout << bit_set<0>(x) << std::endl;
    // std::cout << bit_set<1>(x) << std::endl;
    // std::cout << bit_set<2>(x) << std::endl;
    // std::cout << bit_set<3>(x) << std::endl;
    // std::cout << bit_set<4>(x) << std::endl;
    // std::cout << bit_set<5>(x) << std::endl;
    // std::cout << bit_set<6>(x) << std::endl;
    // std::cout << bit_set<7>(x) << std::endl;

}