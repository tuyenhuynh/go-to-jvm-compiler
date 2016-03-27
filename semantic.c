#include "semantic.h"
#include <string.h>

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
				printf("Semantic error. Operand must be bool type \n");
				type = NULL;
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
				printf("Semantic error. Operand must be int or bool type \n");
				type = NULL;
			}
			break;
		}
		case AND_EXPRESSION:
		case OR_EXPRESSION:
		{
			if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME &&
				expr->rightExpr->semanticType->typeName == BOOL_TYPE_NAME)
				type->typeName = BOOL_TYPE_NAME;
			else
			{
				printf("Semantic error. Left and right operands should be bool type \n");
				type = NULL;
			}
			break;
		}
		case EQU_EXPRESSION:
		case NE_EXPRESSION:
		{
			if (expr->leftExpr->semanticType->typeName == expr->rightExpr->semanticType->typeName)
				type->typeName = BOOL_TYPE_NAME;
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type = NULL;
			}
			break;
		}

		case GT_EXPRESSION:
		case GTE_EXPRESSION:
		case LT_EXPRESSION:
		case LTE_EXPRESSION:
		{
			if (expr->leftExpr->semanticType->typeName == expr->rightExpr->semanticType->typeName)
			{
				if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be bool type \n");
					type = NULL;
				}
				else
				{
					type->typeName = BOOL_TYPE_NAME;
				}
			}
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type = NULL;
			}
			break;
		}

		case PLUS_EXPRESSION:
		{
			if(expr->leftExpr->semanticType->typeName == expr->rightExpr->semanticType->typeName)
			{
				if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be bool type \n");
					type = NULL;
				}
				
				else if (expr->leftExpr->semanticType->typeName == FLOAT32_TYPE_NAME)
					type->typeName = FLOAT32_TYPE_NAME;
				
				else if (expr->leftExpr->semanticType->typeName == INT_TYPE_NAME)
					type->typeName = INT_TYPE_NAME;
				
				else if (expr->leftExpr->semanticType->typeName == STRING_TYPE_NAME)
					type->typeName = STRING_TYPE_NAME;
				
				else
				{
					printf("Semantic error. Unknown type \n");
					type = NULL;
				}
			}
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type = NULL;
			}
			break;
		}
		case MINUS_EXPRESSION:
		case MUL_EXPRESSION:
		{
			if (expr->leftExpr->semanticType->typeName == expr->rightExpr->semanticType->typeName)
			{
				if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be bool type \n");
					type = NULL;
				}

				else if (expr->leftExpr->semanticType->typeName == FLOAT32_TYPE_NAME)
					type->typeName = FLOAT32_TYPE_NAME;

				else if (expr->leftExpr->semanticType->typeName == INT_TYPE_NAME)
					type->typeName = INT_TYPE_NAME;

				else if (expr->leftExpr->semanticType->typeName == STRING_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be string type \n");
					type = NULL;
				}

				else
				{
					printf("Semantic error. Unknown type \n");
					type = NULL;
				}
			}
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type = NULL;
			}
			break;
		}
		
		case DIV_EXPRESSION:
		{
			if (expr->leftExpr->semanticType->typeName == expr->rightExpr->semanticType->typeName)
			{
				if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be bool type \n");
					type = NULL;
				}

				else if (expr->leftExpr->semanticType->typeName == FLOAT32_TYPE_NAME)
					type->typeName = FLOAT32_TYPE_NAME;

				else if (expr->leftExpr->semanticType->typeName == INT_TYPE_NAME)
					type->typeName = FLOAT32_TYPE_NAME;

				else if (expr->leftExpr->semanticType->typeName == STRING_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be string type \n");
					type = NULL;
				}

				else
				{
					printf("Semantic error. Unknown type \n");
					type = NULL;
				}
			}
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type = NULL;
			}
			break;
		}
		case MOD_EXPRESSION: 
		{
			if (expr->leftExpr->semanticType->typeName == expr->rightExpr->semanticType->typeName)
			{
				if (expr->leftExpr->semanticType->typeName == BOOL_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be bool type \n");
					type = NULL;
				}

				else if (expr->leftExpr->semanticType->typeName == FLOAT32_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be float type \n");
					type = NULL;
				}

				else if (expr->leftExpr->semanticType->typeName == INT_TYPE_NAME)
					type->typeName = FLOAT32_TYPE_NAME;

				else if (expr->leftExpr->semanticType->typeName == STRING_TYPE_NAME)
				{
					printf("Semantic error. Left and right operands shouldn't be string type \n");
					type = NULL;
				}

				else
				{
					printf("Semantic error. Unknown type \n");
					type = NULL;
				}
			}
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type = NULL;
			}
			break;
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

bool doSemantic(struct Program* program) {
	bool isOk = true; 
	if (program->pkg != NULL) {
		char* packageName = program->pkg->packageName;
		if (strcmp(packageName, "main") != 0) {
			printf("Semantic error. Package name must be main\n");
			isOk = false;
		}
		
	}

	struct DeclarationList* declList = program->declList;
	
	if (declList != NULL) {
		struct Declaration* decl = declList->firstDecl;
		while (decl != NULL) {
			if (decl->declType == CONST_DECL) {
				isOk &= checkSemanticConstDecl(decl->constDecl, NULL);
			}
			else if (decl->declType == VAR_DECL) {
				isOk &= checkSemanticVarDecl(decl->varDecl, NULL);
			}
			else if (decl->declType == FUNC_DECL) {
				isOk &= checkSemanticFunctionDecl(decl->funcDecl);
			}
		}
	}
	else {
		printf("Semantic error. No declaration found");
		isOk = false; 
	}
	//yield an error if function main not found 
	return isOk; 
}

