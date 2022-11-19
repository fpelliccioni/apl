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

namespace APL
{

	using namespace APL::errors;
	using namespace APL::types;


	class Sys : public std::enable_shared_from_this<Sys>
	{
  public:
	  std::shared_ptr<Scope> gsc; // global/top-level scope
	  std::shared_ptr<Scope> csc; // current scope in which things happen
	  bool ln = false;
	  std::wstring cd;

	  Sys();

	  virtual void ucmd(const std::wstring &cr);

	  static std::shared_ptr<Path> path(const std::wstring &path, const std::wstring &s);

	  virtual std::vector<std::wstring> split(std::shared_ptr<Path> p);
	  virtual std::shared_ptr<Obj> execFile(std::shared_ptr<Path> path, std::shared_ptr<Scope> sc);

	  virtual void line(const std::wstring &s);

	  virtual void lineCatch(const std::wstring &s);
	  virtual void report(std::runtime_error t);


	  virtual void println(const std::wstring &s) = 0; // may contain newlines
	  virtual void print(const std::wstring &s) = 0;
	  virtual void colorprint(const std::wstring &s, int col);
	  virtual void off(int code) = 0;


	  virtual void println(std::shared_ptr<Obj> v);

	  virtual std::wstring input() = 0;
	};

}
