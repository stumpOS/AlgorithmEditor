#include "LanguageBuilder.h"
#include "Token.h"
LanguageBuilder::LanguageBuilder(void)
{
}


LanguageBuilder::~LanguageBuilder(void)
{
}
AVLTree<Keyword*> *LanguageBuilder::CreateKeywordTree()
{

	AVLTree<Keyword*> *keywords = new AVLTree<Keyword*>();

	std::string* keyword_str = new std::string("DP");
	
	Keyword *key = new Keyword(keyword_str);
	
	keywords->Insert(key);
	return keywords;
}

