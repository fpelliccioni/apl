#pragma once

#include <cassert>
#include <charconv>
#include <cmath>
#include <limits>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include <apl/helpers/unicode.hpp>
#include <apl/tokenizer/token.hpp>

//Asserts floating point compatibility at compile time
static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");

class tokenizer {
    // static constexpr char validNames[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_∆";
    // static constexpr std::string_view ops = "⍺⍳⍴⍵!%*+,-./<=>?@\\^|~⍬⊢⊣⌷¨⍨⌿⍀≤≥≠∨∧÷×∊↑↓○⌈⌊∇∘⊂⊃∩∪⊥⊤⍱⍲⍒⍋⍉⌽⊖⍟⌹⍕⍎⍫⍪≡≢⍷→⎕⍞⍣⍶⍸⍹⌸⌺⍇⍢⍤⍁⍂⊆⊇⊙⌾⌻⌼⍃⍄⍅⍆⍈⍊⍌⍍⍏⍐⍑⍓⍔⍖⍗⍘⍚⍛⍜⍠⍡⍥⍦⍧⍩⍭⍮⍯⍰√‽⊗ϼ∍⋾…ᑈᐵ"; // stolen from https://bitbucket.org/zacharyjtaylor/rad/src/master/RAD_document.txt?fileviewer=file-view-default

