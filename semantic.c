#include "semantic.h"
#include <string.h>
#include "semantic_struct.h"
#include "helpers.h"

struct SemanticType* checkExpressionType(struct Expression* expr, struct Method* method) {
	struct SemanticType* type = (struct SemanticType*) malloc(sizeof(struct SemanticType));
	switch (expr->exprType) 
	{
		case PRIMARY: {
			type = checkPrimaryExpressionType(expr->primaryExpr, method);
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

//pass the method and program to this function
struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr, struct Method* method) {
	struct SemanticType* type = (struct SemanticType*)malloc(sizeof(struct SemanticType));
	//type->IS_ARRAY_ACCESS = false; 
	switch (primaryExpr->exprType) {
		case BOOL_TRUE_EXPRESSION:
		case BOOL_FALSE_EXPRESSION: {
			printf("Boolean primary expressions ar not supported\n");
			type = NULL; 
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
			struct SemanticType* nestedType = checkExpressionType(primaryExpr->expr, method);
			type = nestedType;
			break;
		}
		case PE_COMPOSITE: {
			struct SemanticType* leftExpr = checkExpressionType(primaryExpr->primaryExpr->expr, method);
			struct SemanticType* rightExpr = checkExpressionType(primaryExpr->expr, method);
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
		case FUNCTION_CALL:{
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
	//Initialize constantsTable
	list_new(&constantsTable); 
	semanticClass->constantsTable = constantsTable; 
	//Initialize fieldsTable
	hashtable_new(&fieldsTable); 
	semanticClass->fieldsTable = fieldsTable;
	//Initialize methodsTable 
	hashtable_new(&methodsTable); 
	semanticClass->methodsTable = methodsTable; 
	
	//add CLASS to constantsTAble
	struct Constant* constClassName = addUtf8ToConstantsTable(CLASS_NAME); 
	constantClass = (struct Constant*) malloc(sizeof(struct Constant)); 
	constantClass->type = CONSTANT_Class; 
	constantClass->utf8 = CLASS_NAME; 
	constantClass->id = list_size(constantsTable) + 1;
	list_add(constantsTable, constantClass);
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


//check and add function to method table
bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl) {
	bool isOk = true;
	struct Method* method = (struct Method*)malloc(sizeof(struct Method));
	//check for existing of method reference and add method to methods table + constants table if it does not exist
	if (hashtable_get(semanticClass->methodsTable, functionDecl, &method) != CC_OK) {
		//check semantic of parameter list
		struct ParameterList* paramList = functionDecl->signature->paramInParen->paramList; 
		isOk = checkSemanticParamList(paramList, functionDecl->identifier);
		if (!isOk) {
			return false; 
		}
		enum TypeNames typeName = getFunctionReturnType(functionDecl);
		if (typeName == UNKNOWN_TYPE) {
			printf("Semantic error. Unsupport return type in function %s\n", functionDecl->identifier);
			return false; 
		}
		if (functionDecl->block == NULL) {
			printf("Body of function %s not found", functionDecl->identifier);
			return false; 
		}

		//add name and type to constants table 
		char* returnTypeStr = convertTypeToString(typeName);
		char* methodDescriptor = createMethodDescriptor(paramList, returnTypeStr); 
		//add method ref to constants table
		struct Constant* constMethodRef = addMethodRefToConstantsTable(functionDecl->identifier, methodDescriptor); 
		
		/*-----------------*/
		//add method to methodsTable of class
		hashtable_add(methodsTable, functionDecl->identifier, method);

		//add variable to local variables table
		hashtable_new(&method->localVariablesTable);
		
		
		//TODO: check semantic of body
		
	}
	else {
		printf("Function with the same name as %s has been define\n", functionDecl->identifier); 
		bool isOk = false;
	}
	//TODO:check for compatible of return type in the body and in signature
	return isOk; 
}

//Here, propose that the semantic of  param list has been check
char* createMethodDescriptor(struct ParameterList* paramList, char* returnTypeStr) {
	if (paramList == NULL) {
		return "()"; 
	}
	char* result = (char*)malloc(100*sizeof (char)); 
	struct ParameterDeclare* param = paramList->firstParamDecl;
	char* ptr = result; 
	strcpy(ptr, "("); 
	ptr += 1; 
	while (param != NULL) {
		enum TypeNames typeName = param->type->typeName; 
		char* typeNameStr = convertTypeToString(typeName); 
		strcpy(ptr, typeNameStr); 
		ptr += strlen(typeNameStr); 
		param = param->nextParamDecl; 
	}
	strcpy(ptr, ")"); 
	ptr += 1; 
	strcpy(ptr, returnTypeStr); 
	return result; 
}

bool checkSemanticBlock(struct Block* block, struct Method* method) {
	bool isOk = true; 
	if (block->stmtList == NULL) {
		return true; 
	}
	struct Statement* stmt = block->stmtList->firstStmt; 
	while (stmt != NULL) {
		isOk &= checkSemanticStmt(stmt,method);
		stmt = stmt->nextStatement; 
	}
	return isOk; 
}

bool checkSemanticStmt(struct Statement* statement, struct Method* method) {
	switch (statement->stmtType) {
		case SIMPLE_STMT: {
			return checkSemanticSimpleStmt(statement->simpleStmt, method);
		}
		case VAR_DECL_STMT: {
			return checkSemanticVarDecl(statement->varDecl, method);
		}
		case CONST_DECL_STMT: {
			return checkSemanticConstDecl(statement->constDecl, method);
		}
		case BLOCK: {
			return checkSemanticBlock(statement->block, method);
		}
		case IF_STMT: {
			return checkSemanticIfStmt(statement->ifStmt, method);
		}
		case SWITCH_STMT: {
			return checkSemanticSwitchStmt(statement->switchStmt, method);
		}
		case FOR_STMT: {
			return checkSemanticForStmt(statement->forStmt, method);
		}
		case PRINT_STMT: {
			return checkSemanticPrintStmt(statement->printStatement, method);
		}
		case SCAN_STMT: {
			return checkSemanticScanStmt(statement->scanStatement, method);
		}
	}
	return true; 
}

bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, struct Method* method) {
	switch(simpleStmt->stmtType)
	{
		case EXPR_SIMPLE_STMT:
		{
			if (checkExpressionType(simpleStmt->expr, method) == NULL)
				return false;
			return true;
		}
		case INC_SIMPLE_STMT:
		case DEC_SIMPLE_STMT:
		{
			struct SemanticType * type = checkExpressionType(simpleStmt->expr, method);
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

bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, struct Method* method)
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

bool checkSemanticAssignStmt(struct Expression* leftExpr, struct Expression* rightExpr, struct Method* method)
{
	if (leftExpr->semanticType->typeName != rightExpr->semanticType->typeName)
		return false;
	return true;
}

bool checkSemanticIfStmt(struct IfStmt* ifStmt, struct Method* method) {
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
			
			struct SemanticType *type = checkExpressionType(ifStmt->ifStmtExpr->expr, method);

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

bool checkSemanticElseBlock(struct ElseBlock* elseBlock, struct Method* method) {
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

bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, struct Method*  method) {
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

bool checkSemanticExpressionCaseClause(struct ExpressionCaseClause *ecc, struct Method* method)
{
	bool isOk = true;
	if (ecc->expreSwitchCase != NULL && ecc->stmtList != NULL)
	{
		if (ecc->expreSwitchCase->exprList != NULL)
		{
			struct Expression *expr = ecc->expreSwitchCase->exprList->firstExpression;
			while(expr != NULL)
			{
				if (checkExpressionType(expr, method) == NULL)
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

bool checkSemanticForStmt(struct ForStmt* forStmt, struct Method* method) {
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
			checkExpressionType(forCondition->expression, method);
			if (forCondition->expression->semanticType->typeName != BOOL_TYPE_NAME) {
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

bool checkSemanticParamList(struct ParameterList* paramList, char* functionName) {
	struct ParameterDeclare* param = paramList->firstParamDecl; 
	bool isOk = true; 
	while (param != NULL && isOk ) {
		//check for existing of param name
		if (param->identifier == NULL) {
			printf("Semantic error. Parameter name not given. Function %s\n", functionName); 
			isOk = false; 
		}
		//check type of param
		struct Type* type = param->type; 
		if (type->expr == NULL &&
			(type->typeName == INT_TYPE_NAME ||
				type->typeName == FLOAT32_TYPE_NAME ||
				type->typeName == STRING_TYPE_NAME)) {
			//current param passed
			param = param->nextParamDecl;
		}
		else {
			printf("Semantic error. Unsupport type name in param list of function %s \n", functionName);
			isOk = false;
		}
	}
	return isOk;
}

//return type should be one of the following:	INT, FLOAT, STRING, VOID,// INT[], FLOAT[], STRING[]
//the format is (), (INT|FLOAT|STRING), INT, FLOAT, STRING
enum TypeNames  getFunctionReturnType(struct FunctionDecl* functionDecl) {
	enum TypeNames typeName;
	if (functionDecl->signature->result != NULL) {
		struct Result* returnType = functionDecl->signature->result;
		struct Type* type = NULL;
		if (returnType != NULL) {
			type = returnType->type;
		}
		else if (returnType->paramInParen != NULL) {
			//(int),(float), (string)
			struct ParameterList* paramList = returnType->paramInParen->paramList;
			//(a int) will not be accepted
			if (paramList != NULL && paramList->size == 1 && paramList->firstParamDecl->identifier == NULL) {
				type = paramList->firstParamDecl->type;
			}
		}
		else {
			typeName = VOID_TYPE_NAME;
		}
		if (type != NULL && type->expr == NULL) {
			typeName = type->typeName;
		}
		else {
			typeName = UNKNOWN_TYPE;
		}
	}
	else {
		typeName = VOID_TYPE_NAME;
	}
	return typeName;
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



bool checkSemanticPrintStmt(struct PrintStatement* printStmt, struct Method* method) {
	return true;
}

bool checkSemanticScanStmt(struct ScanStatement* scanStmt, struct Method* method) {
	return true; 
}

bool checkSemanticReturnStmt(struct ReturnStmt* returnStmt, struct Method* method)
{
	//Currently ,only statements which return one expression are implemented
	if (returnStmt->exprList->size == 1) {
		struct SemanticType* semanticType = checkExpressionType(returnStmt->exprList->firstExpression, method); 
		if (semanticType->typeName != method->returnType) {
			char* methodName = method->constMethodref->const2->utf8; 
			printf("Semantic error. Formal return type incompatible with declared return type in method %s\n", methodName); 
			return false; 
		}
		return true;
	}
	else {
		printf("Too many expressions in return statement\n"); 
		return false; 
	}
}

bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, struct Method* method)
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
			checkExpressionType(expr, method);
			if (expr->semanticType->typeName != param->type->typeName) {
				printf("Formal paramter's type and parameter's type mismatch\n"); 
				isOk = false; 
			}
			expr = expr->nextExpr; 
		}
	}
	return isOk;
}

bool checkSemanticVarDecl(struct VarDecl* varDecl, struct Method* method) {
	bool isOk = true; 
	//if(varDecl)
	return true;
}

bool checkSemanticConstDecl(struct ConstDecl* constDecl, struct Method* method) {
	bool isOk = true;
	char* functionName = ""; 
	if (method != NULL) {
		functionName = method->constMethodref->const2->utf8;
	}
	if (constDecl->constSpec != NULL) {
		struct ConstSpec* constSpec = constDecl->constSpec; 
		isOk = checkSemanticConstSpec(constSpec, method); 
	}
	else if (constDecl->constSpecList != NULL) {
		struct ConstSpec* constSpec = constDecl->constSpecList->firstConstSpec;
		while (constSpec != NULL) {
			isOk &= checkSemanticConstSpec(constSpec, method);
			constSpec = constSpec->nextConstSpec;
		}
		//The compiler not support untyped variables declaration
		isOk = false;
	}
	return isOk;
}

//TODO: check for value of constant (constant must have a value when it's declare, but in grammar, the value is optional)
bool checkSemanticConstSpec(struct ConstSpec* constSpec, struct Method* method) {
	bool isOk = true;
	char* methodName = ""; 
	if (method != NULL) {
		methodName = method->constMethodref->const2->utf8;
	}
	//check for match of number of variables and number of values 
	if (constSpec->idListType != 0) {
		if (constSpec->exprList != 0) {
			if (constSpec->idListType->identifierList->size != constSpec->exprList->size) {
				printf("Variable count and value count mismatch in function %s ", methodName);
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
						printf("Constant initializer %s is not a constant %s", id->name, methodName);
						isOk = false;
					}
					struct SemanticType* semanticType = checkExpressionType(expr, method);
					if (semanticType != NULL) {
						if (semanticType->typeName != constSpec->idListType->type->typeName) {
							printf("Types  mismatch in variable declaration in function %s", methodName);
							isOk = false;
						}
					}
					id = id->nextId;
					expr = expr->nextExpr;
				}
			}
		}
		else {
			printf("Missing value in constant declaration   %s", methodName);
		}
	}
	return isOk;
}

bool checkSemanticVarSpec(struct VarSpec* varSpec, struct Method* method)
{	
	bool isOk = true; 
	char* functionName = "";
	if (method != NULL) {
		functionName = method->constMethodref->const2->utf8; 
	}
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
					struct SemanticType* semanticType =checkExpressionType(expr, method); 
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
	if (checkSemanticVarSpec(varSpec,method)) {
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
					localVariable->type->typeName = semanticType->typeName;
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

struct LocalVariable* getLocalVariableFromTable( HashTable* variablesTable, char* varName) {
	struct LocalVariable* result = (struct LocalVariable*) malloc(sizeof(struct LocalVariable));

	if (hashtable_get(variablesTable, varName, &result) == CC_OK) {
		return result; 
	}
	//fail
	return NULL; 
}

struct Constant* addUtf8ToConstantsTable(char* utf8) {
	struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant)); 
	bool found = false; 
	int size = list_size(constantsTable); 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant);
		if (constant->type == CONSTANT_Utf8 && !strcmp(constant->utf8, utf8)) {
			found = true; 
		}
	}
	if (!found) {
		constant->type = CONSTANT_Utf8; 
		constant->utf8 = utf8;
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant; 
}

struct Constant* addNameAndTypeToConstantsTable(char* name, char* type) {

	struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant)); 
	struct Constant* nameConst = addUtf8ToConstantsTable(name); 
	struct Constant* typeConst = addUtf8ToConstantsTable(type); 
	int size = list_size(constantsTable); 
	bool found = false; 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant); 
		if (constant->type == CONSTANT_NameAndType && constant->const1 == nameConst && constant->const2 == typeConst) {
			found = true; 
		}
	}
	
	if (!found) {
		constant->type = CONSTANT_NameAndType; 
		constant->const1 = nameConst; 
		constant->const2 = typeConst; 
		constant->id = size + 1; 
		list_add(constantsTable, constant);
	}
	return constant; 

}

struct Constant* addFieldRefToConstantsTable(char* fieldName, char* typeName) {
	//field ref: 1. class 2. name and type 
	struct Constant* const1 = constantClass;
	struct Constant* const2 = addNameAndTypeToConstantsTable(fieldName, typeName);
	bool found = false; 
	int size = list_size(constantsTable);
	struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant));
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant); 
		if (constant->type  == CONSTANT_Fieldref && constant->const1 == const1 && constant->const2 == const2) {
			found = true; 
		}
	}
	if (!found) {
		constant->type = CONSTANT_Fieldref; 
		constant->const1 = const1; 
		constant->const2 = const2; 
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant; 
}

struct Constant* addMethodRefToConstantsTable(char* methodName, char* methodDescriptor) {
	struct Constant* constant = (struct Constant*) malloc(sizeof(struct Constant)); 
	int size = list_size(constantsTable); 
	struct Constant* const1 = constantClass; 
	struct Constant* const2 = addNameAndTypeToConstantsTable(methodName, methodDescriptor);
	bool found = false; 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant); 
		if (constant->type == CONSTANT_Methodref && constant->const1 == const1 && constant->const2 == const2) {
			found = true; 
		}
	}
	if (!found) {
		constant->type = CONSTANT_Methodref; 
		constant->const1 = const1; 
		constant->const2 = const2; 
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant; 
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
