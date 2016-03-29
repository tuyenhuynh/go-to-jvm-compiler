#include "semantic.h"
#include <string.h>
#include "semantic_struct.h"
#include "helpers.h"


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
			return true;
		}
		case INC_SIMPLE_STMT:
		case DEC_SIMPLE_STMT:
		{
			struct SemanticType * type = checkExpressionType(simpleStmt->expr);
			if (type != NULL) {
				if (type->typeName != FLOAT32_TYPE_NAME && type->typeName != INT_TYPE_NAME) {
					return false;
				}
			}
			//add error msg
			return false;
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
		while(leftExpr != NULL && isOk != false)
		{
			isOk = checkSemanticAssignStmt(leftExpr, rightExpr, NULL);
			leftExpr = leftExpr->nextExpr;
			rightExpr = rightExpr->nextExpr;
		}
		//add error msg if !isOk
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
	if (leftExpr->semanticType->typeName != rightExpr->semanticType->typeName)
		return false;
	return true;
}

bool checkSemanticIfStmt(struct IfStmt* ifStmt, char* functionName) {
	bool isOk = true;
	
	if(ifStmt->ifStmtExpr == NULL)
	{
		// add error message
		isOk = false;
	}
	else if(ifStmt->block == NULL)
	{
		// add error message
		isOk = false;
	}
	else
	{
		if (ifStmt->ifStmtExpr->expr == NULL)
		{
			// add error message
			isOk = false;
		}
		else
		{
			if (ifStmt->ifStmtExpr->simpleStmt != NULL)
				isOk &= checkSemanticSimpleStmt(ifStmt->ifStmtExpr->simpleStmt, NULL);
			
			if(checkExpressionType(ifStmt->ifStmtExpr->expr)->typeName != BOOL_TYPE_NAME)
			{
				// add error message
				isOk &= false;
			}
		}
	}

	return isOk;
}

bool checkSemanticElseBlock(struct ElseBlock* elseBlock, char* functionName) {
	bool isOk = true;

	if(elseBlock->ifStmt != NULL)
	{
		isOk = checkSemanticIfStmt(elseBlock->ifStmt, NULL);
	}

	if(elseBlock->block != NULL)
	{
		isOk &= checkSemanticBlock(elseBlock->block, NULL);
	}
	else
	{
		// add error message 
		isOk &= false;
	}

	return isOk;
}

bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, char* functionName) {
	bool isOk = true;

	if (switchStmt->initialAndExpression != NULL)
	{
		switch (switchStmt->initialAndExpression->switchType)
		{
		case WITH_INITIAL_STMT:
		{
			isOk &= checkSemanticSimpleStmt(switchStmt->initialAndExpression->initialStmt, NULL);
			break;
		}
		case WITH_EXPRESSION:
		{
			if (switchStmt->initialAndExpression->expression == NULL)
			{
				// add error message 
				isOk &= false;
			}
			break;
		}
		case WITH_INITIAL_AND_EXPRESSION:
		{
			isOk &= checkSemanticSimpleStmt(switchStmt->initialAndExpression->initialStmt, NULL);
			if (switchStmt->initialAndExpression->expression == NULL)
			{
				// add error message 
				isOk &= false;
			}
			break;
		}
		}
	}
	else
	{
		// add error message
		isOk &= false;
	}

	if(switchStmt->switchBody != NULL)
	{
		if(switchStmt->switchBody->eccl != NULL)
		{
			struct ExpressionCaseClause *ecc = switchStmt->switchBody->eccl->firstExprCaseClause;
			while(ecc != NULL)
			{
				isOk &= checkSemanticExpressionCaseClause(ecc, NULL);
				ecc = ecc->nextExprCaseClause;
			}
		}
		else
		{
			// add error message
			isOk &= false;
		}
	}
	else
	{
		// add error message
		isOk &= false;
	}
	return isOk;
}

bool checkSemanticExpressionCaseClause(struct ExpressionCaseClause *ecc, char* functionName)
{
	bool isOk = true;
	if (ecc->expreSwitchCase != NULL && ecc->stmtList != NULL)
	{
		if (ecc->expreSwitchCase->exprList != NULL)
		{
			struct Expression *expr = ecc->expreSwitchCase->exprList->firstExpression;
			while(expr != NULL)
			{
				if (checkExpressionType(expr) == NULL)
					isOk &= false;
				expr = expr->nextExpr;
			}
		}
		else
			isOk = false;
	}
	else
		isOk = false;

	return isOk;
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
	return true;
}

bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, char* functionName)
{
	return true;
}

