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
	AVLTree<int> testTree;
	testTree.Insert(5);
	testTree.Insert(6);
	testTree.Insert(2);
	testTree.Insert(3);
	testTree.Insert(4);


	AVLTree<Keyword*> *keywords = new AVLTree<Keyword*>();
	Ascii_range *range = new Ascii_range(97,120);
	LiteralExpression *identifier = new LiteralExpression(range);

	std::string* keyword_str = new std::string("DP");
	
	std::string *str = new std::string("+");
	ConstLiteralExpression *plus = new ConstLiteralExpression(str);

	
	UnionExpression *add_r = new UnionExpression(plus,"",identifier);
	UnionExpression *add = new UnionExpression(identifier,"", plus);
	RegularExpression *re = GetEnclosedExpression("{",add,"}");

	Keyword *key = new Keyword(keyword_str);
	key->SetExpression(re);
	keywords->Insert(key);
	return keywords;
}
RegularExpression* LanguageBuilder::GetEnclosedExpression(const char* delimit_left, RegularExpression* re, const char* delimit_right)
{

	UnionExpression *left_exp = new UnionExpression(delimit_left,re);
	UnionExpression *exp = new UnionExpression(left_exp,delimit_right);

	return exp;
}
RegularExpression * LanguageBuilder::GetKeyValueExpressionPair(std::string* key, const char* separator, RegularExpression *identifier)
{
	ConstLiteralExpression *key_exp = new ConstLiteralExpression(key);
	UnionExpression *kv_pair_expression = new UnionExpression(identifier, separator,key_exp);
	return kv_pair_expression;
}
