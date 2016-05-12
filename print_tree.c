#include "print_tree.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "semantic.h"

int maxId = 0;

void printProgram(char* output) {

	if (root != NULL) {
		FILE* file = freopen(output, "w", stdout);

		printf("digraph {\n");
		int rootId = maxId; 
		printf("%d[label = root]", rootId);
		printDeclarationList(rootId, root->declList);
		printf("\n}\n");
		fclose(stdout);
	}
}

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
		//char* typeNameStr = convertTypeToString(expression->semanticType->typeName);
		//char* exprTypeStr = (char*)malloc(20 * sizeof(char)); 
		//strcpy(exprTypeStr, "\"EXPR\\n");
		//strcpy(exprTypeStr + 7, typeNameStr);
		//int length = strlen(exprTypeStr); 
		//strcpy(exprTypeStr + length, "\""); 
		printEdgeWithDestName(parentId, id, "EXPR"); 
		switch (expression->exprType) {
			case DECIMAL_EXPR: {
				char buffer[10];
				itoa(expression->primaryExpr->decNumber, buffer, 10);
				printPrimitiveExpression(id, "INT", buffer);
				break;
			}	 
			case FLOAT_EXPR: {
				char buffer[10];
				gcvt(expression->primaryExpr->floatNumber, 10, buffer);
				printPrimitiveExpression(id, "FLOAT", buffer);
				break;
			}
			case STRING_EXPR: {
				printPrimitiveExpression(id, "STRING", expression->primaryExpr->stringLiteral);
				break;
			}
			case ID_EXPRESSION: {
				printPrimitiveExpression(id, "ID", expression->primaryExpr->identifier);
				break;
			}
			case PRIMARY: {
				printPrimaryExpression(id, expression->primaryExpr);
				break; 
			}
			case NOT_UNARY_EXPR:
			case PLUS_UNARY_EXPR:
			case MINUS_UNARY_EXPR: {
				printUnaryExpression(id, expression);
				break; 
			}
			case AND_EXPRESSION:
			case OR_EXPRESSION:
			case NE_EXPRESSION:
			case EQU_EXPRESSION:
			case GT_EXPRESSION:
			case GTE_EXPRESSION:
			case LT_EXPRESSION:
			case LTE_EXPRESSION:
			case PLUS_EXPRESSION:
			case MINUS_EXPRESSION:
			case MUL_EXPRESSION:
			case DIV_EXPRESSION:
			case MOD_EXPRESSION: {
				printBinaryExpression(id, expression);
				break; 
			}
		}
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
				char buffer[20];
				itoa(primaryExpr->decNumber, buffer, 10);
				printPrimitiveExpression(parentId, "INT", buffer);
				break;
			}
			case FLOAT_EXPR: {
				char buffer[20];
				gcvt(primaryExpr->floatNumber, 10, buffer);
				buffer[19] = '\0';
				printPrimitiveExpression(parentId, "FLOAT", buffer);
				break;
			}
			case STRING_EXPR: {
				printPrimitiveExpression(parentId, "STRING", primaryExpr->stringLiteral);
				break;
			}
			case ID_EXPRESSION: {
				struct SemanticType* semanticType = primaryExpr->semanticType; 
				//print id's name
				printPrimitiveExpression(parentId, "ID", primaryExpr->identifier);
				char idBuffer[10]; 
				int id = maxId - 1;
				itoa(semanticType->idNum, idBuffer, 10);
				//print id number
				maxId++; 
				printEdgeWithDestName(id, maxId, idBuffer); 
				//print id type
				maxId++;
				char* typeNameStr = convertTypeNameToString(semanticType->typeName); 		
				printEdgeWithDestName(id, maxId, typeNameStr);
				break;
			}
			case EXPRESSION: {
				printExpression(parentId, primaryExpr->expr);
				break; 
			}
			case PE_COMPOSITE: {
				printEdgeWithDestName(parentId, id, "ARRAY_ACCESS"); 
				printPrimaryExpression(id, primaryExpr->primaryExpr);
				printExpression(id, primaryExpr->expr);
				break;
			}
			case FUNCTION_CALL:{
				printFunctionCall(parentId, primaryExpr->funcCall); 
				break; 
			}
		}
	}
}

