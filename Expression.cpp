#include "Expression.h"
#include "Token.h"
#include "BinaryTree.h"

void RegularExpression::IsValidContext(Context context)
{
	if(context.GetBegin()==NULL||context.GetEnd()==NULL)
	{
		throw std::bad_typeid("null context");
	}
}
const char* RegularExpression::FindOccurrenceOf(const char *symbol, Context context)
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

void RegularExpression::SafeDelete(RegularExpression *re)
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
	_leftExpression = NULL;
	_rightExpression = NULL;
}
NonTerminalExpression::~NonTerminalExpression()
{
	SafeDelete(_leftExpression);
	SafeDelete(_rightExpression);
}
void NonTerminalExpression::InterpretRightSide(Context context, const char *delimiter)
{
	if(_rightExpression != NULL)
	{
		const char* start = delimiter+1;
		const char* end = context.GetEnd();
		context.Set(start, end);
		_rightExpression->Interpret(context);
	}
}
void NonTerminalExpression::InterpretLeftSide(Context context, const char *delimiter)
{
	if(_leftExpression != NULL)
	{
		const char* start = context.GetBegin();
		const char* end = delimiter-1;
		context.Set(start, end);
		_leftExpression->Interpret(context);
	}
}


