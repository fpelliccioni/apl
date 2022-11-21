#pragma once

#include <APL/types/Tokenable.h>
#include <string>
#include <cassert>
#include <memory>

namespace APL::tokenizer
{

    using Tokenable = APL::types::Tokenable;

    class Token : public std::enable_shared_from_this<Token>, public Tokenable
    {
  public:
      const std::string raw;
      const int spos; // incl
      int epos = 0; // excl
      static constexpr int EPOS_DEF = -12345;
  protected:
      Token(std::string const& raw, int spos);

  public:
      Token(std::string const& raw, int spos, int epos);

  protected:
      virtual void end(int i);

  public:
      std::shared_ptr<Token> getToken() override;
      virtual std::string toTree(std::string const& p);
      virtual std::string toRepr() = 0;

      virtual std::string source();
    };
}
