#pragma once

#include <optional>
#include <vector>

#include <apl/errors/DomainError.hpp>
#include <apl/types/Obj.hpp>
#include <apl/Helpers.hpp>

// #include <apl/types/arrs/EmptyArr.hpp>
static const std::vector<int> NOINTS;       //This is copied from apl/types/arrs/EmptyArr.hpp

// include/apl/types/arrs/DoubleArr.hpp

class DoubleArr;

/*abstract*/
struct Value : Obj { //implements Iterable<Value> {
    std::vector<int> shape;
    int rank;
    int ia; // item amount

    Value(std::vector<int> shape)
        : shape(shape)
        , rank(shape.size())
    {
        int tia = 1;
        for (int i = 0; i < rank; i++) tia*= shape[i];
        ia = tia;
    }

    Value(std::vector<int> shape, int ia, int rank)
        : shape(shape)
        , ia(ia)
        , rank(rank)
    {}

    virtual std::vector<int> asIntVec() const { // succeeds on rank ≤ 1
        if (rank > 1) {
            //TODO
            // throw new DomainError("Using rank " + std::to_string(rank) + " array as an integer vector", this);
            throw "Using rank " + std::to_string(rank) + " array as an integer vector";
        }
        return asIntArr();
    }

    virtual std::vector<int> asIntArrClone() const = 0;

    std::vector<int> asIntArr() const {
        return asIntArrClone();
    }

    virtual int asInt() const = 0;

    bool scalar() {
        return rank == 0;
    }

    virtual Value const* first() const {
        return get(0);
    }

    virtual Value const* get(int i) const = 0; // WARNING: UNSAFE; doesn't need to throw for out-of-bounds

    int compareTo(Value const* r) const {
        Value const* l = this;

        bool rA = instanceof<Arr*>(r);
        bool lA = instanceof<Arr*>(l);

        // instanceof<Num*>(l)


        // if (instanceof<Num*>(l)       && instanceof<Num*>(r)      ) return ((Num) l).compareTo((Num) r);
        // if (l instanceof Char         && r instanceof Char        ) return ((Char) l).compareTo((Char) r);

        if (auto [valid, cmp] = compareToAs<Num*, Num*>(l, r); valid) {
            return cmp;
        }

        if (auto [valid, cmp] = compareToAs<Char*, Char*>(l, r); valid) {
            return cmp;
        }

        // if (l instanceof  Num         && (r instanceof Char || rA)) return -1;
        // if ((l instanceof Char || lA) && r instanceof Num         ) return 1;
        // if (l instanceof BigValue     && r instanceof BigValue    ) return ((BigValue) l).i.compareTo(((BigValue) r).i);


        if (!lA && !rA) {
            //TODO
            // throw new DomainError("Failed to compare " + l->toString() +" and " + r->toString(), r);
            throw "Failed to compare " + l->toString() +" and " + r->toString();
        }
        if (!lA) return -1;
        if (!rA) return  1;

        if (l->rank != r->rank) {
            //TODO
            // throw new RankError("Expected ranks to be equal for compared elements", r);
            throw "Expected ranks to be equal for compared elements";
        }

        if (l->rank > 1) {
            //TODO
            // throw new DomainError("Expected rank of compared array to be ≤ 2", l);
            throw "Expected rank of compared array to be ≤ 2";
        }

        int min = std::min(l->ia, r->ia);
        for (int i = 0; i < min; i++) {
            int cr = l->get(i)->compareTo(r->get(i));
            if (cr != 0) return cr;
        }
        return compare(l->ia, r->ia);
    }


    virtual std::string asString() const = 0;

    // Integer[] gradeUp() {
    std::vector<int> gradeUp() {
        if (rank != 1) {
            //TODO
            // throw new DomainError("grading rank ≠ 1", this);
            throw "grading rank ≠ 1";
        }
        std::vector<int> na(ia);

        for (int i = 0; i < na.size(); i++) {
            na[i] = i;
        }
        // Arrays.sort(na, (a, b) -> get(a).compareTo(get(b)));
        std::sort(std::begin(na), std::end(na), [this](auto a, auto b) { return compare(get(a), get(b)); });
        return na;
    }

    // Integer[] gradeDown() {
    std::vector<int> gradeDown() {
        if (rank != 1) {
            //TODO
            // throw new DomainError("grading rank ≠ 1", this);
            throw "grading rank ≠ 1";
        }

        std::vector<int> na(ia);

        for (int i = 0; i < na.size(); i++) {
            na[i] = i;
        }
        // Arrays.sort(na, (a, b) -> get(b).compareTo(get(a)));
        std::sort(std::begin(na), std::end(na), [this](auto a, auto b) { return compare(get(b), get(a)); });
        return na;
    }

    std::vector<int> eraseDim(int place) {
        // std::vector<int> res(rank - 1);
        std::vector<int> res;
        res.reserve(rank - 1);
        res.insert(std::begin(res), std::begin(shape), std::begin(shape) + place);
        res.insert(std::end(res), std::begin(shape) + place + 1, std::end(shape));

        // arraycopy(Object src, int srcPos, Object dest, int destPos, int length)
        // System.arraycopy(shape, 0, res, 0, place);
        // System.arraycopy(shape, place+1, res, place, rank-1-place);
        return res;
    }

    virtual Type type() const override {
        return Type::array;
    }

