#ifndef _TREES_H_
#define _TREES_H_

struct Tree {
	struct Program* program; 
};

struct StringNode {
	char* string; 
	struct StringNode*  nextString; 
};

struct StringList {
	struct StringNode* firstNode; 
	struct StringNode* lastNode; 
};

struct Identifier {
	char* name; 
	struct Identifier* nextId; 
};

struct Program {
	struct Package *pkg;
	struct Imports *imports;
	struct DeclarationList *declList;
};

struct Package {
	char *packageName;
};

struct Imports {
	struct Import *firstImport;
	struct Import *lastImport;
};

struct DeclarationList {
	struct Declaration *firstDecl;
	struct Declaration *lastDecl;
};

struct Import {
	struct StringNode* lib; 
	struct StringList* libList; 
	struct Import* nextImport; 
};


enum DeclType {
	CONST_DECL,
	VAR_DECL,
	FUNC_DECL
};

struct Declaration {
	enum DeclType declType;
	struct VarDecl *varDecl;
	struct ConstDecl *constDecl;
	struct FunctionDecl *funcDecl;
	struct Declaration* nextDecl; 
};

struct VarDecl {
	struct VarSpec *varSpec;
	struct VarSpecList *varSpecList;
};

struct VarSpec {
	struct IdentifierListType *idListType;
	struct IdentifierList *idList;
	struct ExpressionList *exprList;
	struct VarSpec*  nextVarSpec; 
};

struct VarSpecList {
	struct VarSpec *firstVarSpec;
	struct VarSpec *lastVarSpec;
};

struct ConstDecl {
	struct VarSpec *varSpec;
	struct VarSpecList *varSpecList;
};

struct FunctionDecl {
	char *identifier;
	struct Signature *signature;
	struct Block *block;
};

struct IdentifierList {
	struct Identifier* firstId;  
	struct Identifier* lastId; 
};

struct IdentifierListType {
	struct Type *type;
	struct IdentifierList *identifierList;
};

struct ExpressionList {
	struct Expression *firstExpression;
	struct Expression *lastExpression;
};

enum TypeNames {
	IDENTIFIER_TYPE_NAME,
	FLOAT32_TYPE_NAME,
	INT_TYPE_NAME,
	STRING_TYPE_NAME,
	BOOL_TYPE_NAME
};

struct Type {
	enum TypeNames typeName;
	struct Expression *expr;
};

enum ExpressionType {
	DECIMAL_EXPR,
	FLOAT_EXPR,
	STRING_EXPR,
	ID_EXPRESSION,
	PE_COMPOSITE,
	FUNCTION_CALL_EMPTY,
	FUNCTION_CALL, 
	NOT_UNARY_EXPR,
	PLUS_UNARY_EXPR,
	MINUS_UNARY_EXPR,
	AND_EXPRESSION,
	OR_EXPRESSION,
	EQU_EXPRESSION,
	NE_EXPRESSION,
	GT_EXPRESSION,
	GTE_EXPRESSION,
	LT_EXPRESSION,
	LTE_EXPRESSION,
	PLUS_EXPRESSION,
	MINUS_EXPRESSION,
	MUL_EXPRESSION,
	DIV_EXPRESSION,
	MOD_EXPRESSION,
	EXPRESSION,
	PRIMARY,
	BOOL_TRUE_EXPRESSION,
	BOOL_FALSE_EXPRESSION
};

enum SwitchInitialExpressionType {
	ALWAYS_TRUE, 
	WITH_INITIAL_STMT, 
	WITH_EXPRESSION,  
	WITH_INITIAL_AND_EXPRESSION
};

struct Expression {
	enum ExpressionType exprType;
	struct PrimaryExpression *primaryExpr;
	struct Expression *leftExpr;
	struct Expression *rightExpr;
	struct Expression* nextExpr; 
};

struct PrimaryExpression
{
	enum ExpressionType exprType;
	int decNumber;
	float floatNumber;
	char* stringLiteral;
	char* identifier;
	int boolValue;
	struct PrimaryExpression *primaryExpr;
	struct Expression *expr;
	struct FunctionCall *funcCall; 
};

