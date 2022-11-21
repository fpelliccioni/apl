#pragma once

#include <APL/errors/DomainError.h>
#include <APL/tokenizer/types/LineTok.h>
#include <APL/tokenizer/types/TokArr.h>
#include <string>
#include <vector>
#include <memory>
#include <helpers/tangible_stringbuilder.h>

namespace APL::tokenizer::types {


    // using List = java::util::List;

class BracketTok : public TokArr<std::shared_ptr<APL::tokenizer::types::LineTok>> {
public:
    const bool array;

    BracketTok(std::string const& line, int spos, int epos, std::vector<std::shared_ptr<APL::tokenizer::types::LineTok>> &tokens, bool hasDmd);

    std::string toRepr() override;

    virtual std::string toString();

protected:
    std::shared_ptr<BracketTok> shared_from_this()
    {
        return std::static_pointer_cast<BracketTok>(TokArr::shared_from_this());
    }
};

}
