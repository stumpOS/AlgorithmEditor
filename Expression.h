#pragma once
#ifndef EXPRESSION_H_
#define EXPRESSION_H_
#include<stdexcept>
#include<typeinfo>
#include<cstring>
#include<string>
#include "BinaryTree.h"

class Token;

class Context
{
public:
	Context(const char *start,const char *end):_begin(start),_end(end){}
	Context(const char *start,const char *end, Token *token):_begin(start),_end(end), _parseTreeBuilder(token){}
	void Set(const char *start, const char *end){_begin = start;_end = end;}
	void AdvanceOneCharacter(){_begin++;}
	const char *GetBegin(){return _begin;}
	const char *GetEnd(){return _end;}

	void SetASTreeBuilder(Token* token){_parseTreeBuilder = token;}
	Token* GetASTreeBuilder(){return _parseTreeBuilder;}

	std::string GetStringFromContext()
	{
		unsigned size = (unsigned)((_end - _begin)/sizeof(char));
		std::string str(_begin, size);
		return str;
	}

private:
	const char *_begin;
	const char *_end;

	Token *_parseTreeBuilder;
};

class RegularExpression
{
public:

	RegularExpression(){}
	virtual ~RegularExpression(){}
	virtual void Interpret(Context context) = 0;
	static const char* FindOccurrenceOf(const char *needle, Context context);
	void SafeDelete(RegularExpression *re);


protected:
	void IsValidContext(Context context);

};

class TerminalExpression:public RegularExpression
{
public:
	TerminalExpression();
	TerminalExpression(std::string *str):_literal(str){}
	virtual ~TerminalExpression();
	virtual void Interpret(Context context) = 0;
	virtual void AddNode(Token *ast_builder) = 0;
	
	std::string* GetLiteral(){return _literal;}
protected:
	std::string *_literal;
	
};

class NonTerminalExpression:public RegularExpression
{
public:
	NonTerminalExpression();
	NonTerminalExpression(RegularExpression *lhs,const char *delimiter, RegularExpression *rhs):
		_leftExpression(lhs), _rightExpression(rhs),_delimiter(delimiter){}
		
	NonTerminalExpression(const char* delimiter, RegularExpression *rhs):_delimiter(delimiter),_rightExpression(rhs){_leftExpression = NULL;}
	NonTerminalExpression(RegularExpression *lhs,const char* delimiter):_delimiter(delimiter),_leftExpression(lhs){_rightExpression = NULL;}
	virtual ~NonTerminalExpression();
	virtual void Interpret(Context context) = 0;
	
	void InterpretRightSide(Context context, const char *delimiter);
	void InterpretLeftSide(Context context, const char *delimiter);

	const char* GetDelimiter(){return _delimiter;}
	
protected:

	RegularExpression *_leftExpression;
	RegularExpression *_rightExpression;
	const char* _delimiter;
};





#endif