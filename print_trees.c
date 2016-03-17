#include "print_trees.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#pragma warning (disable:4996)

void print_program(struct Program* program) {}

void print_package(int parentId, struct Package* package) {
	
}

void print_import(int parentId, struct Import* import) {
	
}

void print_import_statement_list(int parentId, struct ImportStmtList* importStmtList) {}

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
void printFunctionDecl(int parentId, struct FunctionDecl* functionDecl){}


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


void print_statement(int parentId, struct Statement* statement){}
void print_simple_stmt(int parentId, struct SimpleStmt* simpleStmt){}
void print_return_stmt(int parentId, struct ReturnStmt* returnStmt){}
void print_block(int parentId, struct Block* block){}
void print_switch_stmt(int parentId, struct SwitchStmt* switchStmt){}
void print_if_stmt(int parentId, struct IfStmt* ifStmt){}
void print_for_stmt(int parentId, struct ForStmt* forStmt){}
void print_if_stmt_expression(int parentId, struct IfStmtExpression* ifStmtExpr){}
void print_else_block(int parentId, struct ElseBlock* elseBlock){}
void print_stmt_list(int parentId, struct StatementList* stmtList){}
void print_switch_body(int parentId, struct SwitchBody* switchBody){}
void print_expression_case_clause_list(int parentId, struct ExpressionCaseClauseList* eccl){}
void print_expression_case_clause(int parentId, struct ExpressionCaseClause* ecc){}
void print_expression_switch_case(int parentId, struct ExpressionSwitchCase* expressionSwitchCase){}
void print_for_clause(int parentId, struct ForClause* ForClause){}
void print_signature(int parentId, struct Signature* signature){}
void print_param_in_paren(int parentId, struct ParamInParen* paramInParen){}
void print_param_list(int parentId, struct ParameterList* paramList){}
void print_param_declare(int parentId, struct ParameterDeclare* paramDeclare){}
void print_result(int parentId, struct Result* result){}
void print_function_call(int parentId, struct FunctionCall* functionCall){}
void print_switch_initial_expression(int parentId, struct SwitchInitialAndExpression* switchInitialAndExpression){}
void print_for_init_stmt(int parentId, struct ForInitStmt* forInitStmt){}
void print_for_condition(int parentId, struct ForCondition* forCondition){}
void print_for_post_stmt(int parentId, struct ForPostStmt* forPostStmt){}
void print_print_stmt(int parentId, struct PrintStatement* printStmt){}
void print_scan_stmt(int parentId, struct ScanStatement* scanStmt){}


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

void print_import_statement_list(int parentId, struct ImportStmtList* importStmtList){}

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

void print_statement(int parentId, struct Statement* statement){}
void printSimpleStmt(int parentId, struct SimpleStmt* simpleStmt){}
void print_return_stmt(int parentId, struct ReturnStmt* returnStmt){}
void print_block(int parentId, struct Block* block){}




void printSwitchStmt(int parentId, struct SwitchStmt* switchStmt) {
	if (switchStmt != NULL) {
		maxId++;
		int id = maxId;
		printSwitchInitialExpression(parentId, switchStmt->initialAndExpression);
		id++;
		printSwitchBody(id, switchStmt->switchBody);
	}
	else {
		printf("Switch statement is null\n");
	}
}


void print_if_stmt(int parentId, struct IfStmt* ifStmt){}
void print_for_stmt(int parentId, struct ForStmt* forStmt){}
void print_if_stmt_expression(int parentId, struct IfStmtExpression* ifStmtExpr){}
void print_else_block(int parentId, struct ElseBlock* elseBlock){}
void print_stmt_list(int parentId, struct StatementList* stmtList){}


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
void print_expression_case_clause(int parentId, struct ExpressionCaseClause* ecc){}
void print_expression_switch_case(int parentId, struct ExpressionSwitchCase* expressionSwitchCase){}
void print_for_clause(int parentId, struct ForClause* ForClause){}
void print_signature(int parentId, struct Signature* signature){}
void print_param_in_paren(int parentId, struct ParamInParen* paramInParen){}
void print_param_list(int parentId, struct ParameterList* paramList){}
void print_param_declare(int parentId, struct ParameterDeclare* paramDeclare){}
void print_result(int parentId, struct Result* result){}
void print_function_call(int parentId, struct FunctionCall* functionCall){}

void printSwitchInitialExpression(int parentId, struct SwitchInitialAndExpression* switchInitialAndExpression){
	if (switchInitialAndExpression != NULL) {
		maxId++;
		printExpression(parentId, switchInitialAndExpression->expression);
		printSimpleStmt(parentId, switchInitialAndExpression->initialStmt);
	}


}
void print_for_init_stmt(int parentId, struct ForInitStmt* forInitStmt){}
void print_for_condition(int parentId, struct ForCondition* forCondition){}
void print_for_post_stmt(int parentId, struct ForPostStmt* forPostStmt){}
void print_print_stmt(int parentId, struct PrintStatement* printStmt){}
void print_scan_stmt(int parentId, struct ScanStatement* scanStmt){}