struct FunctionCall {
	struct PrimaryExpression *primaryExpr;
	struct ExpressionList *exprList; 
};

enum StatementType {
	SIMPLE_STMT,
	EXPR_SIMPLE_STMT,
	INC_SIMPLE_STMT,
	DEC_SIMPLE_STMT,
	ASSIGN_STMT,
	PLUS_ASSIGN_STMT,
	MINUS_ASSIGN_STMT,
	MUL_ASSIGN_STMT,
	DIV_ASSIGN_STMT,
	VAR_DECL_STMT,
	CONST_DECL_STMT,
	BREAK_STMT,
	CONTINUE_STMT,
	RETURN_STMT,
	IF_STMT,
	IF_ELSE_STMT,
	FOR_STMT,
	BLOCK,
	SWITCH_STMT,
	PRINT_STMT,
	SCAN_STMT
};

struct Statement {
	enum StatemenType stmtType;
	struct SimpleStmt *simpleStmt;
	struct VarDecl *varDecl;
	struct ConstDecl *constDecl;
	struct ReturnStmt *returnStmt;
	struct Block *block;
	struct IfStmt *ifStmt;
	struct SwitchStmt *switchStmt;
	struct ForStmt *forStmt;
	struct ScanStatement *scanStatement;
	struct PrintStatement *printStatement;
	struct Statement* nextStatement; 
};

struct StatementList {
	struct Statement *firstStmt;
	struct Statement *lastStmt;
};

struct SimpleStmt {
	enum StatemenType stmtType;
	struct Expression *expr;
	struct ExpressionList *exprListLeft;
	struct ExpressionList *exprListRight;
};

struct ReturnStmt {
	struct ExpressionList *exprList;
};

struct Block {
	struct StatementList *stmtList;
};

struct IfStmt {
	struct IfStmtExpression *ifStmtExpr;
	struct Block *block;
	struct ElseBlock *elseBlock;
};

struct IfStmtExpression {
	struct Expression *expr;
	struct SimpleStmt *simpleStmt;
};

struct ElseBlock {
	struct IfStmt *ifStmt;
	struct Block *block;
};

struct SwitchStmt {
	struct SwitchInitialAndExpression* initialAndExpression; 
	struct SwitchBody *switchBody;
};

struct SwitchInitialAndExpression {
	enum SwitchInitialExpressionType switchType; 
	struct SimpleStmt *initialStmt; 
	struct Expression *expression; 
};

struct SwitchBody {
	struct ExpressionCaseClauseList *eccl;
};

struct ExpressionCaseClauseList {
	struct ExpressionCaseClause *firstExprCaseClause;
	struct ExpressionCaseClause *lastExprCaseClause;
};

struct ExpressionCaseClause {
	struct ExpressionSwitchCase *expreSwitchCase;
	struct StatementList *stmtList;
	struct ExpressionCaseClause* nextExprCaseClause; 
};

struct ExpressionSwitchCase {
	struct ExpressionList *exprList;
};

struct ForStmt {
	struct Block *block;
	struct Expression *expr;
	struct ForClause *forClause;
};

struct ForClause {
	struct ForInitStmt *forInitStmt;
	struct ForCondition *forCondition;
	struct ForPostStmt *forPostStmt;
};

struct Signature {
	struct ParamInParen *paramInParen;
	struct Result *result;
};

struct ParamInParen {
	struct ParameterList *paramList;
};

struct ParameterList {
	struct ParameterDeclare *firstParamDecl;
	struct ParameterDeclare *lastParamDecl;

};

struct ParameterDeclare {
	struct Type *type;
	char* identifier;
	struct ParameterDeclare* nextParamDecl; 
};

struct Result {
	struct ParamInParen *paramInParen;
	struct Type *type;
};

struct ForInitStmt {
	struct SimpleStmt *initStmt; 
};

struct ForCondition {
	struct Expression *expression;
};

struct ForPostStmt {
	struct SimpleStmt *postStmt; 
};

struct PrintStatement {
	struct ExpressionList * expressionList;
};

struct ScanStatement {
	struct IdentifierList *identifierList;
};

#endif// _TREES_H_