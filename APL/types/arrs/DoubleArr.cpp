//====================================================================================================
//The Free Edition of Java to C++ Converter limits conversion output to 100 lines per file.

//To purchase the Premium Edition, visit our website:
//https://www.tangiblesoftwaresolutions.com/order/order-java-to-cplus.html
//====================================================================================================

#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/Num.h>

namespace APL::types::arrs
{
    using Main = APL::Main;
    using DomainError = APL::errors::DomainError;
    // using namespace APL::types;
const std::vector<double> DoubleArr::EMPTY = std::vector<double>(0);

    DoubleArr::DoubleArr(std::vector<double> &arr, std::vector<int> &sh) : Arr(sh), arr(arr)
    {
      assert((Main::enclosePrimitives || sh.size() != 0, L"Internal: attempting to create a DoubleArr of shape ⍬"));
    }

    DoubleArr::DoubleArr(std::vector<double> &arr) : Arr(std::vector<int>{arr.size()}), arr(arr)
    { // 1D
    }

    DoubleArr::DoubleArr(std::vector<int> &arr) : Arr(std::vector<int>{arr.size()}), arr(a)
    { // 1D
      std::vector<double> a(ia);
      for (int i = 0; i < ia; i++)
      {
        a[i] = arr[i];
      }
    }

    DoubleArr::DoubleArr(std::vector<signed char> &arr) : Arr(std::vector<int>{arr.size()}), arr(a)
    { // 1D
      std::vector<double> a(ia);
      for (int i = 0; i < ia; i++)
      {
        a[i] = arr[i];
      }
    }

    DoubleArr::DoubleArr(std::vector<double> &arrl) : Arr(std::vector<int>{arrl.size()}), arr(std::vector<double>(ia))
    {
      int j = 0;
      for (auto d : arrl)
      {
        arr[j++] = d;
      }
    }

    std::shared_ptr<APL::types::Value> DoubleArr::safe(std::vector<double> &vs, std::vector<int> &sh)
    {
      if (sh.empty() && !Main::enclosePrimitives)
      {
          return std::make_shared<Num>(vs[0]);
      }
      return std::make_shared<DoubleArr>(vs, sh);
    }

    std::vector<int> DoubleArr::asIntArrClone()
    {
      std::vector<int> r(ia);
      for (int i = 0; i < ia; i++)
      {
        int conv = static_cast<int>(arr[i]);
        if (arr[i] != conv)
        {
            throw DomainError(L"Using a fractional number as integer", shared_from_this());
        }
        r[i] = conv;
      }
      return r;
    }

    int DoubleArr::asInt()
    {
      throw DomainError(L"Using a number array as integer", shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DoubleArr::get(int i)
    {
      return Num::of(arr[i]);
    }

    std::shared_ptr<APL::types::Value> DoubleArr::first()
    {
      if (ia > 0)
      {
          return std::make_shared<Num>(arr[0]);
      }
      return Num::ZERO;
    }

    std::string DoubleArr::asString()
    {
      throw DomainError(L"Using number array as string", shared_from_this());
    }

    std::shared_ptr<APL::types::Value> DoubleArr::prototype()
    {
      return Num::ZERO;
    }

    std::shared_ptr<APL::types::Value> DoubleArr::safePrototype()
    {
      return Num::ZERO;
    }

    std::shared_ptr<APL::types::Value> DoubleArr::ofShape(std::vector<int> &sh)
    {
      if (sh.empty() && !Main::enclosePrimitives)
      {
          return this->operator[](0);
      }
      return std::make_shared<DoubleArr>(arr, sh);
    }

    double DoubleArr::sum()
    {
      double r = 0;
      for (auto val : arr)
      {
          r += val;
      }
      return r;
    }

    std::vector<double> DoubleArr::asDoubleArr()
    {
      return arr;
    }

    std::vector<double> DoubleArr::asDoubleArrClone()
    {
      return arr.clone();
    }

    bool DoubleArr::quickDoubleArr()
    {
      return true;
    }

    std::shared_ptr<APL::types::Value> DoubleArr::squeeze()
    {
      return shared_from_this();
    }

    std::vector<std::shared_ptr<APL::types::Value>> DoubleArr::valuesCopy()
    {
      std::vector<std::shared_ptr<APL::types::Value>> vs(ia);
      for (int i = 0; i < ia; i++)
      {
          vs[i] = std::make_shared<Num>(arr[i]);
      }
      return vs;
    }

    std::shared_ptr<Arr> DoubleArr::reverseOn(int dim)
    {
      if (rank == 0)
      {
        if (dim != 0)
        {
            throw DomainError(L"rotating a scalar with a non-⎕IO axis", shared_from_this());
        }
        return shared_from_this();
      }
      if (dim < 0)
      {
          dim += rank;
      }
      // 2×3×4:
      // 0 - 3×4s for 2
      // 1 - 4s for 3
      // 2 - 1s for 4
      int chunkS = 1;
      int cPSec = shape[dim]; // chunks per section
      for (int i = rank - 1; i > dim; i--)
      {
        chunkS *= shape[i];
      }
      int sec = chunkS * cPSec; // section length
      std::vector<double> res(ia);
      int c = 0;
      while (c < ia)
      {
        for (int i = 0; i < cPSec; i++)
        {
          for (int j = 0; j < chunkS; j++)
          {
            res[c + (cPSec - i - 1) * chunkS + j] = arr[c + i * chunkS + j];
          }
        }
        c += sec;
      }
      return std::make_shared<DoubleArr>(res, shape);
    }

    bool DoubleArr::equals(std::shared_ptr<APL::types::Obj> o)
    {
      if (std::dynamic_pointer_cast<DoubleArr>(o) != nullptr)
      {
        std::shared_ptr<DoubleArr> da = std::static_pointer_cast<DoubleArr>(o);
        if ((hash != 0 && da->hash != 0 && hash != da->hash) || !Arrays::equals(shape, da->shape))
        {
            return false;
        }
        for (int i = 0; i < ia; i++)
        {
          if (arr[i] != da->arr[i])
          {
              return false;
          }
        }
        return true;
      }
      return Arr::equals(o);
    }

    int DoubleArr::hashCode()
    {
      if (hash == 0)
      {
        for (auto d : arr)
        {
          hash *= 31;
          if (d != 0.0)
          {
              hash += Double::hashCode(d); // ¯0 == 0
          }
        }
        hash = shapeHash(hash);
      }
      return hash;
    }
}
