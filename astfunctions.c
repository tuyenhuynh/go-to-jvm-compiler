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
	if (_imports == NULL) {
		_imports = (struct Imports*) malloc(sizeof(struct Imports)); 
		_imports->firstImport = _import; 
		_imports->lastImport = _import; 
	}
	else {
		//_imports->lastImport->nextImport = _import; 
		//_imports->lastImport = _import; 
	}
	return _imports; 
}

struct StringNode* CreateStringNode(char* _string) {
	struct StringNode * Result = (struct StringNode*) malloc(sizeof(struct StringNode));
	Result->string = _string; 
	Result->nextString = NULL; 

	return Result; 
}

struct StringList* CreateStringList(char* _string) {
	struct StringList* Result = (struct StringList*) malloc(sizeof(struct StringList));
	struct StringNode* node = CreateStringNode(_string); 
	Result->firstNode = node; 
	Result->lastNode = node; 
	return Result;

}

struct StringList* AppendToStringList(struct StringList* _strList, char* _string) {
	struct StringNode* node = CreateStringNode(_string);
	if (_strList == NULL) {
		_strList = (struct StringList*) malloc(sizeof(struct StringList)); 
		_strList->firstNode = node; 
		_strList->lastNode = node; 
	}
	else {
		_strList->lastNode->nextString = node; 
		_strList->lastNode = node; 
	}
	return _strList; 
}

struct Import *CreateImportFromLib(char *_libName) {
	struct Import *Result = (struct Import *)malloc(sizeof(struct Import));
	Result->lib = CreateStringNode(_libName); 
	Result->libList = NULL; 
	Result->nextImport = NULL;

	return Result;
}

struct Import *CreateImportFromLibList(struct StringList *libList) {
	struct Import *Result = (struct Import *)malloc(sizeof(struct Import));

	Result->libList = libList;
	Result->lib = NULL;
	Result->nextImport = NULL; 

	return Result;
}


struct DeclarationList *CreateDeclarationList(struct Declaration *_decl) {
	struct DeclarationList *Result = (struct DeclarationList *)malloc(sizeof(struct DeclarationList));
	Result->firstDecl = _decl;
	Result->lastDecl = _decl;
	return Result;
}

struct DeclarationList *AppendToDeclarationList(struct DeclarationList *_declList, struct Declaration *_decl) {
	if (_declList == NULL) {
		_declList = (struct DeclarationList*)malloc(sizeof(struct DeclarationList)); 
		_declList->firstDecl = _decl; 
		_declList->lastDecl = _decl; 
	}
	else {
		_declList->lastDecl->nextDecl = _decl;
		_declList->lastDecl = _decl;
	}
	return _declList; 
}

struct Declaration *CreateDeclarationFromVarDecl(enum DeclType _declType, struct VarDecl *_varDecl) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	Result->declType = _declType;
	Result->varDecl = _varDecl;

	Result->constDecl = NULL;
	Result->funcDecl = NULL;

	Result->nextDecl = NULL; 

	return Result;
}

struct Declaration *CreateDeclarationFromConstDecl(enum DeclType _declType, struct ConstDecl *_constDecl) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	Result->declType = _declType;
	Result->constDecl = _constDecl;
	
	Result->funcDecl = NULL;
	Result->varDecl = NULL;

	Result->nextDecl = NULL;
	return Result;
}

struct Declaration *CreateDeclarationFromFuncDecl(enum DeclType _declType, struct FunctionDecl *_funcDecl) {
	struct Declaration *Result = (struct Declaration *)malloc(sizeof(struct Declaration));
	Result->declType = _declType;
	Result->funcDecl = _funcDecl;

	Result->constDecl = NULL;
	Result->varDecl = NULL;
	Result->nextDecl = NULL; 
	return Result;
}

struct ConstDecl *CreateConstDecl(struct VarSpec *_varSpec) {
	struct ConstDecl *Result = (struct ConstDecl *)malloc(sizeof(struct ConstDecl));

	Result->varSpec = _varSpec;
	Result->varSpecList = NULL;
	return Result;

}

struct ConstDecl *CreateConstDeclFromList(struct VarSpecList *_varSpecList) {
	struct ConstDecl *Result = (struct ConstDecl *)malloc(sizeof(struct ConstDecl));

	Result->varSpecList = _varSpecList;

	Result->varSpec = NULL; 
	return Result;

}

