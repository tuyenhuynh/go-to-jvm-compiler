#include "print_trees.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

int maxId = 0;

void printProgram() {

	if (root != NULL) {
		FILE* file = freopen("ast.dot", "w", stdout);

		printf("digraph {\n");
		//here root's id is 0
		int rootId = maxId; 
		printf("%d[label = root]", rootId);
		printPackage(rootId, root->pkg); 
		printImports(rootId, root->imports); 
		printDeclarationList(rootId, root->declList);
		printf("\n}\n");
		fclose(stdout);
	}
	else {
		printf("program is null\n"); 
	}
}

void printPackage(int parentId, struct Package* package) {
	if (package != NULL) {
		maxId++;
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "PACKAGE");
		maxId++; 
		printEdgeWithDestName(id, maxId, package->packageName);
	}
	else {
		printf("Package is NULL\n"); 
	}
}

void printImport(int parentId, struct Import* import) {
	
}

void printImports(int parentId, struct Imports* imports) {
	
}

void printImportStatementList(int parentId, struct ImportStmtList* importStmtList) {}

//import is not very clear

void printPrimitiveExpression(int parentId, char*name, char*value) {
	maxId++; 
	int nodeId =maxId; 
	printEdgeWithDestName(parentId, nodeId, name);
	maxId++; 
	printEdgeWithDestName(nodeId, maxId, value);
}
void printExpression(int parentId, struct Expression* expression) {
	if (expression != NULL) {
		maxId++;
		int id = maxId; 
		switch (expression->exprType) {
			case DECIMAL_EXPR: {
				char buffer[10];
				itoa(expression->primaryExpr->decNumber, buffer, 10);
				printPrimitiveExpression(parentId, "INT", buffer);
				break;
			}	 
			case FLOAT_EXPR: {
				char buffer[10];
				gcvt(expression->primaryExpr->floatNumber, 10, buffer);
				printPrimitiveExpression(parentId, "FLOAT", buffer);
				break;
			}
			case STRING_EXPR: {
				printPrimitiveExpression(parentId, "STRING", expression->primaryExpr->stringLiteral);
				break;
			}
			case ID_EXPRESSION: {
				printPrimitiveExpression(parentId, "ID", expression->primaryExpr->identifier);
				break;
			}
			case PE_COMPOSITE: {
				//TODO: implement this
				break;
			}
			case FUNCTION_CALL: {
				//TODO: implement this
			}
			case FUNCTION_CALL_EMPTY: {
				//TODO: implement this
			}
			case NOT_UNARY_EXPR:
			case PLUS_UNARY_EXPR:
			case MINUS_UNARY_EXPR: {
				printUnaryExpression(parentId, expression);
				break; 
			}
			case AND_EXPRESSION:
			case OR_EXPRESSION:
			case NE_EXPRESSION:
			case GT_EXPRESSION:
			case GTE_EXPRESSION:
			case LT_EXPRESSION:
			case LTE_EXPRESSION:
			case PLUS_EXPRESSION:
			case MINUS_EXPRESSION:
			case MUL_EXPRESSION:
			case DIV_EXPRESSION:
			case MOD_EXPRESSION: {
				printBinaryExpression(parentId, expression);
			}
			//default ???
		}
	}
	else {
		printf("Expression is null\n");
	}
}

void printBinaryExpression(int parentId, struct Expression* expression) {
	if (expression != NULL) {
		maxId++;
		int id = maxId;
		char* nodeName = (char*)malloc(20*sizeof(char));
		expressionTypeToString(expression->exprType, nodeName);
		printEdgeWithDestName(parentId, maxId, nodeName);
		printExpression(id, expression->leftExpr);
		printExpression(id, expression->rightExpr);
	}else {
		printf("Binary expression is null\n");
	}
}

void printUnaryExpression(int parentId, struct Expression* expression) {
	if (expression != NULL) {
		maxId++; 
		int id = maxId;
		char* nodeName = (char*)malloc(20 * sizeof(char));
		expressionTypeToString(expression->exprType, nodeName); 
		printEdgeWithDestName(parentId, id, nodeName);
		printPrimaryExpression(id, expression->primaryExpr);
	}
	else {
		printf("Unary expression is null\n");
	}
}