bool checkSemanticVarDecl(struct VarDecl* varDecl, char* functionName) {
	bool isOk = true; 
	//if(varDecl)
	return true;
}

bool checkSemanticConstDecl(struct ConstDecl* constDecl, char* functionName) {
	bool isOk = true;
	if (constDecl->varSpec != NULL) {
		struct VarSpec* varSpec = constDecl->varSpec; 
		isOk = checkSemanticConstSpec(varSpec, functionName); 
	}
	else if (constDecl->varSpecList != NULL) {
		struct VarSpec* varSpec = constDecl->varSpecList->firstVarSpec;
		while (varSpec != NULL) {
			isOk &= checkSemanticConstSpec(varSpec, functionName);
			varSpec = varSpec->nextVarSpec;
		}
		//The compiler not support untyped variables declaration
		isOk = false;
	}
	return isOk;
}

//TODO: check for value of constant (constant must have a value when it's declare, but in grammar, the value is optional)
bool checkSemanticConstSpec(struct VarSpec* varSpec, char* functionName) {
	bool isOk = true;
	//check for match of number of variables and number of values 
	if (varSpec->idListType != 0) {
		if (varSpec->exprList != 0) {
			if (varSpec->idListType->identifierList->size != varSpec->exprList->size) {
				printf("Variable count and value count mismatch in function %s ", functionName);
				isOk = false;
			}
			else {
				struct Identifier* id = varSpec->idListType->identifierList->firstId;
				struct Expression* expr = varSpec->exprList->firstExpression;
				while (expr != NULL) {
					//TODO: tackle the problem of how to retrieve the type of  expression if expression is an identifier
					//so in check Expression type, there should be a call to getVariableFromTable
					if (expr->exprType != INT_TYPE_NAME
						&& expr->exprType != FLOAT32_TYPE_NAME
						&& expr->exprType != STRING_TYPE_NAME
						&& expr->exprType != BOOL_TYPE_NAME) {
						//TODO: support const a int = 5 ; const b int = a ; 
						printf("Constant initializer %s is not a constant %s", id, functionName);
						isOk = false;
					}
					struct SemanticType* semanticType = checkExpressionType(expr);
					if (semanticType != NULL) {
						if (semanticType->typeName != varSpec->idListType->type->typeName) {
							printf("Types  mismatch in variable declaration in function %s", functionName);
							isOk = false;
						}
					}
					id = id->nextId;
					expr = expr->nextExpr;
				}
			}
		}
		else {
			printf("Missing value in constant declaration   %s", functionName);
		}
	}
	return isOk;
}

bool checkSemanticVarSpec(struct VarSpec* varSpec, char* functionName)
{	
	bool isOk = true; 
	//check for match of number of variables and number of values 
	if (varSpec->idListType != 0) {
		if (varSpec->exprList != 0) {
			if (varSpec->idListType->identifierList->size != varSpec->exprList->size) {
				printf("Variable count and value count mismatch in function %s ", functionName);
				isOk = false; 
			}
			else {
				struct Expression* expr = varSpec->exprList->firstExpression; 
				while (expr != NULL) {
					//TODO: tackle the problem of how to retrieve the type of  expression if expression is an identifier
					//so in check Expression type, there should be a call to getVariableFromTable
					struct SemanticType* semanticType =checkExpressionType(expr); 
					if (semanticType != NULL) {
						if (semanticType->typeName != varSpec->idListType->type->typeName) {
							printf("Types  mismatch in variable declaration in function %s", functionName);
							isOk = false; 
						}
					}
				}
			}
		}
	}
	else {
		//The compiler not support untyped variables declaration
		isOk = false; 
	}
	return isOk ;
}

//TODO: transform the multiple assignment to single assignment
bool addLocalVariablesToTable(struct VarSpec* varSpec, struct Method* method) {
	bool isOk = true;
	//here assumpt that we check semantic for variables first, then add them to local variable table
	if (checkSemanticVarSpec(varSpec, method->constMethodref->value.utf8)) {
		//TODO : implement size for variable
		if (varSpec->idListType != NULL) {
			struct IdentifierList* idList = varSpec->idListType->identifierList;
			struct Identifier* id = idList->firstId;
			struct Type* type = varSpec->idListType->type;
			while (id != NULL) {
				if (getLocalVariableFromTable(method->localVariablesTable, id->name) == NULL) {
					struct LocalVariable* localVariable = (struct LocalVariable*) malloc(sizeof(struct LocalVariable));
					localVariable->id = hashtable_size(method->localVariablesTable) + 1;
					struct SemanticType* semanticType = (struct SemanticType*) malloc(sizeof(struct SemanticType));
					semanticType->typeName = type->typeName;
					localVariable->type = semanticType;
					hashtable_add(method->localVariablesTable, id->name, localVariable);
				}
				else {
					isOk = false;
					printf("Variable with the same name %s exists in the table", id->name);
				}
				id = id->nextId;
			}
		}
		else {
			//The compiler currently doesnt support declarations without type 
			isOk = false; 
		}
	}
	else {
		isOk = false; 
	}
	return isOk; 
}