void printFunctionCall(int parentId, struct FunctionCall* functionCall) {
	if (functionCall != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "F_CALL");
		maxId++; 
		printEdgeWithDestName(id, maxId, functionCall->primaryExpr->identifier);
		maxId++; 
		printEdgeWithDestName(id, maxId, "PARAMS");
		printExpressionList(maxId, functionCall->exprList); 
	}
}

void printExpressionList(int parentId, struct ExpressionList* expressionList) {
	if (expressionList != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "EXPR_LIST");
		struct Expression* expr = expressionList->firstExpression; 
		while (expr != NULL) {
			printExpression(id, expr); 
			expr = expr->nextExpr; 
		}
	}
}

void printDeclarationList(int parentId, struct DeclarationList* declarationList){
	if (declarationList != NULL) {
		struct Declaration *declaration = declarationList->firstDecl; 
		while (declaration != NULL) {
			printDeclaration(parentId, declaration);
			declaration = declaration->nextDecl;
		}
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
	}
}

void printVarDecl(int parentId, struct VarDecl * varDecl){
	if (varDecl != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "VAR_DECL");
		if (varDecl->varSpec != NULL) {
			printVarSpec(id, varDecl->varSpec); 
		}
		else if (varDecl->varSpecList != NULL) {
			printVarSpecList(id, varDecl->varSpecList);
		}
	}
}

void printConstDecl(int parentId, struct ConstDecl * constDecl){
	if (constDecl != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "CONST");
		if (constDecl->constSpec != NULL) {
			printConstSpec(id, constDecl->constSpec); 
		}
		else if (constDecl->constSpecList != NULL) {
			printConstSpecList(id, constDecl->constSpecList);
		}
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
		struct Method* method = getMethod(semanticClass, functionDecl->identifier); 
		
		printSignature(id, functionDecl->signature,method);
		
		//print function body
		if (functionDecl->block != NULL) {
			printBlock(id, functionDecl->block); 
		}
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
			printExpressionList(id, varSpec->exprList);
		}
	}
}

void printVarSpecList(int parentId, struct VarSpecList* varSpecList){
	if (varSpecList != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "VAR_SPEC_LIST");
		struct VarSpec* varSpec = varSpecList->firstVarSpec; 
		while (varSpec != NULL) {
			printVarSpec(id, varSpec);
			varSpec = varSpec->nextVarSpec;
		}
	}
}

void printConstSpec(int parentId, struct ConstSpec* constSpec) {
	if (constSpec != NULL) {
		maxId++;
		int id = maxId;
		printEdgeWithDestName(parentId, id, "CON_SPEC");
		if (constSpec->idListType != NULL) {
			printIdentifierList(id, constSpec->idListType->identifierList);
			printTypeName(id, constSpec->idListType->type);
		}
		else if (constSpec->idList != NULL) {
			printIdentifierList(id, constSpec->idList);
		}

		printExpressionList(id, constSpec->exprList);
	}
}

