#pragma once

#include <apl/types/Value.hpp>

// abstract
struct Primitive : Value {
    Primitive()
        : Value(SHAPE, 1, 0)
    {}

    virtual Value const* get(int i) const override {
        return this;
    }

    Value const* first() const override
    {
        return this;
    }

    virtual std::vector<int> asIntArrClone() const override {
        //TODO
        // throw new DomainError("Using " + this.oneliner() + " as integer array", this);
        throw "Using ... as integer array";
    }

    virtual std::vector<int> asIntVec() const override {
        //TODO
        // throw new DomainError("Using " + this.oneliner() + " as integer vector", this);
        throw "Using ... as integer vector";
    }

    virtual int asInt() const override {
        //TODO
        // throw new DomainError("Using " + this.oneliner() + " as integer", this);
        throw "Using ... as integer";
    }

    virtual std::string asString() const override {
        //TODO
        // throw new DomainError("Using " + this.oneliner() + " as string", this);
        throw "Using ... as string";
    }

    Value const* prototype() final {
        Value const* v = safePrototype();
        if (v == nullptr) {
            //TODO
            // throw new DomainError("Getting prototype of "+this, this);
            throw "Getting prototype of ...";
        }
        return v;
    }

    Value const* safePrototype() override {
        return nullptr;
    }

    virtual Value const* squeeze() const override { // primitives are already pretty squeezed
        return this;
    }
private:
    static const std::vector<int> SHAPE;    // = new int[0];
};
