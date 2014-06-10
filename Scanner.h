#pragma once
#ifndef SCANNER_H_
#define SCANNER_H_
#include<vector>
#include<cstring>
#include<string>
#include"ascii_codes.h"
class Interpreter;

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
	void IsValid(const char *source);
	static const char* GetEndOfString(const char*source);
	static std::string *GetFormattedString(const char* source, unsigned numberOfChars);
	static char *GetCharArrayFromSource(const char*source, unsigned numberOfChars);
private:
	Scanner();

	Interpreter *_interpreter;
};

#endif

