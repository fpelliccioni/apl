#include <stdexcept>
#include <string_view>

class Node
{
public:

	constexpr virtual ~Node() = default;
	constexpr virtual int evaluate() const = 0;
};

class Int: public Node
{
private:

	int value_;

public:

	constexpr explicit Int( int value ): value_( value )
	{
	}

	constexpr virtual int evaluate() const
	{
		return value_;
	}
};

class Add: public Node
{
private:

	Node* left_;
	Node* right_;

public:

	constexpr explicit Add( Node* left, Node* right ): left_( left ), right_( right )
	{
	}

	constexpr ~Add()
	{
		delete left_;
		delete right_;
	}

	constexpr virtual int evaluate() const
	{
		return left_->evaluate() + right_->evaluate();
	}
};

class Mul: public Node
{
private:

	Node* left_;
	Node* right_;

public:

	constexpr explicit Mul( Node* left, Node* right ): left_( left ), right_( right )
	{
	}

	constexpr ~Mul()
	{
		delete left_;
		delete right_;
	}

	constexpr virtual int evaluate() const
	{
		return left_->evaluate() * right_->evaluate();
	}
};

constexpr Node* parse_expression( char const* & first, char const* last );

constexpr Node* parse_integer( char const* & first, char const* last )
{
	int r = 0;

	while( first != last && *first >= '0' && *first <= '9' )
	{
		r = r * 10 + ( *first - '0' );
		++first;
	}

	return new Int( r );
}

constexpr Node* parse_term( char const* & first, char const* last )
{
	if( first == last )
	{
		throw std::runtime_error( "Unexpected end of input" );
	}

	char ch = *first;

	if( ch >= '0' && ch <= '9' )
	{
		return parse_integer( first, last );
	}
	else if( ch == '(' )
	{
		++first;
		Node * n1 = parse_expression( first, last );

		if( first == last || *first != ')' )
		{
			delete n1;
			throw std::runtime_error( "Expected ')'" );
		}

		++first;
		return n1;
	}
	else
	{
		throw std::runtime_error( "Expected integer or (expression)" );
	}
}

constexpr Node* parse_factor( char const* & first, char const* last )
{
	Node* n1 = parse_term( first, last );

	while( first != last && *first == '*' )
	{
		++first;
		Node * n2 = parse_term( first, last );

		n1 = new Mul( n1, n2 );
	}

	return n1;
}

constexpr Node* parse_expression( char const* & first, char const* last )
{
	Node* n1 = parse_factor( first, last );

	while( first != last && *first == '+' )
	{
		++first;
		Node * n2 = parse_factor( first, last );

		n1 = new Add( n1, n2 );
	}

	return n1;
}

constexpr int evaluate( std::string_view expr )
{
	char const * first = expr.data();
	char const * last = expr.data() + expr.size();

	Node* n = parse_expression( first, last );

	int r = n->evaluate();

	delete n;

	return r;
}

#include <cstdio>

int main()
{
	constexpr char const * expr = "(11+22)*(33+44)";
	static_assert( evaluate( expr ) == 2541 );
}
