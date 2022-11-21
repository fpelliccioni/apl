#pragma once

//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/Callable.h>
#include <APL/types/Value.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Num.h>
#include <APL/types/Char.h>
#include <APL/types/APLMap.h>
#include <APL/types/BigValue.h>
#include <APL/types/arrs/BitArr.h>
#include <APL/Type.h>
#include <string>
#include <vector>
#include <cassert>
#include <memory>
#include <helpers/tangible_string_helper.h>

//JAVA TO C++ CONVERTER NOTE: Forward class declarations:
namespace APL::types { class D_AA; }

namespace APL::types {

// using namespace APL;
// using namespace APL::errors;
// using namespace APL::types::arrs;


class Fun : public Callable
{

public:
    virtual std::shared_ptr<APL::types::Value> identity();

protected:
    Fun(std::shared_ptr<Scope> sc);
    Fun();
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Obj> callObj(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

    virtual std::shared_ptr<APL::types::Value> callInv(std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> callInvW(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> callInvA(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);


    virtual std::shared_ptr<APL::types::Value> under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> underA(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

public:
    class NumMV
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<Num> w) = 0;
    virtual bool retNum();
    virtual double call(double w);
    virtual void call(std::vector<double> &res, std::vector<double> &a);
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> w);
    };
public:
    class ChrMV
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<Char> w) = 0;
    virtual std::shared_ptr<Arr> call(std::shared_ptr<APL::types::arrs::ChrArr> a);
    };
public:
    class MapMV
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APLMap> w) = 0;
    };

public:
    class AllMV
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> w) = 0;
    };


protected:
    virtual std::shared_ptr<APL::types::Value> allM(std::shared_ptr<AllMV> f, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> numM(std::shared_ptr<NumMV> nf, std::shared_ptr<APL::types::Value> w);

    virtual std::shared_ptr<APL::types::Value> numChrM(std::shared_ptr<NumMV> nf, std::shared_ptr<ChrMV> cf, std::shared_ptr<APL::types::Value> w);

    virtual std::shared_ptr<APL::types::Value> numChrMapM(std::shared_ptr<NumMV> nf, std::shared_ptr<ChrMV> cf, std::shared_ptr<MapMV> mf, std::shared_ptr<APL::types::Value> w);


    virtual std::shared_ptr<APL::types::Value> allD(std::shared_ptr<D_AA> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);







public:
    class D_AA
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w) = 0;
    };
public:
    class D_NNeN : public std::enable_shared_from_this<D_NNeN>, public D_NN {
		// dyadic number-number equals number
public:
    virtual double on(double a, double w) = 0;
    virtual void on(std::vector<double> &res, double a, std::vector<double> &w);
    virtual void on(std::vector<double> &res, std::vector<double> &a, double w);
    virtual void on(std::vector<double> &res, std::vector<double> &a, std::vector<double> &w);

    std::shared_ptr<APL::types::Value> call(double a, double w) override;
    std::shared_ptr<APL::types::Value> call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh) override;
    std::shared_ptr<APL::types::Value> call(double a, std::vector<double> &w, std::vector<int> &sh) override;
    std::shared_ptr<APL::types::Value> call(std::vector<double> &a, double w, std::vector<int> &sh) override;
    std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w) override;
    };

public:
    class D_NNeB : public std::enable_shared_from_this<D_NNeB>, public D_NN
    { // dyadic number-number equals boolean
public:
    virtual bool on(double a, double w) = 0;
    virtual void on(std::shared_ptr<APL::types::arrs::BitArr::BA> res, double a, std::vector<double> &w) = 0;
    virtual void on(std::shared_ptr<APL::types::arrs::BitArr::BA> res, std::vector<double> &a, double w) = 0;
    virtual void on(std::shared_ptr<APL::types::arrs::BitArr::BA> res, std::vector<double> &a, std::vector<double> &w) = 0;

    std::shared_ptr<APL::types::Value> call(double a, double w) override;
    std::shared_ptr<APL::types::Value> call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh) override;
    std::shared_ptr<APL::types::Value> call(double a, std::vector<double> &w, std::vector<int> &sh) override;
    std::shared_ptr<APL::types::Value> call(std::vector<double> &a, double w, std::vector<int> &sh) override;
    std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w) override;
    };


public:
    class D_NN
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(double a, double w) = 0;
    virtual std::shared_ptr<APL::types::Value> call(std::vector<double> &a, std::vector<double> &w, std::vector<int> &sh) = 0;
    virtual std::shared_ptr<APL::types::Value> call(double a, std::vector<double> &w, std::vector<int> &sh) = 0;
    virtual std::shared_ptr<APL::types::Value> call(std::vector<double> &a, double w, std::vector<int> &sh) = 0;
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::BigValue> a, std::shared_ptr<APL::types::BigValue> w) = 0;
    virtual std::shared_ptr<APL::types::Value> call(double a, std::shared_ptr<APL::types::BigValue> w);
    };
public:
    class D_BB
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::arrs::BitArr> a, std::shared_ptr<APL::types::arrs::BitArr> w) = 0;
    virtual std::shared_ptr<APL::types::Value> call(bool a, std::shared_ptr<APL::types::arrs::BitArr> w) = 0;
    virtual std::shared_ptr<APL::types::Value> call(std::shared_ptr<APL::types::arrs::BitArr> a, bool w) = 0;
    };
public:
    class D_CC
    {
public:
    virtual std::shared_ptr<APL::types::Value> call(wchar_t a, wchar_t w) = 0;
    };


protected:
    virtual std::shared_ptr<APL::types::Value> numD(std::shared_ptr<D_NN> f, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> bitD(std::shared_ptr<D_NN> n, std::shared_ptr<D_BB> b, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);


    virtual std::shared_ptr<APL::types::Value> numChrD(std::shared_ptr<D_NN> n, std::shared_ptr<D_CC> c, std::shared_ptr<D_AA> def, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);
    virtual std::shared_ptr<APL::types::Value> ncbaD(std::shared_ptr<D_NN> n, std::shared_ptr<D_BB> b, std::shared_ptr<D_CC> c, std::shared_ptr<D_AA> def, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w);

public:
    Type type() override;


    virtual std::string repr() = 0;

    virtual std::string toString();

    // functions are equal per-object basis
    virtual int hashCode();
    virtual bool equals(std::shared_ptr<APL::types::Obj> o);

protected:
    std::shared_ptr<Fun> shared_from_this()
    {
        return std::static_pointer_cast<Fun>(Callable::shared_from_this());
    }
};

}
