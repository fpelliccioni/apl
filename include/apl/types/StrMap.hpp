#pragma once

struct StrMap : APLMap {
    std::unordered_map<std::string, Obj> vals;
    // final Scope sc;

    StrMap(Scope sc)
        : vals(sc.vars)
        // , sc(sc)
    {}


    StrMap(std::unordered_map<std::string, Obj> vals)
        : vals(vals)
    {}

    // StrMap() {
    //   this.vals = new std::unordered_map<>();
    //   // this.sc = null;
    // }

    // NOTE: Commented in the original code
    // StrMap(Scope sc, std::unordered_map<std::string, Obj> vals) {
    //   this.sc = sc;
    //   this.vals = vals;
    // }


    virtual Obj getRaw(Value k) override {
        return getRaw(k.asString());
    }

    virtual Obj getRaw(std::string k) override {
        Obj v = vals.get(k);
        if (v == null) return Null.NULL;
        return v;
    }

    virtual void set(Value k, Obj v) override {
        if (v == Null.NULL) vals.remove(k.asString());
        else vals.put(k.asString(), v);
    }

    void setStr(std::string k, Obj v) {
        if (v == Null.NULL) vals.remove(k);
        else vals.put(k, v);
    }

    virtual Arr allValues() override {
        auto items = new std::vector<Value>();
        for (Obj o : vals.values()) {
            if (o instanceof Value) items.add((Value) o);
        }
        return Arr.create(items);
    }

    virtual Arr allKeys() override {
        auto items = new std::vector<Value>();
        for (std::string o : vals.keySet()) {
            items.add(Main.toAPL(o));
        }
        return Arr.create(items);
    }

    virtual override Arr kvPair() {
        std::vector<Value> ks = new std::vector<>();
        std::vector<Value> vs = new std::vector<>();
        vals.forEach((k, v) -> {
            if (v instanceof Value) {
                ks.add(Main.toAPL(k));
                vs.add((Value) v);
            }
        });
        return new HArr(new Value[]{new HArr(ks), Arr.create(vs)});
    }

    virtual int size() override {
        return vals.size();
    }

    virtual bool equals(Obj o) override {
        return o instanceof StrMap && vals.equals(((StrMap) o).vals);
    }

    virtual std::string toString() override {
        std::string res = "(";
        vals.forEach((key, value) -> {
            if (res.length() != 1) res.append(" ⋄ ");
            res.append(key).append(":").append(value);
        });
        return res + ")";
    }
};
