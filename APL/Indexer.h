#pragma once

#include <APL/types/Callable.h>
#include <APL/types/Value.h>
#include <vector>
#include <memory>

namespace APL
{


	using namespace APL::errors;
	using namespace APL::types;
	using namespace APL::types::arrs;

	using Iterator = java::util::Iterator;

	class Indexer final : public std::enable_shared_from_this<Indexer>, public std::vector<std::vector<int>>, public Iterator<std::vector<int>>
	{
  private:
	  const std::vector<int> shape;
	  const int rank;
	  const std::vector<int> c;
	  int ia = 1;
	  int ci = 0;
	  const std::vector<int> offsets;

  public:
	  Indexer(std::vector<int> &sh, std::vector<int> &offsets);
	  Indexer(std::vector<int> &sh, int IO);

	  int pos();

	  bool hasNext();
	  std::vector<int> next();

	  static std::vector<int> add(std::vector<int> &a, int b);
	  static std::vector<int> sub(std::vector<int> &a, int b);

	  static std::vector<int> sub(std::vector<int> &a, std::vector<int> &b);
	  static std::vector<int> add(std::vector<int> &a, std::vector<int> &b);

	  static int fromShape(std::vector<int> &shape, std::vector<int> &pos, int IO);
	  static int fromShapeChk(std::vector<int> &sh, std::vector<int> &pos, std::shared_ptr<Callable> blame);
	  static int fromShapeChk(std::vector<int> &sh, std::shared_ptr<Value> pos, int IO, std::shared_ptr<Callable> blame);

  public:
	  class PosSh : public std::enable_shared_from_this<PosSh>
	  { // multiple results ._.
	public:
		const std::vector<int> vals;
		const std::vector<int> sh;
		PosSh(std::vector<int> &vals, std::vector<int> &sh);
	  };

	  // checks for rank & bound errors
	  // ⎕VI←1 and sh.length≡1 allows for a shortcut of items (1 2 3 ←→ ⊂1 2 3)
  public:
	  static std::shared_ptr<PosSh> poss(std::shared_ptr<Value> v, std::vector<int> &ish, int IO, std::shared_ptr<Callable> blame);

	  static std::vector<int> intsNoIO(std::shared_ptr<Value> v, int IO);

	  std::shared_ptr<Iterator<std::vector<int>>> iterator();
	};
}
