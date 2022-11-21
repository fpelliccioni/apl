#pragma once

#include <APL/tokenizer/Tokenizer.h>
#include <APL/types/arrs/HArr.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL {

    // using namespace APL::errors;
    // using namespace APL::types;


    class Sys : public std::enable_shared_from_this<Sys>
    {
  public:
      std::shared_ptr<Scope> gsc; // global/top-level scope
      std::shared_ptr<Scope> csc; // current scope in which things happen
      bool ln = false;
      std::string cd;

      Sys();

      virtual void ucmd(std::string const& cr);

      static std::shared_ptr<Path> path(std::string const& path, std::string const& s);

      virtual std::vector<std::string> split(std::shared_ptr<Path> p);
      virtual std::shared_ptr<APL::types::Obj> execFile(std::shared_ptr<Path> path, std::shared_ptr<Scope> sc);

      virtual void line(std::string const& s);

      virtual void lineCatch(std::string const& s);
      virtual void report(std::runtime_error t);


      virtual void println(std::string const& s) = 0; // may contain newlines
      virtual void print(std::string const& s) = 0;
      virtual void colorprint(std::string const& s, int col);
      virtual void off(int code) = 0;


      virtual void println(std::shared_ptr<APL::types::Obj> v);

      virtual std::string input() = 0;
    };

}
