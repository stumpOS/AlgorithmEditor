#pragma once
#ifndef NONTERMINALEXPRESSIONS_H_
#define NONTERMINALEXPRESSIONS_H_
#include "Expression.h"
#include "Functors.h"
class UnionExpression:public NonTerminalExpression
{
public:
	UnionExpression(RegularExpression *lhs,const char* delimiter, RegularExpression *rhs):NonTerminalExpression(lhs,delimiter,rhs){}
	UnionExpression(const char* delimiter, RegularExpression *rhs):NonTerminalExpression(delimiter,rhs){}
	UnionExpression(RegularExpression *lhs,const char* delimiter=" "):NonTerminalExpression(lhs,delimiter){}
	virtual ~UnionExpression(){}
	virtual void Interpret(Context context);
	
};

#endif
