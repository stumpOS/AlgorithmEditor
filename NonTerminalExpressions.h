#pragma once
#ifndef NONTERMINALEXPRESSIONS_H_
#define NONTERMINALEXPRESSIONS_H_
#include<stack>
#include "Expression.h"
#include "Functors.h"

struct Parenthesis
{
	Parenthesis(const char* r, const char* l):_rightSeparator(r),_leftSeparator(l){}
	const char *_rightSeparator;
	const char *_leftSeparator;
};
class ParenthesisExpression:public NonTerminalExpression
{
public:
	ParenthesisExpression(NonTerminalExpression *nte,TerminalExpression *te, Parenthesis *p):
	  NonTerminalExpression(nte,te),_parenthesis(p){_end = NULL;}
	virtual ~ParenthesisExpression(){delete _parenthesis;}
	virtual void Interpret(Context context);
	virtual void UpdateContext(Context &context);
private:
	Parenthesis *_parenthesis;
	const char *_end;
};


#endif
