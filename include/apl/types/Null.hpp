#pragma once

#include <vector>

#include <apl/types/Primitive.hpp>

struct Null : Primitive {
    // static Null const* NULL_ = new Null();
    static Null const* NULL_;

    virtual std::string toString() const override {
        return "⎕NULL";
    }

    virtual Type type() const override {
        return Type::nul;
    }

    virtual Value const* ofShape(std::vector<int> sh) const override;

    // virtual int hashCode() override {
    //     return 387678968; // random yay
    // }
private:
    Null() = default;
};

#include <apl/types/arrs/SingleItemArr.hpp>

/*virtual*/ Value const* ofShape(std::vector<int> sh) const /*override*/ {
    return SingleItemArr::maybe(this, sh);
}

static Null const* Null::NULL_ = new Null();