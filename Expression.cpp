#include "Expression.h"


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
LiteralExpression::~LiteralExpression()
{
	if(_literal != NULL)
	{
		delete _literal;
		_literal = NULL;
	}
}
void LiteralExpression::Interpret(Context context)
{
	RegularExpression::IsValidContext(context);
	bool match = true;
	for(unsigned i=0;context.GetBegin()+i != context.GetEnd() && match==true;i++)
	{
		if(i>=_literal->length())
			match = false;
		else if(*(context.GetBegin()+i)!=(*_literal)[i])
			match = false;
	}
	if(!match)
	{
		throw std::invalid_argument("syntax error in literal");
	}
}
EnclosedExpression::~EnclosedExpression()
{
	if(_separator!=NULL)
	{
		delete _separator;
		_separator = NULL;
	}
	if(_internalExpression!=NULL)
	{
		delete _internalExpression;
		_internalExpression = NULL;
	}
}
void EnclosedExpression::Interpret(Context context)
{
	RegularExpression::IsValidContext(context);

	if(*context.GetBegin() != *_separator->_left)
	{
		throw std::invalid_argument("enclosed expression syntax error - left hand side");
	}
	else
	{
		UpdateContext(context);
		if(_internalExpression != NULL)
		{
			_internalExpression->Interpret(context);
		}
	}

}
void EnclosedExpression::UpdateContext(Context &context)
{
	const char* end = RegularExpression::FindOccurrenceOf(_separator->_right, context);
	const char* start = context.GetBegin()+1;
	if(end!=NULL)
	{
		context.Set(start,end);
	}
	else
		throw std::invalid_argument("enclosed expression syntax error - right hand side");
}
void ListExpression::Interpret(Context context)
{
	RegularExpression::IsValidContext(context);
	const char* end = RegularExpression::FindOccurrenceOf(_delimiter, context);
}