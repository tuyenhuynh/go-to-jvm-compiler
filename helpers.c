#include "helpers.h"


int exprListSize(const struct ExpressionList* exprList)
{
	struct Expression *expr = exprList->firstExpression;
	int len = 0;
	while (expr != NULL)
	{
		len++;
		expr = expr->nextExpr;
	}
	return len;
}
