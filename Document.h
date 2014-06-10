#pragma once
#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include<cstring>
/*
The Document represents the information in a document
once its read from its external source
*/

class Document
{
public:
	Document(void);
	virtual ~Document(void);
	
	void Save();
	virtual void Destroy() = 0;

	virtual void SetSourceString(const char* input);
	const char *GetSourceString(){return _sourceString;}
protected:
	const char *_sourceString;

};

#endif

