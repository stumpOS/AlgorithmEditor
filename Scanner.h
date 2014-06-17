#pragma once
#ifndef SCANNER_H_
#define SCANNER_H_
#include<vector>
#include<cstring>
#include<string>
#include"ascii_codes.h"
class Interpreter;
class Context;
class Keyword;
/*
the scanner converts a string of text into an array of tokens
it enforces the lexical grammar
*/

class Scanner
{
public:


	Scanner(Interpreter *interpreter);
	virtual ~Scanner(void);
	void TransformCharsToTokens(const char *source);
	void Interpret(Context context);
	void IsValid(const char *source);
	const char* GetEndOfString(const char*source);
	static std::string* GetKeywordAndUpdateContext(Context context);
	Keyword *ExtractKeyword(Context context);

private:
	Scanner();

	Interpreter *_interpreter;
	
};

#endif

