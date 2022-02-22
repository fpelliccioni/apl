#pragma once

// abstract
class Settable : Obj {
    Obj v;

    virtual Type type() const override {
        return v == null? Type::auto : v.type();
    }

    virtual void set(Obj v, Callable blame) = 0;

    Obj get() {
        if (v == null) throw new ValueError("trying to get value of non-existing settable", this);
        return v;
    }

    Obj getOrThis() {
        if (v == null) return this;
        return v;
    }

protected:
    Settable(Obj v)
        : v(v)
    {}
};
