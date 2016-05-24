#include "semantic.h"
#include <string.h>
#include "semantic_struct.h"
#include "helpers.h"


char* CLASS_NAME = "GO_CLASS";
int scope = 0;

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
			type = checkPrimaryExpressionType(expr->primaryExpr, method); 
			
			if (type->typeName != BOOL_TYPE_NAME)
			{
				printf("Semantic error. Operand must be bool type \n");
				type->typeName = UNKNOWN_TYPE;
			}
			break;
		}
		case PLUS_UNARY_EXPR:
		case MINUS_UNARY_EXPR:
		{
		
			type = checkPrimaryExpressionType(expr->primaryExpr, method); 
			if(type->typeName != FLOAT32_TYPE_NAME && type->typeName != INT_TYPE_NAME){
				printf("Semantic error. Type of plus/minus unary expression should be int or float \n");
				type->typeName = UNKNOWN_TYPE;
			}
			break;
		}
		case AND_EXPRESSION:
		case OR_EXPRESSION:
		{
			struct SemanticType* leftType = checkExpressionType(expr->leftExpr, method); 
			struct SemanticType* rightType = checkExpressionType(expr->rightExpr, method); 
			
			if (leftType->typeName == BOOL_TYPE_NAME &&
				rightType->typeName == BOOL_TYPE_NAME)
				type->typeName = BOOL_TYPE_NAME;
			else
			{
				printf("Semantic error. Left and right operands of logical operator should be bool type \n");
				type->typeName = UNKNOWN_TYPE;
			}
			break;
		}
		case EQU_EXPRESSION:
		case NE_EXPRESSION:
		{
			struct SemanticType* leftType = checkExpressionType(expr->leftExpr, method);
			struct SemanticType* rightType = checkExpressionType(expr->rightExpr, method);
			
			if (leftType->typeName != rightType->typeName || leftType->typeName == UNKNOWN_TYPE)
			{
				printf("Semantic error. Left and right operands of comparation should be same type\n");
				type->typeName = UNKNOWN_TYPE;
			}
			else {
				type->typeName = BOOL_TYPE_NAME;				
			}
			break;
		}
		case GT_EXPRESSION:
		case GTE_EXPRESSION:
		case LT_EXPRESSION:
		case LTE_EXPRESSION:
		{
			struct SemanticType* leftType = checkExpressionType(expr->leftExpr, method); 
			struct SemanticType* rightType = checkExpressionType(expr->rightExpr, method);

			if (leftType->typeName == INT_TYPE_NAME && rightType->typeName == INT_TYPE_NAME ||
				leftType->typeName == FLOAT32_TYPE_NAME && rightType->typeName == FLOAT32_TYPE_NAME||
				leftType->typeName == BOOL_TYPE_NAME && rightType->typeName == BOOL_TYPE_NAME) {
				type->typeName = BOOL_TYPE_NAME;
			}
			else {
				if (leftType->typeName != UNKNOWN_TYPE && rightType->typeName != UNKNOWN_TYPE) {
					printf("Semantic error. Left and right operands of comparation should be same type\n");
				}
				type->typeName = UNKNOWN_TYPE; 
			}
			
			break;
		}

		case PLUS_EXPRESSION:
		case MINUS_EXPRESSION:
		case MUL_EXPRESSION:
		case DIV_EXPRESSION:
		case MOD_EXPRESSION:
		{
			struct SemanticType*  leftType = checkExpressionType(expr->leftExpr, method);
			struct SemanticType* rightType = checkExpressionType(expr->rightExpr, method);
			if (leftType->typeName == rightType->typeName && leftType->typeName != UNKNOWN_TYPE)
			{
				if (expr->exprType == PLUS_EXPRESSION) {
					type->typeName = leftType->typeName; 
				}
				if (expr->exprType == MINUS_EXPRESSION) {
					if (leftType->typeName == STRING_TYPE_NAME || rightType->typeName == STRING_TYPE_NAME) {
						printf("Semantic error. Operands of subtract cannot be string\n");
						type->typeName = UNKNOWN_TYPE;
					}
					else {
						type->typeName = leftType->typeName;
					}
				}
				else if (expr->exprType == MUL_EXPRESSION) {
					if (leftType->typeName == STRING_TYPE_NAME || rightType->typeName == STRING_TYPE_NAME) {
						printf("Semantic error. Operands of multiple cannot be string\n");
						type->typeName = UNKNOWN_TYPE;
					}
					else {
						type->typeName = leftType->typeName;
					}
				}
				else if (expr->exprType == DIV_EXPRESSION) {
					if (leftType->typeName == STRING_TYPE_NAME || rightType->typeName == STRING_TYPE_NAME) {
						printf("Semantic error. Operands of division cannot be string\n");
						type->typeName = UNKNOWN_TYPE;
					}
					else {
						type->typeName = leftType->typeName;
					}
				}
				else if (expr->exprType == MOD_EXPRESSION) {
					if (leftType->typeName != INT_TYPE_NAME || rightType->typeName != INT_TYPE_NAME) {
						printf("Semantic error. Incompatible types of modulo operation\n");
					}
					else {
						type->typeName = INT_TYPE_NAME;
					}
				}
			}
			else
			{
				printf("Semantic error. Left and right operands should be same type\n");
				type->typeName = UNKNOWN_TYPE;
			}
			break;
		}				
	}
	expr->semanticType = type;
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
			type ->typeName = UNKNOWN_TYPE; 
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
			struct LocalVariable* variable = findActiveLocalVariableById(method->localVariablesTable, primaryExpr->identifier);
			if (variable == NULL) {
				struct Field* field = getField(semanticClass, primaryExpr->identifier); 
				if (field == NULL) {
					printf("Semantic error. Identifier %s not declared\n", primaryExpr->identifier);
					type ->typeName = UNKNOWN_TYPE; 
				}
				else {
					type->typeName = field->type->typeName; 
					type->idNum = field->id; 
				}
			}
			else {
				type->typeName = variable->type->typeName; 
				type->idNum = variable->id; 
			}
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
			struct FunctionCall* functionCall = primaryExpr->funcCall;
			char* methodName = functionCall->primaryExpr->identifier; 
			struct Method* calledMethod = getMethod(semanticClass, methodName); 
			if (calledMethod != NULL) {
				bool isOk = checkSemanticFunctionCall(functionCall->exprList, calledMethod->paramList,  method);
				if (isOk) {
					type->typeName = calledMethod->returnType;
					method->returnType; 
				}
			}
			else {
				printf("Semantic error. Method %s not declared\n", methodName);
				type->typeName = UNKNOWN_TYPE; 
			}
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
	
	//add CLASS's name to constantsTAble
	struct Constant* constClassName = addUtf8ToConstantsTable(CLASS_NAME); 
	//add class to constants table
	constantClass = addClassToConstantsTable(CLASS_NAME);
	
	//
	bool isOk = true; 
	struct DeclarationList* declList = program->declList;
	
	if (declList != NULL) {
		struct Declaration* decl = declList->firstDecl;
		while (decl != NULL && isOk) {
			if (decl->declType == CONST_DECL) {
				isOk = checkSemanticConstDecl(decl->constDecl, NULL);
			}
			else if (decl->declType == VAR_DECL) {
				isOk = checkSemanticVarDecl(decl->varDecl, NULL);
			}
			else if (decl->declType == FUNC_DECL) {
				isOk = checkSemanticFunctionDecl(decl->funcDecl);
			}
			decl = decl->nextDecl; 
		}
	}

	//TODO: yield an error if function main not found
	//check semantic main function (function without parameters)
	return isOk; 
}


