#include "Expression.h"
#include "Token.h"
#include "BinaryTree.h"

void Expression::IsValidContext(Context context)
{
	if(context.GetBegin()==NULL||context.GetEnd()==NULL)
	{
		throw std::bad_typeid("null context");
	}
}
const char* Expression::FindOccurrenceOf(const char *symbol, Context context)
{
	unsigned index = 0;
	const char* hit = NULL;
	if(context.GetBegin()==NULL)
	{
		throw std::bad_typeid("error in trying to search a null string");
	}
	while((context.GetBegin()+index)!= context.GetEnd()&&*(context.GetBegin()+index)!='\0')
	{
		if(*(context.GetBegin()+index)==*symbol)
		{
			hit = context.GetBegin()+index;
			break;
		}
		else
			index++;
	}
	return hit;
}
const char* Expression::FindOccurenceOfStr(std::string *str,Context context)
{
	const char* result = NULL;
	bool isMatch = true;
	int i=0;
	for(;context.GetBegin()+i!=context.GetEnd()&&isMatch==true;i++)
	{
		if(i>=str->length())
		{
			isMatch = false;
		}
		else if(*(context.GetBegin()+i) != (*str)[i])
		{
			isMatch = false;
		}
	}
	if(isMatch)
	{
		result = context.GetBegin()+i;
	}
	return result;
}
void Expression::SafeDelete(Expression *re)
{
	if(re != NULL)
	{
		delete re;
		re = NULL;
	}
}

TerminalExpression::TerminalExpression()
{
}
TerminalExpression::~TerminalExpression()
{
	if(_literal != NULL)
	{
		delete _literal;
		_literal = NULL;
	}
}

NonTerminalExpression::NonTerminalExpression()
{
	_nonterminalExpression = NULL;
	_terminalExpression = NULL;
}
NonTerminalExpression::~NonTerminalExpression()
{

}



