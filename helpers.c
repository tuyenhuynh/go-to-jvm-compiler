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


char* convertTypeToString(enum TypeNames type) {
	switch (type) {
	case STRING_TYPE_NAME:
		return "Ljava/lang/String;";
	case INT_TYPE_NAME:
		return "I";
	case FLOAT32_TYPE_NAME:
		return "F";
	case VOID_TYPE_NAME:
		return "V";
	default:
		return "UNKNOWN";
	}
}