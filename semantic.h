#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include <stdbool.h>
#include <trees.h>
#include <stdlib.h>
#include <stdio.h>

struct SemanticType* checkExpressionType(struct Expression* expr);

struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr); 
bool doSemantic(struct Program* program); 
bool checkSemanticIfStmt(struct IfStmt* ifStmt, char* functionName);
bool checkSemanticElseBlock(struct ElseBlock* elseBlock, char* functionName);
bool checkSemanticBlock(struct Block* block, char* functionName); 
bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, char* functionName);
bool checkSemanticForStmt(struct ForStmt* forStmt, char* functionName ); 
bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl);
bool checkSemanticSignature(struct Signature* signature);
bool checkSemanticParamList(struct ParameterList* paramList); 
bool checkSemanticReturnType(struct Result* result); 
bool checkSemanticPrintStmt(struct PrintStatement* printStmt, char* functionName);
bool checkSemanticScanStmt(struct ScanStatement* scanStmt, char* functionName); 
bool checkSemanticReturnStmt(struct ReturnStmt* returnStmt); 
bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, char* functionName);
bool checkSemanticVarDecl(struct VarDecl* varDecl, char* functionName);
bool checkSemanticConstDecl(struct ConstDecl* constDecl, char* functionName); 
bool checkSemanticVarSpec(struct VarSpec* varSpec, char* functionName);
bool checkSemanticStmt(struct Statement* statement, char* functionName);
bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, char* functionName);
bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, char* functionName);
bool checkSemanticAssignStmt(struct Expression* leftExpr, struct Expression* rightExpr, char* functionName);
bool checkSemanticBlock(struct Block* block, char* functionName);

#endif //_SEMANTIC_H_
