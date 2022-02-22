#pragma once

// #include <optional>
// #include <vector>

// #include <apl/errors/DomainError.hpp>
// #include <apl/types/Obj.hpp>
// #include <apl/Helpers.hpp>

#include <apl/types/arrs/DoubleArr.hpp>
#include <apl/types/Value.hpp>

Value const* Value::squeeze() {
    if (ia == 0) return this;
    Value* f = get(0);

    if (instanceof<Num>(f)) {
        std::optional<std::vector<double>> ds(ia);
        for (int i = 0; i < ia; i++) {
            if (instanceof<Num>(get(i))) {
                (*ds)[i] = get(i)->asDouble();
            } else {
                ds = std::nullopt;
                break;
            }
        }
        if (ds) return new DoubleArr(ds, shape);
    }

    if (instanceof<Char>(f)) {
        std::string s;
        for (int i = 0; i < ia; i++) {
            if (instanceof<Char>(get(i))) s.append(((Char) get(i)).chr);
            else {
                s = nullptr;
                break;
            }
        }
        if (s != nullptr) return new ChrArr(s.toString(), shape);
    }

    bool anyBetter = false;
    std::vector<Value*> optimized = new Value*[ia];
    std::vector<Value*> values = values();
    for (int i = 0, valuesLength = values.size(); i < valuesLength; i++) {
        Value* v = values[i];
        Value* vo = v.squeeze();
        if (vo != v) anyBetter = true;
        optimized[i] = vo;
    }
    if (anyBetter) return new HArr(optimized, shape);
    return this;
}

Value* Value::cut(int s, int len, std::vector<int> sh) {
    if (len==1) {
        Value* v = get(s);
        return !Config::enclosePrimitives && instanceof<Primitive>(v) ? v : new Rank0Arr(v);
    }
    if (quickDoubleArr()) {
        std::vector<double> w = asDoubleArr();
        std::vector<double> r(len);
        System.arraycopy(w, s, r, 0, len);
        return new DoubleArr(r, sh);
    }
    std::vector<Value*> w = values();
    std::vector<Value*> r = new Value*[len];
    System.arraycopy(w, s, r, 0, len);
    return new HArr(r, sh);
}

