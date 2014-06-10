#include "Interpreter.h"
#include "Document.h"
#include "LanguageBuilder.h"
#include "Token.h"
Interpreter::Interpreter(void)
{
	LanguageBuilder builder;
	_reservedWords = builder.CreateTree();
	_scanner = new Scanner(this);
}


Interpreter::~Interpreter(void)
{
	delete _scanner;
	delete _reservedWords;
}
void Interpreter::InterpretDocument(Document *doc)
{
	_scanner->TransformCharsToTokens(doc->GetSourceString());

}
