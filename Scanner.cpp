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
	if(*source != '\0')
	{
		Context context(source,GetEndOfString(source));

		Interpret(context);
	}
}
void Scanner::Interpret(Context context)
{
	Keyword *keyword = ExtractKeyword(context);
	if(keyword!=NULL)
	{
		keyword->Interpret(context);
		keyword->UpdateContext(context);
		if(*context.GetBegin()!='\0')
			Interpret(context);
	}

}
Keyword *Scanner::ExtractKeyword(Context context)
{
		AVLTree<Keyword*>* reservedWords = _interpreter->GetReservedWords();
	
		IsValid(context.GetBegin());

		std::string *keyword_str = GetKeywordAndUpdateContext(context);

		Keyword *keyword = reservedWords->Search<std::string *>(keyword_str)->GetNodeContents();

		delete keyword_str;
		return keyword;
}
std::string* Scanner::GetKeywordAndUpdateContext(Context context)
{
	char letter = *(context.GetBegin());
	unsigned i=0;
	while(IS_A_LETTER(letter))
	{
		i++;
		letter = *(context.GetBegin()+i);
	}

	std::string *keyword_str = new std::string(context.GetBegin(),context.GetBegin()+i);

	context.SetBegin(context.GetBegin()+i);
	return keyword_str;
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