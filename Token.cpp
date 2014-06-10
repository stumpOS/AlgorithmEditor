#include "Token.h"


Token::Token(void)
{
	_expression = NULL;
}


Token::~Token(void)
{
	if(_expression!=NULL)
	{
		delete _expression;
		_expression = NULL;
	}
}
void Token::Interpret(Context context)
{
	if(_expression!=NULL)
		_expression->Interpret(context);
	else
		throw std::bad_typeid("null expression exception");
}
void Token::SetExpression(RegularExpression *expression)
{
	_expression = expression;
}
Keyword::Keyword(std::string *key):Token()
{
	_keyword = key;
}
Keyword::~Keyword()
{
	if(_keyword!=NULL)
	{
		delete _keyword;
		_keyword = NULL;
	}
}

bool operator<(Keyword const& lhs, Keyword const& rhs)
{
	if(lhs._keyword != NULL&& rhs._keyword != NULL)
	{
		return lhs._keyword < rhs._keyword;
	}
	else
		throw std::bad_typeid("null keywords");
}
bool operator==(Keyword const& lhs, Keyword const& rhs)
{
	return (!(lhs<rhs)&&!(lhs>rhs));
}
bool operator>(Keyword const& lhs, Keyword const& rhs)
{
	if(lhs._keyword != NULL&& rhs._keyword != NULL)
	{
		return lhs._keyword > rhs._keyword;
	}
	else
		throw std::bad_typeid("null keywords");
}

bool operator< (Keyword const& lhs,std::string* const& rhs)
{
	return lhs._keyword < rhs;
}

