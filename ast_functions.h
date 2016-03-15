#ifndef	_AST_FUNCTION_H_
#define _AST_FUNCTION_H_

#include "trees.h"
#include <malloc.h>

struct Program *CreateProgram(struct Package *pkg, struct Imports *imports, struct DeclarationList *declList);
struct Package *CreatePackage(char *pkgName);
struct Imports *AppendToImportsList(struct Imports *imports, struct Import *import);
struct Import *CreateImportFromStatement(char *importStmt);
struct Import *CreateCompositeImportFromStatementList(struct ImportStmtList *importStmtList);
struct ImportStmtList *CreateImportStatementList(char *importStmt);
struct ImportStmtList *AppendToImportStatementList(struct ImportStmtList *importStmtList, char *importStmt);
struct DeclarationList *AppendToDeclarationList(struct DeclarationList *declList, struct Declaration *decl);
struct Declaration *CreateConstDecl(enum DeclType type, struct ConstSpec *constSpec);
struct ConstSpec *CreateConstSpecFromIdList(struct IdentifierList *idList, struct ExpressionList *exprList);
struct ConstSpec *CreateConstSpecFromIdListWithType(struct IdentifierListType *idListType, struct ExpressionList *expressionList);
struct Type *CreateTypeFromId(char *id);
struct Type *CreateCompositeType(struct Expression *expr, char *id);
struct IdentifierListType *CreateIdListWithType(struct IdentifierList *identifierList, struct Type *type);
struct Declaration *CreateSimpleVarDecl(enum DeclType declType, struct VarSpec *varSpec);
struct Declaration *CreateCompositeVarDecl(enum DeclType declType, struct VarSpecList *varSpecList);
struct VarSpec *CreateSimpleVarSpecWType(struct IdentifierListType *idListType);
struct VarSpec *CreateCompositeVarSpecWtype(struct IdentifierListType *idListType, struct ExpressionList *exprList);
struct VarSpec *CreateCompositeVarSpecWOType(struct IdentifierList *idList, struct ExpressionList *exprList);
struct VarSpecList *CreateVarSpecList(struct VarSpec *varSpec);
struct VarSpecList *AppendToVarSpecList(struct VarSpecList *varSpecList, struct VarSpec *varSpec);

#endif //_AST_FUNCTION_H_