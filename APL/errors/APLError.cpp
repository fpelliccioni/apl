#include <APL/errors/APLError.h>
#include <APL/Main.h>

namespace APL::errors
{
	using namespace APL;
	using Token = APL::tokenizer::Token;
	using namespace APL::types;

	APLError::APLError(const std::wstring &msg) : RuntimeException(msg)
	{
	}

	APLError::APLError(const std::wstring &msg, std::shared_ptr<Tokenable> blame) : RuntimeException(msg)
	{
	  if (std::dynamic_pointer_cast<Callable>(blame) != nullptr)
	  {
		  Main::faulty = blame;
	  }
	  else
	  {
		  cause = blame;
	  }
	}

	APLError::APLError(const std::wstring &msg, std::shared_ptr<Callable> blame, std::shared_ptr<Tokenable> cause) : RuntimeException(msg)
	{
	  Main::faulty = blame;
	  this->cause = cause;
	}

	void APLError::print(std::shared_ptr<Sys> s)
	{
	  std::wstring type = getClass().getSimpleName();
	  std::wstring msg = getMessage();
	  if (msg == L"")
	  {
		  msg = L"";
	  }
	  if (msg.length() == 0)
	  {
		  s->colorprint(type, 246);
	  }
	  else
	  {
		  s->colorprint(type + L": " + msg, 246);
	  }
	  std::vector<std::shared_ptr<Mg>> l;
	  std::shared_ptr<Tokenable> faulty = Main::faulty;
	  if (faulty != nullptr)
	  {
		  Mg::add(l, faulty, L'^');
	  }
	  if (cause != nullptr)
	  {
		  Mg::add(l, cause, L'¯');
	  }
	  if (l.size() == 2 && l[0]->eqSrc(l[1]))
	  {
		  println(s, l);
	  }
	  else
	  {
		  for (auto g : l)
		  {
		std::vector<std::shared_ptr<Mg>> c;
		c.push_back(g);
		println(s, c);
		  }
	  }
	}

	void APLError::println(std::shared_ptr<Sys> s, std::vector<std::shared_ptr<Mg>> &gs)
	{
	  if (gs.empty())
	  {
		  return;
	  }

	  std::wstring raw = gs[0]->raw;
	  int lns = gs[0]->lns;

	  int lne = (int)raw.find(L"\n", lns);
	  if (lne == -1)
	  {
		  lne = raw.length();
	  }

	  std::wstring ln = gs[0]->raw->substr(lns, lne - lns);
	  s->println(ln);
	  std::vector<wchar_t> str(ln.length());
	  for (int i = 0; i < str.size(); i++)
	  {
		wchar_t c = L' ';
		for (auto g : gs)
		{
			if (i >= g->spos && i < g->epos)
			{
				c = g->c;
			}
		}
		str[i] = c;
	  }
	  s->println(std::wstring(str));
	}

	APLError::Mg::Mg(std::shared_ptr<Token> t, wchar_t c, const std::wstring &raw, int lns, int spos, int epos) : t(t), c(c), raw(raw)
	{
	  this->lns = lns;
	  this->spos = spos;
	  this->epos = epos;
	}

	void APLError::Mg::add(std::vector<std::shared_ptr<Mg>> &l, std::shared_ptr<Tokenable> to, wchar_t c)
	{
	  std::shared_ptr<Token> t = to->getToken();
	  if (t == nullptr)
	  {
		  return;
	  }

	  std::wstring raw = t->raw;

	  int lns = (int)raw.rfind(L"\n", t->spos) + 1; // not found handles itself


	  int spos = t->spos - lns;
	  int epos = (t->epos == Token::EPOS_DEF? spos + 1 : t->epos) - lns;

	  l.push_back(std::make_shared<Mg>(t, c, raw, lns, spos, epos));
	}

	bool APLError::Mg::eqSrc(std::shared_ptr<Mg> g)
	{
	  // noinspection StringEquality \\ we want that
//JAVA TO C++ CONVERTER TODO TASK: Cannot test for object identity between 2 string objects in C++:
	  return raw == g->raw && lns == g->lns;
	}
}
