#pragma once
#include "AVLTree.h"
#include"NonTerminalExpressions.h"
#include"TerminalExpressions.h"
#include<string>
#include<vector>
#include"Problem.h"
class Keyword;
class RegularExpression;

class LanguageBuilder
{
public:
	typedef LiteralExpression::AsciiRange Ascii_range;
	LanguageBuilder(void);
	~LanguageBuilder(void);

	RegularExpression *GetEnclosedExpression(const char* delimit_left, RegularExpression* re, const char* delimit_right);

	RegularExpression *GetKeyValueExpressionPair(std::string* key, const char* separator, RegularExpression *re);
	AVLTree<Keyword*> *CreateKeywordTree();

private:
	std::vector<Problem*> _problems;

};

