#include"TerminalExpressions.h"
#include"Token.h"
LiteralExpression::LiteralExpression(AsciiRange *ar)
{
	_characterRange = ar;
	_literal = NULL;
	_terminatingCharacter = "";
}
LiteralExpression::~LiteralExpression()
{
	if(_characterRange != NULL)
	{
		delete _characterRange;
		_characterRange = NULL;
	}
}
LiteralExpression::LiteralExpression(std::string *strng):TerminalExpression(strng)
{
	_characterRange = NULL;
	_literalInstance = "";
}
void LiteralExpression::Interpret(Context context)
{
	Expression::IsValidContext(context);
	_literalInstance = context.GetStringFromContext();

	if(_characterRange == NULL && _literal != NULL)
		InterpretWithString(context);
	else
		InterpretWithAsciiRange(context);
}
void LiteralExpression::InterpretWithString(Context context)
{
	if(*context.GetBegin()==*context.GetEnd())
	{
		AddNode(context.GetASTreeBuilder());
	}
	else
	{
		bool found = false;
		for(unsigned i=0;i<_literal->length() && found==false;i++)
		{
			if(*(context.GetBegin())==(*_literal)[i])
			{
				found = true;
			}
		}
		if(found)
		{
			context.AdvanceOneCharacter(); 
			InterpretWithString(context);
		}
		else if(!found)
		{
			throw std::invalid_argument("syntax error in string");
		}
	}
}
void LiteralExpression::InterpretWithAsciiRange(Context context)
{
	if(*context.GetBegin()==*context.GetEnd())
	{
		AddNode(context.GetASTreeBuilder());
	}
	else if(_characterRange->IsWithinRange(*context.GetBegin()))
	{
		context.AdvanceOneCharacter(); 
		InterpretWithAsciiRange(context);
	}
	else
	{
		throw std::invalid_argument("syntax error in string");
	}
}
void LiteralExpression::AddNode(Token *ast_builder)
{
	ast_builder->AddLeaf(_literalInstance);
}
ConstLiteralExpression::~ConstLiteralExpression()
{

}
void ConstLiteralExpression::Interpret(Context context)
{
	Expression::IsValidContext(context);
	bool match = true;
	for(unsigned i=0;context.GetBegin()+i != context.GetEnd() && match==true;i++)
	{
		if(i>=_literal->length())
			match = false;
		else if(*(context.GetBegin()+i)!=(*_literal)[i])
			match = false;
	}
	if(!match)
	{
		throw std::invalid_argument("syntax error in string literal");
	}
	else
	{
		AddNode(context.GetASTreeBuilder());
	}
}
void ConstLiteralExpression::AddNode(Token *ast_builder)
{
	ast_builder->AddInternalNode(*_literal);
}