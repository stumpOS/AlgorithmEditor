#pragma once
#include "AVLTree.h"
#include"NonTerminalExpressions.h"
#include"TerminalExpressions.h"
#include<string>
#include<vector>
#include"Problem.h"
class Keyword;
class Expression;

class LanguageBuilder
{
public:
	typedef LiteralExpression::AsciiRange Ascii_range;
	LanguageBuilder(void);
	~LanguageBuilder(void);

	AVLTree<Keyword*> *CreateKeywordTree();

private:
	std::vector<Problem*> _problems;

};

