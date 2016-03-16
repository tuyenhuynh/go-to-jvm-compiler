#include "trees.h"
#include "astfunctions.h"

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

struct DeclarationList *CreateDeclarationList(struct Declaration *_decl) {
	struct DeclarationList *Result = (struct DeclarationList *)malloc(sizeof(struct DeclarationList));

	Result->nextDecl = NULL;
	Result->decl = _decl;

	return Result;
}

struct DeclarationList *AppendToDeclarationList(struct DeclarationList *_declList, struct Declaration *_decl) {
	struct DeclarationList *Result = (struct DeclarationList *)malloc(sizeof(struct DeclarationList));

	Result->nextDecl = NULL;
	_declList->nextDecl = Result;
	Result->decl = _decl;

	return Result;

}

struct Declaration *CreateDeclarationFromVarDecl(enum DeclType _declType, struct VarDecl *_varDecl) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	Result->declType = _declType;
	Result->varDecl = _varDecl;

	return Result;
}

struct Declaration *CreateDeclarationFromConstDecl(enum DeclType _declType, struct ConstDecl *_constDecl) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	Result->declType = _declType;
	Result->constDecl = _constDecl;

	return Result;
}

struct Declaration *CreateDeclarationFromFuncDecl(enum DeclType _declType, struct FuncDecl *_funcDecl) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	Result->declType = _declType;
	Result->funcDecl = _funcDecl;

	return Result;
}



struct ConstDecl *CreateConstDecl(struct ConstSpec *_constSpec) {
	struct ConstDecl *Result = (struct ConstDecl *)malloc(sizeof(struct ConstDecl));

	Result->constSpec = _constSpec;;

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

struct VarDecl *CreateSimpleVarDecl(struct VarSpec *_varSpec) {
	struct VarDecl *Result = (struct VarDecl *)malloc(sizeof(struct VarDecl));

	Result->varSpec = _varSpec;
	return Result;

}

struct VarDecl *CreateCompositeVarDecl(struct VarSpecList *_varSpecList) {
	struct VarDecl *Result = (struct VarDecl *)malloc(sizeof(struct VarDecl));


	Result->varSpecList = _varSpecList;
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

struct PrimaryExpression *CreateBoolExpr(enum ExpressionType _exprType, int _boolValue) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->boolValue = _boolValue;

	return Result;
}


struct PrimaryExpression *CreateDecimalExpression(enum ExpressionType _exprType, int _decNumber) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->decNumber = _decNumber;

	return Result;
}

struct PrimaryExpression *CreateFloatExpression(enum ExpressionType _exprType, float _floatNumber) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->floatNumber = _floatNumber;

	return Result;
}

struct PrimaryExpression *CreateStringExpression(enum ExpressionType _exprType, char* _stringLiteral) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

Result->exprType = _exprType;

Result->stringLiteral = _stringLiteral;

return Result;
}

struct PrimaryExpression *CreateIdExpression(enum ExpressionType _exprType, char* _identifier) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->identifier = _identifier;

	return Result;
}

struct PrimaryExpression *CreateCompositePrimaryExpression(enum ExpressionType _exprType, struct PrimaryExpression *_primaryExpr, struct Expression *_expr) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->primaryExpr = _primaryExpr;

	Result->expr = _expr;

	return Result;
}

struct PrimaryExpression *CreatePrimaryExpressionFromFuncCall(enum ExpressionType _exprType, struct FunctionCall *_funcCall) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->funcCall = _funcCall;

	return Result;
}

struct PrimaryExpression *CreatePrimaryExpressionFromExpression(enum ExpressionType _exprType, struct Expression *_expr) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->expr = _expr;

	return Result;
}

struct FunctionCall *CreateEmptyFunctionCall(struct PrimaryExpression *_primaryExpr) {
	struct FunctionCall *Result = (struct FunctionCall *)malloc(sizeof(struct FunctionCall));

	Result->primaryExpr = _primaryExpr;
	return Result;
}