//check and add function to method table
bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl) {
	bool isOk = true; 
	struct Method* method = NULL; // (struct Method*)malloc(sizeof(struct Method));
	//check for existing of method reference and add method to methods table + constants table if it does not exist
	if (hashtable_get(semanticClass->methodsTable, functionDecl, &method) != CC_OK) {
		//check semantic of parameter list
		struct ParameterList* paramList = functionDecl->signature->paramInParen->paramList; 
		if (paramList != NULL) {
			isOk = checkSemanticParamList(paramList, functionDecl->identifier);
			if (!isOk) {
				printf("Semantic error. Unsupport types in parameter declaration in function %s\n", functionDecl->identifier);
				return false;
			}
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
		//add return type to constant table
		char* returnTypeStr = convertTypeToString(typeName);
		addUtf8ToConstantsTable(returnTypeStr); 
		//add name and type to constants table 
		char* methodDescriptor = createMethodDescriptor(paramList, returnTypeStr);
		//add method ref to constants table
		struct Constant* constMethodRef = addMethodRefToConstantsTable(functionDecl->identifier, methodDescriptor);
		//create method
		method = (struct Method*)malloc(sizeof(struct Method)); 
		method->constMethodref = constMethodRef;
		method->returnType = typeName;
		method->paramList = paramList; 

		/*-----------------*/
		//add method to methodsTable of class
		hashtable_add(methodsTable, functionDecl->identifier, method);

		//add variable to local variables table
		list_new(&method->localVariablesTable);
		if (paramList != NULL) {
			struct ParameterDeclare* param = paramList->firstParamDecl;
			while (param != NULL && isOk) {
				addUtf8ToConstantsTable(param->identifier); 
				char* paramTypeStr = convertTypeToString(param->type->typeName); 
				addUtf8ToConstantsTable(paramTypeStr);
				isOk = addParamToLocalVarsTable(param, method);
				
				if (isOk) {
					param = param->nextParamDecl;
				}
				else {
					printf("Variable with the same name in function %s has been defined\n", functionDecl->identifier);
				}
			}
		}

		//TODO: check semantic of body
		if (isContainStatementType(functionDecl->block->stmtList, BREAK_STMT)) {
			printf("Semantic Error. Invalid break statement in function definition\n");
			return false; 
		}
		else if (isContainStatementType(functionDecl->block->stmtList, CONTINUE_STMT)) {
			printf("Semantic Error. Invalid continue statement in function definition\n");
			return false;
		}

		isOk = checkSemanticBlock(functionDecl->block, method); 
		if (!isOk) {
			return false; 
		}

		if (typeName != UNKNOWN_TYPE && typeName != VOID_TYPE_NAME) {
			isOk = isContainStatementType(functionDecl->block->stmtList, RETURN_STMT);
			if (! isOk ){
				printf("Semantic error. Function %s should return a value\n", functionDecl->identifier); 
			}
		}
	}
	else {
		printf("Function with the same name as %s has been define\n", functionDecl->identifier); 
		isOk = false;
	}
	//TODO:check for compatible of return type in the body and in signature
	return isOk; 
}

//Here, propose that the semantic of  param list has been check
char* createMethodDescriptor(struct ParameterList* paramList, char* returnTypeStr) {
	char* result = (char*)malloc(100 * sizeof(char));
	if (paramList == NULL) {
		strcpy(result, "()"); 
		strcpy(result + 2, returnTypeStr); 
	}
	else {
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
		//strcpy(result, ptr); // = ptr;
	}
	return result;
}

bool checkSemanticParamList(struct ParameterList* paramList, char* functionName) {
	struct ParameterDeclare* param = paramList->firstParamDecl;
	bool isOk = true;
	while (param != NULL && isOk) {
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
	enum TypeNames typeName = UNKNOWN_TYPE;
	if (functionDecl->signature->result != NULL) {
		struct Result* returnType = functionDecl->signature->result;
		struct Type* type = NULL;
		if (returnType == NULL) {
			typeName = VOID_TYPE_NAME; 
		}
		else {
			if (returnType->type != NULL) {
				type = returnType->type; 
			}
			else {
				//returnType->paramInParent != NULL
				if (returnType->paramInParen->paramList != NULL) {
					struct ParameterList* paramList = returnType->paramInParen->paramList; 
					//(int),(float), (string)
					//(a int) will not be accepted
					if (paramList->size == 1 && paramList->firstParamDecl->identifier == NULL) {
						type = paramList->firstParamDecl->type;
					}
				}
				else {
					//()
					typeName = VOID_TYPE_NAME;
				}
			}
		}
		//TODO: check this
		if (type != NULL && type->expr == NULL) {
			typeName = type->typeName;
		}
	}
	else {
		typeName = VOID_TYPE_NAME;
	}
	return typeName;
}


bool checkSemanticBlock(struct Block* block, struct Method* method) {
	//increase scope
	scope++; 
	bool isOk = true; 
	if (block->stmtList == NULL) {
		return true; 
	}
	struct Statement* stmt = block->stmtList->firstStmt; 
	while (stmt != NULL && isOk ) {
		isOk = checkSemanticStmt(stmt,method);
		if (isOk) {
			stmt = stmt->nextStatement;
		}
	}
	deactivateLocalVariablesByScope(method->localVariablesTable, scope); 
	//decrease scope
	scope--; 
	return isOk; 
}

void deactivateLocalVariablesByScope(List* localVariablesTable, int scope) {
	struct LocalVariable* variable = NULL; 
	int size = list_size(localVariablesTable); 
	for (int i = 0; i < size; ++i) {
		list_get_at(localVariablesTable, i, &variable); 
		if (variable->scope == scope && variable->isActive) {
			variable->isActive = false; 
		}
	}
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
		case RETURN_STMT: {
			return checkSemanticReturnStmt(statement->returnStmt, method); 
		}
	}
	return true; 
}

bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, struct Method* method) {
	switch(simpleStmt->stmtType)
	{
		case EXPR_SIMPLE_STMT:
		{
			if (simpleStmt->expr != NULL && simpleStmt->expr->primaryExpr != NULL && simpleStmt->expr->primaryExpr->funcCall != NULL) {
				struct FunctionCall* functionCall = simpleStmt->expr->primaryExpr->funcCall;
				char* methodName = functionCall->primaryExpr->identifier;
				struct Method* calledMethod = getMethod(semanticClass, methodName); 
				
				if (calledMethod != NULL) {
					if (checkSemanticFunctionCall(functionCall->exprList, calledMethod->paramList, method)) {
						if (method->returnType != VOID_TYPE_NAME) {
							printf("Semantic error. Expression evaluated but not used\n");
							return false;
						}
						else {
							struct SemanticType* semanticType = (struct SemanticType*)malloc(sizeof(struct SemanticType)); 
							semanticType->typeName = VOID_TYPE_NAME; 
							simpleStmt->expr->semanticType = semanticType; 
						}
					}
					else {
						return false; 
					}
				}
				else {
					printf("Semantic error. Method %s not declared\n", methodName);
					return false; 
				}
			}
			else {
				printf("Semantic error. Expression evaluated but not used\n");
				return false;
			}
			return true; 
		}
		case INC_SIMPLE_STMT:
		case DEC_SIMPLE_STMT:
		{
			if (simpleStmt->expr->exprType == PRIMARY) {
				struct SemanticType * semanticType = checkExpressionType(simpleStmt->expr, method);
				if (semanticType->typeName != FLOAT32_TYPE_NAME && semanticType->typeName != INT_TYPE_NAME) {
					printf("Semantic error. Increase or decrease statement can only perform in numeric variable\n"); 
					return false; 
				}
			}
			else {
				printf("Semantic error. Increase or decrease statement can only perform on variable\n"); 
				return false; 
			}
			return true; 
			
		}

		case ASSIGN_STMT:
		{
			return checkSemanticAssignStmtList(simpleStmt->exprListLeft, simpleStmt->exprListRight, method);
		}
		case PLUS_ASSIGN_STMT:
		case MINUS_ASSIGN_STMT:
		case MUL_ASSIGN_STMT:
		case DIV_ASSIGN_STMT: {
			if (exprListSize(simpleStmt->exprListLeft) == 1 && exprListSize(simpleStmt->exprListRight) == 1)
			{
				return checkSemanticAssignStmt(simpleStmt->exprListLeft->firstExpression, simpleStmt->exprListRight->firstExpression, method);
			}
			else {
				printf("Semantic error. Multiple arithmetic assign is not supported. \n"); 
				return false;
			}
		}
		default:
			return true; 
	}
}

