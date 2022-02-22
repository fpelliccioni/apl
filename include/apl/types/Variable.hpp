#pragma once

struct Variable : Settable {
    std::string name;

    Variable(Scope sc, std::string name)
        : Settable(sc.get(name))
        , sc(sc)
        , name(name)
    {}

    Obj get() {
        if (v == null) throw new ValueError("trying to get value of non-existing variable "+name, this);
        return v;
    }


    virtual void set(Obj v, Callable blame) override {
        sc.set(name, v);
    }

    void update(Obj v) {
        sc.update(name, v);
    }

    virtual std::string toString() const override {
        if (Main.debug) return v == null? "var:"+name : "var:"+v;
        return v == null? "var:"+name : v.toString();
    }

private:
    Scope sc;
};