struct LocalVariable* getLocalVariableFromTable(char* varName, HashTable* variablesTable) {
	struct LocalVariable* result = (struct LocalVariable*) malloc(sizeof(struct LocalVariable));

	if (hashtable_get(variablesTable, varName, &result) == CC_OK) {
		return result; 
	}
	//fail
	return NULL; 
}

void addConstantToConstantTable(List* constantsTable, enum ConstantType type, void* value) {
	struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant));
	constant->type = type;
	switch (type) {
		case CONSTANT_Utf8: {
			if (getConstant(constantsTable, type, value) != NULL) {
				constant->value.utf8 = (char*)value; 
				list_add(constantsTable, constant); 
			}
			break;
		}
		case CONSTANT_String: {
			if (getConstant(constantsTable, type, value) != NULL) {
				constant->value.utf8 = (char*)value; 
				list_add(constantsTable, constant); 
			}
			break;
		}
		case CONSTANT_Integer: {
			if (getConstant(constantsTable, type, value) != NULL) {
				constant->value.intValue = *((int*)value);
				list_add(constantsTable, constant);
			}
			break;
		}
		case CONSTANT_Float: {
			if (getConstant(constantsTable, type, value) != NULL) {
				constant->value.floatValue = *((float*)value);
				list_add(constantsTable, constant);
			}
			break;
		}
		case CONSTANT_Class: {
			//check it
			if (getConstant(constantsTable, type, value) != NULL) {
				constant->value.utf8 = (char*)value;
				list_add(constantsTable, constant);
			}
			break;
		}
	}
}

struct Constant* getConstant(List* constantsTable, enum ConstantType type, void* value) {
	struct Constant* result = (struct Constant*)malloc(sizeof(struct Constant)); 
	int size = list_size(constantsTable);
	bool found = false; 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &result); 
		if (result->type == type) {
			switch (type) {
				case CONSTANT_Utf8: {
					if (strcpy(result->value.utf8, (char*)value) == 0) {
						found = true; 
					}
					break;
				}
				case CONSTANT_String: {
					if (strcpy(result->value.utf8, (char*)value) == 0) {
						found = true;
					}
					break;
				}
				case CONSTANT_Integer: {
					if (result->value.intValue == *((int*)value)) {
						found = true;
					}
					break;
				}
				case CONSTANT_Float: {
					if (result->value.floatValue == *((float*)value)) {
						found = true; 
					}
					break;
				}
				case CONSTANT_Class: {
					if (strcpy(result->value.utf8, (char*)value) == 0) {
						found = true;
					}
					break;
				}									
			}
		}
	}
	if (!found) {
		result = NULL; 
	}
	return result; 
}



bool addMethodRefToConstantTable(List* constantsTable, enum ConstantType type, char* className, char* methodName) {

}


/*
//Global constant table
bool addConstantToConstantTable(struct VarSpec* varSpec, HashTable* constantsTable) {

	bool isOk = true;
	//here assumpt that we check semantic for constants first, then add them to constants table
	if (checkSemanticConstSpec(varSpec, NULL)) {
		//TODO : implement size for variable
		if (varSpec->idListType != NULL) {
			struct Identifier* id = varSpec->idListType->identifierList->firstId;
			struct Type* type = varSpec->idListType->type;
			while (id != NULL) {
				if (getConstant(id->name, constantsTable) == NULL) {
					struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant));
					constant->id = hashtable_size(constantsTable) + 1;
					struct SemanticType* semanticType = (struct SemanticType*) malloc(sizeof(struct SemanticType));
					semanticType->typeName = type->typeName;
					localVariable->type = semanticType;
					hashtable_add(method->localVariablesTable, id->name, localVariable);
				}
				else {
					isOk = false;
					printf("Variable with the same name %s exists in the table", id->name);
				}
				id = id->nextId;
			}
		}
		else {
			//The compiler currently doesnt support declarations without type 
			isOk = false;
		}
	}
	else {
		isOk = false;
	}
	return isOk;
}

*/