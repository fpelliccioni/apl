#include <APL/DownArrowBuiltin.h>
#include <APL/types/Primitive.h>
#include <APL/types/arrs/Rank0Arr.h>
#include <APL/types/arrs/DoubleArr.h>
#include <APL/types/arrs/HArr.h>
#include <APL/types/Arr.h>
#include <APL/errors/DomainError.h>
#include <APL/types/functions/builtins/fns/UpArrowBuiltin.h>
#include <APL/types/Fun.h>
#include <APL/errors/LengthError.h>

namespace APL::types::functions::builtins::fns
{
	using Main = APL::Main;
	// using namespace APL::errors;
	// using namespace APL::types;
	// using namespace APL::types::arrs;
	// using namespace APL::types::dimensions;
	using Builtin = APL::types::functions::Builtin;
	using Arrays = java::util::Arrays;

	std::string DownArrowBuiltin::repr()
	{
	  return L"↓";
	}

	std::shared_ptr<APL::types::Value> DownArrowBuiltin::call(std::shared_ptr<APL::types::Value> w)
	{
	  if (std::dynamic_pointer_cast<Primitive>(w) != nullptr)
	  {
		  return w;
	  }
	  if (w->rank <= 1)
	  {
		  return std::make_shared<Rank0Arr>(w);
	  }
	  if (w->quickDoubleArr())
	  {
		std::vector<double> dw = w->asDoubleArr();
		int csz = w->shape[w->rank - 1]; // chunk size
		int cam = w->ia / csz; // chunk amount
		std::vector<std::shared_ptr<APL::types::Value>> res(cam);
		for (int i = 0; i < cam; i++)
		{
		  std::vector<double> c(csz);
		  std::copy_n(dw.begin() + i * csz, csz, c.begin());
		  // ↑ ≡ for (int j = 0; j < csz; j++) c[j] = dw[i * csz + j];
		  res[i] = std::make_shared<DoubleArr>(c);
		}
		std::vector<int> nsh(w->rank - 1);
		std::copy_n(w->shape.begin(), nsh.size(), nsh.begin());
		return std::make_shared<HArr>(res, nsh);
	  }
	  int csz = w->shape[w->rank - 1]; // chunk size
	  int cam = w->ia / csz; // chunk amount
	  std::vector<std::shared_ptr<APL::types::Value>> res(cam);
	  for (int i = 0; i < cam; i++)
	  {
		std::vector<std::shared_ptr<APL::types::Value>> c(csz);
		for (int j = 0; j < csz; j++)
		{
		  c[j] = w[i * csz + j];
		}
		res[i] = Arr::create(c);
	  }
	  std::vector<int> nsh(w->rank - 1);
	  std::copy_n(w->shape.begin(), nsh.size(), nsh.begin());
	  return std::make_shared<HArr>(res, nsh);
	}

	std::shared_ptr<APL::types::Value> DownArrowBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::vector<int> gsh = a->asIntVec();
	  if (gsh.empty())
	  {
		  return w;
	  }
	  if (gsh.size() > w->rank)
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"↓: ≢⍺ should be less than ⍴⍴⍵ (" + std::to_wstring(gsh.size()) + L" = ≢⍺; " + Main::formatAPL(w->shape) + L" ≡ ⍴⍵)", shared_from_this()));
	  }
	  std::vector<int> sh(w->rank);
	  std::copy_n(gsh.begin(), gsh.size(), sh.begin());
	  std::copy_n(w->shape.begin() + gsh.size(), sh.size() - gsh.size(), sh.begin() + gsh.size());
	  std::vector<int> off(sh.size());
	  for (int i = 0; i < gsh.size(); i++)
	  {
		int am = gsh[i];
		sh[i] = w->shape[i] - std::abs(am);
		if (am > 0)
		{
			off[i] = am;
		}
	  }
	  return UpArrowBuiltin::on(sh, off, w, shared_from_this());
	}

	std::shared_ptr<APL::types::Value> DownArrowBuiltin::call(std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w, std::shared_ptr<DervDimFn> dims)
	{
	  std::vector<int> axV = a->asIntVec();
	  std::vector<int> axK = dims->dims(w->rank);
	  if (axV.size() != axK.size())
	  {
		  throw DomainError(StringHelper::wstring_to_string(L"↓: expected ⍺ and axis specification to have equal number of items (⍺≡" + Main::formatAPL(axV) + L"; axis≡" + dims->format() + L")", dims));
	  }
	  std::vector<int> sh = w->shape.clone();
	  std::vector<int> off(sh.size());
	  for (int i = 0; i < axV.size(); i++)
	  {
		int ax = axK[i];
		int am = axV[i];
		sh[ax] = w->shape[ax] - std::abs(am);
		if (am > 0)
		{
			off[ax] = am;
		}
	  }
	  return UpArrowBuiltin::on(sh, off, w, shared_from_this());
	}

	std::shared_ptr<APL::types::Value> DownArrowBuiltin::underW(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> a, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(a, w)) : std::static_pointer_cast<APL::types::Value>(o);
	  std::vector<int> ls = a->asIntVec();
	  std::vector<int> sh = w->shape;
	  for (int i = 0; i < ls.size(); i++)
	  {
		ls[i] = ls[i] > 0? ls[i] - sh[i] : ls[i] + sh[i];
	  }
	  return UpArrowBuiltin::undo(ls, v, w, shared_from_this());
	}

	std::shared_ptr<APL::types::Value> DownArrowBuiltin::under(std::shared_ptr<APL::types::Obj> o, std::shared_ptr<APL::types::Value> w)
	{
	  std::shared_ptr<APL::types::Value> v = std::dynamic_pointer_cast<Fun>(o) != nullptr? (std::static_pointer_cast<Fun>(o))->call(call(w)) : std::static_pointer_cast<APL::types::Value>(o);
	  std::vector<std::shared_ptr<APL::types::Value>> vs = v->values();
	  if (vs.size() > 0)
	  {
		std::vector<int> sh = vs[0]->shape;
		for (int i = 1; i < vs.size(); i++)
		{
		  if (!Arrays::equals(vs[i]->shape, sh))
		  {
			  throw LengthError(StringHelper::wstring_to_string(L"⍢↓: undoing expected arrays of equal shapes (" + Main::formatAPL(sh) + L" ≢ " + Main::formatAPL(vs[i]->shape) + L")", shared_from_this(), o));
		  }
		}
	  }
	  return UpArrowBuiltin::merge(vs, v->shape, shared_from_this());
	}
}