struct FunctionCall *CreateFunctionCallExpr(struct PrimaryExpression *_primaryExpr, struct ExpressionList *_exprList) {
	struct FunctionCall *Result = (struct FunctionCall *)malloc(sizeof(struct FunctionCall));

	Result->exprList = _exprList;
	Result->primaryExpr = _primaryExpr;

	return Result;
}

struct Expression *CreateUnaryExpression(enum ExpressionType _exprType, struct PrimaryExpression *_primaryExpr) {
	struct Expression *Result = (struct Expression *)malloc(sizeof(struct Expression));

	Result->exprType = _exprType;
	Result->primaryExpr = _primaryExpr;

	return Result;
}

struct Expression *CreateBinaryExpression(enum ExpressionType _exprType, struct Expression *_leftExpr, struct Expression *_rightExpr) {
	struct Expression *Result = (struct Expression *)malloc(sizeof(struct Expression));

	Result->exprType = _exprType;

	Result->leftExpr = _leftExpr;

	Result->rightExpr = _rightExpr;

	return Result;

}

struct ExpressionList *CreateExpressionList(struct Expression *_expr) {
	struct ExpressionList *Result = (struct ExpressionList *)malloc(sizeof(struct ExpressionList));

	Result->nextExpr = NULL;
	Result->expr = _expr;

	return Result;

}

struct ExpressionList *AppendToExpressionList(struct ExpressionList *_exprList, struct Expression *_expr) {
	struct ExpressionList *Result = (struct ExpressionList *)malloc(sizeof(struct ExpressionList));

	Result->nextExpr = NULL;
	_exprList->nextExpr = Result;
	Result->expr = _expr;

	return Result;
}

struct Statement *CreateStmtFromSimpleStmt(enum StatementType _stmtType, struct SimpleStmt *_simpleStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->simpleStmt = _simpleStmt;

	return Result;
}

struct Statement *CreateVarDeclStmt(enum StatementType _stmtType, struct VarDecl *_varDecl) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->varDecl = _varDecl;

	return Result;
}

struct Statement *CreateConstDeclStmt(enum StatementType _stmtType, struct ConstDecl *_constDecl) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;

	Result->constDecl = _constDecl;

	return Result;
}

struct Statement *CreateStmtFromReturnStmt(enum StatementType _stmtType, struct ReturnStmt *_returnStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->returnStmt = _returnStmt;

	return Result;
}

struct Statement *CreateStatement(enum StatementType _stmtType) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;

	return Result;
}

struct Statement *CreateStmtFromBlock(enum StatementType _stmtType, struct Block *_block) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->block = _block;

	return Result;
}

struct Statement *CreateStmtFromIfStmt(enum StatementType _stmtType, struct IfStmt *_ifStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->ifStmt = _ifStmt;

	return Result;
}

struct Statement *CreateStmtFromSwitchStmt(enum StatementType _stmtType, struct SwitchStmt *_switchStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->switchStmt = _switchStmt;

	return Result;
}

struct Statement *CreateStmtFromForStmt(enum StatementType _stmtType, struct ForStmt *_forStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));

	Result->stmtType = _stmtType;
	Result->forStmt = _forStmt;

	return Result;
}

struct IdentifierList *CreateIdList(char *_id) {
	struct IdentifierList *Result = (struct IdentifierList *)malloc(sizeof(struct IdentifierList));

	Result->nextIdentifier = NULL;
	Result->identifier = _id;

	return Result;
}

struct IdentifierList *AppendToIdList(struct IdentifierList *_idList, char *_id) {
	struct IdentifierList *Result = (struct IdentifierList *)malloc(sizeof(struct IdentifierList));

	Result->nextIdentifier = NULL;
	_idList->nextIdentifier = Result;
	Result->identifier = _id;

	return Result;
}

struct ReturnStmt *CreateReturnStatement(struct ExpressionList *_exprList) {
	struct ReturnStmt *Result = (struct ReturnStmt *)malloc(sizeof(struct ReturnStmt));

	Result->exprList = _exprList;

