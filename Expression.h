#pragma once
#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include<stdexcept>
#include<typeinfo>
#include<cstring>
#include<string>
class Context
{
public:
	Context(const char *start,const char *end):_begin(start),_end(end){}
	void Set(const char *start, const char *end){_begin = start;_end = end;}
	const char *GetBegin(){return _begin;}
	const char *GetEnd(){return _end;}
private:
	const char *_begin;
	const char *_end;
};
class RegularExpression
{
public:

	RegularExpression(){}
	virtual ~RegularExpression(){}
	virtual void Interpret(Context context) = 0;
	static const char* FindOccurrenceOf(const char *needle, Context context);
protected:
	void IsValidContext(Context context);
};

class LiteralExpression:public RegularExpression
{
public:
	LiteralExpression(std::string *strng):_literal(strng){}
	virtual ~LiteralExpression();
	virtual void Interpret(Context context);
private:
	std::string *_literal;
};

class EnclosedExpression:public RegularExpression
{
public:
	class Separator{
	public:
		friend class EnclosedExpression;
		Separator(const char* lhs, const char *rhs):_left(lhs),_right(rhs){}
		virtual ~Separator()
		{
	
		}
	private:
		const char *_left;
		const char *_right;
	};
	EnclosedExpression(Separator *sep, RegularExpression *expression):_separator(sep),_internalExpression(expression){}
	~EnclosedExpression();
	virtual void Interpret(Context context);
	void UpdateContext(Context &context);
private:
	Separator *_separator;
	RegularExpression *_internalExpression;
};

class ListExpression:public RegularExpression
{
public:
	ListExpression(const char* delimiter):_delimiter(delimiter){_listItemExpression = NULL;}
	virtual void Interpret(Context context);
private:
	const char *_delimiter;
	RegularExpression *_listItemExpression;
};

#endif