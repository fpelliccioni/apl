#pragma once

// abstract
struct SimpleMap : APLMap {
    virtual Obj getRaw(Value k) override {
        return getv(k.asString());
    }

    virtual Obj getv(std::string s) = 0;
    virtual void setv(std::string s, Obj v) = 0;

    virtual void set(Value k, Obj v) override {
        setv(k.asString(), v);
    }

    virtual Arr allValues() override {
        throw new SyntaxError("getting list of values of "+name());
    }

    virtual Arr allKeys() override {
        throw new SyntaxError("getting list of keys of "+name());
    }

    virtual Arr kvPair() override {
        throw new SyntaxError("getting entries of "+name());
    }

    virtual int size() override {
        throw new SyntaxError("getting size of "+name());
    }
};
