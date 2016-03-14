#pragma once
#include "trees.h"
#include <malloc.h>


struct Program *CreateProgram(struct Package *_pkg, struct Imports *_imports, struct DeclarationList *_declList) {
	struct Program *Result = (struct Program *)malloc(sizeof(struct Program));

	Result->pkg = _pkg;
	Result->imports = _imports;
	Result->declList = _declList;

	return Result;
}

struct Package *CreatePackage(char *_pkgName) {
	struct Package *Result = (struct Package *)malloc(sizeof(struct Package));

	Result->packageName = _pkgName;

	return Result;
}

struct Imports *AppendToImportsList(struct Imports *_imports, struct Import *_import) {
	struct Imports *Result = (struct Imports *)malloc(sizeof(struct Imports));
	Result->nextImport = NULL;
	_imports->nextImport = Result;
	Result->import = _import;
	return Result;
}

struct Import *CreateImportFromStatement(char *_importStmt) {
	struct Import *Result = (struct Import *)malloc(sizeof(struct Import));

	Result->importStmt = _importStmt;

	return Result;
}

struct Import *CreateCompositeImportFromStatementList(struct ImportStmtList *_importStmtList) {
	struct Import *Result = (struct Import *)malloc(sizeof(struct Import));

	Result->importStmtList = _importStmtList;

	return Result;
}

struct ImportStmtList *CreateImportStatementList(char *_importStmt) {
	struct ImportStmtList *Result = (struct ImportStmtList *)malloc(sizeof(struct ImportStmtList));
	Result->nextImportStmt = NULL;
	Result->importStmt = _importStmt;

	return Result;
}

struct ImportStmtList *AppendToImportStatementList(struct ImportStmtList *_importStmtList, char *_importStmt) {
	struct ImportStmtList *Result = (struct ImportStmtList *)malloc(sizeof(struct ImportStmtList));
	Result->nextImportStmt = NULL;
	_importStmtList->nextImportStmt = Result;
	Result->importStmt = _importStmt;

	return Result;
}

struct DeclarationList *AppendToDeclarationList(struct DeclarationList *_declList, struct Declaration *_decl) {
	struct DeclarationList *Result = (struct DeclarationList *)malloc(sizeof(struct DeclarationList));

	Result->nextDecl = NULL;
	_declList->nextDecl = Result;
	Result->decl = _decl;

	return Result;

}

struct Declaration *CreateConstDecl(enum DeclType type, struct ConstSpec *_constSpec) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	struct ConstDecl *newConstDecl = (struct ConstDecl *)malloc(sizeof(struct ConstDecl));


	Result->declType = type;

	newConstDecl->constSpec = _constSpec;;

	Result->constDecl = newConstDecl;

	return Result;

}

struct ConstSpec *CreateConstSpecFromIdList(struct IdentifierList *_idList, struct ExpressionList *_expressionList) {
	struct ConstSpec *Result = (struct ConstSpec *)malloc(sizeof(struct ConstSpec));

	Result->idList = _idList;
	Result->expressionList = _expressionList;

	return Result;
}

struct ConstSpec *CreateConstSpecFromIdListWithType(struct IdentifierListType *_idListType, struct ExpressionList *_expressionList) {
	struct ConstSpec *Result = (struct ConstSpec *)malloc(sizeof(struct ConstSpec));

	Result->idListType = _idListType;
	Result->expressionList = _expressionList;

	return Result;
}

struct Type *CreateTypeFromId(char *_id) {
	struct Type *Result = (struct Type *)malloc(sizeof(struct Type));
	Result->identifier = _id;

	return Result;
}

struct Type *CreateCompositeType(struct Expression *_expr, char *_id) {
	struct Type *Result = (struct Type *)malloc(sizeof(struct Type));

	Result->identifier = _id;
	Result->expr = _expr;

	return Result;
}

struct IdentifierListType *CreateIdListWithType(struct IdentifierList *_identifierList, struct Type *_type) {
	struct IdentifierListType *Result = (struct IdentifierListType *)malloc(sizeof(struct IdentifierListType));

	Result->type = _type;
	Result->identifierList = _identifierList;

	return Result;

}

struct Declaration *CreateSimpleVarDecl(enum DeclType _declType, struct VarSpec *_varSpec) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	struct VarDecl *newVarDecl = (struct VarDecl *)malloc(sizeof(struct VarDecl));

	Result->declType = _declType;

	newVarDecl->varSpec = _varSpec;

	Result->varDecl = newVarDecl;

	return Result;

}

struct Declaration *CreateCompositeVarDecl(enum DeclType _declType, struct VarSpecList *_varSpecList) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	struct VarDecl *newVarDecl = (struct VarDecl *)malloc(sizeof(struct VarDecl));

	Result->declType = _declType;

	newVarDecl->varSpecList = _varSpecList;

	Result->varDecl = newVarDecl;

	return Result;
}

struct VarSpec *CreateSimpleVarSpecWType(struct IdentifierListType *_idListType) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idListType = _idListType;

	return Result;
}

struct VarSpec *CreateCompositeVarSpecWtype(struct IdentifierListType *_idListType, struct ExpressionList *_exprList) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idListType = _idListType;
	Result->exprList = _exprList;

	return Result;
}

struct VarSpec *CreateCompositeVarSpecWOType(struct IdentifierList *_idList, struct ExpressionList *_exprList) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idList = _idList;

	Result->exprList = _exprList;

	return Result;
}

struct VarSpecList *CreateVarSpecList(struct VarSpec *_varSpec) {
	struct VarSpecList *Result = (struct VarSpecList *)malloc(sizeof(struct VarSpecList));

	Result->nextVarSpec = NULL;
	Result->varSpec = _varSpec;

	return Result;
}

struct VarSpecList *AppendToVarSpecList(struct VarSpecList *_varSpecList, struct VarSpec *_varSpec) {
	struct VarSpecList *Result = (struct VarSpecList *)malloc(sizeof(struct VarSpecList));

	Result->nextVarSpec = NULL;
	_varSpecList->nextVarSpec = Result;
	Result->varSpec = _varSpec;

	return Result;
}