void printConstSpecList(int parentId, struct ConstSpecList* constSpecList) {
	if (constSpecList != NULL) {
		int id = ++maxId;
		printEdgeWithDestName(parentId, id, "CONST_SPEC_LIST");
		struct ConstSpec* constSpec = constSpecList->firstConstSpec;
		while (constSpec != NULL) {
			printConstSpec(id, constSpec);
			constSpec = constSpec->nextConstSpec;
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
}

void printSimpleStmt(int parentId, struct SimpleStmt* simpleStmt){
	if (simpleStmt != NULL) {
		maxId++; 
		int id = maxId;
		printEdgeWithDestName(parentId, id, "SIMPLE_STMT"); 
		switch (simpleStmt->stmtType) {
			case EXPR_SIMPLE_STMT: {
				printExpression(id, simpleStmt->expr); 
				break; 
			}
			case INC_SIMPLE_STMT: {
				maxId++; 
				printEdgeWithDestName(id, maxId, "INC_AFTER");
				printExpression(maxId, simpleStmt->expr); 
				break; 
			}
			case DEC_SIMPLE_STMT: {
				maxId++;
				printEdgeWithDestName(id, maxId, "DEC_AFTER");
				printExpression(maxId, simpleStmt->expr);
				break; 
			}
			case ASSIGN_STMT: {
				printAssignStatement(id, simpleStmt->exprListLeft, simpleStmt->exprListRight, "\"=\"");
				break; 
			}
			case PLUS_ASSIGN_STMT: {
				printAssignStatement(id, simpleStmt->exprListLeft, simpleStmt->exprListRight, "\"\+=\"");
				break;
			}
			case MINUS_ASSIGN_STMT: {
				printAssignStatement(id, simpleStmt->exprListLeft, simpleStmt->exprListRight, "\"\-=\"");
				break;
			}
			case MUL_ASSIGN_STMT: {
				printAssignStatement(id, simpleStmt->exprListLeft, simpleStmt->exprListRight, "\"\*=\"");
				break;
			}
			case DIV_ASSIGN_STMT: {
				printAssignStatement(id, simpleStmt->exprListLeft, simpleStmt->exprListRight, "\"\/=\"");
				break;
			}
		}
	}
}

void printAssignStatement(int parentId, struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, char* assign_type){
	int id = ++maxId; 
	printEdgeWithDestName(parentId, id, assign_type); 
	printExpressionList(id, leftExprList); 
	printExpressionList(id, rightExprList);
}

void printReturnStmt(int parentId, struct ReturnStmt* returnStmt){
	if (returnStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "RETURN");
		if (returnStmt->exprList != NULL) {
			printExpressionList(id, returnStmt->exprList);
		}
	}
}

void printBlock(int parentId, struct Block* block){
	if (block != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "BLOCK");
		printStmtList(id, block->stmtList); 
	}
}

void printIfStmt(int parentId, struct IfStmt* ifStmt){
	if (ifStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "IF"); 
		printIfStmtExpression(id, ifStmt->ifStmtExpr); 
		printBlock(id, ifStmt->block);
		if (ifStmt->elseBlock != NULL) {
			printElseBlock(id, ifStmt->elseBlock); 
		}
	}
}

void printIfStmtExpression(int parentId, struct IfStmtExpression* ifStmtExpr) {
	if (ifStmtExpr != NULL) {

		int id = ++maxId;
		printEdgeWithDestName(parentId, id, "EXPR_COND");
		if (ifStmtExpr->simpleStmt != NULL) {
			printSimpleStmt(id, ifStmtExpr->simpleStmt);
		}
		printExpression(id, ifStmtExpr->expr);
	}
}

void printElseBlock(int parentId, struct ElseBlock* elseBlock)
{
	int id = ++maxId; 
	printEdgeWithDestName(parentId, id, "ELSE"); 

	if (elseBlock->ifStmt != NULL) {
		printIfStmt(id, elseBlock->ifStmt); 
	}
	else {
		printBlock(id, elseBlock->block);
	}
}

void printStmtList(int parentId, struct StatementList* stmtList){
	if (stmtList != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "STMT_LIST"); 
		struct Statement* stmt = stmtList->firstStmt; 
		while (stmt != NULL) {
			printStatement(id, stmt); 
			stmt = stmt->nextStatement; 
		}
	}
}

void printSignature(int parentId, struct Signature* signature, struct Method* method){

	if (signature != NULL) {
		maxId++;
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "Signature");
		if (signature->paramInParen != NULL) {
			printParamInParen(id, signature->paramInParen, method);
		}
		if (signature->result != NULL) {
			printResult(id, signature->result, method);
		}
	}
}

