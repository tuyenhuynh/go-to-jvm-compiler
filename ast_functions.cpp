#include "trees.h"
#include "ast_functions.h"

struct Program *CreateProgram(struct Package *pkg, struct Imports *imports, struct DeclarationList *declList) {
	struct Program *Result = (struct Program *)malloc(sizeof(struct Program));

	Result->pkg = pkg;
	Result->imports = imports;
	Result->declList = declList;

	return Result;
}

struct Package *CreatePackage(char *pkgName) {
	struct Package *Result = (struct Package *)malloc(sizeof(struct Package));

	Result->packageName = pkgName;

	return Result;
}

struct Imports *AppendToImportsList(struct Imports *imports, struct Import *import) {
	struct Imports *Result = (struct Imports *)malloc(sizeof(struct Imports));
	Result->nextImport = NULL;
	imports->nextImport = Result;
	Result->import = import;
	return Result;
}

struct Import *CreateImportFromStatement(char *importStmt) {
	struct Import *Result = (struct Import *)malloc(sizeof(struct Import));

	Result->importStmt = importStmt;

	return Result;
}

struct Import *CreateCompositeImportFromStatementList(struct ImportStmtList *importStmtList) {
	struct Import *Result = (struct Import *)malloc(sizeof(struct Import));

	Result->importStmtList = importStmtList;

	return Result;
}

struct ImportStmtList *CreateImportStatementList(char *importStmt) {
	struct ImportStmtList *Result = (struct ImportStmtList *)malloc(sizeof(struct ImportStmtList));
	Result->nextImportStmt = NULL;
	Result->importStmt = importStmt;

	return Result;
}

struct ImportStmtList *AppendToImportStatementList(struct ImportStmtList *importStmtList, char *importStmt) {
	struct ImportStmtList *Result = (struct ImportStmtList *)malloc(sizeof(struct ImportStmtList));
	Result->nextImportStmt = NULL;
	importStmtList->nextImportStmt = Result;
	Result->importStmt = importStmt;

	return Result;
}

struct DeclarationList *AppendToDeclarationList(struct DeclarationList *declList, struct Declaration *decl) {
	struct DeclarationList *Result = (struct DeclarationList *)malloc(sizeof(struct DeclarationList));

	Result->nextDecl = NULL;
	declList->nextDecl = Result;
	Result->decl = decl;

	return Result;

}

struct Declaration *CreateConstDecl(enum DeclType type, struct ConstSpec *constSpec) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	struct ConstDecl *newConstDecl = (struct ConstDecl *)malloc(sizeof(struct ConstDecl));


	Result->declType = type;

	newConstDecl->constSpec = constSpec;;

	Result->constDecl = newConstDecl;

	return Result;

}

struct ConstSpec *CreateConstSpecFromIdList(struct IdentifierList *idList, struct ExpressionList *expressionList) {
	struct ConstSpec *Result = (struct ConstSpec *)malloc(sizeof(struct ConstSpec));

	Result->idList = idList;
	Result->expressionList = expressionList;

	return Result;
}

struct ConstSpec *CreateConstSpecFromIdListWithType(struct IdentifierListType *idListType, struct ExpressionList *expressionList) {
	struct ConstSpec *Result = (struct ConstSpec *)malloc(sizeof(struct ConstSpec));

	Result->idListType = idListType;
	Result->expressionList = expressionList;

	return Result;
}

struct Type *CreateTypeFromId(char *id) {
	struct Type *Result = (struct Type *)malloc(sizeof(struct Type));
	Result->identifier = id;

	return Result;
}

struct Type *CreateCompositeType(struct Expression *expr, char *id) {
	struct Type *Result = (struct Type *)malloc(sizeof(struct Type));

	Result->identifier = id;
	Result->expr = expr;

	return Result;
}

struct IdentifierListType *CreateIdListWithType(struct IdentifierList *identifierList, struct Type *type) {
	struct IdentifierListType *Result = (struct IdentifierListType *)malloc(sizeof(struct IdentifierListType));

	Result->type = type;
	Result->identifierList = identifierList;

	return Result;

}

struct Declaration *CreateSimpleVarDecl(enum DeclType declType, struct VarSpec *varSpec) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	struct VarDecl *newVarDecl = (struct VarDecl *)malloc(sizeof(struct VarDecl));

	Result->declType = declType;

	newVarDecl->varSpec = varSpec;

	Result->varDecl = newVarDecl;

	return Result;

}

struct Declaration *CreateCompositeVarDecl(enum DeclType declType, struct VarSpecList *varSpecList) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	struct VarDecl *newVarDecl = (struct VarDecl *)malloc(sizeof(struct VarDecl));

	Result->declType = declType;

	newVarDecl->varSpecList = varSpecList;

	Result->varDecl = newVarDecl;

	return Result;
}

struct VarSpec *CreateSimpleVarSpecWType(struct IdentifierListType *idListType) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idListType = idListType;

	return Result;
}

struct VarSpec *CreateCompositeVarSpecWtype(struct IdentifierListType *idListType, struct ExpressionList *exprList) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idListType = idListType;
	Result->exprList = exprList;

	return Result;
}

struct VarSpec *CreateCompositeVarSpecWOType(struct IdentifierList *idList, struct ExpressionList *exprList) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idList = idList;

	Result->exprList = exprList;

	return Result;
}

struct VarSpecList *CreateVarSpecList(struct VarSpec *varSpec) {
	struct VarSpecList *Result = (struct VarSpecList *)malloc(sizeof(struct VarSpecList));

	Result->nextVarSpec = NULL;
	Result->varSpec = varSpec;

	return Result;
}

struct VarSpecList *AppendToVarSpecList(struct VarSpecList *varSpecList, struct VarSpec *varSpec) {
	struct VarSpecList *Result = (struct VarSpecList *)malloc(sizeof(struct VarSpecList));

	Result->nextVarSpec = NULL;
	varSpecList->nextVarSpec = Result;
	Result->varSpec = varSpec;

	return Result;
}
