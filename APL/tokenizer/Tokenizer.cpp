//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/Tokenizer.h>
#include <APL/types/BacktickTok.h>
#include <APL/types/ErrTok.h>
#include <APL/types/ParenTok.h>
#include <APL/types/DfnTok.h>
#include <APL/types/APL::tokenizer::types::BracketTok.h>
#include <APL/types/NameTok.h>
#include <APL/types/NumTok.h>
#include <APL/types/BigTok.h>
#include <APL/types/OpTok.h>
#include <APL/types/SetTok.h>
#include <APL/types/DColonTok.h>
#include <APL/types/ColonTok.h>
#include <APL/types/ChrTok.h>
#include <APL/types/StrTok.h>
#include <APL/types/DiamondTok.h>
#include <APL/types/SemiTok.h>
#include <APL/types/CommentTok.h>
#include <APL/types/ScopeTok.h>

namespace APL::tokenizer
{
    using SyntaxError = APL::errors::SyntaxError;
    // using namespace APL::tokenizer::types;
    using APL::types::BigValue = APL::types::APL::types::BigValue;
    // using BigInteger = java::math::BigInteger;
    // using ArrayList = java::util::ArrayList;
const std::vector<wchar_t> Tokenizer::validNames = std::vector<wchar_t>((std::string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_∆")).begin(), (std::string(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_∆")).end());
const std::string Tokenizer::ops = L"⍺⍳⍴⍵!%*+,-./<=>?@\\^|~⍬⊢⊣⌷¨⍨⌿⍀≤≥≠∨∧÷×∊↑↓○⌈⌊∇∘⊂⊃∩∪⊥⊤⍱⍲⍒⍋⍉⌽⊖⍟⌹⍕⍎⍫⍪≡≢⍷→⎕⍞⍣⍶⍸⍹⌸⌺⍇⍢⍤⍁⍂⊆⊇⊙⌾⌻⌼⍃⍄⍅⍆⍈⍊⍌⍍⍏⍐⍑⍓⍔⍖⍗⍘⍚⍛⍜⍠⍡⍥⍦⍧⍩⍭⍮⍯⍰√‽⊗ϼ∍⋾…ᑈᐵ";

    bool Tokenizer::validNameStart(wchar_t c)
    {
      for (auto l : validNames)
      {
          if (l == c)
          {
              return true;
          }
      }
      return false;
    }

    bool Tokenizer::validNameMid(wchar_t c)
    {
      return validNameStart(c) || c >= L'0' && c <= L'9';
    }

    Tokenizer::Line::Line(std::string const& line, int pos, std::vector<std::shared_ptr<Token>> &ts) : ts(ts), line(line), pos(pos)
    {
    }

    Tokenizer::Line::Line(std::string const& line, int pos) : Line(line, pos, std::vector<std::shared_ptr<Token>>())
    {
    }

    int Tokenizer::Line::size()
    {
      return ts.size();
    }

    void Tokenizer::Line::add(std::shared_ptr<Token> r)
    {
      if (annoyingBacktickPos)
      {
        ts.push_back(std::make_shared<BacktickTok>(line, annoyingBacktickPos.value(), r->epos, r));
        annoyingBacktickPos = std::nullopt;
      }
      else
      {
        ts.push_back(r);
      }
    }

    std::shared_ptr<APL::tokenizer::types::LineTok> Tokenizer::Line::tok()
    {
      if (annoyingBacktickPos)
      {
          throw SyntaxError(L"Nothing after backtick");
      }
      int spos = size() == 0? pos : ts[0]->spos;
      int epos = size() == 0? pos : ts[size() - 1]->epos;
      return std::make_shared<APL::tokenizer::types::LineTok>(line, spos, epos, ts);
    }

    Tokenizer::Block::Block(std::vector<std::shared_ptr<Line>> &a, wchar_t b, int pos) : a(a), b(b), pos(pos)
    {
    }

    std::string Tokenizer::Block::toString()
    {
      return L"<" + a + L"," + StringHelper::toString(b) + L">";
    }

    std::shared_ptr<APL::tokenizer::types::BasicLines> Tokenizer::tokenize(std::string const& raw)
    {
      return tokenize(raw, false);
    }

    std::shared_ptr<APL::tokenizer::types::BasicLines> Tokenizer::tokenize(std::string const& raw, bool pointless)
    { // pointless means unevaled things get tokens; mainly for syntax highlighting
      int li = 0;
      int len = raw.length();

      auto levels = std::vector<std::shared_ptr<Block>>();
      levels.push_back(std::make_shared<Block>(std::vector<std::shared_ptr<Line>>(), L'⋄', 0));
      levels[0]->a.push_back(std::make_shared<Line>(raw, 0, std::vector<std::shared_ptr<Token>>()));

      for (int i = 0; i < len; li = i)
      {
        std::shared_ptr<Block> expr = levels[levels.size() - 1];
        std::vector<std::shared_ptr<Line>> &lines = expr->a;
        std::shared_ptr<Line> tokens = lines[lines.size() - 1];
        try
        {
          wchar_t c = raw[i];
          wchar_t next = i + 1 < len? raw[i + 1] : L' ';
          std::string cS = StringHelper::toString(c);
          if (c == L'(' || c == L'{' || c == L'[')
          {
            wchar_t match;
            switch (c)
            {
              case L'(':
                match = L')';
                break;
              case L'{':
                match = L'}';
                break;
              case L'[':
                match = L']';
                break;
              default:
                throw Error("this should really not happen");
            }
            levels.push_back(std::make_shared<Block>(std::vector<std::shared_ptr<Line>>(), match, i));
            lines = levels[levels.size() - 1]->a;
            lines.push_back(std::make_shared<Line>(raw, i));

            i++;
          }
          else if (c == L')' || c == L'}' || c == L']')
          {
            std::shared_ptr<Block> closed = levels.pop_back();
            if (c != closed->b)
            {
              if (pointless)
              {
                levels.push_back(closed);
                tokens->add(std::make_shared<ErrTok>(raw, i));
                // and leave running for quick exit
              }
              throw SyntaxError(StringHelper::wstring_to_string(L"mismatched parentheses of " + StringHelper::toString(c) + L" and " + StringHelper::toString(closed->b)));
            }
            if (lines.size() > 0 && lines[lines.size() - 1]->size() == 0)
            {
                lines.pop_back(); // no trailing empties!!
            }

            auto APL::tokenizer::types::LineTokens = std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>>();
            for (auto ta : closed->a)
            {
                APL::tokenizer::types::LineTokens.push_back(ta->tok());
            }
            std::shared_ptr<Token> r;
            switch (c)
            {
              case L')':
                r = std::make_shared<ParenTok>(raw, closed->pos, i + 1, APL::tokenizer::types::LineTokens, closed->hasDmd);
                break;
              case L'}':
                r = std::make_shared<DfnTok>(raw, closed->pos, i + 1, APL::tokenizer::types::LineTokens);
                break;
              case L']':
                r = std::make_shared<APL::tokenizer::types::BracketTok>(raw, closed->pos, i + 1, APL::tokenizer::types::LineTokens, closed->hasDmd);
                break;
              default:
                throw Error(StringHelper::wstring_to_string(L"this should really not happen " + StringHelper::toString(c)));
            }
            lines = levels[levels.size() - 1]->a;
            tokens = lines[lines.size() - 1];
            tokens->add(r);
            i++;
          }
          else if (validNameStart(c) || c == L'⎕' && validNameStart(next))
          {
            i++;
            while (i < len && validNameMid(raw[i]))
            {
                i++;
            }
            auto name = raw.substr(li, i - li);
            if (c == L'⎕')
            {
                name = StringHelper::toUpper(name);
            }
            tokens->add(std::make_shared<NameTok>(raw, li, i, name));
          }
          else if (c == L'¯' && next == L'∞')
          {
            i += 2;
            tokens->add(std::make_shared<NumTok>(raw, li, i, -std::numeric_limits<double>::infinity()));
          }
          else if (c == L'∞')
          {
            i++;
            tokens->add(std::make_shared<NumTok>(raw, li, i, std::numeric_limits<double>::infinity()));
          }
          else if (c >= L'0' && c <= L'9' || c == L'¯' || c == L'.' && next >= L'0' && next <= L'9')
          {
            bool negative = c == L'¯';
            if (negative)
            {
                i++;
            }
            int si = i;
            bool hasPoint = false;
            while (i < len)
            {
              c = raw[i];
              if (hasPoint)
              {
                if (c < L'0' || c>L'9')
                {
                    break;
                }
              }
              else if (c < L'0' || c>L'9')
              {
                if (c == L'.')
                {
                    hasPoint = true;
                }
                else
                {
                    break;
                }
              }
              i++;
            }
            double f = std::stod(raw.substr(si, i - si));
            if (negative)
            {
                f = -f;
            }
            if (i < len)
            {
              c = raw[i];
              bool hasE = c == L'e' | c == L'E';
              if (hasE && i + 1 == len)
              {
                  throw SyntaxError(L"unfinished number");
              }
              bool hasExp = hasE && !validNameStart(raw[i + 1]);
              if (hasExp)
              {
                i++;
                c = raw[i];
                bool negExp = c == L'¯';
                if (negExp)
                {
                    i++;
                }
                si = i;
                while (i < len)
                {
                  c = raw[i];
                  if (c < L'0' || c > L'9')
                  {
                      break;
                  }
                  i++;
                }
                int exp = std::stoi(raw.substr(si, i - si));
                if (negExp)
                {
                    exp = -exp;
                }
                f *= std::pow(10, exp);
              }
              if (i < len && raw[i] == L'L' && (i + 1 == len || !validNameMid(raw[i + 1])))
              {
                if (hasExp || hasPoint)
                {
                  if (hasExp)
                  {
                      throw SyntaxError(L"biginteger literal with exponent");
                  }
                  throw SyntaxError(L"biginteger literal with decimal part");
                }
                i++;
                std::shared_ptr<BigInteger> big = std::make_shared<BigInteger>(raw.substr(si, (i - 1) - si));
                if (negative)
                {
                    big = big->negate();
                }
                tokens->add(std::make_shared<BigTok>(raw, li, i, std::make_shared<APL::types::BigValue>(big)));
              }
              else
              {
                  tokens->add(std::make_shared<NumTok>(raw, li, i, f));
              }
            }
            else
            {
                tokens->add(std::make_shared<NumTok>(raw, li, i, f));
            }
          }
          else if (ops.find(cS) != std::string::npos)
          {
            tokens->add(std::make_shared<OpTok>(raw, i, i + 1, cS));
            i++;
          }
          else if (c == L'←')
          {
            tokens->add(std::make_shared<SetTok>(raw, i, i + 1));
            i++;
          }
          else if (c == L'`')
          {
            if (tokens->annoyingBacktickPos)
            {
                throw SyntaxError(L"` after `");
            }
            tokens->annoyingBacktickPos = i;
            i++;
          }
          else if (c == L':')
          {
            if (next == L':')
            {
              tokens->add(std::make_shared<DColonTok>(raw, i, i + 2));
              i++;
            }
            else
            {
                tokens->add(std::make_shared<ColonTok>(raw, i, i + 1));
            }
            i++;
          }
          else if (c == L'\'')
          {
            std::shared_ptr<StringBuilder> str = std::make_shared<StringBuilder>();
            i++;
            if (i >= len)
            {
                throw SyntaxError(L"unfinished string");
            }
            while (true)
            {
              if (raw[i] == L'\'')
              {
                if (i + 1 < len && raw[i + 1] == L'\'')
                {
                  str->append(L"'");
                  i++;
                }
                else
                {
                    break;
                }
              }
              else
              {
                  str->append(raw[i]);
              }
              i++;
              if (i >= len)
              {
                  throw SyntaxError(L"unfinished string");
              }
            }
            i++;
            tokens->add(std::make_shared<ChrTok>(raw, li, i, str->toString()));
          }
          else if (c == L'"')
          {
            std::shared_ptr<StringBuilder> str = std::make_shared<StringBuilder>();
            i++;
            if (i == len)
            {
                throw SyntaxError(L"unfinished string");
            }
            while (raw[i] != L'"')
            {
              if (raw[i] == L'\\')
              {
                i++;
                SyntaxError::must(i < len, L"unfinished string");
                wchar_t esc = raw[i];
                switch (esc)
                {
                  case L'n':
                      str->append(L'\n');
                      break;
                  case L'r':
                      str->append(L'\r');
                      break;
                  case L'"':
                      str->append(L'\"');
                      break;
                  case L'\'':
                      str->append(L'\'');
                      break;
                  case L'\\':
                      str->append(L'\\');
                      break;
                  case L't':
                      str->append(L'\t');
                      break;
                  case L'x':
                  {
                    SyntaxError::must(i + 2 < len, L"unfinished string");
                    int num = std::stoi(raw.substr(i + 1, (i + 3) - (i + 1)), nullptr, 16);
                    str->append(Character::toChars(num));
                    i += 2;
                    break;
                  }
                  case L'u':
                  {
                    SyntaxError::must(i + 4 < len, L"unfinished string");
                    int num = std::stoi(raw.substr(i + 1, (i + 5) - (i + 1)), nullptr, 16);
                    str->append(Character::toChars(num));
                    i += 4;
                    break;
                  }
                  default:
                      throw SyntaxError(StringHelper::wstring_to_string(L"invalid escape character " + StringHelper::toString(esc)));
                }
              }
              else
              {
                str->append(raw[i]);
              }
              i++;
              SyntaxError::must(i < len, L"unfinished string");
            }
            i++;
            tokens->add(std::make_shared<StrTok>(raw, li, i, str->toString()));
          }
          else if (c == L'\n' || c == L'⋄' || c == L'\r' || c == L';')
          {
            if (c == L'⋄' && pointless)
            {
                tokens->add(std::make_shared<DiamondTok>(raw, i));
            }
            if (c == L'⋄' || c == L'\n')
            {
                expr->hasDmd = true;
            }
            if (c == L';')
            {
                tokens->add(std::make_shared<SemiTok>(raw, i, i + 1));
            }

            if (tokens->size() > 0)
            {
              lines.push_back(std::make_shared<Line>(raw, li));
            }
            i++;
          }
          else if (c == L'⍝')
          {
            i++;
            while (i < len && raw[i] != L'\n')
            {
                i++;
            }
            if (pointless)
            {
                tokens->add(std::make_shared<CommentTok>(raw, li, i));
            }
          }
          else if (c == L'#')
          {
            tokens->add(std::make_shared<ScopeTok>(raw, i, i + 1));
            i++;
          }
          else if (c == L' ' || c == L'\t')
          {
              i++;
          }
          else
          {
            if (pointless)
            {
                tokens->add(std::make_shared<ErrTok>(raw, i, i + 1));
            }
            else
            {
              std::string hex = Integer::toHexString(c);

              while (hex.length() < 4)
              {
                //noinspection StringConcatenationInLoop \\ shut UUuuppp
                hex = L"0" + hex;
              }
              throw SyntaxError(StringHelper::wstring_to_string(L"unknown token `" + StringHelper::toString(c) + L"` (\\u" + hex + L")"));
            }
            i++;
          }
          //if (c != ' ') {
          //  printdbg("> "+(c+"").replace("\n","\\n"));
          //  printdbg("curr: "+join(levels, "|"));
          //}
          assert(li < i); // error if nothing changed!
        }
        catch (const std::runtime_error &e)
        {
          // System.out.println("BAD");
          // e.printStackTrace();
          if (!pointless)
          {
              throw e;
          }
          if (li == i)
          {
              i = li + 1; // lazy exit out of infinite loops
          }
          tokens->add(std::make_shared<ErrTok>(raw, li, i));
        }
      }
      if (levels.size() != 1)
      {
        if (!pointless)
        {
            throw SyntaxError(L"error matching parentheses"); // or too many
        }
        // else, attempt to recover
        while (levels.size() > 1)
        {
          std::shared_ptr<Block> closed = levels.pop_back();

          auto APL::tokenizer::types::LineTokens = std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>>();
          for (auto ta : closed->a)
          {
              APL::tokenizer::types::LineTokens.push_back(ta->tok());
          }
          std::shared_ptr<Token> r;
          switch (closed->b)
          {
            case L')':
              r = std::make_shared<ParenTok>(raw, closed->pos, len, APL::tokenizer::types::LineTokens, closed->hasDmd);
              break;
            case L'}':
              r = std::make_shared<DfnTok>(raw, closed->pos, len, APL::tokenizer::types::LineTokens);
              break;
            case L']':
              r = std::make_shared<APL::tokenizer::types::BracketTok>(raw, closed->pos, len, APL::tokenizer::types::LineTokens, closed->hasDmd);
              break;
            default:
              throw Error(StringHelper::wstring_to_string(L"this should really not happen " + StringHelper::toString(closed->b)));
          }
          auto lines = levels[levels.size() - 1]->a;
          std::shared_ptr<Line> tokens = lines[lines.size() - 1];
          tokens->add(r);
        }
      }
      auto lines = levels[0]->a;
      if (lines.size() > 0 && lines[lines.size() - 1]->size() == 0)
      {
          lines.pop_back(); // no trailing empties!!
      }
      auto expressions = std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>>();
      for (auto line : lines)
      {
        expressions.push_back(line->tok());
      }
      return std::make_shared<APL::tokenizer::types::BasicLines>(raw, 0, len, expressions);
    }
}
