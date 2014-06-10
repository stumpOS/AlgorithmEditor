#include "LanguageBuilder.h"
#include "Token.h"
LanguageBuilder::LanguageBuilder(void)
{
}


LanguageBuilder::~LanguageBuilder(void)
{
}
AVLTree<Keyword*> *LanguageBuilder::CreateTree()
{
	EnclosedExpression::Separator *curly_brackets = new EnclosedExpression::Separator("{","}");
	std::string *str_literal = new std::string("instance");
	LiteralExpression *str = new LiteralExpression(str_literal);

	EnclosedExpression *algoExprsn = new EnclosedExpression(curly_brackets, str);

	AVLTree<Keyword*> *keywords = new AVLTree<Keyword*>();
	std::string *key = new std::string("DP");
	Keyword *keyword = new Keyword(key);
	
	keyword->SetExpression(algoExprsn);
	keywords->Insert(keyword);

	return keywords;
}