void printParamInParen(int parentId, struct ParamInParen* paramInParen, struct Method* method){
	if (paramInParen != NULL) {
		if (paramInParen->paramList != NULL) {
			printParamList(parentId, paramInParen->paramList, method);
		}
	}
}

void printParamList(int parentId, struct ParameterList* paramList, struct Method* method){
	if (paramList != NULL) {
		maxId++;
		int id = maxId;
		printEdgeWithDestName(parentId, id, "ParamList");
		struct ParameterDeclare* paramDecl = paramList->firstParamDecl; 
		while (paramDecl != NULL) {
			printParamDeclare(id, paramDecl, method); 
			paramDecl = paramDecl->nextParamDecl; 
		}
	}
}

void printParamDeclare(int parentId, struct ParameterDeclare* paramDeclare, struct Method* method){
	if (paramDeclare != NULL) {
		maxId++; 
		int id = maxId; 
		printEdgeWithDestName(parentId, id, "PARAM_DECL"); 
		if (paramDeclare->type != NULL) {
			printTypeName(id, paramDeclare->type); 
		}
		if (paramDeclare->identifier != NULL) {
			printPrimitiveExpression(id, "ID", paramDeclare->identifier); 
			struct LocalVariable* param = findLocalVariableByScope(method->localVariablesTable, paramDeclare->identifier, 1);
			int paramId = param->id;
			int sourceId = maxId - 1; 
			maxId++; 
			char* paramIdBuffer[10]; 
			itoa(paramId, paramIdBuffer, 10); 
			printEdgeWithDestName(sourceId, maxId, paramIdBuffer); 
		}
	}
}

void printResult(int parentId, struct Result* result, struct Method* method){
	if (result != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "ReturnType"); 
		if (result->type != NULL) {
			printTypeName(id, result->type); 
		}
		if (result->paramInParen != NULL) {
			printParamInParen(id, result->paramInParen, method);
		}
	}
}

void printForStmt(int parentId, struct ForStmt* forStmt) {
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
}

void printForClause(int parentId, struct ForClause* forClause) {
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
}

void printForInitStmt(int parentId, struct ForInitStmt* forInitStmt){
	if (forInitStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "FOR_INIT");
		if (forInitStmt->initStmt != NULL) {
			printSimpleStmt(id, forInitStmt->initStmt);
		}
	}
}

void printForCondition(int parentId, struct ForCondition* forCondition){
	if (forCondition != NULL) {
		maxId++;
		int id = maxId;
		printEdgeWithDestName(parentId, id, "FOR_COND");
		if (forCondition->expression != NULL) {
			printExpression(id, forCondition->expression);
		}
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
}

void printPrintStmt(int parentId, struct PrintStatement* printStmt){
	if (printStmt != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "PRINT");
		printExpressionList(id, printStmt->expressionList); 
	}
}

void printScanStmt(int parentId, struct ScanStatement* scanStmt){
	if (scanStmt != NULL) {
		int id = ++maxId;
		printEdgeWithDestName(parentId, id, "SCAN");
		printIdentifierList(id, scanStmt->identifierList);
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
	case FUNCTION_CALL:
		strcpy(result, "FUNC_CALL");
		break;
	case NOT_UNARY_EXPR:
		strcpy(result, "!");
		break;
	case PLUS_UNARY_EXPR:
		strcpy(result, "\"+\"");
		break;
	case MINUS_UNARY_EXPR:
		strcpy(result, "\"-\"");
		break;
	case AND_EXPRESSION:
		strcpy(result, "\"&&\"");
		break;
	case OR_EXPRESSION:
		strcpy(result, "\"||\"");
		break;
	case EQU_EXPRESSION:
		strcpy(result, "\"==\"");
		break;
	case NE_EXPRESSION:
		strcpy(result, "\"!=\"");
		break;
	case GT_EXPRESSION:
		strcpy(result, "\">\"");
		break;
	case GTE_EXPRESSION:
		strcpy(result, "\">=\"");
		break;
	case LT_EXPRESSION:
		strcpy(result, "\"<\"");
		break;
	case LTE_EXPRESSION:
		strcpy(result, "\"<=\"");
		break;
	case PLUS_EXPRESSION:
		strcpy(result, "\"+\"");
		break;
	case MINUS_EXPRESSION:
		strcpy(result, "\"-\"");
		break;
	case MUL_EXPRESSION:
		strcpy(result, "\"*\"");
		break;
	case DIV_EXPRESSION:
		strcpy(result, "\"/\"");
		break;
	case MOD_EXPRESSION:
		strcpy(result, "\"%\"");
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
		struct Identifier* identifier = identifierList->firstId; 
		while (identifier != NULL) {
			printPrimitiveExpression(id, "ID", identifier->name);
			identifier = identifier->nextId; 
		}
	}
}

