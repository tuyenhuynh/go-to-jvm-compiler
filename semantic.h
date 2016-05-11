#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include <stdbool.h>
#include <trees.h>
#include <stdlib.h>
#include <stdio.h>
#include <semantic_struct.h>
#include "list.h"
#include "helpers.h"

struct  Class* semanticClass; 

//node of list : struct Constant*
List* constantsTable;

//key: char*, value: Field*; 
HashTable* fieldsTable;

//key: char*, value: struct Method* ; 
HashTable* methodsTable;

struct Constant* constantClass; 

struct SemanticType* checkExpressionType(struct Expression* expr, struct Method* method);

struct SemanticType* checkPrimaryExpressionType(struct PrimaryExpression* primaryExpr, struct Method* method); 

bool doSemantic(struct Program* program); 
bool checkSemanticIfStmt(struct IfStmt* ifStmt, struct Method* method);
bool checkSemanticElseBlock(struct ElseBlock* elseBlock, struct Method* method);
bool checkSemanticBlock(struct Block* block, struct Method* method); 
bool checkSemanticSwitchStmt(struct SwitchStmt* switchStmt, struct Method* method);
bool checkSemanticForStmt(struct ForStmt* forStmt, struct Method* method ); 
bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl);
bool checkSemanticSignature(struct Signature* signature, struct Method* method);
bool checkSemanticParamList(struct ParameterList* paramList, char* functionName); 
bool checkSemanticPrintStmt(struct PrintStatement* printStmt, struct Method* method);
bool checkSemanticScanStmt(struct ScanStatement* scanStmt, struct Method* method); 
bool checkSemanticReturnStmt(struct ReturnStmt* returnStmt, struct Method* method); 
bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList, struct Method* method);
bool checkSemanticVarDecl(struct VarDecl* varDecl, struct Method* method);
bool checkSemanticConstDecl(struct ConstDecl* constDecl, struct Method* method); 
bool checkSemanticVarSpec(struct VarSpec* varSpec, struct Method* method);
bool checkSemanticStmt(struct Statement* statement, struct Method* method);
bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, struct Method* method);
bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, struct Method* method);
bool checkSemanticAssignStmt(struct Expression* leftExpr, struct Expression* rightExpr, struct Method* method);
bool checkSemanticBlock(struct Block* block, struct Method* method);
bool checkSemanticExpressionCaseClause(struct ExpressionCaseClause *ecc, struct Method* method);
bool addLocalVariableToTable(struct VarDecl* varDecl, struct Method* method);
struct LocalVariable* getLocalVariableFromTable(List* variablesTable, char* varName, int scope);
bool addVariableToLocalVarsTable(char* id, enum TypeNames typeName, struct Method* method, bool isMutable);
bool addVarSpecToLocalVarsTable(struct VarSpec* varSpec, struct Method* method, bool isMutable);
bool addConstantToLocalConstantTable(char* constName, HashTable* localConstTable, struct Method* method); 
bool checkSemanticConstSpec(struct ConstSpec* varSpec, struct Method* method);
bool addParamToLocalVarsTable(struct ParameterDeclare* paramDeclare, struct Method* method);
bool isContainReturnStatement(struct Block* block); 
void deactivateLocalVariablesByScope(List* localVariablesTable, int scope);

struct Constant* addUtf8ToConstantsTable(char* utf8);
struct Constant* addNameAndTypeToConstantsTable(char* name, char* type);
struct Constant* addFieldRefToConstantsTable(char* fieldName, char* typeName);
struct Constant* addMethodRefToConstantsTable(char* methodName, char* methodDescriptor);

char* createMethodDescriptor(struct ParameterList* paramList, char* returnTypeStr);

struct Field* getField(struct Class* class, char* fieldName); 
struct Method* getMethod(struct Class* class, char* methodName); 

enum TypeName getFunctionReturnType(struct FunctionDecl* functionDecl);

void printLocalVariablesTable(struct Method* method);
#endif //_SEMANTIC_H_
