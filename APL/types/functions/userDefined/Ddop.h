#pragma once

#include <APL/errors/DomainError.h>
#include <APL/tokenizer/types/DfnTok.h>
#include <APL/types/functions/Dop.h>
#include <APL/Scope.h>
#include <APL/types/Obj.h>
#include <APL/types/Value.h>
#include <APL/types/functions/DerivedDop.h>
#include <string>
#include <vector>
#include <any>
#include <memory>
#include <helpers/tangible_string_helper.h>

namespace APL::types::functions::userDefined
{

	using namespace APL;
	using DfnTok = APL::tokenizer::types::DfnTok;
	using namespace APL::types;
	using namespace APL::types::functions;



	class Ddop : public Dop
	{
  public:
	  const std::shared_ptr<DfnTok> code;

	  std::wstring repr() override;

	  Ddop(std::shared_ptr<DfnTok> t, std::shared_ptr<Scope> sc);

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	  std::shared_ptr<Value> call(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;
	  std::shared_ptr<Obj> callObj(std::shared_ptr<Obj> aa, std::shared_ptr<Obj> ww, std::shared_ptr<Value> a, std::shared_ptr<Value> w, std::shared_ptr<DerivedDop> derv) override;

	protected:
		std::shared_ptr<Ddop> shared_from_this()
		{
			return std::static_pointer_cast<Ddop>(Dop::shared_from_this());
		}
	};
}
