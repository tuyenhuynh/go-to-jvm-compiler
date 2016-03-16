#ifndef	_ASTFUNCTIONS_H_
#define _ASTFUNCTIONS_H_

#include "trees.h"
#include <malloc.h>

struct Program *CreateProgram(struct Package *_pkg, struct Imports *_imports, struct DeclarationList *_declList);
struct Package *CreatePackage(char *_pkgName);
struct Imports *AppendToImportsList(struct Imports *_imports, struct Import *_import);
struct Import *CreateImportFromStatement(char *_importStmt);
struct Import *CreateCompositeImportFromStatementList(struct ImportStmtList *_importStmtList);
struct ImportStmtList *CreateImportStatementList(char *_importStmt);
struct ImportStmtList *AppendToImportStatementList(struct ImportStmtList *_importStmtList, char *_importStmt);
struct DeclarationList *AppendToDeclarationList(struct DeclarationList *_declList, struct Declaration *_decl);
struct Declaration * CreateDeclarationFromVarDecl(enum DeclType _declType, struct VarDecl * _varDecl);
struct Declaration * CreateDeclarationFromConstDecl(enum DeclType _declType, struct ConstDecl * _constDecl);
struct Declaration * CreateDeclarationFromFuncDecl(enum DeclType _declType, struct FuncDecl * _funcDecl);
struct ConstDecl *CreateConstDecl(struct ConstSpec *_constSpec);
struct Type *CreateTypeFromId(char *_id);
struct Type *CreateCompositeType(struct Expression *_expr, char *_id);
struct IdentifierListType *CreateIdListWithType(struct IdentifierList *_identifierList, struct Type *_type);
struct VarDecl *CreateSimpleVarDecl(struct VarSpec *_varSpec);
struct VarDecl *CreateCompositeVarDecl(struct VarSpecList *_varSpecList);
struct VarSpec *CreateSimpleVarSpecWType(struct IdentifierListType *_idListType);
struct VarSpec *CreateCompositeVarSpecWtype(struct IdentifierListType *_idListType, struct ExpressionList *_exprList);
struct VarSpec *CreateCompositeVarSpecWOType(struct IdentifierList *_idList, struct ExpressionList *_exprList);
struct VarSpecList *CreateVarSpecList(struct VarSpec *_varSpec);
struct VarSpecList *AppendToVarSpecList(struct VarSpecList *_varSpecList, struct VarSpec *_varSpec);
struct PrimaryExpression *CreateDecimalExpression(enum ExpressionType _exprType, int _decNumber);
struct PrimaryExpression *CreateFloatExpression(enum ExpressionType _exprType, float _floatNumber);

struct PrimaryExpression *CreateStringExpression(enum ExpressionType _exprType, char * _stringLiteral);

struct PrimaryExpression *CreateIdExpression(enum ExpressionType _exprType, char * _identifier);

struct PrimaryExpression * CreateCompositePrimaryExpression(enum ExpressionType _exprType, struct PrimaryExpression * _primaryExpr, struct Expression * _expr);

struct PrimaryExpression * CreatePrimaryExpressionFromFuncCall(enum ExpressionType _exprType, struct FunctionCall *_funcCall);

struct PrimaryExpression * CreatePrimaryExpressionFromExpression(enum ExpressionType _exprType, struct Expression * _expr);

struct FunctionCall * CreateFunctionCallExpr(char * _identifier, struct ExpressionList * _exprList);

struct Expression * CreateUnaryExpression(enum ExpressionType _exprType, struct PrimaryExpression * _primaryExpr);

struct Expression * CreateBinaryExpression(enum ExpressionType _exprType, struct Expression * _leftExpr, struct Expression * _rightExpr);

struct ExpressionList * CreateExpressionList(struct Expression * _expr);

struct ExpressionList * AppendToExpressionList(struct ExpressionList * _exprList, struct Expression * _expr);

struct Statement * CreateStmtFromSimpleStmt(enum StatementType _stmtType, struct SimpleStmt * _simpleStmt);

struct Statement * CreateConstDeclStmt(enum StatementType _stmtType, struct ConstDecl * _constDecl);

struct Statement * CreateStmtFromReturnStmt(enum StatementType _stmtType, struct ReturnStmt * _returnStmt);

struct Statement * CreateStmtFromBlock(enum StatementType _stmtType, struct Block * _block);

