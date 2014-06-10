#include "AlgorithmDocument.h"


AlgorithmDocument::AlgorithmDocument(void)
{
	_sourceString = NULL;
}


AlgorithmDocument::~AlgorithmDocument(void)
{

}
void AlgorithmDocument::Destroy()
{
}
void AlgorithmDocument::SetSourceString(const char *content)
{
	Document::SetSourceString(content);
}
