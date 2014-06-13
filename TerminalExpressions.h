#pragma once
#ifndef TERMINALEXPRESSIONS_H_
#define TERMINALEXPRESSIONS_H_
#include "Expression.h"
#include<string>
class Token;

class LiteralExpression:public TerminalExpression
{
public:
	class AsciiRange{
	public:
		friend class LiteralExpression;
		AsciiRange(unsigned lowInclusive, unsigned highInclusive):_lowerBound(lowInclusive),_upperBound(highInclusive){}
		~AsciiRange(){}
		bool IsWithinRange(char x)
		{
			unsigned numeric_x = (unsigned)x;
			if(numeric_x <= _upperBound && numeric_x >= _lowerBound)
				return true;
			else
				return false;
		}		
	private:
		AsciiRange(){}
		unsigned _lowerBound;
		unsigned _upperBound;
	};
	LiteralExpression(std::string *strng);
	LiteralExpression(AsciiRange *ar);
	virtual ~LiteralExpression();

	virtual void Interpret(Context context);
	void InterpretWithString(Context context);
	void InterpretWithAsciiRange(Context context);

	virtual void AddNode(Token *ast_builder);

private:
	AsciiRange *_characterRange;
	const char* _terminatingCharacter;
	std::string _literalInstance;
};
class ConstLiteralExpression:public TerminalExpression
{
public:
	ConstLiteralExpression(std::string *strng):TerminalExpression(strng){}
	virtual ~ConstLiteralExpression();
	virtual void Interpret(Context context);

	virtual void AddNode(Token *ast_builder);
};

#endif