struct Statement * CreateStmtFromIfStmt(enum StatementType _stmtType, struct IfStmt * _ifStmt);

struct Statement * CreateStmtFromSwitchStmt(enum StatementType _stmtType, struct SwitchStmt * _switchStmt);

struct Statement * CreateStmtFromForStmt(enum StatementType _stmtType, struct ForStmt * _forStmt);

struct IdentifierList * CreateIdList(char * _id);

struct IdentifierList * AppendToIdList(struct IdentifierList * _idList, char * _id);

struct ReturnStmt * CreateReturnStatement(struct ExpressionList * _exprList);

struct IfStmt * CreateIfStatement(struct IfStmtExpression * _ifStmtExpr, struct Block * _block);

struct IfStmt * CreateIfElseStatement(struct IfStmtExpression * _ifStmtExpr, struct Block * _block, struct ElseBlock * _elseBlock);

struct IfStmtExpression * CreateIfStmtExpression(struct Expression * _expr);

struct IfStmtExpression * CreateCompositeIfStmtExpression(struct SimpleStmt * _simpleStmt, struct Expression *_expr);

struct ElseBlock * CreateElseBlockFromIfStmt(struct IfStmt * _ifStmt);

struct ElseBlock * CreateElseBlockFromBlock(struct Block * _block);

struct Block * CreateBlock(struct StatementList * _stmtList);

struct StatementList * CreateStmtList(struct Statement * _stmt);

struct StatementList * AppendToStmtList(struct StatementList * _stmtList, struct Statement * _stmt);

struct SwitchStmt * CreateSwitchStatementWSimpleStmt(struct  SimpleStmt * _simpleStmt, struct SwitchBody * _switchBody);

struct SwitchStmt * CreateSwitchStatementWExpression(struct Expression * _expr, struct SwitchBody * _switchBody);

struct SwitchBody * CreateSwitchBody(struct ExpressionCaseClauseList *_eccl);

struct ExpressionCaseClauseList * CreateExpressionCaseClauseList(struct ExpressionCaseClause * _exprCaseClause);

struct ExpressionCaseClauseList * AppendToExpressionCaseClauseList(struct ExpressionCaseClauseList * _eccl, struct ExpressionCaseClause * _exprCaseClause);

struct ExpressionCaseClause * CreateExpressionCaseClause(struct ExpressionSwitchCase * _expreSwitchCase, struct StatementList * _stmtList);

struct ExpressionSwitchCase * CreateExprSwitchCase(struct ExpressionList * _exprList);

struct SimpleStmt * CreateSimpleStmt(enum StatementType _stmtType, struct Expression * _expr);

struct SimpleStmt * CreatAssignSimpleStmt(enum StatementType _stmtType, struct ExpressionList * _exprListLeft, struct ExpressionList * _exprListRight);

struct ForStmt * CreateForStmt(struct Block * _block);

struct ForStmt * CreateForStmtWExpr(struct Expression * _expr, struct  Block * _block);

struct ForStmt * CreateForStmtWClause(struct ForClause * _forClause, struct  Block * _block);

struct ForClause * CreateForClause(struct SimpleStatement * _simpleStmtLeft, struct Expression * _expr, struct SimpleStatement * _simpleStmtRight);

struct FunctionDecl * CreateFunctionDeclaration(char * _identifier, struct Signature * _signature);

struct FunctionDecl * CreateFunctionDeclarationWithBlock(char * _identifier, struct Signature * _signature, struct Block * _block);

struct Signature * CreateSignature(struct ParamInParen * _paramInParen);

struct Signature * CreateSignatureWithResult(struct ParamInParen * _paramInParen, struct Result * _result);

struct ParamInParen * CreateParametersInParens(struct ParameterList * _paramList);

struct ParameterList * CreateParameterDeclareList(struct ParameterDeclare * _paramDecl);

struct ParameterList * AppendToParameterDeclareList(struct ParameterList * _paramDeclList, struct  ParameterDeclare * _paramDecl);

struct ParameterDeclare * CreateParameterDeclareWithoutId(struct Type * _type);

struct ParameterDeclare * CreateParameterDeclareWithId(char * _identifier, struct Type * _type);

struct Result * CreateResultFromParameters(struct ParamInParen * _paramInParen);

struct Result * CreateResultFormType(struct Type * _type);

#endif //_AST_FUNCTIONS_H_