void printPrimaryExpression(int parentId, struct PrimaryExpression* primaryExpr) {
	if (primaryExpr != NULL) {
		maxId++; 
		int id = maxId; 
		switch (primaryExpr->exprType) {
			case BOOL_TRUE_EXPRESSION:
			case BOOL_FALSE_EXPRESSION: {
				char*nodeName = (char*)malloc(20*sizeof(char));
				expressionTypeToString(primaryExpr->exprType, nodeName);
				printEdgeWithDestName(parentId, id, nodeName);
				break; 
			}
			case DECIMAL_EXPR: {
				char buffer[10];
				itoa(primaryExpr->primaryExpr->decNumber, buffer, 10);
				printPrimitiveExpression(parentId, "INT", buffer);
				break;
			}
			case FLOAT_EXPR: {
				char buffer[10];
				gcvt(primaryExpr->primaryExpr->floatNumber, 10, buffer);
				printPrimitiveExpression(parentId, "FLOAT", buffer);
				break;
			}
			case STRING_EXPR: {
				printPrimitiveExpression(parentId, "STRING", primaryExpr->stringLiteral);
				break;
			}
			case ID_EXPRESSION: {
				printPrimitiveExpression(parentId, "ID", primaryExpr->identifier);
				break;
			}
			case PE_COMPOSITE: {
				printEdgeWithDestName(parentId, id, "ARRAY_ACCESS"); 
				printPrimaryExpression(id, primaryExpr->primaryExpr);
				printExpression(id, primaryExpr->expr);
				break;
			}
			case FUNCTION_CALL: {
				printFunctionCall(parentId, primaryExpr->funcCall); 
				break; 
			}
			case FUNCTION_CALL_EMPTY: {
				//TODO: implement this
				break; 
			}
		}
	}
	else {
		printf("Primary expression is null\n"); 
	}
}

void printFunctionCall(int parentId, struct FunctionCall* functionCall) {
	if (functionCall != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "F_CALL");
		//TODO:
		//stuck with components of function name
		//should print node NAME ???
		maxId++; 
		printEdgeWithDestName(id, maxId, functionCall->primaryExpr->identifier);
		maxId++; 
		printEdgeWithDestName(id, maxId, "PARAMS");
		//here maxId comes to be parentNode of expressionList 
		printExpressionList(maxId, functionCall->exprList); 
	}
	else {
		printf("Function call is null\n"); 
	}
}

void printExpressionList(int parentId, struct ExpressionList* expressionList) {
	while (expressionList != NULL) {
		printExpression(parentId, expressionList->expr);
		expressionList = expressionList->nextExpr; 
	}
}

void printDeclarationList(int parentId, struct DeclarationList* declarationList){
	while (declarationList != NULL) {
		printDeclaration(parentId, declarationList->decl); 
		declarationList = declarationList->nextDecl;
	}
}

void printDeclaration(int parentId, struct Declaration* declaration) {
	if (declaration != NULL) {
		if (declaration->declType == CONST_DECL) {
			printConstDecl(parentId, declaration->constDecl);
		}
		else if (declaration->declType == VAR_DECL) {
			printVarDecl(parentId, declaration->varDecl);
		}
		else if (declaration->declType == FUNC_DECL) {
			printFunctionDecl(parentId, declaration->funcDecl);
		}
		else {
			printf("Unknown declaration type\n");
		}
	}
	else {
		printf("Declaration is null\n"); 
	}
}

void printVarDecl(int parentId, struct VarDecl * varDecl){
	if (varDecl != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "VAR");
		if (varDecl->varSpec != NULL) {
			printVarSpec(id, varDecl->varSpec); 
		}
		else if (varDecl->varSpecList != NULL) {
			printVarSpecList(id, varDecl->varSpecList);
		}
		else {
			printf("VarDecl is undefined\n"); 
		}
	}
	else {
		printf("VarDecl is NULL\n"); 
	}
}



void printConstDecl(int parentId, struct ConstDecl * constDecl){
	if (constDecl != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "CONST");
		if (constDecl->varSpec != NULL) {
			printVarSpec(id, constDecl->varSpec); 
		}
		else if (constDecl->varSpecList != NULL) {
			printVarSpecList(id, constDecl->varSpecList);
		}
		else {
			printf("Const spec is undefined\n"); 
		}

	}
	else {
		printf("ConstDecl is NULL\n"); 
	}
}
void printFunctionDecl(int parentId, struct FunctionDecl* functionDecl){
	
	if (functionDecl != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "FUNC_DECL"); 
		//print function name
		printPrimitiveExpression(id, "ID", functionDecl->identifier);
		//print function signature
		printSignature(id, functionDecl->signature); 
		//print function boby
		if (functionDecl->block != NULL) {
			printBlock(id, functionDecl->block); 
		}
	}
	else {
		printf("Function Declare is NULL"); 
	}
}


