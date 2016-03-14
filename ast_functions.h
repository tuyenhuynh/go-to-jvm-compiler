#ifndef	_AST_FUNCTION_H_
#define _AST_FUNCTION_H_

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
struct Declaration *CreateConstDecl(enum DeclType type, struct ConstSpec *_constSpec);
struct ConstSpec *CreateConstSpecFromIdList(struct IdentifierList *_idList, struct ExpressionList *_exprList);
struct ConstSpec *CreateConstSpecFromIdListWithType(struct IdentifierListType *_idListType, struct ExpressionList *_expressionList);
struct Type *CreateTypeFromId(char *_id);
struct Type *CreateCompositeType(struct Expression *_expr, char *_id);
struct IdentifierListType *CreateIdListWithType(struct IdentifierList *_identifierList, struct Type *_type);
struct Declaration *CreateSimpleVarDecl(enum DeclType _declType, struct VarSpec *_varSpec);
struct Declaration *CreateCompositeVarDecl(enum DeclType _declType, struct VarSpecList *_varSpecList);
struct VarSpec *CreateSimpleVarSpecWType(struct IdentifierListType *_idListType);
struct VarSpec *CreateCompositeVarSpecWtype(struct IdentifierListType *_idListType, struct ExpressionList *_exprList);
struct VarSpec *CreateCompositeVarSpecWOType(struct IdentifierList *_idList, struct ExpressionList *_exprList);
struct VarSpecList *CreateVarSpecList(struct VarSpec *_varSpec);
struct VarSpecList *AppendToVarSpecList(struct VarSpecList *_varSpecList, struct VarSpec *_varSpec);

#endif //_AST_FUNCTION_H_