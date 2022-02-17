#pragma onde

// #include <apl/types/obj.hpp>
#include <apl/types/obj_fwd.hpp>

struct variable {
    // std::optional<obj> v;
    // obj v;
    Type type() const;
    obj getOrThis() const;
    bool hasValue() const;
    std::string to_string() const;
};

// package APL.types;

// import APL.*;
// import APL.errors.ValueError;

// public class Variable extends Settable {

//   private final Scope sc;
//   public final String name;

//   public Variable(Scope sc, String name) {
//     super(sc.get(name));
//     this.sc = sc;
//     this.name = name;
//   }

//   public Obj get() {
//     if (v == null) throw new ValueError("trying to get value of non-existing variable "+name, this);
//     return v;
//   }

//   @Override
//   public void set(Obj v, Callable blame) {
//     sc.set(name, v);
//   }
//   public void update(Obj v) {
//     sc.update(name, v);
//   }

//   @Override
//   public String toString() {
//     if (Main.debug) return v == null? "var:"+name : "var:"+v;
//     return v == null? "var:"+name : v.toString();
//   }
// }