struct Type *CreateTypeFromTypeName(enum TypeNames _typeName) {
	struct Type *Result = (struct Type *)malloc(sizeof(struct Type));
	Result->typeName = _typeName;

	Result->expr = NULL;
	return Result;
}

struct Type *CreateCompositeType(struct Expression *_expr, enum TypeNames _typeName) {
	struct Type *Result = (struct Type *)malloc(sizeof(struct Type));

	Result->typeName = _typeName;
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
	Result->varSpecList = NULL;

	return Result;

}

struct VarDecl *CreateCompositeVarDecl(struct VarSpecList *_varSpecList) {
	struct VarDecl *Result = (struct VarDecl *)malloc(sizeof(struct VarDecl));

	Result->varSpecList = _varSpecList;
	Result->varSpec = NULL;
	return Result;
}

struct VarSpec *CreateSimpleVarSpecWType(struct IdentifierListType *_idListType) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idListType = _idListType;
	Result->exprList = NULL;
	Result->idList = NULL;

	Result->exprList = NULL; 
 
	Result->nextVarSpec = NULL; 

	return Result;
}

struct VarSpec *CreateCompositeVarSpecWtype(struct IdentifierListType *_idListType, struct ExpressionList *_exprList) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idListType = _idListType;
	Result->exprList = _exprList;
	Result->idList = NULL;
	Result->nextVarSpec = NULL; 

	return Result;
}

struct VarSpec *CreateCompositeVarSpecWOType(struct IdentifierList *_idList, struct ExpressionList *_exprList) {
	struct VarSpec *Result = (struct VarSpec *)malloc(sizeof(struct VarSpec));

	Result->idList = _idList;

	Result->idListType = NULL;

	Result->exprList = _exprList;

	Result->nextVarSpec = NULL; 

	return Result;
}

struct VarSpecList *CreateVarSpecList(struct VarSpec *_varSpec) {
	struct VarSpecList *Result = (struct VarSpecList *)malloc(sizeof(struct VarSpecList));

	Result->firstVarSpec = _varSpec;
	Result->lastVarSpec = _varSpec;

	return Result;
}

struct VarSpecList *AppendToVarSpecList(struct VarSpecList *_varSpecList, struct VarSpec *_varSpec) {
	if (_varSpecList == NULL) {
		_varSpecList = (struct VarSpecList*)malloc(sizeof(struct VarSpecList));
		_varSpecList->firstVarSpec = _varSpec; 
		_varSpecList->lastVarSpec = _varSpec; 
	}
	else {
		_varSpecList->lastVarSpec->nextVarSpec = _varSpec;
		_varSpecList->lastVarSpec = _varSpec;
	}
	
	return _varSpecList;
}

struct PrimaryExpression *CreateBoolExpr(enum ExpressionType _exprType, int _boolValue) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->boolValue = _boolValue;

	Result->expr = NULL;
	Result->funcCall = NULL;
	Result->identifier = NULL;
	Result->primaryExpr = NULL;
	Result->stringLiteral = NULL;

	return Result;
}


struct PrimaryExpression *CreateDecimalExpression(enum ExpressionType _exprType, int _decNumber) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->decNumber = _decNumber;

	Result->expr = NULL;
	Result->funcCall = NULL;
	Result->identifier = NULL;
	Result->primaryExpr = NULL;
	Result->stringLiteral = NULL;

	return Result;
}

struct PrimaryExpression *CreateFloatExpression(enum ExpressionType _exprType, float _floatNumber) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->floatNumber = _floatNumber;

	Result->expr = NULL;
	Result->funcCall = NULL;
	Result->identifier = NULL;
	Result->primaryExpr = NULL;
	Result->stringLiteral = NULL;

	return Result;
}

struct PrimaryExpression *CreateStringExpression(enum ExpressionType _exprType, char* _stringLiteral) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->stringLiteral = _stringLiteral;

	Result->expr = NULL;
	Result->funcCall = NULL;
	Result->identifier = NULL;
	Result->primaryExpr = NULL;

return Result;
}

struct PrimaryExpression *CreateIdExpression(enum ExpressionType _exprType, char* _identifier) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->identifier = _identifier;

	Result->expr = NULL;
	Result->funcCall = NULL;
	Result->primaryExpr = NULL;
	Result->stringLiteral = NULL;

	return Result;
}

