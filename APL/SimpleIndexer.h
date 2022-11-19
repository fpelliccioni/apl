#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>

namespace APL
{

	using Iterator = java::util::Iterator;

	class SimpleIndexer : public std::enable_shared_from_this<SimpleIndexer>, public std::vector<int>
	{ // todo this is horrible (or at least i think so, i can't be bothered to understand it)
  private:
	  const std::vector<int> shape;

  private:
	  class FunAnonymousInnerClass : public Fun
	  {
	  private:
		  std::shared_ptr<DR> outerInstance;

	  public:
		  FunAnonymousInnerClass(std::shared_ptr<DR> outerInstance);

		  std::wstring repr();
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w);

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass>(Fun::shared_from_this());
		  }
	  };

  private:
	  class FunAnonymousInnerClass2 : public Fun
	  {
	  private:
		  std::shared_ptr<DR> outerInstance;

	  public:
		  FunAnonymousInnerClass2(std::shared_ptr<DR> outerInstance);

		  std::wstring repr();
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w);

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass2> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass2>(Fun::shared_from_this());
		  }
	  };

  private:
	  class FunAnonymousInnerClass3 : public Fun
	  {
	  private:
		  std::shared_ptr<DR> outerInstance;

	  public:
		  FunAnonymousInnerClass3(std::shared_ptr<DR> outerInstance);

		  std::wstring repr();
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w);

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass3> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass3>(Fun::shared_from_this());
		  }
	  };

  private:
	  class FunAnonymousInnerClass4 : public Fun
	  {
	  private:
		  std::shared_ptr<DR> outerInstance;

	  public:
		  FunAnonymousInnerClass4(std::shared_ptr<DR> outerInstance);

		  std::wstring repr();
		  std::shared_ptr<Value> call(std::shared_ptr<Value> w);

	  protected:
		  std::shared_ptr<FunAnonymousInnerClass4> shared_from_this()
		  {
			  return std::static_pointer_cast<FunAnonymousInnerClass4>(Fun::shared_from_this());
		  }
	  };
  private:
	  const std::vector<int> chosen;
	  const std::vector<int> shapeTP;
	  const int len;

  public:
	  SimpleIndexer(std::vector<int> &shape, std::vector<int> &chosen);

	  std::shared_ptr<Iterator<int>> iterator() override;

  private:
	  class IteratorAnonymousInnerClass : public std::enable_shared_from_this<IteratorAnonymousInnerClass>, public Iterator<int>
	  {
	  private:
		  std::shared_ptr<SimpleIndexer> outerInstance;

		  bool finalEmpty = false;

	  public:
		  IteratorAnonymousInnerClass(std::shared_ptr<SimpleIndexer> outerInstance, bool finalEmpty);

		  int index = 0;
//JAVA TO C++ CONVERTER NOTE: Field name conflicts with a method name of the current type:
		  bool hasNext_Conflict = false;
		  bool hasNext();

		  std::optional<int> next();
	  };
	};
}
