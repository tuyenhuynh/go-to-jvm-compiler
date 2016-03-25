#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include <stdbool.h>
#include <trees.h>

struct SemanticType* checkExpressionType(struct Expression* expr);

struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr); 
bool doSemantic(struct Program* program); 
bool checkSemanticIfStmt(struct IfStmt* ifStmt, char* functionName);
bool checkSemanticElseBlock(struct ElseBlock* elseBlock, char* functionName);
bool checkSemanticBlock(struct Block* block, char* functionName); 
bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, char* functionName);
bool checkSemanticForStmt(struct ForStmt* forStmt, char* functionName ); 

#endif //_SEMANTIC_H_
