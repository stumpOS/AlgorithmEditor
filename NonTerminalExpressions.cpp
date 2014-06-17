#include "NonTerminalExpressions.h"

void ParenthesisExpression::Interpret(Context context)
{
	std::stack<unsigned> indices_of_separators;
	unsigned i=0;

	if(*context.GetBegin()!=*_parenthesis->_leftSeparator)
	{
		throw std::invalid_argument("syntax error: missing " + std::string(_parenthesis->_leftSeparator,1));
	}
	else
	{
		indices_of_separators.push(i);
	}
	i++;
	const char *cntxt_ptr = context.GetBegin()+i;
	bool found_end = false;
	for(;context.GetBegin()+i!=context.GetEnd()&&found_end==false;i++)
	{
		if(*cntxt_ptr == *_parenthesis->_leftSeparator)
		{
			indices_of_separators.push(i);
		}
		else if(*cntxt_ptr == *_parenthesis->_rightSeparator)
		{
			if(!indices_of_separators.empty())
				indices_of_separators.pop();
			else
				found_end = true;
		}
	}
	if(found_end)
	{
		_nonterminalExpression->Interpret(Context(context.GetBegin()+1,context.GetBegin()+i));
		_end = context.GetBegin()+i;
	}
	else
		throw std::invalid_argument("syntax error: missing " + std::string(_parenthesis->_rightSeparator,1));

}
void ParenthesisExpression::UpdateContext(Context &context)
{
	if(_end != NULL)
	{
		context.SetBegin(_end+1);
	}
}


