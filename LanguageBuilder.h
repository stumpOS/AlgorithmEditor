#pragma once
#include "AVLTree.h"
#include"Expression.h"
#include<string>
class Keyword;

class LanguageBuilder
{
public:
	LanguageBuilder(void);
	~LanguageBuilder(void);

	AVLTree<Keyword*> *CreateTree();
};

