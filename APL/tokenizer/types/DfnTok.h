#pragma once

#include <APL/tokenizer/types/LineTok.h>
#include <APL/tokenizer/types/TokArr.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types {

    // using List = java::util::List;

    class DfnTok : public TokArr<std::shared_ptr<APL::tokenizer::types::LineTok>>
    {

  public:
      DfnTok(std::string const& line, int spos, int epos, std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>> &tokens);

      std::string toRepr() override;

    protected:
        std::shared_ptr<DfnTok> shared_from_this() {
            return std::static_pointer_cast<DfnTok>(TokArr::shared_from_this());
        }
    };
}
