#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_
#include <stdbool.h>
#include <trees.h>
#include <stdlib.h>
#include <stdio.h>
#include <semantic_struct.h>
#include "list.h"

const char* CLASS_NAME = "GO_CLASS";
struct  Class* semanticClass; 

struct SemanticType* checkExpressionType(struct Expression* expr);

struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr); 
bool doSemantic(struct Program* program); 
bool checkSemanticIfStmt(struct IfStmt* ifStmt, char* functionName);
bool checkSemanticElseBlock(struct ElseBlock* elseBlock, char* functionName);
bool checkSemanticBlock(struct Block* block, char* functionName); 
bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, char* functionName);
bool checkSemanticForStmt(struct ForStmt* forStmt, char* functionName ); 
bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl);
bool checkSemanticSignature(struct Signature* signature, char* functionName);
bool checkSemanticParamList(struct ParameterList* paramList, char* functionName); 
bool checkSemanticReturnType(struct Result* result, char* functionName); 
bool checkSemanticPrintStmt(struct PrintStatement* printStmt, char* functionName);
bool checkSemanticScanStmt(struct ScanStatement* scanStmt, char* functionName); 
bool checkSemanticReturnStmt(struct ReturnStmt* returnStmt, char* functionName); 
bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, char* functionName);
bool checkSemanticVarDecl(struct VarDecl* varDecl, char* functionName);
bool checkSemanticConstDecl(struct ConstDecl* constDecl, char* functionName); 
bool checkSemanticVarSpec(struct VarSpec* varSpec, char* functionName);
bool checkSemanticStmt(struct Statement* statement, char* functionName);
bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, char* functionName);
bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, char* functionName);
bool checkSemanticAssignStmt(struct Expression* leftExpr, struct Expression* rightExpr, char* functionName);
bool checkSemanticBlock(struct Block* block, char* functionName);
bool checkSemanticExpressionCaseClause(struct ExpressionCaseClause *ecc, char* functionName);
bool addLocalVariableToTable(struct VarDecl* varDecl, struct Method* method);
struct LocalVariable* getLocalVariableFromTable(char* varName, HashTable* variablesTable);

bool addLocalConstantsToConstantTable(struct VarSpec* varSpec, struct Method* method); 
bool addConstantToLocalConstantTable(char* constName, HashTable* localConstTable, struct Method* method); 

bool checkSemanticConstSpec(struct VarSpec* varSpec, char* functionName);
struct Constant* addConstantToConstantsTable(List* constantsTable, enum ConstantType type, void* value);
struct Constant* addRefConstantToConstantsTable(List* constantsTable, enum ConstantType type, void* const1, void* const2);
struct Constant* getConstant(List* constantsTable, enum ConstantType type, void* value);
struct Constant* getRefConstant(List* constantsTable, enum  ConstantType type, char* const1, char* const2);
struct Constant* getConstantFromLocalConstantTable(char* constName, HashTable* constsTable, struct Method* method);

struct Field* getField(struct Class* class, char* fieldName); 
struct Method* getMethod(struct Class* class, char* methodName); 


char* getFunctionReturnType(struct FunctionDecl* functionDecl);

bool addParamToVariableTable(struct ParameterDeclare* paramDeclare, struct Method* method);

#endif //_SEMANTIC_H_