//not supported
bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, struct Method* method)
{
	bool isOk = true;
	if (exprListSize(leftExprList) == exprListSize(rightExprList))
	{
		struct Expression *leftExpr = leftExprList->firstExpression;
		struct Expression *rightExpr = rightExprList->firstExpression;
		//Dont need to check for isOk
		while(leftExpr != NULL && isOk)
		{
			isOk = checkSemanticAssignStmt(leftExpr, rightExpr, method);
			if (isOk) {
				leftExpr = leftExpr->nextExpr;
				rightExpr = rightExpr->nextExpr;
			}
		}
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
	bool isOk = true; 
	if (leftExpr->exprType != PRIMARY || leftExpr->primaryExpr->exprType != ID_EXPRESSION) {
		printf("Semantic error. Left expression of assign statement must be identifier\n"); 
		isOk = false; 
	}
	else {
		struct LocalVariable* variable = findActiveLocalVariableById(method->localVariablesTable, leftExpr->primaryExpr->identifier); 
		if (variable == NULL) {
			printf("Semantic error. Identifier %s not declared \n", leftExpr->primaryExpr->identifier);
			isOk = false; 
		}
		else {
			if (rightExpr->exprType == PRIMARY && rightExpr->primaryExpr->exprType == ID_EXPRESSION) {
				struct LocalVariable* variable = findActiveLocalVariableById(method->localVariablesTable, rightExpr->primaryExpr->identifier); 
				if (variable == NULL) {
					printf("Semantic error. Identifier %s not declare\n", rightExpr->primaryExpr->identifier); 
					isOk = false; 
				}
			}
		}
		if (isOk) {
			struct SemanticType* leftType = checkExpressionType(leftExpr, method);
			struct SemanticType* rightType = checkExpressionType(rightExpr, method);
			isOk = (leftType->typeName == rightType->typeName && leftType->typeName != UNKNOWN_TYPE);
			if (!isOk) {
				printf("Semantic error. Type mismatch in assign statement of variable %s\n", leftExpr->primaryExpr->identifier); 
			}
		}
	}
	return isOk;
}

bool checkSemanticIfStmt(struct IfStmt* ifStmt, struct Method* method) {
	bool isOk = true;
	if (ifStmt->ifStmtExpr->simpleStmt != NULL) {
		printf("Semantic error. Simple statement before expression of if is not accepted. \n"); 
		isOk = false; 
	}
	else {
		struct SemanticType* semanticType = checkExpressionType(ifStmt->ifStmtExpr->expr, method);
		if (semanticType->typeName != BOOL_TYPE_NAME) {
			if (semanticType->typeName != UNKNOWN_TYPE) {
				printf("Semantic error. Non bool used as if condition\n");
			}
			isOk = false; 
		}
		else {
			if (isContainStatementType(ifStmt->block->stmtList, BREAK_STMT)) {
				printf("Semantic Error. Invalid break statement inside if statement\n");
				isOk = false;
			}
			else if (isContainStatementType(ifStmt->block->stmtList, CONTINUE_STMT)) {
				printf("Semantic Error. Invalid continue statement inside if statement\n");
				isOk = false;
			}
			if (isOk) {
				isOk = checkSemanticBlock(ifStmt->block, method);
				if (isOk && ifStmt->elseBlock != NULL) {
					isOk = checkSemanticElseBlock(ifStmt->elseBlock, method);
				}
			}
		}
	}	
	return isOk;
}

bool checkSemanticElseBlock(struct ElseBlock* elseBlock, struct Method* method) {
	bool isOk = true;
	if(elseBlock->ifStmt != NULL){
		isOk = checkSemanticIfStmt(elseBlock->ifStmt, method);
	}
	else {
		if (isContainStatementType(elseBlock->block->stmtList, BREAK_STMT)) {
			printf("Semantic Error. Invalid break statement inside else statement\n");
			return false;
		}
		else if (isContainStatementType(elseBlock->block->stmtList, CONTINUE_STMT)) {
			printf("Semantic Error. Invalid continue statement inside else statement\n");
			return false;
		}
		if (isOk) {
			isOk = checkSemanticBlock(elseBlock->block, method);
		}
	}
	return isOk;
}



bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, struct Method*  method) {
	bool isOk = true;

	struct SemanticType* initExprSemanticType = (struct SemanticType*) malloc(sizeof(struct SemanticType)); 
	initExprSemanticType->typeName = UNKNOWN_TYPE; 
	if (switchStmt->initialAndExpression != NULL)
	{	
		if (switchStmt->initialAndExpression->initialStmt != NULL) {
			struct SimpleStmt* initStmt = switchStmt->initialAndExpression->initialStmt;
			if (initStmt->stmtType == EXPR_SIMPLE_STMT) {
				printf("Semantic error. Initial expression of switch statement cannot be expression\n");
				isOk = false;
			}
			else {
				isOk = checkSemanticSimpleStmt(switchStmt->initialAndExpression->initialStmt, method);
			}
		}
		if (isOk && switchStmt->initialAndExpression->expression != NULL) {
			struct PrimaryExpression* primaryExpr = switchStmt->initialAndExpression->expression->primaryExpr;
			if (primaryExpr != NULL && primaryExpr->identifier != 0) {
				//what do to with semanticType (probably nothing :v)
				initExprSemanticType = checkExpressionType(switchStmt->initialAndExpression->expression, method);
				if (initExprSemanticType->typeName == UNKNOWN_TYPE) {
					isOk = false;
				}
			}
			else {
				printf("Semantic error. Expression of switch statement should be an identifier\n");
				isOk = false;
			}
		}
	}
	//empty switch initial statement and expression -> nothing to do :v

	//check semantic of switch's body
	if (isOk) {
		if (switchStmt->switchBody->eccl != NULL) {
			scope++; 
			struct ExpressionCaseClause* ecc = switchStmt->switchBody->eccl->firstExprCaseClause; 
			
			while (ecc != NULL && isOk) {
				isOk = checkSemanticExpressionCaseClause(ecc, initExprSemanticType->typeName, method);
				ecc = ecc->nextExprCaseClause; 
			}
			scope--; 
		} 
	}
	return isOk;
}

