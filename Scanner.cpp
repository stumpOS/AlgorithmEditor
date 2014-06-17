#include "Scanner.h"
#include "Interpreter.h"
#include "Token.h"

Scanner::Scanner(Interpreter *interpreter):_interpreter(interpreter)
{
	_terminatingCharacter = ";";
}


Scanner::~Scanner(void)
{
}
void Scanner::TransformCharsToTokens(const char *source)
{
	if(*source != '\0')
	{
		AVLTree<Keyword*>* reservedWords = _interpreter->GetReservedWords();
	
		IsValid(source);

		unsigned indexOfContextBegin = 0;
		std::string *keyword_str = GetKeywordFromSource(source,indexOfContextBegin);

		Keyword *keyFound = reservedWords->Search<std::string *>(keyword_str)->GetNodeContents();

		const char *end;

		if(keyFound != NULL)
		{
			end = GetEndOfString(source);
			Context context(source+indexOfContextBegin, end,keyFound);
			
			keyFound->Interpret(context);
		}

		delete keyword_str;
		if(*end!='\0')
		{
			TransformCharsToTokens(end+1);
		}
	}
	
}
std::string* Scanner::GetKeywordFromSource(const char* source,unsigned &indexOfContextBegin)
{
	const char* current = source;
	char letter = *(current+indexOfContextBegin);

	while(IS_A_LETTER(letter))
	{
		indexOfContextBegin++;
		letter = *(current+indexOfContextBegin);
	}

	std::string *keyword_str = GetFormattedString(source,indexOfContextBegin);
	return keyword_str;
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
	while((*end_ptr != *_terminatingCharacter)&&(*end_ptr != '\0'))
	{
		end_ptr++;
	}
	return end_ptr;
}