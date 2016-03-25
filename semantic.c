#include "semantic.h"

struct SemanticType* checkExpressionType(struct Expression* expr) {
	struct SemanticType* type = (struct SemanticType*) malloc(sizeof(struct SemanticType));
	switch (expr->exprType) {
		case PRIMARY: {
			type = checkPrimaryExpressionType(expr->primaryExpr); 
		}
	}

	return type; 
}

struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr) {
	struct SemanticType* type = (struct SemanticType*) malloc(sizeof(struct SemanticType));

	switch (primaryExpr->exprType)
	{
		case BOOL_TRUE_EXPRESSION:
		case BOOL_FALSE_EXPRESSION: {
			type->typeName = BOOL_TYPE_NAME; 

		}
		case DECIMAL_EXPR: {
			type->typeName = INT_TYPE_NAME; 
		}
		case ID_EXPRESSION: {
			//??? how to get the semantic type of and declared id ? from constant table ???
		}
		default:
			break;
	}
	return type; 
}