bool checkSemanticExpressionCaseClause(struct ExpressionCaseClause *ecc, enum TypeNames identifierType, struct Method* method)
{
	bool isOk = true;
	if (ecc->expreSwitchCase->exprList != NULL) {
		//check semantic for expression list in case
		struct ExpressionList* exprList = ecc->expreSwitchCase->exprList; 
		struct Expression* expr = exprList->firstExpression; 
		struct SemanticType* semanticType = NULL; 
		while (expr != NULL && isOk) {	
			semanticType  = checkExpressionType(expr, method); 
			if (identifierType != UNKNOWN_TYPE) {
				if (semanticType->typeName != identifierType) {
					printf("Semantic error. Semantic type of switch's identifier and case's value are different\n");
					isOk = false;
				}
			}
			else {
				//expression and init of switch is empty (switch {...})
				if (semanticType->typeName != BOOL_TYPE_NAME) {
					printf("Semantic error. Type of case's expression must be bool-type\n"); 
					isOk = false; 
				}
			}
			if (isOk) {
				expr = expr->nextExpr; 
			}
		}
	}
	if (isOk) {
		//check semantic body of case 
		struct Statement* stmt = ecc->stmtList->firstStmt;
		if (isContainStatementType(ecc->stmtList, CONTINUE_STMT)) {
			printf("Semantic error. Invalid continue statement in body of switch statement\n"); 
			isOk = false; 
		}
		while (stmt != NULL && isOk) {
			isOk = checkSemanticStmt(stmt, method);
			if (isOk) {
				stmt = stmt->nextStatement;
			}
		}
	}
	return isOk;
}

