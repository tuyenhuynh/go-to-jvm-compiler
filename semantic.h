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
bool checkSemanticSwitchbody(struct SwitchBody* switchBody, struct Method* method); 
bool checkSemanticForStmt(struct ForStmt* forStmt, struct Method* method ); 
bool checkSemanticFunctionDecl(struct FunctionDecl* functionDecl);
bool checkSemanticSignature(struct Signature* signature, struct Method* method);
bool checkSemanticParamList(struct ParameterList* paramList, char* functionName); 
bool checkSemanticPrintStmt(struct PrintStatement* printStmt, struct Method* method);
bool checkSemanticScanStmt(struct ScanStatement* scanStmt, struct Method* method); 
bool checkSemanticReturnStmt(struct ReturnStmt* returnStmt, struct Method* method); 
bool checkSemanticFunctionCall(struct ExpressionList* exprList, struct ParameterList* paramList,  struct Method* method);
bool checkSemanticVarDecl(struct VarDecl* varDecl, struct Method* method);
bool checkSemanticConstDecl(struct ConstDecl* constDecl, struct Method* method); 
bool checkSemanticVarSpec(struct VarSpec* varSpec, struct Method* method);
bool checkSemanticStmt(struct Statement* statement, struct Method* method);
bool checkSemanticSimpleStmt(struct SimpleStmt* simpleStmt, struct Method* method);
bool checkSemanticAssignStmtList(struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, struct Method* method);
bool checkSemanticAssignStmt(struct Expression* leftExpr, struct Expression* rightExpr, struct Method* method);
bool checkSemanticBlock(struct Block* block, struct Method* method);
bool checkSemanticExpressionCaseClause(struct ExpressionCaseClause *ecc, enum TypeNames identifierType,  struct Method* method);
bool addLocalVariableToTable(struct VarDecl* varDecl, struct Method* method);
struct LocalVariable* findActiveLocalVariableByScope(List* variablesTable, char* varName, int scope);
//for tree printing purpose
struct LocalVariable* findLocalVariableByScope(List* variablesTable, char* varName, int scope);
struct LocalVariable* findActiveLocalVariableById(List* variablesTable, char* varName);
struct LocalVariable* addVariableToLocalVarsTable(char* id, struct SemanticType* type, struct Method* method, bool isMutable);
bool addVarSpecToLocalVarsTable(struct VarSpec* varSpec, struct Method* method);
bool addConstantToLocalConstantTable(char* constName, HashTable* localConstTable, struct Method* method); 
bool checkSemanticConstSpec(struct ConstSpec* varSpec, struct Method* method);
bool addParamToLocalVarsTable(char* paramName, struct SemanticType* type,  struct Method* method);
void deactivateLocalVariablesByScope(List* localVariablesTable, int scope);
bool isContainStatementType(struct StatementList* stmtList, enum StatementType stmtType); 
bool detectBreakOrContainue(struct StatementList* stmtList);
struct Constant* addUtf8ToConstantsTable(char* utf8);
struct Constant* addIntegerToConstantsTable(int value);
struct Constant* addFloatToConstantsTable(float value);
struct Constant* addNameAndTypeToConstantsTable(char* name, char* type);
struct Constant* addFieldRefToConstantsTable(char* fieldName, char* typeName);
struct Constant* addMethodRefToConstantsTable(char* methodName, char* methodDescriptor);
struct Constant* addClassToConstantsTable(char* className);
char* createMethodDescriptor(struct ParameterList* paramList, char* returnTypeStr);
char* convertTypeToString(struct SemanticType* type);
struct Field* getField(struct Class* class, char* fieldName); 
struct Method* getMethod(char* methodName);
struct SemanticType* getFunctionReturnType(struct FunctionDecl* functionDecl);
void printLocalVariablesTable(struct Method* method);
void printConstantsTable();
void printMethodsTable(); 
void printConstant(struct Constant* constant);
#endif //_SEMANTIC_H_