struct PrimaryExpression *CreateCompositePrimaryExpression(enum ExpressionType _exprType, struct PrimaryExpression *_primaryExpr, struct Expression *_expr) {
	struct PrimaryExpression *Result = (struct PrimaryExpression *)malloc(sizeof(struct PrimaryExpression));

	Result->exprType = _exprType;

	Result->primaryExpr = _primaryExpr;

	Result->expr = _expr;

	Result->funcCall = NULL;
	Result->identifier = NULL;
	Result->stringLiteral = NULL;

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

	Result->funcCall = NULL;
	Result->identifier = NULL;
	Result->primaryExpr = NULL;
	Result->stringLiteral = NULL;

	return Result;
}

struct FunctionCall *CreateEmptyFunctionCall(struct PrimaryExpression *_primaryExpr) {
	struct FunctionCall *Result = (struct FunctionCall *)malloc(sizeof(struct FunctionCall));

	Result->primaryExpr = _primaryExpr;

	Result->exprList = NULL;
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

	Result->leftExpr = NULL;
	Result->rightExpr = NULL;
	Result->nextExpr = NULL; 

	return Result;
}

struct Expression *CreateBinaryExpression(enum ExpressionType _exprType, struct Expression *_leftExpr, struct Expression *_rightExpr) {
	struct Expression *Result = (struct Expression *)malloc(sizeof(struct Expression));

	Result->exprType = _exprType;

	Result->leftExpr = _leftExpr;

	Result->rightExpr = _rightExpr;

	Result->primaryExpr = NULL;
	Result->nextExpr = NULL; 
	return Result;

}

struct ExpressionList *CreateExpressionList(struct Expression *_expr) {
	struct ExpressionList *Result = (struct ExpressionList *)malloc(sizeof(struct ExpressionList));

	Result->firstExpression = _expr;
	Result->lastExpression = _expr;

	return Result;

}

struct ExpressionList *AppendToExpressionList(struct ExpressionList *_exprList, struct Expression *_expr) {
	if (_exprList == NULL) {
		_exprList = (struct ExpressionList*) malloc(sizeof(struct ExpressionList)); 
		_exprList->firstExpression = _expr; 
		_exprList->lastExpression = _expr; 
	}
	else {
		_exprList->lastExpression->nextExpr = _expr;
		_exprList->lastExpression = _expr;
	}
	return _exprList; 
}

void clearStatement(struct Statement* stmt) {
	if (stmt != NULL) {
		stmt->block = NULL; 
		stmt->constDecl = NULL; 
		stmt->forStmt = NULL; 
		stmt->ifStmt = NULL; 
		stmt->nextStatement = NULL; 
		stmt->printStatement = NULL; 
		stmt->returnStmt = NULL; 
		stmt->scanStatement = NULL; 
		stmt->simpleStmt = NULL; 
		stmt->switchStmt = NULL; 
		stmt->varDecl = NULL;
	}
}
struct Statement *CreateStmtFromSimpleStmt(enum StatementType _stmtType, struct SimpleStmt *_simpleStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->simpleStmt = _simpleStmt;
	return Result;
}

struct Statement *CreateVarDeclStmt(enum StatementType _stmtType, struct VarDecl *_varDecl) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->varDecl = _varDecl; 
	return Result;
}

struct Statement *CreateConstDeclStmt(enum StatementType _stmtType, struct ConstDecl *_constDecl) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result);
	Result->stmtType = _stmtType;
	Result->constDecl = _constDecl;
	return Result;
}

struct Statement *CreateStmtFromReturnStmt(enum StatementType _stmtType, struct ReturnStmt *_returnStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->returnStmt = _returnStmt;
	return Result;
}

//????
struct Statement *CreateStatement(enum StatementType _stmtType) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType; 
	return Result;
}

struct Statement *CreateStmtFromBlock(enum StatementType _stmtType, struct Block *_block) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->block = _block;
	return Result;
}

struct Statement *CreateStmtFromIfStmt(enum StatementType _stmtType, struct IfStmt *_ifStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->ifStmt = _ifStmt;
	return Result;
}

struct Statement *CreateStmtFromSwitchStmt(enum StatementType _stmtType, struct SwitchStmt *_switchStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->switchStmt = _switchStmt;
	return Result;
}