bool checkSemanticForStmt(struct ForStmt* forStmt, struct Method* method) {
	bool isOk = true; 
	//for statement with for-clause (for a = 5 ; a < 8 ;a++ {...})
	if (forStmt->forClause != NULL) {
		struct ForInitStmt* forInit = forStmt->forClause->forInitStmt; 
		struct ForCondition* forCondition = forStmt->forClause->forCondition; 
		struct ForPostStmt* forPostStmt = forStmt->forClause->forPostStmt; 
		if (forInit->initStmt != NULL) {
			if (forInit->initStmt->stmtType == EXPR_SIMPLE_STMT) {
				printf("Semantic error. Initial statement of for expression cannot be an expression\n"); 
				isOk = false; 
			}
		}
		if (forCondition->expression != NULL) {
			//check semantic type of for-condition
			struct SemanticType * semanticType =  checkExpressionType(forCondition->expression, method);
			if (semanticType->typeName != BOOL_TYPE_NAME) {
				if (semanticType->typeName == UNKNOWN_TYPE) {
					printf("Semantic error. Non bool value used as for condition\n");
				}
				isOk = false; 
			}
		}
		if (forPostStmt->postStmt != NULL) {
			if (forPostStmt->postStmt->stmtType == EXPR_SIMPLE_STMT) {
				printf("Semantic error. Post statement of for expression cannot be an expression\n");
				isOk = false; 
			}
			bool isOk =  checkSemanticSimpleStmt(forPostStmt->postStmt, method);
			
			if (!isOk) {
				printf("Semantic error. Problem in post statement of for statement\n");
				//isOk = false; 
			}
		}
	}
	else if (forStmt->expr != NULL) {
		//for statement with for condition ( for 1 < 2 {...})
		//check semantic type of for-condition
		struct SemanticType * semanticType = checkExpressionType(forStmt->expr, method);
		if (semanticType->typeName != BOOL_TYPE_NAME) {
			if (semanticType->typeName != UNKNOWN_TYPE) {
				printf("Semantic error. Non bool value used as for condition\n");
			}
			isOk = false;
		}
	}
	//for statement without for condition and for-clause for {...} -> nothing to do with this
	
	//check semantic block
	if (isOk) {
		isOk = checkSemanticBlock(forStmt->block, method); 
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
	char* methodName = method->constMethodref->const2->const1->utf8;
	if (returnStmt->exprList->size == 1) {
		struct SemanticType* semanticType = checkExpressionType(returnStmt->exprList->firstExpression, method); 
		
		if (semanticType->typeName != method->returnType) {
			char* methodName = method->constMethodref->const2->const1->utf8; 
			printf("Semantic error. Formal return type incompatible with declared return type in method %s\n", methodName); 
			return false; 
		}
		return true;
	}
	else {
		printf("Too many expressions in return statement of function %s\n", methodName); 
		return false; 
	}
}

bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList,  struct Method* method)
{
	bool isOk = true; 
	if (exprList != NULL && paramList == NULL || exprList == NULL && paramList != NULL) {
		isOk = false; 
	}
	else if (exprList != NULL && paramList != NULL) {
		if (exprList->size != paramList->size) {
			printf("Semantic error. Formal parameter count and parameter count mismatch\n");
			isOk = false;
		}
		else {
			struct Expression* expr = exprList->firstExpression;
			struct ParameterDeclare* param = paramList->firstParamDecl;
			while (expr != NULL&& isOk) {
				//call check expression type to define type
				struct SemanticType* semanticType = checkExpressionType(expr, method);
				if (semanticType->typeName != param->type->typeName) {
					printf("Semantic error. Formal paramter's type and declared parameter's type of %s mismatch\n", param->identifier);
					isOk = false;
				}
				if (isOk) {
					expr = expr->nextExpr;
					param = param->nextParamDecl;
				}
			}
		}
	}
	return isOk;
}

