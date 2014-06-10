#include "Scanner.h"
#include "Interpreter.h"
#include "Token.h"

Scanner::Scanner(Interpreter *interpreter):_interpreter(interpreter)
{
}


Scanner::~Scanner(void)
{
}
void Scanner::TransformCharsToTokens(const char *source)
{
	AVLTree<Keyword*>* reservedWords = _interpreter->GetReservedWords();
	
	IsValid(source);
	const char* current = source;
	unsigned index = 0;
	char letter = *(current+index);
	while(IS_A_LETTER(letter))
	{
		index++;
		letter = *(current+index);
	}

	std::string *keyword_str = GetFormattedString(source,index);

	Keyword *keyFound = reservedWords->Search<std::string *>(keyword_str)->GetNodeContents();

	if(keyFound != NULL)
	{
		keyFound->Interpret(Context(current+index, GetEndOfString(source)));
	}
	delete keyword_str;
	
}
std::string* Scanner::GetFormattedString(const char *source,unsigned numberOfChars)
{
	char *keyword = GetCharArrayFromSource(source,numberOfChars);

	std::string *keyword_str = new std::string(keyword);

	delete[] keyword;
	return keyword_str;
}
char* Scanner::GetCharArrayFromSource(const char *source,unsigned numberOfChars)
{
	char *charArray = new char[numberOfChars+1];
	strncpy(charArray,source,numberOfChars);
	charArray[numberOfChars] = '\0';
	return charArray;
}
void Scanner::IsValid(const char *source)
{
	if(source==NULL)
		throw std::bad_typeid("null source");
}
const char* Scanner::GetEndOfString(const char *source)
{
	const char *end_ptr = source;
	while(*end_ptr != '\0')
	{
		end_ptr++;
	}
	return end_ptr;
}