	return Result;
}

struct IfStmt *CreateIfStatement(struct IfStmtExpression *_ifStmtExpr, struct Block *_block) {
	struct IfStmt *Result = (struct IfStmt *)malloc(sizeof(struct IfStmt));

	Result->ifStmtExpr = _ifStmtExpr;
	Result->block = _block;

	return Result;
}

struct IfStmt *CreateIfElseStatement(struct IfStmtExpression *_ifStmtExpr, struct Block *_block, struct ElseBlock *_elseBlock) {
	struct IfStmt *Result = (struct IfStmt *)malloc(sizeof(struct IfStmt));

	Result->ifStmtExpr = _ifStmtExpr;
	Result->elseBlock = _elseBlock;
	Result->block = _block;

	return Result;
}

struct IfStmtExpression *CreateIfStmtExpression(struct Expression *_expr) {
	struct IfStmtExpression *Result = (struct IfStmtExpression *)malloc(sizeof(struct IfStmtExpression));

	Result->expr = _expr;

	return Result;
}

struct IfStmtExpression *CreateCompositeIfStmtExpression(struct SimpleStmt *_simpleStmt, struct Expression *_expr) {
	struct IfStmtExpression *Result = (struct IfStmtExpression *)malloc(sizeof(struct IfStmtExpression));

	Result->simpleStmt = _simpleStmt;
	Result->expr = _expr;

	return Result;
}

struct ElseBlock *CreateElseBlockFromIfStmt(struct IfStmt *_ifStmt) {
	struct ElseBlock *Result = (struct ElseBlock *)malloc(sizeof(struct ElseBlock));
	Result->ifStmt = _ifStmt;

	return Result;
}

struct ElseBlock *CreateElseBlockFromBlock(struct Block *_block) {
	struct ElseBlock *Result = (struct ElseBlock *)malloc(sizeof(struct ElseBlock));

	Result->block = _block;

	return Result;
}

struct Block *CreateBlock( struct StatementList *_stmtList) {
	struct Block *Result = (struct Block *)malloc(sizeof(struct Block));

	Result->stmtList = _stmtList;

	return Result;

}

struct StatementList *CreateStmtList(struct Statement *_stmt) {
	struct StatementList *Result = (struct StatementList *)malloc(sizeof(struct StatementList));

	Result->nextStmt = NULL;
	Result->stmt = _stmt;

	return Result;
}

struct StatementList *AppendToStmtList(struct StatementList *_stmtList, struct Statement *_stmt) {
	struct StatementList *Result = (struct StatementList *)malloc(sizeof(struct StatementList));

	Result->nextStmt = NULL;
	_stmtList->nextStmt = Result;
	Result->stmt = _stmt;

	return Result;
}

struct SwitchStmt * CreateSwitchStatement(struct  SwitchInitialAndExpression * _initialAndExpression, struct SwitchBody * _switchBody) {
	struct SwitchStmt * Result = (struct SwitchStmt*) malloc(sizeof (struct SwitchStmt));

	Result->initialAndExpression = _initialAndExpression; 
	Result->switchBody = _switchBody; 
	return Result ; 
}

struct SwitchInitialAndExpression *CreateSwitchInitialAndExpression(enum SwitchInitialExpressionType _type,
	struct SimpleStmt *_initialStmt, struct Expression * _expression) {
	struct SwitchInitialAndExpression *Result = 
		(struct SwitchInitialAndExpression*) malloc(sizeof(struct SwitchInitialAndExpression));
	Result->switchType = _type; 
	Result->expression = _expression; 
	Result->initialStmt = _initialStmt; 
}

struct SwitchBody *CreateSwitchBody(struct ExpressionCaseClauseList *_eccl) {
	struct SwitchBody *Result = (struct SwitchBody *)malloc(sizeof(struct SwitchBody));

	Result->eccl = _eccl;

	return Result;
}