bool checkSemanticVarDecl(struct VarDecl* varDecl, struct Method* method) {
	bool isOk = true; 
	if (varDecl->varSpec != NULL) {
		isOk = checkSemanticVarSpec(varDecl->varSpec, method);
		if (isOk) {

			isOk = addVarSpecToLocalVarsTable(varDecl->varSpec, method, true);
		} 
	}
	else {
		struct VarSpec * varSpec = varDecl->varSpecList->firstVarSpec; 
		while (varSpec != NULL && isOk) {
			isOk = checkSemanticVarSpec(varSpec, method); 
			if (isOk) {
				isOk = addVarSpecToLocalVarsTable(varSpec, method, true);
				varSpec = varSpec->nextVarSpec;
			}
		}
	}
	//if(varDecl)
	return isOk;
}


bool checkSemanticVarSpec(struct VarSpec* varSpec, struct Method* method)
{
	bool isOk = true;
	char* functionName = "";
	if (method != NULL) {
		functionName = method->constMethodref->const2->const1->utf8;
	}
	//check for match of number of variables and number of values 
	if (varSpec->idListType != 0) {
		if (varSpec->exprList != 0) {
			struct Type* type = varSpec->idListType->type; 
			if (varSpec->idListType->identifierList->size != varSpec->exprList->size) {
				printf("Variable count and value count mismatch in function %s ", functionName);
				isOk = false;
			}
			else {
				struct Expression* expr = varSpec->exprList->firstExpression;
				struct Identifier* id = varSpec->idListType->identifierList->firstId; 
				while (expr != NULL && isOk) {
					struct SemanticType* semanticType = checkExpressionType(expr, method);
					if (semanticType != NULL) {
						if (semanticType->typeName != type->typeName && semanticType->typeName != UNKNOWN_TYPE) {
							printf("Semantic error. Incompatible between declared type and semantic type of variable %s and  in function %s\n",id->name,  functionName);
							isOk = false;
						}
					}
					else{
						isOk = false; 
					}
					expr = expr->nextExpr;
					id = id->nextId; 
				}
			}
		}
	}
	else {
		//The compiler not support untyped variables declaration
		printf("Semantic error. The compiler is currently not support var spec without type\n"); 
		isOk = false;
	}
	return isOk;
}

bool addVarSpecToLocalVarsTable(struct VarSpec* varSpec, struct Method* method) {
	bool isOk = true;
	if (varSpec->idListType != NULL) {
		struct IdentifierList* idList = varSpec->idListType->identifierList;
		struct Identifier* id = idList->firstId;
		enum  TypeNames typeName = varSpec->idListType->type->typeName;
		char* typenameStr = convertTypeToString(typeName); 
		addUtf8ToConstantsTable(typenameStr); 
		while (id != NULL && isOk) {
			struct LocalVariable* variable = addVariableToLocalVarsTable(id->name, typeName, method, true);
			addUtf8ToConstantsTable(id->name);
			isOk = variable != NULL; 
			if (isOk) {
				id->idNum = variable->id; 
				id = id->nextId;
			}
			
		}
	}
	else {
		//The compiler currently doesnt support var/const declarations without type 
		printf("Semantic error. The compiler currently doesnt support declarations without type \n");
		isOk = false;
	}
	
	return isOk; 
}

bool addConstSpecToLocalVarsTable(struct ConstSpec* constSpec, struct Method* method) {
	bool isOk = true; 
	if (constSpec->idListType != NULL) {
		struct IdentifierList* idList = constSpec->idListType->identifierList; 
		struct Identifier* id = idList->firstId; 
		
		enum TypeNmes typeName = constSpec->idListType->type->typeName; 
		char* typeNameStr = convertTypeToString(typeName); 
		addUtf8ToConstantsTable(typeNameStr); 
		while (id != NULL && isOk) {
			// add utf8 to constant table
			addUtf8ToConstantsTable(id->name);
			isOk = (addVariableToLocalVarsTable(id->name, typeName, method, false) != NULL );
			id = id->nextId; 
		}
	}
	else {
		//The compiler currently doesnt support var/const declarations without type 
		printf("Semantic error. The compiler currently doesnt support declarations without type \n");
		isOk = false;
	}
	return isOk; 
}

bool addParamToLocalVarsTable(struct ParameterDeclare* paramDeclare, struct Method* method) {
	bool isOk = true;
	List* variablesTable = method->localVariablesTable;
	char* varName = paramDeclare->identifier;
	struct Type* type = paramDeclare->type;
	struct LocalVariable* localVariable = findLocalVariableByScope(variablesTable, varName, 1);
	if (localVariable == NULL) {
		localVariable = (struct LocalVariable*)malloc(sizeof(struct LocalVariable));
		//TODO: augment variable with value(expression); 
		localVariable->name = paramDeclare->identifier;
		localVariable->type = (struct Type*)malloc(sizeof(struct Type));
		localVariable->type->typeName = type->typeName;
		localVariable->id = list_size(variablesTable) + 1;
		localVariable->scope = 1;
		list_add(variablesTable, localVariable);
	}
	else {
		isOk = false;
	}
	return isOk;
}

