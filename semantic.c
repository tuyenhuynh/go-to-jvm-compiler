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
	//create class to wrap programm
	semanticClass = (struct Class*)malloc(sizeof(struct Class));
	semanticClass->className = CLASS_NAME;
	//Create constantsTable
	List* constantsTable; 
	list_new(&constantsTable); 
	semanticClass->constantsTable = constantsTable; 
	//create fieldsTable
	HashTable* fieldsTable; 
	hashtable_new(&fieldsTable); 
	semanticClass->fieldsTable = fieldsTable;
	//create methodsTable
	HashTable* methodsTable; 
	hashtable_new(&methodsTable); 
	semanticClass->methodsTable = methodsTable; 
	//add CLASS to constantsTAble
	addConstantToConstantsTable(semanticClass->constantsTable, CONSTANT_Class, CLASS_NAME); 
	//
	bool isOk = true; 
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
	struct Method* method = (struct Method*)malloc(sizeof(struct Method)); 
	if (hashtable_get(semanticClass->methodsTable, functionDecl, &method) != CC_OK) {
		//add methodRef to constants table 
		char* type = getFunctionReturnType(functionDecl); 
		struct Constant* nameAndType = addRefConstantToConstantsTable(semanticClass->constantsTable, CONSTANT_NameAndType, functionDecl->identifier, type);
		struct Constant* clazz = getConstant(semanticClass->constantsTable, CONSTANT_Class, CLASS_NAME); 


		//TODO:check for existing of method reference

		//add methodRef to constantsTable
		
		struct Constant* constMethodRef = (struct Constant*)malloc(sizeof(struct Constant));
		constMethodRef->type = CONSTANT_Methodref; 
		constMethodRef->id = hashtable_size(semanticClass->constantsTable) +1 ;
		constMethodRef->value.ref.const1 = clazz; 
		constMethodRef->value.ref.const2 = nameAndType; 
		list_add(semanticClass->constantsTable, &constMethodRef);

		/*-----------------*/
		//add method to methodsTable of class
		hashtable_add(semanticClass->methodsTable, functionDecl->identifier, method);

		//add variable to local variables table
		hashtable_new(&method->localVariablesTable); 

		//check semantic of signature
		isOk = checkSemanticSignature(functionDecl->signature, functionDecl->identifier);
		//check semantic of body
		if (functionDecl->block != NULL) {
			isOk &= checkSemanticBlock(functionDecl->block, functionDecl->identifier);
		}
		else {
			printf("Body of function %s not found", functionDecl->identifier);
			isOk &= false;
		}
	}
	else {
		printf("Function with the same name as % has been define\n", functionDecl->identifier); 
		bool isOk = false;
	}
	//TODO:check for compatible of return type in the body and in signature
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
		//Dont need to check for isOk
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
			
			struct SemanticType *type = checkExpressionType(ifStmt->ifStmtExpr->expr);

			if (type != NULL){
				if (type->typeName != BOOL_TYPE_NAME)
				{
					// add error message
					isOk &= false;
				}
			}
			else
			{
				// adde error message
				isOk &= false;
			}
		}
	}
	
	if(ifStmt->block == NULL)
	{
		// add error message
		isOk = false;
	}
	else
	{
		isOk &= checkSemanticBlock(ifStmt->block, NULL);
	}

	if(ifStmt->elseBlock != NULL)
	{
		isOk &= checkSemanticElseBlock(ifStmt->elseBlock, NULL);
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
	bool isOk = true; 
	if (forStmt->forClause != NULL) {
		struct ForInitStmt* forInit = forStmt->forClause->forInitStmt; 
		struct ForCondition* forCondition = forStmt->forClause->forCondition; 
		struct ForPostStmt* forPostStmt = forStmt->forClause->forPostStmt; 
		if (forInit != NULL) {
			if (forInit->initStmt->stmtType == EXPR_SIMPLE_STMT) {
				printf("Initial statment of for expression cannot be an expression\n"); 
				isOk = false; 
			}
		}
		//check for expression type of for-condition
		if (forCondition != NULL) {
			checkExpressionType(forCondition->expression);
			if (forCondition->expression->semanticType != BOOL_TYPE_NAME) {
				printf("Condition of for statment must be boolean type\n"); 
				isOk = false; 
			}
		}
		if (forPostStmt != NULL) {
			if (forPostStmt->postStmt->stmtType == EXPR_SIMPLE_STMT) {
				printf("Post statment of for expression cannot be an expression\n");
				isOk = false; 
			}
		}
	}
	return isOk; 
}

