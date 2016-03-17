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
		printf("Expression is null");
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
		printf("Binary expression is null");
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
		printf("Unary expression is null");
	}
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
		//strcpy(result, "I");
		break;
	case PRIMARY:
		//TODO: remove this ?
		//strcpy(result, "INT");
		break;
	case BOOL_TRUE_EXPRESSION:
		strcpy(result, "true");
		break;
	case BOOL_FALSE_EXPRESSION:
		strcpy(result, "false");
		break;
	}
}

void printPrimaryExpression(int parentId, struct PrimaryExpression* primaryExpr) {}

void print_declaration_list(int parentId, struct DeclarationList* program){}
void print_declaration(int parentId, struct Declaration* declaration){}
void print_import_statement_list(int parentId, struct ImportStmtList* importStmtList){}
void print_var_decl(int parentId, struct VarDecl * varDecl){}
void print_const_decl(int parentId, struct ConstDecl * constDecl){}
void print_function_decl(int parentId, struct FunctionDecl functionDecl){}
void print_identifier_list(int parentId, struct IdentifierList * identifierList){}
void print_type_name(int parentId, struct Type* typeName){}
void print_var_spec(int parentId, struct VarSpec* varSpec){}
void print_var_spec_list(int parentId, struct VarSpecList* varSpecList){}
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