    virtual Value const* prototype() = 0; // what to append to this array
    virtual Value const* safePrototype() = 0;

    std::string oneliner(std::vector<int> where) const {
        return toString();
    }

    std::string oneliner() const {
    //    return oneliner(EmptyArr::NOINTS);
       return oneliner(NOINTS);
    }

    std::vector<Value const*> values() const {
        return valuesCopy();
    }

    virtual std::vector<Value const*> valuesCopy() const {
        std::vector<Value const*> vs(ia);
        for (int i = 0; i < ia; i++) {
            vs[i] = get(i);
        }
        return vs;
    }

    //TODO: implement this
    // virtual Iterator<Value*> iterator() override {
    //     return new ValueIterator();
    // }


    Value const* ind(std::vector<std::vector<double>> ind, int id, int IO) {
        if (ind.size() != rank) {
            //TODO
            // throw new RankError("array rank was "+rank+", tried to get item at rank "+ind.size(), this);
            throw "array rank was ..., tried to get item at rank";
        }
        int x = 0;
        for (int i = 0; i < rank; i++) {
            double c = ind[i][id];
            if (c < IO) {
                //TODO
                // throw new DomainError("Tried to access item at position " + c, this);
                throw "Tried to access item at position ";
            }
            if (c >= shape[i]+IO) {
                //TODO
                // throw new DomainError("Tried to access item at position " + c + " while max was " + shape[i], this);
                throw "Tried to access item at position ... while max was ";
            }
            x+= c-IO;
            if (i != rank-1) x*= shape[i+1];
        }
        return get(x);
    }

    //TODO: implement this
    // class ValueIterator implements Iterator<Value*> {
    //     int c = 0;
    //     @Override
    //     bool hasNext() {
    //         return c < ia;
    //     }

    //     @Override
    //     Value* next() {
    //         return get(c++);
    //     }
    // }

    struct ValueIterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = Value const*;
        using pointer           = value_type*;
        using reference         = Value const*;

        explicit ValueIterator(Value const* parent, int c)
            : parent_(parent)
            , c_(c)
        {}

        reference operator*() const {
            return parent_->get(c_);
        }

        // pointer operator->() {
        //     return m_ptr;
        // }

        ValueIterator& operator++() {
            ++c_;
            return *this;
        }

        ValueIterator operator++(int) {
            ValueIterator tmp = *this;
            ++(*this); return
            tmp;
        }

        friend bool operator==(ValueIterator const& a, ValueIterator const& b) { return a.c_ == b.c_; };
        friend bool operator!=(ValueIterator const& a, ValueIterator const& b) { return a.c_ != b.c_; };

    private:
        // pointer m_ptr;
        Value const* parent_;
        int c_;
    };

    ValueIterator begin() const { return ValueIterator(this, 0); }
    ValueIterator end()   const { return ValueIterator(this, ia); }

    Value const* at(std::vector<int> pos, int IO) {
        if (pos.size() != rank) {
            //TODO
            // throw new RankError("array rank was "+rank+", tried to get item at rank "+pos.size(), this);
            throw "array rank was ..., tried to get item at rank ";
        }
        int x = 0;
        for (int i = 0; i < rank; i++) {
            if (pos[i] < IO) {
                //TODO
                // throw new DomainError("Tried to access item at position "+pos[i], this);
                throw "Tried to access item at position ";
            }
            if (pos[i] >= shape[i]+IO) {
                //TODO
                // throw new DomainError("Tried to access item at position "+pos[i]+" while max was "+(shape[i]+IO-1), this);
                throw "Tried to access item at position ... while max was ";
            }
            x+= pos[i]-IO;
            if (i != rank-1) x*= shape[i+1];
        }
        return get(x);
    }

    Value const* at(std::vector<int> pos, Value* def) { // 0-indexed
        int x = 0;
        for (int i = 0; i < rank; i++) {
            if (pos[i] < 0 || pos[i] >= shape[i]) return def;
            x+= pos[i];
            if (i != rank-1) x*= shape[i+1];
        }
        return get(x);
    }

    Value const* simpleAt(std::vector<int> pos) const {
        int x = 0;
        for (int i = 0; i < rank; i++) {
            x+= pos[i];
            if (i != rank-1) x*= shape[i+1];
        }
        return get(x);
    }

    virtual Value const* ofShape(std::vector<int> sh) const = 0; // don't call with ×/sh ≠ ×/shape!

    //TODO
    // double sum() {
    //     double res = 0;
    //     for (Value* v : *this) {
    //         res+= v.asDouble();
    //     }
    //     return res;
    // }

    virtual std::vector<double> asDoubleArr() const { // warning: also succeeds on a primitive number; don't modify
        std::vector<double> res(ia);
        int i = 0;
        for (Value const* c : values()) {
            res[i++] = c->asDouble();
        }
        return res;
    }

    // std::vector<double> asDoubleArrClone() {
    //     return asDoubleArr().clone();
    // }

    double asDouble() const {
        //TODO
        // throw new DomainError("Using "+this.humanType(true)+" as a number", this);
        throw "Using ... as a number";
    }

    virtual bool quickDoubleArr() const { // if true, asDoubleArr must succeed; warning: also succeeds on a primitive number
        return false;
    }

    virtual Value const* squeeze() const;
    Value* cut(int s, int len, std::vector<int> sh);
};