bool checkSemanticSignature(struct Signature* signature, char* functionName) {
	bool isOk = true; 
	if (signature->paramInParen->paramList != NULL) {
		isOk = checkSemanticParamList(signature->paramInParen->paramList,functionName); 
	}
	if (signature->result != NULL) {
		isOk &= checkSemanticReturnType(signature->result, functionName); 
	}
	return isOk;
}

bool checkSemanticParamList(struct ParameterList* paramList, char* functionName) {
	struct ParameterDeclare* param = paramList->firstParamDecl; 
	bool isOk = true; 
	while (param != NULL) {
		if (param->identifier == NULL) {
			printf("Semantic error. Parameter name not given.\n" ); 
			isOk = false; 
		}
		if (param->type->typeName == IDENTIFIER_TYPE_NAME) {
			printf("Semantic error. Unsupport type name: %d", param->type->typeName); 
			isOk = false; 
		}
		if (isOk) {
			addParamToVariableTable(param, functionName);
		}
		param = param->nextParamDecl; 
	}
	return isOk;
}


bool addParamToVariableTable(struct ParameterDeclare* paramDeclare, struct Method* method) {
	bool isOk = true; 
	HashTable* hashtable = method->localVariablesTable; 
	struct LocalVariable* localVariable = (struct LocalVariable*) malloc(sizeof(struct LocalVariable)); 
	if (hashtable_get(hashtable, paramDeclare->identifier, &localVariable) != CC_OK) {
		localVariable->name = paramDeclare->identifier; 
		localVariable->type = paramDeclare->type; 
		localVariable->id = hashtable_size(hashtable) + 1; 
		hashtable_add(hashtable, paramDeclare->identifier, &localVariable);
	}
	else {
		//TODO: get method name
		printf("Variable with the same name in function %s has been defined", "method"); 
		isOk = false; 
	}
	return isOk; 
}

bool checkSemanticReturnType(struct Result* result) {
	bool isOk; 
	//The compiler supports functions which return one value
	if (result->type != NULL) {
		//INT|FLOAT|STRING|BOOL
		if (result->type->typeName == IDENTIFIER_TYPE_NAME) {
			printf("Semantic error. Unsupport type name: %d as return type\n", result->type->typeName);
			isOk = false;
		}
	}
	else {
		//(INT|FLOAT|STRING|BOOL)
		if (result->paramInParen->paramList != NULL) {
			struct ParameterList* paramList = result->paramInParen->paramList;
			if (paramList->firstParamDecl->nextParamDecl != NULL) {
				if (paramList->firstParamDecl->type == IDENTIFIER_TYPE_NAME) {
					printf("Semantic error. Unsupport type name: %d as return type\n", IDENTIFIER_TYPE_NAME);
					isOk = false;
				}
			}
			else {
				printf("Semantic error. Function with multiple return values not supported.\n");
				isOk = false;
			}
		}
		else {
			//()
			printf("Semantic error. Return type undefined.\n");
			isOk = false;
		}
	}
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
	//Currently ,only statements which return one expression are implemented
	if (returnStmt->exprList->size == 1) {
		return true;
	}
	else {
		printf("Too many expressions in return statement"); 
		return false; 
	}
}

bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, char* functionName)
{
	bool isOk = true; 
	if (exprList->size != paramList->size) {
		printf("Formal parameter count and parameter count mismatch\n"); 
		isOk = false; 
	}
	else {
		struct Expression* expr = exprList->firstExpression; 
		struct ParameterDeclare* param = paramList->firstParamDecl; 
		while (expr != NULL) {
			//call check expression type to define type
			checkExpressionType(expr);
			if (expr->semanticType != param->type) {
				printf("Formal paramter's type and parameter's type mismatch\n"); 
				isOk = false; 
			}
			expr = expr->nextExpr; 
		}
	}
	return isOk;
}

bool checkSemanticVarDecl(struct VarDecl* varDecl, char* functionName) {
	bool isOk = true; 
	//if(varDecl)
	return true;
}

