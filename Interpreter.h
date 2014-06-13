#pragma once
#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include"Scanner.h"

#include "AVLTree.h"

class Document;
class Keyword;

class Interpreter
{
public:
	Interpreter(void);
	virtual ~Interpreter(void);
	void InterpretDocument(Document *doc);
	AVLTree<Keyword*>* GetReservedWords(){return _reservedWords;}
private:
	Scanner *_scanner;
	AVLTree<Keyword*> *_reservedWords;
};
#endif

