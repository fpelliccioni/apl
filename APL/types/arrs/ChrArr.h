#pragma once

#include <APL/Main.h>
#include <APL/errors/DomainError.h>
#include <APL/types/Arr.h>
#include <APL/types/Value.h>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::arrs {

// using namespace APL::types;

class ChrArr : public Arr
{
public:
    std::string s;

    ChrArr(std::string const& s);
    ChrArr(std::string const& s, std::vector<int> &sh);
    ChrArr(std::vector<wchar_t> &arr, std::vector<int> &sh);
    ChrArr(std::vector<wchar_t> &arr);

    std::vector<int> asIntArrClone() override;

    int asInt() override;

    std::shared_ptr<APL::types::Value> get(int i) override;

    std::shared_ptr<APL::types::Value> first() override;
    std::string asString() override;

    std::shared_ptr<APL::types::Value> prototype() override;
    std::shared_ptr<APL::types::Value> safePrototype() override;

    std::shared_ptr<APL::types::Value> ofShape(std::vector<int> &sh) override;

    std::shared_ptr<APL::types::Value> squeeze() override;

    virtual int hashCode();

protected:
    std::shared_ptr<ChrArr> shared_from_this() {
        return std::static_pointer_cast<ChrArr>(Arr::shared_from_this());
    }
};

}
