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
	int idNum; 
};

struct Program {
	struct DeclarationList *declList;
};

struct DeclarationList {
	struct Declaration *firstDecl;
	struct Declaration *lastDecl;
	int size; 
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
	int size; 
};

struct ConstDecl {
	struct ConstSpec *constSpec;
	struct ConstSpecList *constSpecList;
};

struct ConstSpec {
	struct IdentifierListType *idListType;
	struct IdentifierList *idList;
	struct ExpressionList *exprList;
	struct ConstSpec*  nextConstSpec;
};

struct ConstSpecList {
	struct ConstSpec *firstConstSpec;
	struct ConstSpec *lastConstSpec;
	int size;
};

struct FunctionDecl {
	char *identifier;
	struct Signature *signature;
	struct Block *block;
};

struct IdentifierList {
	struct Identifier* firstId;  
	struct Identifier* lastId; 
	int size; 
};

struct IdentifierListType {
	struct Type *type;
	struct IdentifierList *identifierList;
};

struct ExpressionList {
	struct Expression *firstExpression;
	struct Expression *lastExpression;
	int size; 
};

enum TypeNames {
	IDENTIFIER_TYPE_NAME,
	FLOAT32_TYPE_NAME,
	INT_TYPE_NAME,
	STRING_TYPE_NAME,
	BOOL_TYPE_NAME, 
	VOID_TYPE_NAME, 
	UNKNOWN_TYPE
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

struct Expression {
	enum ExpressionType exprType;
	struct PrimaryExpression *primaryExpr;
	struct Expression *leftExpr;
	struct Expression *rightExpr;
	struct Expression* nextExpr;
	struct SemanticType* semanticType;
};

enum ArrayType {
	NONE_ARRAY, 
	ARRAY
};

struct SemanticType {
	enum TypeNames typeName;
	int idNum; //index of variable in local variable table or in fields table
	enum ArrayType arrayType;
	int arraySize; 
	int constantExpressionNum; //index of constant types integer, float, string in constants table
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
	struct SemanticType* semanticType; 
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
	enum StatementType stmtType;
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
	struct BreakStmt* breakStmt;
	struct ContinueStmt* continueStmt; 
};

struct BreakStmt{
	int gotoPosition; 
};

struct ContinueStmt {
	int gotoPosition; 
};

struct StatementList {
	struct Statement *firstStmt;
	struct Statement *lastStmt;
	int size;
};

struct SimpleStmt {
	enum StatementType stmtType;
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

enum SwitchInitialExpressionType {
	ALWAYS_TRUE,
	WITH_INITIAL_STMT,
	WITH_EXPRESSION,
	WITH_INITIAL_AND_EXPRESSION
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
	int caseCount; 
	int defaultCount; 
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
	int size;
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