    static constexpr char validNames[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_"; // and unicode char ∆
    static constexpr std::string_view ops[] = {"⍺","⍳","⍴","⍵","!","%","*","+",",","-",".","/","<","=",">","?","@","\\","^","|","~","⍬","⊢","⊣","⌷","¨","⍨","⌿","⍀","≤","≥","≠","∨","∧","÷","×","∊","↑","↓","○","⌈","⌊","∇","∘","⊂","⊃","∩","∪","⊥","⊤","⍱","⍲","⍒","⍋","⍉","⌽","⊖","⍟","⌹","⍕","⍎","⍫","⍪","≡","≢","⍷","→","⎕","⍞","⍣","⍶","⍸","⍹","⌸","⌺","⍇","⍢","⍤","⍁","⍂","⊆","⊇","⊙","⌾","⌻","⌼","⍃","⍄","⍅","⍆","⍈","⍊","⍌","⍍","⍏","⍐","⍑","⍓","⍔","⍖","⍗","⍘","⍚","⍛","⍜","⍠","⍡","⍥","⍦","⍧","⍩","⍭","⍮","⍯","⍰","√","‽","⊗","ϼ","∍","⋾","…","ᑈ","ᐵ"}; // stolen from https://bitbucket.org/zacharyjtaylor/rad/src/master/RAD_document.txt?fileviewer=file-view-default

    static
    bool validNameStart(std::string_view c) {
        if (c == "∆") return true;

        for (size_t i = 0; i < std::size(validNames); ++i) {
          std::string_view l(validNames + i, 1);
          if (l == c) return true;
        }
        return false;

        // for (char l : validNames) if (l == c) return true;
        // return false;
    }

    static
    bool is_operator(std::string_view c) {
        return std::find(std::begin(ops), std::end(ops), c) != std::end(ops);
    }

public:
    static
    bool is_digit(std::string_view c) {
        if (c == "0") return true;
        if (c == "1") return true;
        if (c == "2") return true;
        if (c == "3") return true;
        if (c == "4") return true;
        if (c == "5") return true;
        if (c == "6") return true;
        if (c == "7") return true;
        if (c == "8") return true;
        if (c == "9") return true;
        return false;
    }


    static
    bool validNameMid(std::string_view c) {
        return validNameStart(c) || is_digit(c);
        // return validNameStart(c) || c >= '0' && c <= '9';
    }

    struct Line {
        std::vector<token> ts;
        std::string_view line;
        int pos;
        // std::optional<int> annoyingBacktickPos;

        Line(std::string_view line, int pos, std::vector<token> ts)
          : ts(ts)
          , line(line)
          , pos(pos)
        {}

        Line(std::string_view line, int pos)
          : line(line)
          , pos(pos)
        {}

    public:
        int size() {
            return ts.size();
        }

        void add(token r) {
            ts.push_back(r);

            //TODO: not supported yet
            // if (annoyingBacktickPos) {
            //     ts.push_back(tokens::backtick(line, *annoyingBacktickPos, epos(r), r));
            //     annoyingBacktickPos = std::nullopt;
            // } else {
            //     ts.push_back(r);
            // }
        }

        tokens::line tok() {
            //TODO: not supported yet
            // if (annoyingBacktickPos) {
            //     // throw new SyntaxError("Nothing after backtick");  //TODO
            //     throw "Nothing after backtick";
            // }
            int spos_ = size() == 0 ? pos : spos(ts.at(0));
            int epos_ = size() == 0 ? pos : epos(ts.at(size()-1));    //TODO: changes all .at(size()-1)
            return tokens::line(line, spos_, epos_, ts);
        }
    };

    struct Block { // temp storage of multiple lines
        std::vector<Line> a;
        // char b;
        std::string_view b;
        bool hasDmd = false;
        int pos;

        Block(std::vector<Line> a, std::string_view b, int pos)
            : a(a)
            , b(b)
            , pos(pos)
        {}

        std::string toString() {
            // return "<" + a + "," + b + ">";
            return ""; //TODO: how to concatenate the vector<Line>
        }
    };

    static
    tokens::basic_lines tokenize(std::string raw) {
        return tokenize(raw, false);
    }

    static
    token chr_to_token(std::string_view c, std::string_view raw, Block closed, int i, std::vector<tokens::line> lineTokens) {
        if (c == ")") {
            return tokens::paren(raw, closed.pos, i, lineTokens, closed.hasDmd);
        } else if (c == "}") {
            return tokens::dfn(raw, closed.pos, i, lineTokens);
        } else if (c == "]") {
            return tokens::bracket(raw, closed.pos, i, lineTokens, closed.hasDmd);
        } else {
            // throw new Error("this should really not happen "+c);
            throw "this should really not happen ...";
        }
    }

    // token r;
    // switch (closed.b) {
    //   case ')':
    //     r = new ParenTok(raw, closed.pos, len, lineTokens, closed.hasDmd);
    //     break;
    //   case '}':
    //     r = new DfnTok(raw, closed.pos, len, lineTokens);
    //     break;
    //   case ']':
    //     r = new BracketTok(raw, closed.pos, len, lineTokens, closed.hasDmd);
    //     break;
    //   default:
    //     throw new Error("this should really not happen "+closed.b);
    // }


    static
    tokens::basic_lines tokenize(std::string_view raw, bool pointless) { // pointless means unevaled things get tokens; mainly for syntax highlighting
      int li = 0;
      int len = raw.size();

      std::vector<Block> levels;
      levels.push_back(Block(std::vector<Line>{}, "⋄", 0));
      levels.at(0).a.push_back(Line(raw, 0, std::vector<token>{}));

      for (int i = 0; i < len; li = i) {
          Block& expr = levels.back();
          std::vector<Line>& lines = expr.a;
          Line& tokens = lines.back();
          try {
            // char c = raw[i];
            // char next = i + 1 < len ? raw.at(i + 1) : ' ';
            // std::string cS = String.valueOf(c);
            // std::string c_str(1, c);
            // std::string_view c_sv = c_str;

            size_t c_size = utf8_char_size(raw.substr(i));
            if (c_size == 0) {
                throw "UTF8 encoding error";
            }
            auto c = raw.substr(i, c_size);
            std::cout << "c: " << c << std::endl;

            size_t next_i = i + c_size;
            std::string_view next = " ";
            size_t next_size = 0;
            if (next_i < len) {
                next_size = utf8_char_size(raw.substr(next_i));
                if (next_size == 0) {
                    throw "UTF8 encoding error";
                }
                next = raw.substr(next_i, next_size);
                std::cout << "next: " << next << std::endl;
            }

            if (c == "(" || c == "{" || c == "[") {
                std::string_view match;

                if (c == "(") {
                    match = ")";
                } else if (c == "{") {
                    match = "}";
                } else if (c == "[") {
                    match = "]";
                } else {
                    // throw new Error("this should really not happen");  //TODO: look at all the throw new
                    throw "this should really not happen";
                }

                levels.push_back(Block{std::vector<Line>{}, match, i});
                lines = levels.back().a;
                lines.push_back(Line(raw, i));

                // i++;
                i += c_size;
            } else if (c == ")" || c == "}" || c == "]") {
                // Block closed = levels.remove(levels.size() - 1);
                Block closed = levels.back();
                levels.pop_back();

                if (c != closed.b) {
                    if (pointless) {
                        levels.push_back(closed);
                        tokens.add(tokens::err(raw, i));
                        // and leave running for quick exit
                    }
                    // throw new SyntaxError("mismatched parentheses of " + c + " and " + closed.b);
                    throw "mismatched parentheses of ...";
                }
                if (lines.size() > 0 && lines.back().size() == 0) {
                    // lines.remove(lines.size() - 1); // no trailing empties!!
                    lines.pop_back(); // no trailing empties!!
                }

                std::vector<tokens::line> lineTokens;
                for (Line ta : closed.a) {
                    lineTokens.push_back(ta.tok());
                }
                // token r;
                // switch (c) {
                //   case ')':
                //     r = new ParenTok(raw, closed.pos, i + 1, lineTokens, closed.hasDmd);
                //     break;
                //   case '}':
                //     r = new DfnTok(raw, closed.pos, i + 1, lineTokens);
                //     break;
                //   case ']':
                //     r = new BracketTok(raw, closed.pos, i + 1, lineTokens, closed.hasDmd);
                //     break;
                //   default:
                //     throw new Error("this should really not happen "+c);
                // }

                token r = chr_to_token(c, raw, closed, i + c_size, lineTokens);
                lines = levels.back().a;
                tokens = lines.back();
                tokens.add(r);
                // i++;
                i += c_size;


            //TODO: not suported yet
            // } else if (validNameStart(c) || c == "⎕" && validNameStart(next)) {
            //     i++;
            //     while (i < len && validNameMid(raw.at(i))) i++;
            //     auto name = raw.substr(li, i);
            //     if (c == '⎕') name = name.toUpperCase();
            //     tokens.add(tokens::name(raw, li, i, name));



            } else if (c == "¯" && next == "∞") {
                // i += 2;
                i = next_i + next_size;
                tokens.add(tokens::num(raw, li, i, -std::numeric_limits<double>::infinity()));
            } else if (c == "∞") {
                // i++;
                i += c_size;
                tokens.add(tokens::num(raw, li, i, std::numeric_limits<double>::infinity()));


            // } else if (c>='0' && c<='9' || c=='¯' || c=='.' && next>='0' && next<='9') {
            } else if (is_digit(c) || c == "¯" || c == "." && is_digit(next)) {
                bool negative = c == "¯";

                // if (negative) i++;
                if (negative) i += c_size;

                int si = i;
                bool hasPoint = false;
                while (i < len) {
                    // c = raw.at(i);

                    c_size = utf8_char_size(raw.substr(i));
                    if (c_size == 0) {
                        throw "UTF8 encoding error";
                    }
                    c = raw.substr(i, c_size);
                    std::cout << "c: " << c << std::endl;



                    if (hasPoint) {
                        if ( ! is_digit(c)) {
                          break;
                        }
                    } else if ( ! is_digit(c)) {
                        if (c == ".") {
                            hasPoint = true;
                        } else {
                            break;
                        }
                    }
                    // i++;
                    i += c_size;
                }
                //TODO:
                if (hasPoint) {
                    throw "Floating point numbers not supported yet";
                }

                // double f = Double.parseDouble(raw.substr(si, i));

                auto sub = raw.substr(si, i);
                // double f;
                int64_t f;
                auto [ptr, ec] = std::from_chars(sub.begin(), sub.end(), f);

                if (ec != std::errc()) {
                    throw "That isn't a number";
                }

                if (negative) f = -f;

                if (i < len) {
                    // c = raw.at(i);
                    c_size = utf8_char_size(raw.substr(i));
                    if (c_size == 0) {
                        throw "UTF8 encoding error";
                    }
                    c = raw.substr(i, c_size);
                    std::cout << "c: " << c << std::endl;


                    bool hasE = c == "e" || c == "E";

                    // if (hasE && i+1==len) throw new SyntaxError("unfinished number");
                    if (hasE && i + c_size == len) throw "unfinished number";



                    c_size = utf8_char_size(raw.substr(i + c_size));
                    if (c_size == 0) {
                        throw "UTF8 encoding error";
                    }
                    c = raw.substr(i, c_size);
                    std::cout << "c: " << c << std::endl;


                    // bool hasExp = hasE && !validNameStart(raw.at(i+1));
                    bool hasExp = hasE && !validNameStart(c);

                    if (hasExp) {
                        // i++;
                        i += c_size;
                        // c = raw.at(i);
                        c_size = utf8_char_size(raw.substr(i));
                        if (c_size == 0) {
                            throw "UTF8 encoding error";
                        }
                        c = raw.substr(i, c_size);
                        std::cout << "c: " << c << std::endl;


                        bool negExp = c == "¯";

                        // if (negExp) i++;
                        if (negExp) i += c_size;

                        si = i;
                        while (i < len) {
                            // c = raw.at(i);
                            c_size = utf8_char_size(raw.substr(i));
                            if (c_size == 0) {
                                throw "UTF8 encoding error";
                            }
                            c = raw.substr(i, c_size);
                            std::cout << "c: " << c << std::endl;

                            // if (c < '0' || c > '9') break;
                            if ( ! is_digit(c)) break;

                            // i++;
                            i += c_size;
                        }
                        // int exp = Integer.parseInt(raw.substr(si, i));

                        auto expsub = raw.substr(si, i);
                        int64_t exp;
                        auto [ptr, ec] = std::from_chars(expsub.begin(), expsub.end(), exp);

                        if (ec != std::errc()) {
                            throw "That isn't a number";
                        }

                        if (negExp) exp = -exp;
                        // f *= Math.pow(10, exp);
                        f *= std::pow(10, exp);
                    }

                    //TODO: big numbers not supported yet
                    // if (i < len && raw.at(i)=='L' && (i+1 == len || !validNameMid(raw.at(i+1)))) {
                    //     if (hasExp || hasPoint) {
                    //         if (hasExp) throw new SyntaxError("biginteger literal with exponent");
                    //         throw new SyntaxError("biginteger literal with decimal part");
                    //     }
                    //     i++;
                    //     BigInteger big = new BigInteger(raw.substr(si, i-1));
                    //     if (negative) big = big.negate();
                    //     tokens.add(new BigTok(raw, li, i, new BigValue(big)));
                    // } else {
                    //     tokens.add(new NumTok(raw, li, i, f));
                    // }

                    tokens.add(tokens::num(raw, li, i, f));


                } else {
                    tokens.add(tokens::num(raw, li, i, f));
                }


            // } else if (ops.contains(cS)) {
            } else if (is_operator(c)) {
                std::cout << " *** IS OPERATOR ***\n";
                // tokens.add(tokens::operator(raw, i, i + 1, cS));
                // // i++;
                tokens.add(tokens::operator(raw, i, i + c_size, std::string(c)));
                i += c_size;

            } else if (c == "←") {
                tokens.add(tokens::set(raw, i, i + c_size));
                // i++;
                i += c_size;

            //TODO: not supported yet
            // } else if (c == '`') {
            //     if (tokens.annoyingBacktickPos != null) throw new SyntaxError("` after `");
            //     tokens.annoyingBacktickPos = i;
            //     i++;

            } else if (c == ":") {
                if (next == ":") {
                    tokens.add(tokens::dcolon(raw, i, next_i + next_size));
                    // i++;
                    i = next_i + next_size;
                } else {
                    tokens.add(tokens::colon(raw, i, i + c_size));
                    i += c_size;
                }
                // i++;


            //TODO: strings not supported yet
            // } else if (c == '\'') {
            //     StringBuilder str = new StringBuilder();
            //     i++;
            //     if (i >= len) throw new SyntaxError("unfinished string");
            //     while (true) {
            //       if (raw.at(i) == '\'') {
            //         if (i+1 < len && raw.at(i+1) == '\'') {
            //           str.append("'");
            //           i++;
            //         } else break;
            //       } else str.append(raw.at(i));
            //       i++;
            //       if (i >= len) throw new SyntaxError("unfinished string");
            //     }
            //     i++;
            //     tokens.add(new ChrTok(raw, li, i, str.toString()));
            // } else if (c == '"') {
            //     StringBuilder str = new StringBuilder();
            //     i++;
            //     if (i == len) throw new SyntaxError("unfinished string");
            //     while (raw.at(i) != '"') {
            //       if (raw.at(i) == '\\') {
            //         i++;
            //         SyntaxError.must(i < len, "unfinished string");
            //         char esc = raw.at(i);
            //         switch (esc) {
            //           case  'n': str.append('\n'); break;
            //           case  'r': str.append('\r'); break;
            //           case  '"': str.append('\"'); break;
            //           case '\'': str.append('\''); break;
            //           case '\\': str.append('\\'); break;
            //           case  't': str.append('\t'); break;
            //           case  'x': {
            //             SyntaxError.must(i+2 < len, "unfinished string");
            //             int num = Integer.parseInt(raw.substr(i+1, i+3), 16);
            //             str.append(Character.toChars(num));
            //             i+= 2;
            //             break;
            //           }
            //           case  'u': {
            //             SyntaxError.must(i+4 < len, "unfinished string");
            //             int num = Integer.parseInt(raw.substr(i+1, i+5), 16);
            //             str.append(Character.toChars(num));
            //             i+= 4;
            //             break;
            //           }
            //           default: throw new SyntaxError("invalid escape character "+esc);
            //         }
            //       } else {
            //         str.append(raw.at(i));
            //       }
            //       i++;
            //       SyntaxError.must(i < len, "unfinished string");
            //     }
            //     i++;
            //     tokens.add(new StrTok(raw, li, i, str.toString()));


            } else if (c == "\n" || c == "⋄" || c == "\r" || c == ";") {
                if (c == "⋄" && pointless) tokens.add(tokens::diamond(raw, i));
                if (c == "⋄" || c == "\n") expr.hasDmd = true;
                if (c == ";") tokens.add(tokens::semi(raw, i, i + c_size));

                if (tokens.size() > 0) {
                    lines.push_back(Line(raw, li));
                }
                // i++;
                i += c_size;

            // //TODO: comments not supported yet
            // } else if (c == "⍝") {
            //     i++;
            //     while (i < len && raw.at(i) != '\n') i++;
            //     if (pointless) tokens.add(new CommentTok(raw, li, i));


            // //TODO: scope not supported yet
            // } else if (c == '#') {
            //   tokens.add(new ScopeTok(raw, i, i+1));
            //   i++;


            } else if (c == " " || c == "\t") {
              // i++;
              i += c_size;
            } else {
                if (pointless) {
                    tokens.add(tokens::err(raw, i, i + c_size));
                } else {
                    // std::string hex = Integer.toHexString(c);

                    // while(hex.length() < 4) {
                    //     //noinspection StringConcatenationInLoop \\ shut UUuuppp
                    //     hex = "0"+hex;
                    // }
                    // throw new SyntaxError("unknown token `" + c + "` (\\u"+hex+")");
                    throw "unknown token `";
                }
                i += c_size;
            }
            //if (c != ' ') {
            //  printdbg("> "+(c+"").replace("\n","\\n"));
            //  printdbg("curr: "+join(levels, "|"));
            //}
            assert(li < i); // error if nothing changed!
          } catch (...) {
              // System.out.println("BAD");
              // e.printStackTrace();
              if (!pointless) throw "ERROR!!!!!";
              if (li == i) i = li + 1; // lazy exit out of infinite loops
              tokens.add(tokens::err(raw, li, i));
          }
          // } catch (Throwable e) {
          //     // System.out.println("BAD");
          //     // e.printStackTrace();
          //     if (!pointless) throw e;
          //     if (li == i) i = li + 1; // lazy exit out of infinite loops
          //     tokens.add(new ErrTok(raw, li, i));
          // }
      }

      if (levels.size() != 1) {
          if (!pointless) {
              // throw new SyntaxError("error matching parentheses"); // or too many
              throw "error matching parentheses"; // or too many
          }
          // else, attempt to recover
          while (levels.size() > 1) {
              // Block closed = levels.remove(levels.size() - 1);
              Block closed = levels.back();
              levels.pop_back();

              std::vector<tokens::line> lineTokens;
              for (Line ta : closed.a) {
                 lineTokens.push_back(ta.tok());
              }
              // token r;
              // switch (closed.b) {
              //   case ')':
              //     r = new ParenTok(raw, closed.pos, len, lineTokens, closed.hasDmd);
              //     break;
              //   case '}':
              //     r = new DfnTok(raw, closed.pos, len, lineTokens);
              //     break;
              //   case ']':
              //     r = new BracketTok(raw, closed.pos, len, lineTokens, closed.hasDmd);
              //     break;
              //   default:
              //     throw new Error("this should really not happen "+closed.b);
              // }

              token r = chr_to_token(closed.b, raw, closed, len, lineTokens);

              auto lines = levels.back().a;
              Line tokens = lines.back();
              tokens.add(r);
          }
      }
      auto lines = levels.at(0).a;
      // if (lines.size() > 0 && lines.at(lines.size()-1).size() == 0) {
      //    lines.remove(lines.size()-1); // no trailing empties!!
      // }

      std::cout << "lines.size(): " << lines.size() << std::endl;
      if (lines.size() > 0 && lines.back().size() == 0) {
         lines.pop_back();
      }

      std::vector<tokens::line> expressions;
      for (Line line : lines) {
          expressions.push_back(line.tok());
      }
      std::cout << "expressions.size(): " << expressions.size() << std::endl;
      std::cout << "lines.size(): " << lines.size() << std::endl;
      return tokens::basic_lines(raw, 0, len, expressions);
    }
};

// package APL.tokenizer;

// import APL.errors.SyntaxError;
// import APL.tokenizer.types.*;
// import APL.types.BigValue;

// import java.math.BigInteger;
// import java.util.ArrayList;

// public class Tokenizer {
//   private static final char[] validNames = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_∆".toCharArray();
//   private static final String ops = "⍺⍳⍴⍵!%*+,-./<=>?@\\^|~⍬⊢⊣⌷¨⍨⌿⍀≤≥≠∨∧÷×∊↑↓○⌈⌊∇∘⊂⊃∩∪⊥⊤⍱⍲⍒⍋⍉⌽⊖⍟⌹⍕⍎⍫⍪≡≢⍷→⎕⍞⍣⍶⍸⍹⌸⌺⍇⍢⍤⍁⍂⊆⊇⊙⌾⌻⌼⍃⍄⍅⍆⍈⍊⍌⍍⍏⍐⍑⍓⍔⍖⍗⍘⍚⍛⍜⍠⍡⍥⍦⍧⍩⍭⍮⍯⍰√‽⊗ϼ∍⋾…ᑈᐵ"; // stolen from https://bitbucket.org/zacharyjtaylor/rad/src/master/RAD_document.txt?fileviewer=file-view-default
//   private static boolean validNameStart(char c) {
//     for (char l : validNames) if (l == c) return true;
//     return false;
//   }
//   public static boolean validNameMid(char c) {
//     return validNameStart(c) || c >= '0' && c <= '9';
//   }
//   static class Line {
//     final ArrayList<Token> ts;
//     final String line;
//     final int pos;
//     Integer annoyingBacktickPos;

//     Line(String line, int pos, ArrayList<Token> ts) {
//       this.ts = ts;
//       this.line = line;
//       this.pos = pos;
//     }

//     Line(String line, int pos) {
//       this(line, pos, new ArrayList<>());
//     }

//     public int size() {
//       return ts.size();
//     }

//     public void add(Token r) {
//       if (annoyingBacktickPos != null) {
//         ts.add(new BacktickTok(line, annoyingBacktickPos, r.epos, r));
//         annoyingBacktickPos = null;
//       } else {
//         ts.add(r);
//       }
//     }

//     LineTok tok() {
//       if (annoyingBacktickPos != null) throw new SyntaxError("Nothing after backtick");
//       int spos = size()==0? pos : ts.get(0).spos;
//       int epos = size()==0? pos : ts.get(size()-1).epos;
//       return new LineTok(line, spos, epos, ts);
//     }
//   }
//   static class Block { // temp storage of multiple lines
//     final ArrayList<Line> a;
//     final char b;
//     boolean hasDmd = false;
//     private final int pos;

//     Block(ArrayList<Line> a, char b, int pos) {
//       this.a = a;
//       this.b = b;
//       this.pos = pos;
//     }
//     public String toString() {
//       return "<"+a+","+b+">";
//     }
//   }

//   public static BasicLines tokenize(String raw) {
//     return tokenize(raw, false);
//   }

//   public static BasicLines tokenize(String raw, boolean pointless) { // pointless means unevaled things get tokens; mainly for syntax highlighting
//     int li = 0;
//     int len = raw.length();

//     var levels = new ArrayList<Block>();
//     levels.add(new Block(new ArrayList<>(), '⋄', 0));
//     levels.get(0).a.add(new Line(raw, 0, new ArrayList<>()));

//     for (int i = 0; i < len; li = i) {
//       Block expr = levels.get(levels.size() - 1);
//       ArrayList<Line> lines = expr.a;
//       Line tokens = lines.get(lines.size() - 1);
//       try {
//         char c = raw.charAt(i);
//         char next = i + 1 < len? raw.charAt(i + 1) : ' ';
//         String cS = String.valueOf(c);
//         if (c == '(' || c == '{' || c == '[') {
//           char match;
//           switch (c) {
//             case '(':
//               match = ')';
//               break;
//             case '{':
//               match = '}';
//               break;
//             case '[':
//               match = ']';
//               break;
//             default:
//               throw new Error("this should really not happen");
//           }
//           levels.add(new Block(new ArrayList<>(), match, i));
//           lines = levels.get(levels.size() - 1).a;
//           lines.add(new Line(raw, i));

//           i++;
//         } else if (c == ')' || c == '}' || c == ']') {
//           Block closed = levels.remove(levels.size() - 1);
//           if (c != closed.b) {
//             if (pointless) {
//               levels.add(closed);
//               tokens.add(new ErrTok(raw, i));
//               // and leave running for quick exit
//             }
//             throw new SyntaxError("mismatched parentheses of " + c + " and " + closed.b);
//           }
//           if (lines.size() > 0 && lines.get(lines.size() - 1).size() == 0) lines.remove(lines.size() - 1); // no trailing empties!!

//           var lineTokens = new ArrayList<LineTok>();
//           for (Line ta : closed.a) lineTokens.add(ta.tok());
//           Token r;
//           switch (c) {
//             case ')':
//               r = new ParenTok(raw, closed.pos, i + 1, lineTokens, closed.hasDmd);
//               break;
//             case '}':
//               r = new DfnTok(raw, closed.pos, i + 1, lineTokens);
//               break;
//             case ']':
//               r = new BracketTok(raw, closed.pos, i + 1, lineTokens, closed.hasDmd);
//               break;
//             default:
//               throw new Error("this should really not happen "+c);
//           }
//           lines = levels.get(levels.size() - 1).a;
//           tokens = lines.get(lines.size() - 1);
//           tokens.add(r);
//           i++;
//         } else if (validNameStart(c) || c == '⎕' && validNameStart(next)) {
//           i++;
//           while (i < len && validNameMid(raw.charAt(i))) i++;
//           var name = raw.substring(li, i);
//           if (c == '⎕') name = name.toUpperCase();
//           tokens.add(new NameTok(raw, li, i, name));
//         } else if (c=='¯' && next=='∞') {
//           i+= 2;
//           tokens.add(new NumTok(raw, li, i, Double.NEGATIVE_INFINITY));
//         } else if (c == '∞') {
//           i++;
//           tokens.add(new NumTok(raw, li, i, Double.POSITIVE_INFINITY));
//         } else if (c>='0' && c<='9' || c=='¯' || c=='.' && next>='0' && next<='9') {
//           boolean negative = c=='¯';
//           if (negative) i++;
//           int si = i;
//           boolean hasPoint = false;
//           while(i < len) {
//             c = raw.charAt(i);
//             if (hasPoint) {
//               if (c<'0' || c>'9') break;
//             } else if (c<'0' || c>'9') {
//               if (c == '.') hasPoint = true;
//               else break;
//             }
//             i++;
//           }
//           double f = Double.parseDouble(raw.substring(si,i));
//           if (negative) f = -f;
//           if (i < len) {
//             c = raw.charAt(i);
//             boolean hasE = c=='e' | c=='E';
//             if (hasE && i+1==len) throw new SyntaxError("unfinished number");
//             boolean hasExp = hasE && !validNameStart(raw.charAt(i+1));
//             if (hasExp) {
//               i++;
//               c = raw.charAt(i);
//               boolean negExp = c == '¯';
//               if (negExp) i++;
//               si = i;
//               while (i < len) {
//                 c = raw.charAt(i);
//                 if (c < '0' || c > '9') break;
//                 i++;
//               }
//               int exp = Integer.parseInt(raw.substring(si, i));
//               if (negExp) exp = -exp;
//               f *= Math.pow(10, exp);
//             }
//             if (i<len && raw.charAt(i)=='L' && (i+1 == len || !validNameMid(raw.charAt(i+1)))) {
//               if (hasExp || hasPoint) {
//                 if (hasExp) throw new SyntaxError("biginteger literal with exponent");
//                 throw new SyntaxError("biginteger literal with decimal part");
//               }
//               i++;
//               BigInteger big = new BigInteger(raw.substring(si, i-1));
//               if (negative) big = big.negate();
//               tokens.add(new BigTok(raw, li, i, new BigValue(big)));
//             } else tokens.add(new NumTok(raw, li, i, f));
//           } else tokens.add(new NumTok(raw, li, i, f));
//         } else if (ops.contains(cS)) {
//           tokens.add(new OpTok(raw, i, i + 1, cS));
//           i++;
//         } else if (c == '←') {
//           tokens.add(new SetTok(raw, i, i + 1));
//           i++;
//         } else if (c == '`') {
//           if (tokens.annoyingBacktickPos != null) throw new SyntaxError("` after `");
//           tokens.annoyingBacktickPos = i;
//           i++;
//         } else if (c == ':') {
//           if (next == ':') {
//             tokens.add(new DColonTok(raw, i, i + 2));
//             i++;
//           } else tokens.add(new ColonTok(raw, i, i + 1));
//           i++;
//         } else if (c == '\'') {
//           StringBuilder str = new StringBuilder();
//           i++;
//           if (i >= len) throw new SyntaxError("unfinished string");
//           while (true) {
//             if (raw.charAt(i) == '\'') {
//               if (i+1 < len && raw.charAt(i+1) == '\'') {
//                 str.append("'");
//                 i++;
//               } else break;
//             } else str.append(raw.charAt(i));
//             i++;
//             if (i >= len) throw new SyntaxError("unfinished string");
//           }
//           i++;
//           tokens.add(new ChrTok(raw, li, i, str.toString()));
//         } else if (c == '"') {
//           StringBuilder str = new StringBuilder();
//           i++;
//           if (i == len) throw new SyntaxError("unfinished string");
//           while (raw.charAt(i) != '"') {
//             if (raw.charAt(i) == '\\') {
//               i++;
//               SyntaxError.must(i < len, "unfinished string");
//               char esc = raw.charAt(i);
//               switch (esc) {
//                 case  'n': str.append('\n'); break;
//                 case  'r': str.append('\r'); break;
//                 case  '"': str.append('\"'); break;
//                 case '\'': str.append('\''); break;
//                 case '\\': str.append('\\'); break;
//                 case  't': str.append('\t'); break;
//                 case  'x': {
//                   SyntaxError.must(i+2 < len, "unfinished string");
//                   int num = Integer.parseInt(raw.substring(i+1, i+3), 16);
//                   str.append(Character.toChars(num));
//                   i+= 2;
//                   break;
//                 }
//                 case  'u': {
//                   SyntaxError.must(i+4 < len, "unfinished string");
//                   int num = Integer.parseInt(raw.substring(i+1, i+5), 16);
//                   str.append(Character.toChars(num));
//                   i+= 4;
//                   break;
//                 }
//                 default: throw new SyntaxError("invalid escape character "+esc);
//               }
//             } else {
//               str.append(raw.charAt(i));
//             }
//             i++;
//             SyntaxError.must(i < len, "unfinished string");
//           }
//           i++;
//           tokens.add(new StrTok(raw, li, i, str.toString()));
//         } else if (c == '\n' || c == '⋄' || c == '\r' || c == ';') {
//           if (c=='⋄' && pointless) tokens.add(new DiamondTok(raw, i));
//           if (c=='⋄' || c=='\n') expr.hasDmd = true;
//           if (c == ';') tokens.add(new SemiTok(raw, i, i + 1));

//           if (tokens.size() > 0) {
//             lines.add(new Line(raw, li));
//           }
//           i++;
//         } else if (c == '⍝') {
//           i++;
//           while (i < len && raw.charAt(i) != '\n') i++;
//           if (pointless) tokens.add(new CommentTok(raw, li, i));
//         } else if (c == '#') {
//           tokens.add(new ScopeTok(raw, i, i+1));
//           i++;
//         } else if (c == ' ' || c == '\t') {i++;} else {
//           if (pointless) tokens.add(new ErrTok(raw, i, i + 1));
//           else {
//             String hex = Integer.toHexString(c);

//             while(hex.length() < 4)
//               //noinspection StringConcatenationInLoop \\ shut UUuuppp
//               hex = "0"+hex;
//             throw new SyntaxError("unknown token `" + c + "` (\\u"+hex+")");
//           }
//           i++;
//         }
//         //if (c != ' ') {
//         //  printdbg("> "+(c+"").replace("\n","\\n"));
//         //  printdbg("curr: "+join(levels, "|"));
//         //}
//         assert li < i; // error if nothing changed!
//       } catch (Throwable e) {
//         // System.out.println("BAD");
//         // e.printStackTrace();
//         if (!pointless) throw e;
//         if (li == i) i = li + 1; // lazy exit out of infinite loops
//         tokens.add(new ErrTok(raw, li, i));
//       }
//     }
//     if (levels.size() != 1) {
//       if (!pointless) throw new SyntaxError("error matching parentheses"); // or too many
//       // else, attempt to recover
//       while (levels.size() > 1) {
//         Block closed = levels.remove(levels.size() - 1);

//         var lineTokens = new ArrayList<LineTok>();
//         for (Line ta : closed.a) lineTokens.add(ta.tok());
//         Token r;
//         switch (closed.b) {
//           case ')':
//             r = new ParenTok(raw, closed.pos, len, lineTokens, closed.hasDmd);
//             break;
//           case '}':
//             r = new DfnTok(raw, closed.pos, len, lineTokens);
//             break;
//           case ']':
//             r = new BracketTok(raw, closed.pos, len, lineTokens, closed.hasDmd);
//             break;
//           default:
//             throw new Error("this should really not happen "+closed.b);
//         }
//         var lines = levels.get(levels.size() - 1).a;
//         Line tokens = lines.get(lines.size() - 1);
//         tokens.add(r);
//       }
//     }
//     var lines = levels.get(0).a;
//     if (lines.size() > 0 && lines.get(lines.size()-1).size() == 0) lines.remove(lines.size()-1); // no trailing empties!!
//     var expressions = new ArrayList<LineTok>();
//     for (Line line : lines) {
//       expressions.add(line.tok());
//     }
//     return new BasicLines(raw, 0, len, expressions);
//   }
// }