#ifndef _PRINT_TREE_
#define _PRINT_TREE_
#include "dot.h"
#include "trees.h"
#include "astfunctions.h" 

extern struct Program *root; 


void printBinaryExpression(int parentId, struct Expression* expression);
void printUnaryExpression(int parentId, struct Expression* expression);
void expressionTypeToString(enum ExpressionType exprType, char* result);
void printPrimitiveExpression(int parentId, char*name, char*value);
void printFunctionCall(int parentId, struct FunctionCall* functionCall); 
void printExpressionList(int parentId, struct ExpressionList* expressionList);

void printProgram(char* output);
void printPackage(int parentId, struct Package* package);
void printDeclarationList(int parentId, struct DeclarationList* declarationList);
void printDeclaration(int parentId, struct Declaration* declaration);
void printImportStatementList(int parentId, struct ImportStmtList* importStmtList);
void printImport(int parentId, struct Import* import);
void printImports(int parentId, struct Imports* imports); 

void printVarDecl(int parentId, struct VarDecl * varDecl);
void printVarSpec(int parentId, struct VarSpec* varSpec); 
void printVarSpecList(int parentId, struct VarSpecList* varSpecList); 
void printAssignStatement(int parentId, struct ExpressionList* leftExprList, struct ExpressionList* rightExprList, char* assign_op); 
void printConstDecl(int parentId, struct ConstDecl * constDecl);
void printFunctionDecl(int parentId, struct FunctionDecl* functionDecl);
void printIdentifierList(int parentId, struct IdentifierList * identifierList);
void printTypeName(int parentId, struct Type* type);
void printExpression(int parentId, struct Expression* expression);
void printStatement(int parentId, struct Statement* statement);
void printSimpleStmt(int parentId, struct SimpleStmt* simpleStmt);
void printReturnStmt(int parentId, struct ReturnStmt* returnStmt);
void printBlock(int parentId, struct Block* block);
void printSwitchStmt(int parentId, struct SwitchStmt* switchStmt);
void printIfStmt(int parentId, struct IfStmt* ifStmt);
void printForStmt(int parentId, struct ForStmt* forStmt);
void printIfStmtExpression(int parentId, struct IfStmtExpression* ifStmtExpr);
void printElseBlock(int parentId, struct ElseBlock* elseBlock);
void printStmtList(int parentId, struct StatementList* stmtList);
void printSwitchBody(int parentId, struct SwitchBody* switchBody);
void printExpressionCaseClauseList(int parentId, struct ExpressionCaseClauseList* eccl);
void printExpressionCaseClause(int parentId, struct ExpressionCaseClause* ecc);
void printExpressionSwitchCase(int parentId, struct ExpressionSwitchCase* expressionSwitchCase);
void printForClause(int parentId, struct ForClause* ForClause);
void printSignature(int parentId, struct Signature* signature);
void printParamInParen(int parentId, struct ParamInParen* paramInParen);
void printParamList(int parentId, struct ParameterList* paramList);
void printParamDeclare(int parentId, struct ParameterDeclare* paramDeclare);
void printResult(int parentId, struct Result* result);
void printPrimaryExpression(int parentId, struct PrimaryExpression* primaryExpr);
void printFunctionCall(int parentId, struct FunctionCall* functionCall);
void printSwitchInitialExpression(int parentId, struct SwitchInitialAndExpression* switchInitialAndExpression);
void printForInitStmt(int parentId, struct ForInitStmt* forInitStmt);
void printForCondition(int parentId, struct ForCondition* forCondition);
void printForPostStmt(int parentId, struct ForPostStmt* forPostStmt);
void printPrintStmt(int parentId, struct PrintStatement* printStmt);
void printScanStmt(int parentId, struct ScanStatement* scanStmt);

#endif //_PRINT_TREE_