bool checkSemanticVarDecl(struct VarDecl* varDecl, char* functionName) {
	return true; 
}
bool checkSemanticConstDecl(struct ConstDecl* constDecl, char* functionName) {
	return true; 
}

bool checkSemanticVarSpec(struct VarSpec* varSpec, char* functionName)
{
}

bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl) {
	bool isOk = true; 
	isOk = checkSemanticSignature(functionDecl->signature);
	if (functionDecl->block != NULL) {
		isOk &= checkSemanticBlock(functionDecl->block, functionDecl->identifier);
	}
	else {
		printf("Body of function %s not found", functionDecl->identifier); 
		isOk &= false; 
	}
	return isOk; 
}

bool checkSemanticBlock(struct Block* block, char* functionName) {
	bool isOk = true; 
	if (block->stmtList == NULL) {
		return true; 
	}
	struct Statement* stmt = block->stmtList->firstStmt; 
	while (stmt != NULL) {
		isOk &= checkSemanticStmt(stmt, functionName);
		stmt = stmt->nextStatement; 
	}
	return isOk; 
}


bool checkSemanticStmt(struct Statement* statement, char* functionName) {
	switch (statement->stmtType) {
		case SIMPLE_STMT: {
			return checkSemanticSimpleStmt(statement->simpleStmt, functionName);
		}
		case VAR_DECL_STMT: {
			return checkSemanticVarDecl(statement->varDecl, functionName);
		}
		case CONST_DECL_STMT: {
			return checkSemanticConstDecl(statement->constDecl, functionName);
		}
		case BLOCK: {
			return checkSemanticBlock(statement->block, functionName);
		}
		case IF_STMT: {
			return checkSemanticIfStmt(statement->ifStmt, functionName);
		}
		case SWITCH_STMT: {
			return checkSemanticSwitchStmt(statement->switchStmt, functionName);
		}
		case FOR_STMT: {
			return checkSemanticForStmt(statement->forStmt, functionName);
		}
		case PRINT_STMT: {
			return checkSemanticPrintStmt(statement->printStatement, functionName);
		}
		case SCAN_STMT: {
			return checkSemanticScanStmt(statement->scanStatement, functionName);
		}
	}
	return true; 
}

bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, char* functionName) {
	switch(simpleStmt->stmtType)
	{
		case EXPR_SIMPLE_STMT:
		{
			if (checkExpressionType(simpleStmt->expr) == NULL)
				return false;
			break;
		}
		case INC_SIMPLE_STMT:
		case DEC_SIMPLE_STMT:
		{
			if (checkExpressionType(simpleStmt->expr) != NULL)
			{
				if (checkExpressionType(simpleStmt->expr)->typeName != FLOAT32_TYPE_NAME ||
					checkExpressionType(simpleStmt->expr)->typeName != INT_TYPE_NAME)
					return false;
			}
			else
				//add error msg
				return false;
			break;
		}

		case ASSIGN_STMT:
		{
			if (simpleStmt->exprListLeft != NULL && simpleStmt->exprListRight != NULL)
			{
				return checkSemanticAssignStmtList(simpleStmt->exprListLeft, simpleStmt->exprListRight, NULL);
			}
			//add error msg
			return false;
		}
		case PLUS_ASSIGN_STMT:
		case MINUS_ASSIGN_STMT:
		case MUL_ASSIGN_STMT:
		case DIV_ASSIGN_STMT: {
			if (simpleStmt->exprListLeft != NULL && simpleStmt->exprListRight != NULL)
			{
				if(exprListSize(simpleStmt->exprListLeft) == 1 && exprListSize(simpleStmt->exprListRight) == 1)
				{
					return checkSemanticAssignStmtList(simpleStmt->exprListLeft, simpleStmt->exprListRight, NULL);
				}
				// add error msg
				return false;
			}
			// add error msg
			return false;
		}
	}
	return true;
}

bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, char* functionName)
{
	bool isOk = true;
	if (exprListSize(leftExprList) == exprListSize(rightExprList))
	{
		struct Expression *leftExpr = leftExprList->firstExpression;
		struct Expression *rightExpr = rightExprList->firstExpression;
		while(leftExpr != NULL || isOk != false)
		{
			isOk = checkSemanticAssignStmt(leftExpr, rightExpr, NULL);
			leftExpr = leftExpr->nextExpr;
			rightExpr = rightExpr->nextExpr;
		}
	}
	else
	{
		printf("Assignment count mismatch \n");
		isOk = false;
	}
	return isOk;
}

bool checkSemanticAssignStmt(struct Expression* leftExpr, struct Expression* rightExpr, char* functionName)
{
	if (leftExpr->semanticType != rightExpr->semanticType)
		return false;
	return true;
}

bool checkSemanticIfStmt(struct IfStmt* ifStmt, char* functionName) {
	return true; 
}
bool checkSemanticElseBlock(struct ElseBlock* elseBlock, char* functionName) {
	return true; 
}
bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, char* functionName) {
	return true; 
}
bool checkSemanticForStmt(struct ForStmt* forStmt, char* functionName) {
	return true; 
}
bool checkSemanticSignature(struct Signature* signature) {
	return true;
}
bool checkSemanticParamList(struct ParameterList* paramList) {
	return true;
}
bool checkSemanticReturnType(struct Result* result) {
	return true;
}
bool checkSemanticPrintStmt(struct PrintStatement* printStmt, char* functionName) {
	return true;
}
bool checkSemanticScanStmt(struct ScanStatement* scanStmt, char* f) {
	return true; 
}

bool checkSemanticReturnStmt(struct ReturnStmt* returnStmt)
{
}

bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, char* functionName)
{
}
