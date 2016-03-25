#include "semantic.h"

struct SemanticType* checkExpressionType(struct Expression* expr) {
	struct SemanticType* type = (struct SemanticType*) malloc(sizeof(struct SemanticType));
	switch (expr->exprType) {
		case PRIMARY: {
			type = checkPrimaryExpressionType(expr->primaryExpr);
			break;
		}
		case NOT_UNARY_EXPR: 
		{
			if(expr->primaryExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME) 
			{
				
			}
			else if(expr->primaryExpr->semanticType->typeName == BOOL_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else
			{
				// error
			}
			break;
		}
		case PLUS_UNARY_EXPR:
		case MINUS_UNARY_EXPR: 
		{
			if (expr->primaryExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{

			}
			else if (expr->primaryExpr->semanticType->typeName == INT_TYPE_NAME)
				type->typeName = INT_TYPE_NAME;
			else if (expr->primaryExpr->semanticType->typeName == FLOAT32_TYPE_NAME)
				type->typeName = FLOAT32_TYPE_NAME;
			else 
			{
				// error
			}
			break;
		}
		case AND_EXPRESSION:
		case OR_EXPRESSION: 
		{
			if(expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				
			}
			else if(expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == BOOL_TYPE_NAME)
			{
				
			}
			else if(expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				
			}
			else if(expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME &&
			   expr->rightExpr->semanticType->typeName == BOOL_TYPE_NAME)
				type->typeName = BOOL_TYPE_NAME;
			else 
			{
				// error
			}
			break;
		}
		case EQU_EXPRESSION:
		case NE_EXPRESSION:
		case GT_EXPRESSION:
		case GTE_EXPRESSION:
		case LT_EXPRESSION:
		case LTE_EXPRESSION:
		{
			if(expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				
			}
			else if(expr->leftExpr->semanticType->typeName == 
				expr->rightExpr->semanticType->typeName)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else
			{
				// error
			}
			break;
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
			break;

		}
		case DECIMAL_EXPR: {
			type->typeName = INT_TYPE_NAME; 
			break;
		}
		case ID_EXPRESSION: {
			//??? how to get the semantic type of and declared id ? from constant table ???
			break;
		}
		default:
			break;
	}
	return type; 
}
