#include "NonTerminalExpressions.h"

void UnionExpression::Interpret(Context context)
{
	RegularExpression::IsValidContext(context);
	const char* delimiter;
	if(*_delimiter!='\0')
	{
		delimiter = RegularExpression::FindOccurrenceOf(_delimiter, context);
	}
	else
	{
		delimiter = RegularExpression::FindOccurrenceOf(" ", context);
	}

	if(delimiter != NULL)
	{
		InterpretLeftSide(context, delimiter);
		InterpretRightSide(context,delimiter);
	}
}



