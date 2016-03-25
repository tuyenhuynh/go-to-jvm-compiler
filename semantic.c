#include "semantic.h"
#define NULL 0

struct SemanticType* checkExpressionType(struct Expression* expr) {
	struct SemanticType* type = (struct SemanticType*) malloc(sizeof(struct SemanticType));
	switch (expr->exprType) 
	{
		case PRIMARY: {
			type = checkPrimaryExpressionType(expr->primaryExpr);
			break;
		}
		case NOT_UNARY_EXPR:
		{
			if (expr->primaryExpr->semanticType->typeName == BOOL_TYPE_NAME)
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
			if (expr->primaryExpr->semanticType->typeName == INT_TYPE_NAME)
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
			if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{

			}
			else if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == BOOL_TYPE_NAME)
			{

			}
			else if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{

			}
			else if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == BOOL_TYPE_NAME)
				type->typeName = BOOL_TYPE_NAME;
			else
			{
				// error
			}
			break;
		}
		case EQU_EXPRESSION:
		{
			// a == b
			if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			// checks e.g. a == 3.2 ; a == 3; a == "s"; a == true;
			else if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == FLOAT32_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == INT_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == STRING_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else if (expr->leftExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == BOOL_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}

			// checks e.g. 3.2 == a ; 3 == a; "s" == a; true == a;
			else if (expr->leftExpr->semanticType->typeName == FLOAT32_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else if (expr->leftExpr->semanticType->typeName == INT_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else if (expr->leftExpr->semanticType->typeName == STRING_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}
			else if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == IDENTIFIER_TYPE_NAME)
			{
				type->typeName = BOOL_TYPE_NAME;
			}


			// 3 == 2; true == false
			else if (expr->leftExpr->semanticType->typeName ==
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
		case NE_EXPRESSION:
		case GT_EXPRESSION:
		case GTE_EXPRESSION:
		case LT_EXPRESSION:
		case LTE_EXPRESSION:
		{

		}
	}

	return type;
}

struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr) {
	struct SemanticType* type = (struct SemanticType*)malloc(sizeof(struct SemanticType));
	//type->IS_ARRAY_ACCESS = false; 
	switch (primaryExpr->exprType) {
	case BOOL_TRUE_EXPRESSION:
	case BOOL_FALSE_EXPRESSION: {
		//TODO: implement this
		break;
	}
	case DECIMAL_EXPR: {
		type->typeName = INT_TYPE_NAME;
		break;
	}
	case FLOAT_EXPR: {
		type->typeName = FLOAT32_TYPE_NAME;
		break;
	}
	case STRING_EXPR: {
		type->typeName = STRING_TYPE_NAME;
		break;
	}
	case ID_EXPRESSION: {
		type->typeName = IDENTIFIER_TYPE_NAME;
		//add id to table of variable
		break;
	}
	case EXPRESSION: {
		//how to eliminate multilevel expression ???
		struct SemanticType* nestedType = checkExpressionType(primaryExpr->expr);
		type = nestedType;
		break;
	}
	case PE_COMPOSITE: {
		struct SemanticType* leftExpr = checkExpressionType(primaryExpr->primaryExpr->expr);
		struct SemanticType* rightExpr = checkExpressionType(primaryExpr->expr);
		if (leftExpr->typeName != IDENTIFIER_TYPE_NAME) {
			printf("Semantic error. Invalid array name type \n");
			type = NULL;
		}
		if (rightExpr->typeName != INT_TYPE_NAME) {
			printf("Semantic error. Index must be integer type \n"); 
			type = NULL;
		}
		else {
			//if identifier and expression type (int) is ok, how to know type of array access ???
			//from table of variables ???
			//TODO: define the type of this expression
		}
		break;
	}
	case FUNCTION_CALL:
	case FUNCTION_CALL_EMPTY: {
		//TODO: search the definition of function in constant table to find return type 
		break;
	}
	}
	primaryExpr->semanticType = type;
	return type;
}
