#pragma once
#ifndef TOKEN_H_
#define TOKEN_H_
#include <cstdlib>
#include <typeinfo>
#include<string>
#include<cstring>
#include "Expression.h"
#include "FunctionTree.h"
class Context;
class Expression;
class NonTerminalExpression;

class Token:public Expression
{
public:
	
	Token(void);
	virtual ~Token(void);
	
	FunctionTree<std::string>* GetAbstractSyntaxTree(Context context);
	void SetExpression(Expression *expression);
	
	void AddLeaf(std::string);
	void AddInternalNode(std::string operation);
	virtual void Interpret(Context context);

protected:
	Expression *_expression;
	
	FunctionTree<std::string> *_ast;
};


class Keyword:public Token
{
public:
	Keyword(std::string *key);
	virtual ~Keyword();
	std::string* GetKeyword(){return _keyword;}

	friend bool operator<(Keyword const& lhs, Keyword const& rhs);
	friend bool operator==(Keyword const& lhs, Keyword const& rhs);
	friend bool operator>(Keyword const& lhs, Keyword const& rhs);
	operator const std::string*(){return _keyword;}
	
	virtual void Interpret(Context context);
	friend bool operator< (Keyword const& lhs, std::string* const& rhs);
	
private:
	std::string *_keyword;
};





#endif