void printVarSpec(int parentId, struct VarSpec* varSpec){
	if (varSpec != NULL) {
		maxId++;
		int id = maxId;
		printEdgeWithDestName(parentId, id, "VAR_SPEC");
		if (varSpec->idListType != NULL) {
			printIdentifierList(id, varSpec->idListType->identifierList);
			printTypeName(id, varSpec->idListType->type);
		}
		else if (varSpec->idList != NULL) {
			printIdentifierList(id, varSpec->idList);
		}

		if (varSpec->exprList != NULL) {
			maxId++;
			printEdgeWithDestName(id, maxId, "EXPR_LIST");
			printExpressionList(maxId, varSpec->exprList);
		}
	}
	else {
		printf("VarSpec is null\n"); 
	}
}

void printVarSpecList(int parentId, struct VarSpecList* varSpecList){
	if (printVarSpecList != NULL) {
		int id = maxId++; 
		printEdgeWithDestName(parentId, id, "VAR_SPEC_LIST"); 
		while (varSpecList != NULL) {
			printVarSpec(id, varSpecList->varSpec);
			varSpecList = varSpecList->nextVarSpec;
		}
	}
}


void printStatement(int parentId, struct Statement* statement){
	if (statement != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "STMT"); 
		switch (statement->stmtType) {
			case SIMPLE_STMT: {
				printSimpleStmt(id, statement->simpleStmt);
				break; 
			}
			case VAR_DECL_STMT: {
				printVarDecl(id, statement->varDecl);
				break; 
			}
			case CONST_DECL_STMT: {
				printConstDecl(id, statement->constDecl);
				break; 
			}
			case RETURN_STMT: {
				printReturnStmt(id, statement->returnStmt); 
				break; 
			}
			case BREAK_STMT: {
				maxId++; 
				printEdgeWithDestName(id, maxId, "BREAK"); 
				break; 
			}
			case CONTINUE_STMT: {
				maxId++;
				printEdgeWithDestName(id, maxId, "CONTINUE");
				break;
			}
			case BLOCK: {
				printBlock(id, statement->block);
				break; 
			}
			case IF_STMT: {
				printIfStmt(id, statement->ifStmt);
				break; 
			}
			case SWITCH_STMT: {
				printSwitchStmt(id, statement->switchStmt); 
				break; 
			}
			case FOR_STMT: {
				printForStmt(id, statement->forStmt); 
				break; 
			}
			case PRINT_STMT: {
				printPrintStmt(id, statement->printStatement); 
				break; 
			}
			case SCAN_STMT: {
				printScanStmt(id, statement->scanStatement); 
				break; 
			}
			default: {
				printf("Unknown Statement type\n"); 
			}
		}
	}
	else {
		printf("Statement is NULL\n"); 
	}
}

void printSimpleStmt(int parentId, struct SimpleStmt* simpleStmt){
	if (simpleStmt != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "SIMPLE_EXPR"); 
		switch (simpleStmt->stmtType) {
			case EXPR_SIMPLE_STMT: {
				printExpression(id, simpleStmt->expr); 
				break; 
			}
			case INC_SIMPLE_STMT: {
				maxId++; 
				printEdgeWithDestName(id, maxId, "++");
				printExpression(maxId, simpleStmt->expr); 
				break; 
			}
			case DEC_SIMPLE_STMT: {
				maxId++;
				printEdgeWithDestName(id, maxId, "--");
				printExpression(maxId, simpleStmt->expr);
				break; 
			}
			case ASSIGN_STMT: {
				printAssignStatement(id, simpleStmt->exprListLeft, simpleStmt->exprListRight); 
				break; 
			}

		}
	}
	else {
		printf("SimpleStatement is NULL\n"); 
	}
}

void printAssignStatement(int parentId, struct ExpressionList* leftExprList, struct ExpressionList* rightExprList){

	int id = ++maxId; 
	printEdgeWithDestName(parentId, id, "="); 
	printExpression(id, leftExprList); 
	printExpression(id, rightExprList);
}

void printReturnStmt(int parentId, struct ReturnStmt* returnStmt){
	if (returnStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "RETURN");
		if (returnStmt->exprList != NULL) {
			printExpressionList(id, returnStmt->exprList);
		}
	}
	else {
		printf("Return stmt is null\n");
	}
}

void printBlock(int parentId, struct Block* block){
	if (block != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "BLOCK");
		printStmtList(id, block->stmtList); 
	}
	else {
		printf("Block is empty\n"); 
	}
}

