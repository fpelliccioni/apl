#pragma once

#include <apl/errors/APLError.hpp>
#include <apl/types/Tokenable.hpp>

template <Tokenable T>
struct DomainError : APLError<T> {
    // using APLError<T>::APLError;
    DomainError(std::string msg)
       : APLError<T>(msg)
    {}

    DomainError(std::string msg, T blame)
       : APLError<T>(msg, blame)
    {}
};


// package APL.errors;

// import APL.types.*;

// public class DomainError extends APLError {
//   public DomainError(std::string s) {
//     super(s);
//   }
//   public DomainError(std::string s, Tokenable fun) {
//     super(s, fun);
//   }
//   public DomainError(std::string s, Callable fun, Tokenable cause) {
//     super(s, fun, cause);
//   }
// }