struct Statement *CreateStmtFromForStmt(enum StatementType _stmtType, struct ForStmt *_forStmt) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result);
	Result->stmtType = _stmtType;
	Result->forStmt = _forStmt;
	return Result;
}

struct Statement *CreateStmtFromPrinStmt(enum StatementType _stmtType, struct PrintStatement *_printStatement) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->printStatement = _printStatement;
	return Result;
}

struct Statement *CreateStmtFromScanStmt(enum StatementType _stmtType, struct ScanStatement *_scanStatement) {
	struct Statement *Result = (struct Statement *)malloc(sizeof(struct Statement));
	clearStatement(Result); 
	Result->stmtType = _stmtType;
	Result->scanStatement = _scanStatement;	
	return Result;
}

struct IdentifierList *CreateIdList(char *_idName) {
	struct IdentifierList *Result = (struct IdentifierList *)malloc(sizeof(struct IdentifierList));
	struct Identifier* id = CreateIdentifier(_idName); 
	Result->firstId = id;
	Result->lastId = id;
	return Result;
}

struct Identifier* CreateIdentifier(char* _idName) {
	struct Identifier* Result = (struct Identifier*) malloc(sizeof(struct Identifier));
	Result->name = _idName; 
	Result->nextId = NULL;
	return Result; 
}

struct IdentifierList *AppendToIdList(struct IdentifierList *_idList, char *_idName) {
	struct Identifier* id = CreateIdentifier(_idName); 
	if (_idList == NULL) {
		_idList = (struct IdentifierList*) malloc(sizeof(struct IdentifierList)); 
		_idList->firstId = id; 
		_idList->lastId = id; 
	}
	else {
		_idList->lastId->nextId = id; 
		_idList->lastId = id; 
	}
	return _idList;
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
	Result->elseBlock = NULL;
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
	Result->simpleStmt = NULL;

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
	Result->block = NULL;

	return Result;
}

struct ElseBlock *CreateElseBlockFromBlock(struct Block *_block) {
	struct ElseBlock *Result = (struct ElseBlock *)malloc(sizeof(struct ElseBlock));

	Result->block = _block;
	Result->ifStmt = NULL;

	return Result;
}

struct Block *CreateBlock( struct StatementList *_stmtList) {
	struct Block *Result = (struct Block *)malloc(sizeof(struct Block));

	Result->stmtList = _stmtList;

	return Result;

}

struct StatementList *CreateStmtList(struct Statement *_stmt) {
	struct StatementList *Result = (struct StatementList *)malloc(sizeof(struct StatementList));

	Result->firstStmt = _stmt;
	Result->lastStmt = _stmt;

	return Result;
}

struct StatementList *AppendToStmtList(struct StatementList *_stmtList, struct Statement *_stmt) {
	if (_stmtList == NULL) {
		_stmtList = (struct StatementList *)malloc(sizeof(struct StatementList));
		_stmtList->firstStmt = _stmt; 
		_stmtList->lastStmt = _stmt; 
	}
	else {
		_stmtList->lastStmt->nextStatement = _stmt; 
		_stmtList->lastStmt = _stmt; 
	}
	return _stmtList;
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

	return Result;
}

struct SwitchBody *CreateSwitchBody(struct ExpressionCaseClauseList *_eccl) {
	struct SwitchBody *Result = (struct SwitchBody *)malloc(sizeof(struct SwitchBody));
	Result->eccl = _eccl;
	return Result;
}

struct ExpressionCaseClauseList *CreateExpressionCaseClauseList(struct ExpressionCaseClause *_exprCaseClause) {
	struct ExpressionCaseClauseList *Result = (struct ExpressionCaseClauseList *)malloc(sizeof(struct ExpressionCaseClauseList));
	Result->firstExprCaseClause = _exprCaseClause;
	Result->lastExprCaseClause = _exprCaseClause;
	return Result;
}

struct ExpressionCaseClauseList *AppendToExpressionCaseClauseList(struct ExpressionCaseClauseList *_eccl, struct ExpressionCaseClause *_exprCaseClause) {
	if (_eccl == NULL) {
		_eccl = (struct ExpressionCaseClauseList *)malloc(sizeof(struct ExpressionCaseClauseList));
		_eccl->firstExprCaseClause = _exprCaseClause; 
		_eccl->lastExprCaseClause = _exprCaseClause; 
	}
	else {
		_eccl->lastExprCaseClause->nextExprCaseClause = _exprCaseClause; 
		_eccl->lastExprCaseClause = _exprCaseClause; 
	}
	return _eccl; 
}

