#pragma once
#ifndef NONTERMINALEXPRESSIONS_H_
#define NONTERMINALEXPRESSIONS_H_
#include "Expression.h"
#include "Functors.h"
class UnionExpression:public NonTerminalExpression
{
public:
	UnionExpression(NonTerminalExpression *nte,TerminalExpression *te):NonTerminalExpression(nte,te){}
	virtual ~UnionExpression(){}
	virtual void Interpret(Context context);
};


#endif
