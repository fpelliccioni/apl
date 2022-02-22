#pragma once

// abstract
struct APLMap : Primitive {
    MapPointer get(Value k) {
        return new MapPointer(this, k);
    }

    virtual Obj getRaw(Value k) = 0;

    Obj getRaw(std::string k) {
        return getRaw(Main.toAPL(k));
    }

    MapPointer get(std::string k) {
        return get(Main.toAPL(k));
    }

    virtual void set(Value k, Obj v) = 0;
    virtual Arr allValues() = 0;
    virtual Arr allKeys() = 0;
    virtual Arr kvPair() = 0;
    virtual int size() = 0;

    // static
    struct MapPointer : Settable {
        MapPointer(APLMap map, Value k)
            : Settable(map.getRaw(k))
            , map(map)
            , k(k)
        {}

        virtual void set(Obj v, Callable blame) override {
            map.set(k, v);
        }

        virtual std::string toString() override {
            if (Main.debug) return v == null? "map@"+k : "ptr@"+k+":"+v;
            return v == null? "map@"+k : v.toString();
        }
    private:
        APLMap map;
        Value k;
    };

    virtual Value const* ofShape(std::vector<int> sh) const override {
        return SingleItemArr::maybe(this, sh);
    }
};