void printIfStmt(int parentId, struct IfStmt* ifStmt){
	if (ifStmt != NULL) {
		//TODO: continue to implement;
		//int id = 
	}
	else {
		printf("If Stmt is empty\n"); 
	}
}
void printForStmt(int parentId, struct ForStmt* forStmt){
	if (forStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "FOR"); 

		if (forStmt->expr != NULL) {
			printExpression(id, forStmt->expr); 
		}
		if (forStmt->forClause != NULL) {
			printForClause(id, forStmt->forClause); 
		}
		if (forStmt->block != NULL) {
			printBlock(id, forStmt->block);
		}
	}
	else {
		printf("ForStmt is null\n");
	}
}


void printIfStmtExpression(int parentId, struct IfStmtExpression* ifStmtExpr){}
void printElseBlock(int parentId, struct ElseBlock* elseBlock){}

void printStmtList(int parentId, struct StatementList* stmtList){
	if (stmtList != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "STMT_LIST"); 
		while (stmtList != NULL) {
			printStatement(id, stmtList->stmt); 
			stmtList = stmtList->nextStmt; 
		}
	}
	else {
		printf("StatementList is null \n");
	}
}

void printExpressionCaseClause(int parentId, struct ExpressionCaseClause* ecc){}
void printExpressionSwitchCase(int parentId, struct ExpressionSwitchCase* expressionSwitchCase){}

void printForClause(int parentId, struct ForClause* forClause){
	if (forClause != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "FOR_CLAUSE");
		if (forClause->forInitStmt != NULL) {
			printForInitStmt(id, forClause->forInitStmt); 
		}
		if (forClause->forCondition != NULL) {
			printForCondition(id, forClause->forCondition); 
		}
		if (forClause->forPostStmt != NULL) {
			printForPostStmt(id, forClause->forPostStmt);
		}
	}
	else {
		printf("ForClause is NULL\n");
	}
}

void printSignature(int parentId, struct Signature* signature){
	if (signature != NULL) {
		maxId++;
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "Signature");
		printParamInParen(id, signature->paramInParen); 
		if (signature->result != NULL) {
			printResult(id, signature->result);
		}
	}
	else {
		printf("Signature is NULL\n"); 
	}
}

void printParamInParen(int parentId, struct ParamInParen* paramInParen){
	if (paramInParen != NULL) {
		if (paramInParen->paramList != NULL) {
			maxId++;
			int id = maxId;
			printEdgeWithDestName(parentId, id, "ParamList");
			//printParamList(id, paramInParen->paramList);
		}
	}
	else {
		printf("Signature is NULL\n");
	}
}

void printParamList(int parentId, struct ParameterList* paramList){
	if (paramList != NULL) {
		while (paramList != NULL) {
			printParamDeclare(parentId, paramList->paramDecl); 
			paramList = paramList->nextParamDecl; 
		}
	}
	else {
		printf("ParamList is NULL\n"); 
	}
}

void printParamDeclare(int parentId, struct ParameterDeclare* paramDeclare){
	if (paramDeclare != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "PARAM_DECL"); 
		if (paramDeclare->type != NULL) {
			printTypeName(id, paramDeclare->type); 
		}
		if (paramDeclare->identifier != NULL) {
			printPrimitiveExpression(id, "ID", paramDeclare->identifier); 
		}
	}
	else {
		printf("ParamDeclare is NULL \n"); 
	}
}

void printResult(int parentId, struct Result* result){
	if (result != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "ReturnType"); 
		if (result->type != NULL) {
			printTypeName(id, result->type); 
		}
		if (result->paramInParen != NULL) {
			printParamInParen(id, result->paramInParen);
		}
	}
	else {
		printf("ReturnType is null\n"); 
	}
}


void printForInitStmt(int parentId, struct ForInitStmt* forInitStmt){
	if (forInitStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "FOR_INIT");
		if (forInitStmt->initStmt != NULL) {
			printSimpleStmt(id, forInitStmt->initStmt);
		}
	}
	else {
		printf("ForInit is null\n");
	}
}

void printForCondition(int parentId, struct ForCondition* forCondition){
	if (forCondition != NULL) {
		maxId++;
		int id = maxId;
		printEdgeWithDestName(parentId, id, "FOR_POST");
		if (forCondition->expression != NULL) {
			printExpression(id, forCondition->expression);
		}
	}
	else {
		printf("forCondition is NULL\n");
	}
}

void printForPostStmt(int parentId, struct ForPostStmt* forPostStmt){
	if (forPostStmt != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "FOR_POST");
		if (forPostStmt->postStmt != NULL) {
			printSimpleStmt(id, forPostStmt->postStmt);
		}
	}
	else {
		printf("forPostStmt is NULL\n");
	}
}