void printTypeName(int parentId, struct Type* type){
	if (type != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "TYPE"); 
		maxId++;
		if (type->expr == NULL) {

			switch (type->typeName) {
				case IDENTIFIER_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "CUSTOM");
					break;
				}
				case STRING_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "STRING");
					break;
				}
				case FLOAT32_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "FLOAT");
					break;
				}
				case INT_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "INT");
					break;
				}
				case BOOL_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "BOOL");
					break;
				}
			}
		}
		else {
			switch (type->typeName) {
				case IDENTIFIER_TYPE_NAME: {
					char buffer[30]; 
					strcpy(buffer, "ARR_"); 
					printEdgeWithDestName(id, maxId, "ARR_CUSTOM");
					break;
				}
				case STRING_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "ARR_STRING");
					break;
				}
				case FLOAT32_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "ARR_FLOAT");
					break;
				}
				case INT_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "ARR_INT");
					break;
				}
				case BOOL_TYPE_NAME: {
					printEdgeWithDestName(id, maxId, "ARR_BOOL");
					break;
				}
			}
		}
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
}

void printSwitchBody(int parentId, struct SwitchBody* switchBody) {
	if (switchBody != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "SW_BODY"); 
		if (switchBody != NULL) {
			printExpressionCaseClauseList(id, switchBody->eccl);
		}
	}
}

void printExpressionCaseClauseList(int parentId, struct ExpressionCaseClauseList* eccl) {
	if (eccl != NULL) {
		struct ExpressionCaseClause* caseClause = eccl->firstExprCaseClause; 
		while (caseClause != NULL) {
			printExpressionCaseClause(parentId, caseClause);
			caseClause = caseClause->nextExprCaseClause; 
		}
	}
}

void printExpressionCaseClause(int parentId, struct ExpressionCaseClause* ecc) {
	if (ecc != NULL) {
		int id = ++maxId; 
		printEdgeWithDestName(parentId, id, "CLAUSE"); 
		printExpressionSwitchCase(id, ecc->expreSwitchCase);
		printStmtList(id, ecc->stmtList);
	}
}

void printExpressionSwitchCase(int parentId, struct ExpressionSwitchCase* expressionSwitchCase) {
	if (expressionSwitchCase != NULL) {
		printExpressionList(parentId, expressionSwitchCase->exprList);
	}
}

void printSwitchInitialExpression(int parentId, struct SwitchInitialAndExpression* switchInitialAndExpression){
	if (switchInitialAndExpression != NULL) {
		printSimpleStmt(parentId, switchInitialAndExpression->initialStmt);
		printExpression(parentId, switchInitialAndExpression->expression);
	}
}

char* convertTypeNameToString(enum TypeNames type) {
	switch (type) {
	case STRING_TYPE_NAME:
		return "STRING";
	case INT_TYPE_NAME:
		return "INT";
	case FLOAT32_TYPE_NAME:
		return "FLOAT";
	case VOID_TYPE_NAME:
		return "VOID";
	default:
		return "UNKNOWN";
	}
}