bool checkSemanticConstDecl(struct ConstDecl* constDecl, char* functionName) {
	bool isOk = true;
	if (constDecl->constSpec != NULL) {
		struct ConstSpec* constSpec = constDecl->constSpec; 
		isOk = checkSemanticConstSpec(constSpec, functionName); 
	}
	else if (constDecl->constSpecList != NULL) {
		struct ConstSpec* constSpec = constDecl->constSpecList->firstConstSpec;
		while (constSpec != NULL) {
			isOk &= checkSemanticConstSpec(constSpec, functionName);
			constSpec = constSpec->nextConstSpec;
		}
		//The compiler not support untyped variables declaration
		isOk = false;
	}
	return isOk;
}

//TODO: check for value of constant (constant must have a value when it's declare, but in grammar, the value is optional)
bool checkSemanticConstSpec(struct ConstSpec* constSpec, char* functionName) {
	bool isOk = true;
	//check for match of number of variables and number of values 
	if (constSpec->idListType != 0) {
		if (constSpec->exprList != 0) {
			if (constSpec->idListType->identifierList->size != constSpec->exprList->size) {
				printf("Variable count and value count mismatch in function %s ", functionName);
				isOk = false;
			}
			else {
				struct Identifier* id = constSpec->idListType->identifierList->firstId;
				struct Expression* expr = constSpec->exprList->firstExpression;
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
						if (semanticType->typeName != constSpec->idListType->type->typeName) {
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


struct Constant* addConstantToConstantsTable(List* constantsTable, enum ConstantType type, void* value) {
	struct Constant* constant = getConstant(constantsTable, type, value); 
	if (constant == NULL) {
		constant = (struct Constant*) malloc(sizeof(struct Constant));
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
	return constant; 
}


struct Constant* addRefConstantToConstantsTable(List* constantsTable, enum ConstantType type, void* const1, void* const2) {
	
	struct Constant* constant1 = addConstantToConstantsTable(constantsTable, CONSTANT_Utf8, const1);
	struct Constant* constant2 = addConstantToConstantsTable(constantsTable, CONSTANT_Utf8, const2);
	
	struct Constant* constant = getRefConstant(constantsTable, type, (char*)const1, (char*)const2);
	if (constant == NULL) {
		constant = (struct Constant*) malloc(sizeof(struct Constant));
		constant->type = type; 
		constant->value.ref.const1 = constant1->value.utf8; 
		constant->value.ref.const2 = constant2->value.utf8; 
	}
	return constant; 
}

struct Constant* getRefConstant(List* constantsTable, enum  ConstantType type, char* const1, char* const2) {
	int size = list_size(constantsTable); 
	struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant)); 
	bool found = false; 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant); 
		if (strcpy(constant->value.ref.const1, const1) == 0
			&& strcpy(constant->value.ref.const2, const2) == 0
			&& type == constant->type) {
			found = true; 
		}
	}
	if (!found) {
		constant = NULL; 
	}
	return constant; 
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

struct Method* getMethod(struct Class* class, char* methodName) {
	struct Method* method = (struct Method*) malloc(sizeof(struct Method));
	if (hashtable_get(class->methodsTable, methodName, &method) == CC_OK) {
		return method; 
	}
	return NULL; 
}

struct Field* getField(struct Class* class, char* fieldName) {
	struct Field* field = (struct Field*) malloc(sizeof(struct Field));
	if (hashtable_get(class->fieldsTable, fieldName, &field) == CC_OK) {
		return field; 
	}
	return NULL; 
}

char* getFunctionReturnType(struct FunctionDecl* functionDecl) {
	char* result = NULL; 
	if (functionDecl->signature->result != NULL) {
		struct Result* returnType = functionDecl->signature->result; 
		struct Type* type; 
		if (returnType != NULL) {
			type = returnType->type;
		}
		else if (returnType->paramInParen != NULL) {
			if (returnType->paramInParen->paramList != NULL && returnType->paramInParen->paramList->firstParamDecl->nextParamDecl == NULL) {
				type = returnType->paramInParen->paramList->firstParamDecl->type; 
			}
		}
		if (type != NULL) {
			if (type == BOOL_TYPE_NAME) {
				result = "bool";
			}
			else if (type == INT_TYPE_NAME) {
				result = "int";
			}
			else if (type == FLOAT32_TYPE_NAME) {
				result = "float";
			}
			else if (type == STRING_TYPE_NAME) {
				result = "string";
			}
			else {
				result = NULL; 
			}
		}
		else {
			result = NULL; 
		}
	}
	else {
		result = "void"; 
	}
	result = NULL; 
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