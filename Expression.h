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
	void SetBegin(const char *start){_begin = start;}
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

class Expression
{
public:

	Expression(){_terminatingChar = "";}
	virtual ~Expression(){}
	virtual void Interpret(Context context) = 0;
	static const char* FindOccurrenceOf(const char *needle, Context context);
	static const char* FindOccurenceOfStr(std::string* str, Context context);
	void SafeDelete(Expression *re);
	void SetTerminatingChar(const char *tc){_terminatingChar = tc;}
	virtual void UpdateContext(Context &context);
protected:
	void IsValidContext(Context context);
	const char *_terminatingChar;
};

class TerminalExpression:public Expression
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

class NonTerminalExpression:public Expression
{
public:
	NonTerminalExpression();
	NonTerminalExpression(NonTerminalExpression *nte,TerminalExpression *te):
		_nonterminalExpression(nte), _terminalExpression(te){}
	virtual ~NonTerminalExpression();
	virtual void Interpret(Context context) = 0;
	
protected:
	NonTerminalExpression *_nonterminalExpression;
	TerminalExpression *_terminalExpression;

};





#endif