void printPrintStmt(int parentId, struct PrintStatement* printStmt){
	printf("printPrintStmt not implemented\n");
}

void printScanStmt(int parentId, struct ScanStatement* scanStmt){
	printf("printScanStmt not implemented\n");
}

void expressionTypeToString(enum ExpressionType exprType, char* result) {
	if (result == NULL) {
		result = (char*)malloc(20* sizeof(char)); 
	}
	switch (exprType) {
	case DECIMAL_EXPR:
		strcpy(result, "INT");
		break;
	case FLOAT_EXPR:
		strcpy(result, "FLOAT");
		break;
	case STRING_EXPR:
		strcpy(result, "STRING");
		break;
	case ID_EXPRESSION:
		strcpy(result, "ID");
		break;
	case PE_COMPOSITE:
		strcpy(result, "ARRAY_ACCESS");
		break;
	case FUNCTION_CALL_EMPTY:
		strcpy(result, "FUNC_CALL");
		break;
	case FUNCTION_CALL:
		strcpy(result, "FUNC_CALL");
		break;
	case NOT_UNARY_EXPR:
		strcpy(result, "!");
		break;
	case PLUS_UNARY_EXPR:
		strcpy(result, "+");
		break;
	case MINUS_UNARY_EXPR:
		strcpy(result, "-");
		break;
	case AND_EXPRESSION:
		strcpy(result, "&&");
		break;
	case OR_EXPRESSION:
		strcpy(result, "||");
		break;
	case EQU_EXPRESSION:
		strcpy(result, "==");
		break;
	case NE_EXPRESSION:
		strcpy(result, "!=");
		break;
	case GT_EXPRESSION:
		strcpy(result, ">");
		break;
	case GTE_EXPRESSION:
		strcpy(result, ">=");
		break;
	case LT_EXPRESSION:
		strcpy(result, "<");
		break;
	case LTE_EXPRESSION:
		strcpy(result, ">=");
		break;
	case PLUS_EXPRESSION:
		strcpy(result, "+");
		break;
	case MINUS_EXPRESSION:
		strcpy(result, "-");
		break;
	case MUL_EXPRESSION:
		strcpy(result, "*");
		break;
	case DIV_EXPRESSION:
		strcpy(result, "/");
		break;
	case MOD_EXPRESSION:
		strcpy(result, "%");
		break;
	case EXPRESSION:
		//TODO:CHECK THIS
		strcpy(result, "EXPR");
		break;
	case PRIMARY:
		strcpy(result, "PE"); 
		break;
	case BOOL_TRUE_EXPRESSION:
		strcpy(result, "true");
		break;
	case BOOL_FALSE_EXPRESSION:
		strcpy(result, "false");
		break;
	default: {
		printf("Unknown expression type\n");
	}
	}
}

void printIdentifierList(int parentId, struct IdentifierList * identifierList){
	if (identifierList != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "ID_LIST"); 
		while (identifierList != NULL) {
			printPrimitiveExpression(id, "ID", identifierList->identifier);
			identifierList = identifierList->nextIdentifier; 
		}
	}
	else {
		printf("Identifier list is null\n"); 
	}
}


void printTypeName(int parentId, struct Type* typeName){
	if (typeName != NULL) {
		int id = maxId++; 
		printEdgeWithDestName(parentId, id, "TYPE"); 
		maxId++; 
		//Stuck with this 
		//printEdgeWithDestName(id, maxId, ); 
		//TODO:
	}
	else {
		printf("Type name is null \n"); 
	}
}

void printSwitchStmt(int parentId, struct SwitchStmt* switchStmt) {
	if (switchStmt != NULL) {

		//
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "SWITCH");

		printSwitchInitialExpression(id, switchStmt->initialAndExpression);
		
		printSwitchBody(id, switchStmt->switchBody);
	}
	else {
		printf("Switch statement is null\n");
	}
}

void printSwitchBody(int parentId, struct SwitchBody* switchBody) {
	if (switchBody != NULL) {
		maxId++;
		printExpressionCaseClauseList(parentId, switchBody->eccl);
	}
	else {
		printf("Switch body is null\n");
	}

}

void printExpressionCaseClauseList(int parentId, struct ExpressionCaseClauseList* eccl) {
	
}

void printSwitchInitialExpression(int parentId, struct SwitchInitialAndExpression* switchInitialAndExpression){
	if (switchInitialAndExpression != NULL) {
		maxId++;
		printExpression(parentId, switchInitialAndExpression->expression);
		printSimpleStmt(parentId, switchInitialAndExpression->initialStmt);
	}
}