//TODO: transform the multiple assignment to single assignment
struct LocalVariable* addVariableToLocalVarsTable(char* id, enum TypeNames typeName, struct Method* method, bool isMutable) {
	struct LocalVariable* localVariable = NULL;  
	//TODO : implement size for variable
	if (findLocalVariableByScope(method->localVariablesTable, id, scope) == NULL) {
		localVariable = (struct LocalVariable*) malloc(sizeof(struct LocalVariable)); 
		localVariable->id = list_size(method->localVariablesTable) + 1;
		localVariable->scope = scope;
		localVariable->name = id;
		localVariable->isActive = true; 
		localVariable->isMutable = isMutable; 
		struct SemanticType* semanticType = (struct SemanticType*) malloc(sizeof(struct SemanticType));
		semanticType->typeName = typeName;
		localVariable->type = (struct Type*)malloc(sizeof(struct Type));
		localVariable->type->typeName = semanticType->typeName;
		list_add(method->localVariablesTable, localVariable);
	}
	else {
		printf("Variable with the same name %s exists in the table\n", id);
	}
	return localVariable;
}


struct LocalVariable* findLocalVariableByScope(List* variablesTable, char* varName, int scope) {
	struct LocalVariable* result = (struct LocalVariable*) malloc(sizeof(struct LocalVariable));
	int size = list_size(variablesTable);
	bool found = false;
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(variablesTable, i, &result);
		if (result->scope == scope && strcmp(result->name, varName) == 0 && result->isActive) {
			found = true;
		}
	}

	if (found) {
		return result;
	}
	return NULL;
}

struct LocalVariable* findLocalVariableByScope1(List* variablesTable, char* varName, int scope) {
	struct LocalVariable* result = (struct LocalVariable*) malloc(sizeof(struct LocalVariable));
	int size = list_size(variablesTable);
	bool found = false;
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(variablesTable, i, &result);
		if (result->scope == scope && strcmp(result->name, varName) == 0) {
			found = true;
		}
	}

	if (found) {
		return result;
	}
	return NULL;
}




void cloneVariable(struct LocalVariable* dest, struct LocalVariable* source) {
	dest->id = source->id; 
	dest->isActive = source->isActive; 
	dest->isMutable = source->isMutable; 
	strcpy(dest->name, source->name); 
	dest->scope = source->scope; 
	dest->type = (struct Type*) malloc(sizeof(struct Type));
	dest->type->typeName = source->type->typeName; 
	dest->type->expr = source->type->expr; 
}

struct LocalVariable* findActiveLocalVariableById(List* variablesTable, char* varName) {
	struct LocalVariable* result = NULL; 
	struct LocalVariable* variable = NULL; 
	int size = list_size(variablesTable);
	bool found = false;
	int minScope = 0; 
	for (int i = 0; i < size; ++i) {
		list_get_at(variablesTable, i, &variable);
		//this check is strong enough to detect the needed variable
		if (strcmp(variable->name, varName) == 0 && variable->isActive ) {
			result = variable; 
		}
	}

	return result;
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
		if (isOk) {
			isOk = addConstSpecToLocalVarsTable(constSpec, method); 
		}
	}
	else if (constDecl->constSpecList != NULL) {
		struct ConstSpec* constSpec = constDecl->constSpecList->firstConstSpec;
		while (constSpec != NULL && isOk) {
			isOk = checkSemanticConstSpec(constSpec, method);
			if (isOk) {
				isOk = addConstSpecToLocalVarsTable(constSpec, method); 
				constSpec = constSpec->nextConstSpec;
			}
		}
	}
	return isOk;
}

//TODO: check for value of constant (constant must have a value when it's declare, but in grammar, the value is optional)
bool checkSemanticConstSpec(struct ConstSpec* constSpec, struct Method* method) {
	bool isOk = true;
	char* methodName = ""; 
	if (method != NULL) {
		methodName = method->constMethodref->const2->const1->utf8;
	}
	//check for match of number of variables and number of values 
	if (constSpec->idListType != 0) {
		if (constSpec->exprList != 0) {
			if (constSpec->idListType->identifierList->size != constSpec->exprList->size) {
				printf("Variable count and value count mismatch in function %s \n", methodName);
				isOk = false;
			}
			else {
				struct Identifier* id = constSpec->idListType->identifierList->firstId;
				struct Expression* expr = constSpec->exprList->firstExpression;
				enum TypeNames typeName = constSpec->idListType->type->typeName; 
				
				while (expr != NULL && isOk) {
					//primary or unary primary or 
					enum ExpressionType exprType = expr->exprType; 
					if (exprType == PRIMARY || exprType == PLUS_UNARY_EXPR || exprType == MINUS_UNARY_EXPR) {
						struct PrimaryExpression* primaryExpr = expr->primaryExpr;
						if (primaryExpr->exprType == DECIMAL_EXPR ||
							primaryExpr->exprType == FLOAT_EXPR ||
							primaryExpr->exprType == STRING_EXPR ||
							primaryExpr->exprType == ID_EXPRESSION) {
							struct SemanticType* semanticType = checkPrimaryExpressionType(primaryExpr, method);
							if (semanticType->typeName != typeName) {
								printf("Value of constant %s is different from declared type in method %s\n", id->name, methodName);
								isOk = false;
							}
							else {
								if (primaryExpr->exprType == ID_EXPRESSION) {
									struct LocalVariable* variable =
										findActiveLocalVariableById(method->localVariablesTable, primaryExpr->identifier);
									if (variable->isMutable) {
										printf("Value of constant %s cannot be a variable\n", id->name);
										isOk = false;
									}
								}
							}

							id = id->nextId;
							expr = expr->nextExpr;
						}
					}
					else {
						//support const a int = 5 ; const b int = a ; 
						printf("Constant initializer %s is not a constant %s\n", id->name, methodName);
						isOk = false;
					}
				}
			}
		}
		else {
			printf("Missing value in constant declaration in method %s\n", methodName);
		}
	}
	else {
		printf("Semantic error. The compiler currently not support constant specification without type\n"); 
		isOk = false; 
	}
	return isOk;
}

