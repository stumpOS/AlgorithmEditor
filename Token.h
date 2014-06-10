#pragma once
#ifndef TOKEN_H_
#define TOKEN_H_
#include <cstdlib>
#include <typeinfo>
#include<string>
#include<cstring>
#include "Expression.h"
class Context;
class RegularExpression;

class Token
{
public:
	Token(void);
	virtual ~Token(void);
	void Interpret(Context context);
	void SetExpression(RegularExpression *expression);
protected:
	RegularExpression *_expression;
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
	

	friend bool operator< (Keyword const& lhs, std::string* const& rhs);
	
private:
	std::string *_keyword;
};





#endif
