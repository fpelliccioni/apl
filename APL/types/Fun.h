#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/Callable.h>
#include <APL/Value.h>
#include <APL/Scope.h>
#include <APL/Obj.h>
#include <APL/Num.h>
#include <APL/Char.h>
#include <APL/APLMap.h>
#include <APL/BigValue.h>
#include <APL/arrs/BitArr.h>
#include <APL/Type.h>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL::types { class D_AA; }

namespace APL::types
{

	using namespace APL;
	using namespace APL::errors;
	using namespace APL::types::arrs;


	class Fun : public Callable
	{

  public:
	  virtual std::shared_ptr<Value> identity();

  protected:
	  Fun(std::shared_ptr<Scope> sc);
	  Fun();
  public:
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Obj> callObj(std::shared_ptr<Value> a, std::shared_ptr<Value> w);

	  virtual std::shared_ptr<Value> callInv(std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvW(std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> callInvA(std::shared_ptr<Value> a, std::shared_ptr<Value> w);


	  virtual std::shared_ptr<Value> under(std::shared_ptr<Obj> o, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> underW(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> underA(std::shared_ptr<Obj> o, std::shared_ptr<Value> a, std::shared_ptr<Value> w);

  public:
	  class NumMV
	  {
	public:
		virtual std::shared_ptr<Value> call(std::shared_ptr<Num> w) = 0;
		virtual bool retNum();
		virtual double call(double w);
		virtual void call(std::vector<double> &res, std::vector<double> &a);
		virtual std::shared_ptr<Value> call(std::shared_ptr<BigValue> w);
	  };
  public:
	  class ChrMV
	  {
	public:
		virtual std::shared_ptr<Value> call(std::shared_ptr<Char> w) = 0;
		virtual std::shared_ptr<Arr> call(std::shared_ptr<ChrArr> a);
	  };
  public:
	  class MapMV
	  {
	public:
		virtual std::shared_ptr<Value> call(std::shared_ptr<APLMap> w) = 0;
	  };

  public:
	  class AllMV
	  {
	public:
		virtual std::shared_ptr<Value> call(std::shared_ptr<Value> w) = 0;
	  };


  protected:
	  virtual std::shared_ptr<Value> allM(std::shared_ptr<AllMV> f, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> numM(std::shared_ptr<NumMV> nf, std::shared_ptr<Value> w);

	  virtual std::shared_ptr<Value> numChrM(std::shared_ptr<NumMV> nf, std::shared_ptr<ChrMV> cf, std::shared_ptr<Value> w);

	  virtual std::shared_ptr<Value> numChrMapM(std::shared_ptr<NumMV> nf, std::shared_ptr<ChrMV> cf, std::shared_ptr<MapMV> mf, std::shared_ptr<Value> w);


	  virtual std::shared_ptr<Value> allD(std::shared_ptr<D_AA> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w);







  public:
	  class D_AA
	  {
	public:
		virtual std::shared_ptr<Value> call(std::shared_ptr<Value> a, std::shared_ptr<Value> w) = 0;
	  };
  public:
	  class D_NNeN : public std::enable_shared_from_this<D_NNeN>, public D_NN
	  { // dyadic number-number equals number
	public:
		virtual double on(double a, double w) = 0;
		virtual void on(std::vector<double> &res, double a, std::vector<double> &w);
		virtual void on(std::vector<double> &res, std::vector<double> &a, double w);
		virtual void on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w);

		std::shared_ptr<Value> call(double a, double w) override;
		std::shared_ptr<Value> call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh) override;
		std::shared_ptr<Value> call(double a, std::vector<double> &w, std::vector<int> &sh) override;
		std::shared_ptr<Value> call(std::vector<double> &a, double w, std::vector<int> &sh) override;
		std::shared_ptr<Value> call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w) override;
	  };

  public:
	  class D_NNeB : public std::enable_shared_from_this<D_NNeB>, public D_NN
	  { // dyadic number-number equals boolean
	public:
		virtual bool on(double a, double w) = 0;
		virtual void on(std::shared_ptr<BitArr::BA> res, double a, std::vector<double> &w) = 0;
		virtual void on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, double w) = 0;
		virtual void on(std::shared_ptr<BitArr::BA> res, std::vector<double> &a, std::vector<double> &w) = 0;

		std::shared_ptr<Value> call(double a, double w) override;
		std::shared_ptr<Value> call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh) override;
		std::shared_ptr<Value> call(double a, std::vector<double> &w, std::vector<int> &sh) override;
		std::shared_ptr<Value> call(std::vector<double> &a, double w, std::vector<int> &sh) override;
		std::shared_ptr<Value> call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w) override;
	  };


  public:
	  class D_NN
	  {
	public:
		virtual std::shared_ptr<Value> call(double a, double w) = 0;
		virtual std::shared_ptr<Value> call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh) = 0;
		virtual std::shared_ptr<Value> call(double a, std::vector<double> &w, std::vector<int> &sh) = 0;
		virtual std::shared_ptr<Value> call(std::vector<double> &a, double w, std::vector<int> &sh) = 0;
		virtual std::shared_ptr<Value> call(std::shared_ptr<BigValue> a, std::shared_ptr<BigValue> w) = 0;
		virtual std::shared_ptr<Value> call(double a, std::shared_ptr<BigValue> w);
	  };
  public:
	  class D_BB
	  {
	public:
		virtual std::shared_ptr<Value> call(std::shared_ptr<BitArr> a, std::shared_ptr<BitArr> w) = 0;
		virtual std::shared_ptr<Value> call(bool a, std::shared_ptr<BitArr> w) = 0;
		virtual std::shared_ptr<Value> call(std::shared_ptr<BitArr> a, bool w) = 0;
	  };
  public:
	  class D_CC
	  {
	public:
		virtual std::shared_ptr<Value> call(wchar_t a, wchar_t w) = 0;
	  };


  protected:
	  virtual std::shared_ptr<Value> numD(std::shared_ptr<D_NN> f, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> bitD(std::shared_ptr<D_NN> n, std::shared_ptr<D_BB> b, std::shared_ptr<Value> a, std::shared_ptr<Value> w);


	  virtual std::shared_ptr<Value> numChrD(std::shared_ptr<D_NN> n, std::shared_ptr<D_CC> c, std::shared_ptr<D_AA> def, std::shared_ptr<Value> a, std::shared_ptr<Value> w);
	  virtual std::shared_ptr<Value> ncbaD(std::shared_ptr<D_NN> n, std::shared_ptr<D_BB> b, std::shared_ptr<D_CC> c, std::shared_ptr<D_AA> def, std::shared_ptr<Value> a, std::shared_ptr<Value> w);

  public:
	  Type type() override;


	  virtual std::wstring repr() = 0;

	  virtual std::wstring toString();

	  // functions are equal per-object basis
	  virtual int hashCode();
	  virtual bool equals(std::shared_ptr<Obj> o);

	protected:
		std::shared_ptr<Fun> shared_from_this()
		{
			return std::static_pointer_cast<Fun>(Callable::shared_from_this());
		}
	};
}