struct ExpressionCaseClause *CreateExpressionCaseClause(struct ExpressionSwitchCase *_expreSwitchCase, struct StatementList *_stmtList) {
	struct ExpressionCaseClause *Result = (struct ExpressionCaseClause *)malloc(sizeof(struct ExpressionCaseClause));
	Result->expreSwitchCase = _expreSwitchCase;
	Result->stmtList = _stmtList;
	Result->nextExprCaseClause = NULL; 
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

	Result->exprListLeft = NULL;
	Result->exprListRight = NULL;

	return Result;

}

struct SimpleStmt *CreatAssignSimpleStmt(enum StatementType _stmtType, struct ExpressionList *_exprListLeft, struct ExpressionList *_exprListRight) {
	struct SimpleStmt *Result = (struct SimpleStmt *)malloc(sizeof(struct SimpleStmt));
	
	Result->stmtType = _stmtType;
	Result->exprListLeft = _exprListLeft;
	Result->exprListRight = _exprListRight;
	Result->expr = NULL;
	
	return Result;
}

struct ForStmt *CreateForStmt(struct Block *_block) {
	struct ForStmt *Result = (struct ForStmt *)malloc(sizeof(struct ForStmt));
	Result->block = _block;
	Result->expr = NULL; 
	Result->forClause = NULL; 

	return Result;
}

struct ForStmt *CreateForStmtWExpr(struct Expression *_expr, struct Block *_block) {
	struct ForStmt *Result = (struct ForStmt *)malloc(sizeof(struct ForStmt));

	Result->expr = _expr;
	Result->block = _block;
	Result->forClause = NULL; 

	return Result;
}

struct ForStmt *CreateForStmtWClause(struct ForClause *_forClause, struct Block *_block) {
	struct ForStmt *Result = (struct ForStmt *)malloc(sizeof(struct ForStmt));

	Result->forClause = _forClause;
	Result->block = _block;

	Result->expr = NULL; 
	return Result;
}

struct ForClause *CreateForClause(struct ForInitStmt *_forInitStmt, struct ForCondition *_forCondition, struct ForPostStmt *_forPostStmt) {
	struct ForClause *Result = (struct ForClause *)malloc(sizeof(struct ForClause));

	Result->forInitStmt = _forInitStmt;
	Result->forCondition = _forCondition;
	Result->forPostStmt = _forPostStmt;

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
	Result->block = NULL; 

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
	Result->result = NULL;
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
	Result->firstParamDecl = _paramDecl;
	Result->lastParamDecl = _paramDecl;

	return Result;
}

struct ParameterList *AppendToParameterDeclareList(struct ParameterList *_paramDeclList, struct ParameterDeclare *_paramDecl) {
	if (_paramDeclList == NULL) {
		_paramDeclList = (struct ParameterList *)malloc(sizeof(struct ParameterList));
		_paramDeclList->firstParamDecl = _paramDecl;
		_paramDeclList->lastParamDecl = _paramDecl; 
	}
	else {
		_paramDeclList->lastParamDecl->nextParamDecl = _paramDecl; 
		_paramDeclList->lastParamDecl = _paramDecl; 
	}
	return _paramDeclList; 
}

struct ParameterDeclare *CreateParameterDeclareWithoutId(struct Type *_type) {
	struct ParameterDeclare *Result = (struct ParameterDeclare *)malloc(sizeof(struct ParameterDeclare));

	Result->type = _type;
	Result->identifier = NULL; 
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
	Res->type = NULL; 

	return Res;
}

struct Result *CreateResultFromType(struct Type *_type) {
	struct Result *Res = (struct Result *)malloc(sizeof(struct Result));

	Res->type = _type;
	Res->paramInParen = NULL; 
	return Res;
}


struct PrintStatement * CreatePrintStmt(struct ExpressionList * _expressionList) {
	struct PrintStatement * Result = (struct PrintStatement*) malloc(sizeof(struct PrintStatement));
	Result->expressionList = _expressionList; 
	
	return Result; 
}

struct ScanStatement * CreateScanStmt(struct IdentifierList* _identifierList) {
	struct ScanStatement * Result = (struct ScanStatement*) malloc(sizeof (struct ScanStatement));
	Result->identifierList = _identifierList; 
	
	return Result; 

}