struct Constant* addUtf8ToConstantsTable(char* utf8) {
	struct Constant* constant = NULL; 
	bool found = false; 
	int size = list_size(constantsTable); 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant);
		if (constant->type == CONSTANT_Utf8 && !strcmp(constant->utf8, utf8)) {
			found = true; 
		}
	}
	if (!found) {
		constant = (struct Constant*) malloc(sizeof(struct Constant));
		constant->type = CONSTANT_Utf8; 
		constant->utf8 = utf8;
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant; 
}

struct Constant* addClassToConstantsTable(char* className) {
	struct Constant* constant = NULL;
	struct Constant* classNameConst = addUtf8ToConstantsTable(className);
	bool found = false;
	int size = list_size(constantsTable);
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant);
		if (constant->type == CONSTANT_Class && constant->const1== classNameConst) {
			found = true;
		}
	}
	if (!found) {
		constant = (struct Constant*) malloc(sizeof(struct Constant)); 
		constant->type = CONSTANT_Class; 
		constant->const1 = classNameConst; 
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant;
}
struct Constant* addNameAndTypeToConstantsTable(char* name, char* type) {

	struct Constant* constant = NULL; 
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
		constant = (struct Constant*) malloc(sizeof(struct Constant)); 
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
	struct Constant* constant = NULL; 
	for (int i = 0; !found && i < size; ++i) {
		list_get_at(constantsTable, i, &constant); 
		if (constant->type  == CONSTANT_Fieldref && constant->const1 == const1 && constant->const2 == const2) {
			found = true; 
		}
	}
	if (!found) {
		constant = (struct Constant*) malloc(sizeof(struct Constant));
		constant->type = CONSTANT_Fieldref; 
		constant->const1 = const1; 
		constant->const2 = const2; 
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant; 
}

struct Constant* addMethodRefToConstantsTable(char* methodName, char* methodDescriptor) {
	struct Constant* constant = NULL; 
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
		constant = (struct Constant*) malloc(sizeof(struct Constant));
		constant->type = CONSTANT_Methodref; 
		constant->const1 = const1; 
		constant->const2 = const2; 
		constant->id = size + 1; 
		list_add(constantsTable, constant); 
	}
	return constant; 
}


struct Method* getMethod(struct Class* class, char* methodName) {
	struct Method* method = NULL; // (struct Method*) malloc(sizeof(struct Method));
	if (hashtable_get(class->methodsTable, methodName, &method) == CC_OK) {
		return method; 
	}
	return NULL; 
}

struct Field* getField(struct Class* class, char* fieldName) {
	struct Field* field = NULL; // (struct Field*) malloc(sizeof(struct Field));
	if (hashtable_get(class->fieldsTable, fieldName, &field) == CC_OK) {
		return field; 
	}
	return NULL; 
}

void printLocalVariablesTable(struct Method* method) {
	List* localVariablesTable = method->localVariablesTable;
	int size = list_size(localVariablesTable);
	struct LocalVariable* localVariable = NULL; // (struct LocalVariable*) malloc(sizeof(struct LocalVariable));
	for (int i = 0; i < size; ++i) {
		list_get_at(localVariablesTable, i, &localVariable);
		printf("Id: %d, name: %s, type: %s ", localVariable->id, localVariable->name, convertTypeToString(localVariable->type->typeName));
	}
}


void printConstant(struct Constant* constant) {
	switch (constant->type) {
	case CONSTANT_Integer:
		printf("%d  INT %d\n",constant->id, constant->intValue );
		break; 
	case CONSTANT_Float:
		printf("%d FLOAT %f\n", constant->id, constant->floatValue);
		break; 
	case CONSTANT_Utf8:
		printf("%d UTF-8 %s\n", constant->id, constant->utf8); 
		break;
	case CONSTANT_NameAndType:
		printf("%d Name&Type %d,%d\n", constant->id, constant->const1->id, constant->const2->id); 
		break;
	case CONSTANT_Class:
		printf("%d Class %d\n", constant->id, constant->const1->id); 
		break; 
	case CONSTANT_Fieldref:
		printf("%d FieldRef %d,%d\n", constant->id, constant->const1->id, constant->const2->id); 
		break;
	case CONSTANT_Methodref:
		printf("%d MethodRef %d,%d\n", constant->id, constant->const1->id, constant->const2->id);
		break;
	case CONSTANT_String:
		//what the hell to do with this ?
		break; 
	}
}

void printConstantsTable() {
	FILE* file = freopen("constants.txt", "w", stdout);
	int size = list_size(constantsTable); 
	for (int i = 0; i < size; ++i) {
		struct Constant* constant = NULL; 
		list_get_at(constantsTable, i, &constant);
		if (constant->type == CONSTANT_Class) {
			int t = 0; 
			t+=1;
		}
		printConstant(constant); 
	}
	fclose(stdout);
}

bool isContainStatementType(struct StatementList* stmtList, enum StatementType type) {
	bool isContain = false;
	if (stmtList != NULL) {
		struct Statement* stmt = stmtList->firstStmt;
		while (!isContain && stmt != NULL) {
			if (stmt->stmtType == type) {
				isContain = true;
			}
			else {
				stmt = stmt->nextStatement;
			}
		}
	}
	return isContain;
}
