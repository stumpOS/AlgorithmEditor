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

FunctionTree<std::string>* Token::GetAbstractSyntaxTree(Context context)
{
	if(_expression!=NULL)
	{
		FunctionTree<std::string> *ast = new FunctionTree<std::string>();
		_expression->Interpret(context);
		return _ast;
	}
	else
		throw std::bad_typeid("null expression exception");
}
void Token::Interpret(Context context)
{
	Expression::IsValidContext(context);
	_expression->Interpret(context);
}
void Token::SetExpression(Expression *expression)
{
	_expression = expression;
}
void Token::AddLeaf(std::string operand)
{
	_ast->AddChildOperand(operand);
}
void Token::AddInternalNode(std::string operation)
{
	_ast->AddChildOperation(operation);
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
void Keyword::Interpret(Context context)
{

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

