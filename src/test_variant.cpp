// // ------------------------------------------------------------------------------------------------
// // Ejemplo 2
// // ------------------------------------------------------------------------------------------------

// #include <variant>
// #include <type_traits>

// struct A {
//     int something = 1;
// };

// struct B {
//     int something = 2;
// };

// struct Obj;

// struct C {
//     int something = 3;
//     Obj const* x_;

//     // C() = default;

//     constexpr
//     C(Obj const& x)
//         : x_(nullptr)
//         // : x(x)
//     {
//         x_ = std::addressof(x);
//     }
// };

// using Obj_ = std::variant<A, B, C>;
// struct Obj : Obj_ {
//     constexpr
//     Obj() = default;

//     template <typename T>
//     constexpr
//     Obj(T&& t) noexcept
//         requires(! std::is_same_v<Obj, T>)
//         : obj_(t)
//     {}
// };

// constexpr
// auto something(Obj x) {
//     return std::visit([](auto&& arg) {
//         return arg.something;
//     }, x);
// }


// int main() {
//     constexpr Obj x;
//     static_assert(something(x) == 1);

//     constexpr Obj y = B{};
//     static_assert(something(y) == 2);

//     constexpr Obj z = C{x};
//     static_assert(something(z) == 3);

// }

// ------------------------------------------------------------------------------------------------
// Ejemplo 1
// ------------------------------------------------------------------------------------------------

// #include <variant>

// struct A {
//     int something = 1;
// };

// struct B {
//     int something = 2;
// };

// using Obj = std::variant<A, B>;

// constexpr
// auto something(Obj x) {
//     return std::visit([](auto&& arg) {
//         return arg.something;
//     }, x);
// }

// int main() {
//     constexpr Obj x;
//     static_assert(something(x) == 1);

//     constexpr Obj y = B{};
//     static_assert(something(y) == 2);
// }



// ------------------------------------------------------------------------------------------------
// Ejemplo OOP 2
// ------------------------------------------------------------------------------------------------

#include <cassert>

struct Obj {
    constexpr virtual ~Obj() {}
    constexpr virtual int something() const = 0;
};

struct A : Obj{
    constexpr virtual int something() const override {
        return 1;
    }
};

struct B : Obj {
    constexpr virtual int something() const override {
        return 2;
    }
};

struct C : Obj {
    Obj* obj;

    C(Obj* obj)
        : obj(obj)
    {}

    virtual int something() const override {
        return 3 + obj->something();
    }
};

int main() {
    Obj* x = new A{};
    // assert(x->something() == 1);
    // static_assert(x.something() == 1);

    Obj* y = new B{};
    assert(y->something() == 2);
    // static_assert(something(y) == 2);

    Obj* z = new C{x};
    assert(z->something() == 4);
}




// // ------------------------------------------------------------------------------------------------
// // Ejemplo OOP 1
// // ------------------------------------------------------------------------------------------------

// #include <cassert>

// struct Obj {
//     virtual ~Obj() {}
//     virtual int something() const = 0;
// };

// struct A : Obj{
//     virtual int something() const override {
//         return 1;
//     }
// };

// struct B : Obj {
//     virtual int something() const override {
//         return 2;
//     }
// };

// struct C : Obj {
//     Obj* obj;

//     C(Obj* obj)
//         : obj(obj)
//     {}

//     virtual int something() const override {
//         return 3 + obj->something();
//     }
// };

// int main() {
//     Obj* x = new A{};
//     // assert(x->something() == 1);
//     // static_assert(x.something() == 1);

//     Obj* y = new B{};
//     assert(y->something() == 2);
//     // static_assert(something(y) == 2);

//     Obj* z = new C{x};
//     assert(z->something() == 4);
// }