struct ExpressionCaseClauseList *CreateExpressionCaseClauseList(struct ExpressionCaseClause *_exprCaseClause) {
	struct ExpressionCaseClauseList *Result = (struct ExpressionCaseClauseList *)malloc(sizeof(struct ExpressionCaseClauseList));

	Result->nextExprCaseClause = NULL;
	Result->exprCaseClause = _exprCaseClause;

	return Result;
}

struct ExpressionCaseClauseList *AppendToExpressionCaseClauseList(struct ExpressionCaseClauseList *_eccl, struct ExpressionCaseClause *_exprCaseClause) {
	struct ExpressionCaseClauseList *Result = (struct ExpressionCaseClauseList *)malloc(sizeof(struct ExpressionCaseClauseList));

	Result->nextExprCaseClause = NULL;
	Result->exprCaseClause = _exprCaseClause;

	return Result;
}

struct ExpressionCaseClause *CreateExpressionCaseClause(struct ExpressionSwitchCase *_expreSwitchCase, struct StatementList *_stmtList) {
	struct ExpressionCaseClause *Result = (struct ExpressionCaseClause *)malloc(sizeof(struct ExpressionCaseClause));

	Result->expreSwitchCase = _expreSwitchCase;
	Result->stmtList = _stmtList;

	return Result;

}

struct ExpressionSwitchCase *CreateExprSwitchCase(struct ExpressionList *_exprList) {
	struct ExpressionSwitchCase *Result = (struct ExpressionSwitchCase *)malloc(sizeof(struct ExpressionSwitchCase));

	Result->exprList = _exprList;

	return Result;
}

struct SimpleStmt *CreateSimpleStmt(enum StatementType _stmtType, struct Expression *_expr) {
	struct SimpleStmt *Result = (struct SimpleStmt *)malloc(sizeof(struct SimpleStmt));

	Result->stmtType = _stmtType;
	Result->expr = _expr;

	return Result;

}

struct SimpleStmt *CreatAssignSimpleStmt(enum StatementType _stmtType, struct ExpressionList *_exprListLeft, struct ExpressionList *_exprListRight) {
	struct SimpleStmt *Result = (struct SimpleStmt *)malloc(sizeof(struct SimpleStmt));
	
	Result->stmtType = _stmtType;

	Result->exprListLeft = _exprListLeft;
	Result->exprListRight = _exprListRight;

	return Result;
}

struct ForStmt *CreateForStmt(struct Block *_block) {
	struct ForStmt *Result = (struct ForStmt *)malloc(sizeof(struct ForStmt));

	Result->block = _block;

	return Result;
}

struct ForStmt *CreateForStmtWExpr(struct Expression *_expr, struct Block *_block) {
	struct ForStmt *Result = (struct ForStmt *)malloc(sizeof(struct ForStmt));

	Result->expr = _expr;

	Result->block = _block;

	return Result;

}

struct ForStmt *CreateForStmtWClause(struct ForClause *_forClause, struct Block *_block) {
	struct ForStmt *Result = (struct ForStmt *)malloc(sizeof(struct ForStmt));

	Result->forClause = _forClause;

	Result->block = _block;

	return Result;
}

struct ForClause *CreateForClause(struct SimpleStatement *_simpleStmtLeft, struct Expression *_expr, struct SimpleStatement *_simpleStmtRight) {
	struct ForClause *Result = (struct ForClause *)malloc(sizeof(struct ForClause));

	Result->simpleStmtLeft = _simpleStmtLeft;
	Result->expr = _expr;
	Result->simpleStmtRight = _simpleStmtRight;

	return Result;
}

struct ForInitStmt * CreateForInitStmt(struct SimpleStmt * _initStmt) {
	struct ForInitStmt * Result = (struct ForInitStmt*)malloc(sizeof (struct ForInitStmt));
	Result->initStmt = _initStmt; 
	
	return Result; 
}

struct ForCondition * CreateForCondition(struct Expression * _expression) {
	struct ForCondition * Result = (struct ForCondition*) malloc(sizeof (struct ForCondition));
	Result->expression = _expression; 

	return Result; 
}

