#pragma once
#ifndef ALGORITHMDOCUMENT_H_
#define ALGORITHMDOCUMENT_H_

#include "Document.h"



class AlgorithmDocument: public Document
{
public:
	AlgorithmDocument(void);
	virtual ~AlgorithmDocument(void);
	virtual void Destroy();
	virtual void SetSourceString(const char *content);

	
};
#endif