struct ForPostStmt * CreateForPostStmt(struct  SimpleStmt * _postStmt) {
	struct ForPostStmt * Result = (struct ForPostStmt*) malloc(sizeof(struct ForPostStmt));
	Result->postStmt = _postStmt; 

	return Result; 
	
}


struct FunctionDecl *CreateFunctionDeclaration(char *_identifier, struct Signature *_signature) {
	struct FunctionDecl *Result = (struct FunctionDecl *)malloc(sizeof(struct FunctionDecl));

	Result->identifier = _identifier;
	Result->signature = _signature;

	return Result;
}

struct FunctionDecl *CreateFunctionDeclarationWithBlock(char *_identifier, struct Signature *_signature, struct Block *_block) {
	struct FunctionDecl *Result = (struct FunctionDecl *)malloc(sizeof(struct FunctionDecl));
	
	Result->identifier = _identifier;
	Result->signature = _signature;
	Result->block = _block;

	return Result;	
}

struct Signature *CreateSignature(struct ParamInParen *_paramInParen) {
	struct Signature *Result = (struct Signature *)malloc(sizeof(struct Signature));

	Result->paramInParen = _paramInParen;

	return Result;

}

struct Signature *CreateSignatureWithResult(struct ParamInParen *_paramInParen, struct Result *_result) {
	struct Signature *Result = (struct Signature *)malloc(sizeof(struct Signature));

	Result->paramInParen = _paramInParen;
	Result->result = _result;

	return Result;
}

struct ParamInParen *CreateParametersInParens(struct ParameterList *_paramList) {
	struct ParamInParen *Result = (struct ParamInParen *)malloc(sizeof(struct ParamInParen));

	Result->paramList = _paramList;

	return Result;
}

struct ParameterList *CreateParameterDeclareList(struct ParameterDeclare *_paramDecl) {
	struct ParameterList *Result = (struct ParameterList *)malloc(sizeof(struct ParameterList));
	Result->nextParamDecl = NULL;
	Result->paramDecl = _paramDecl;

	return Result;
}

struct ParameterList *AppendToParameterDeclareList(struct ParameterList *_paramDeclList, struct ParameterDeclare *_paramDecl) {
	struct ParameterList *Result = (struct ParameterList *)malloc(sizeof(struct ParameterList));

	Result->nextParamDecl = NULL;
	_paramDeclList->nextParamDecl = Result;
	Result->paramDecl = _paramDecl;

	return Result;
}

struct ParameterDeclare *CreateParameterDeclareWithoutId(struct Type *_type) {
	struct ParameterDeclare *Result = (struct ParameterDeclare *)malloc(sizeof(struct ParameterDeclare));

	Result->type = _type;

	return Result;
}

struct ParameterDeclare *CreateParameterDeclareWithId(char* _identifier, struct Type *_type) {
	struct ParameterDeclare *Result = (struct ParameterDeclare *)malloc(sizeof(struct ParameterDeclare));

	Result->identifier = _identifier;
	Result->type = _type;

	return Result;
}

struct Result *CreateResultFromParameters(struct ParamInParen *_paramInParen) {
	struct Result *Res = (struct Result *)malloc(sizeof(struct Result));

	Res->paramInParen = _paramInParen;

	return Res;
}

struct Result *CreateResultFormType(struct Type *_type) {
	struct Result *Res = (struct Result *)malloc(sizeof(struct Result));

	Res->type = _type;

	return Res;
}


struct PrintStatement * CreatePrintStmt(struct ExpressionList * _expressionList) {
	struct PrintStatement * Result = (struct PrintStatement*) malloc(sizeof(struct PrintStatement));
	Result->expressionList = _expressionList; 
	
	return Result; 
}
struct ScanStatement * CreateScanStmt(struct ScanIdentifierList* _scanIdentifierList) {
	struct ScanStatement * Result = (struct ScanStatement*) malloc(sizeof (struct ScanStatement));
	Result->scanIdentifierList = _scanIdentifierList; 

	return Result; 

}