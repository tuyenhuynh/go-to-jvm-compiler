#ifndef _TREE_H_
#define _TREE_H_

enum ExpressionType {
	AND, 
	OR, 
	EQU, 
	NE, 
	GT, 
	GTE,
	LT, 
	LTE, 
	PLUS, 
	MINUS,
	MULTIPLE, 
	DIVIDE, 
	MODULE,  
	STRING, 
	FLOAT_NUMBER, 
	DECIMAL_NUMBER, 
	IDENTIFIER, 
	ARRAY_ACCESS, 
	FUNCTION_CALL, 
	EXPRESSION_IN_PARENTHESES, 
	UNARY_PLUS, 
	UNARY_MINUS, 
	UNARY_NOT,
	UNARY_EXPR,
	BINARY_EXPR
};

enum StatementType {
	SIMPLE_STATEMENT,
	VAR_DECLARE,
	CONST_DECLARE,
	RETURN_STATEMENT,
	BREAK,
	CONTINUE,
	BLOCK,
	IF_STATEMENT,
	SWITCH_STATEMENT,
	FOR_STATEMENT,
	INC_STATEMENT,
	DEC_STATEMENT,
	ASSIGN_STATEMENT
};

enum DeclarationType {
	VAR_DECL,
	CONST_DECL,
	FUNCTION_DECL
};

enum TypeOfAssignOp {
	ASSIGN_OP,
	PLUS_ASSIGN_OP,
	MINUS_ASSIGN_OP,
	MUL_ASSIGN_OP,
	DIV_ASSIGN_OP
};


// root structure for program
struct Program {
	char *packageName;
	struct Imports *imports;
	struct DeclarationList *declarationList;
};

// Structs for import statement
struct Imports {
	struct Import *import;
	struct Imports *nextImport;
};

struct Import {
	char *importStatement;
	struct ImportStatementList *importStatementList;
};

struct ImportStatementList {
	char *importStatement;
	struct ImportStatementList *nextImportStatement;
};


// Structs for declarations
struct DeclarationList {
	struct Declaration *declaration;
	struct DeclarationList *nextDeclaration;
};


struct Declaration {
	enum DeclarationType Type;
	struct VarDeclaration *varDecl;
	struct ConstSpec *constDecl;
	struct FunctionDeclaration *functionDecl;
};

// Const declaration data structures

struct ConstSpec {
	struct IdentifierList *identifierList;
	struct IdentifierListType *identifierListType;
	struct ExpressionList;
};

struct Type {
	char* identifier;
	struct Expression *expression;
};

struct IdentifierListType {
	struct IdenrifierList *identifierList;
	struct Type *type;
};

struct VarDeclaration {
	struct VarSpec *varSpec;
	struct VarSpecList *varSpecList;
};

struct VarSpec {
	struct IdentifierListType *identifierListType;
	struct ExpressionList *expressionList;
	struct IdentifierList *identifierList;
};

struct VarSpecList {
	struct VarSpec *varSpec;
	struct VarSpecList *nextVarSpec;
};

struct UnaryExpression {
	enum ExpressionType Type;
	struct PriamaryExpression;
};

struct PrimaryExpression {
	enum ExpressionType Type;
	char* indentifier;
	int decNum;
	float floatNum;
	char* strinLiteral;
	struct PrimaryExpression *primaryExpression;
	struct FunctionCall *functionCall;
	struct Expression *expression;
};

struct FunctionCall {
	char* identifier;
	struct ExpressionList *expressionList;
};

struct Expression {
	enum ExpressionType Type;
	struct UnaryExpression *unaryExpression;
	struct Expression *left;
	struct Expression *right;
};

struct ExpressionList {
	struct Expression *expr;
	struct ExpressionList *nextExpression;
};

struct Statement {
	enum StatamentType Type;
	struct VarDeclaration *varDecl;
	struct ConstDeclaration *constDecl;
	// for return statement
	struct ExpressionList *returnStmt;
	// for block
	struct StatementList *block;
	struct IfStatement *ifStmt;
	struct SwitchStatement *switchStatement;
	struct ForStatement *forStatement;
};

struct IdentifierList {
	char* identifier;
	struct IdentifierList *nextIdentifier;
};

struct IfStatement {
	struct IfStatementExpression *ifStatementExpression;
	struct StatementList *block;
	struct ElseBlock *elseBlock;

};

struct IfStatementExpression {
	struct Expression *expression;
	struct SimpleStatement *simpleStmt;
};

struct ElseBlock {
	struct IfStatement *ifStatement;
	struct StatementList *block;
};

struct StatementList {
	struct Statement *stmt;
	struct StatementList *nextStmt;
};


struct SwitchStatement {
	struct SimpleStatement *simpleStmt;
	struct Expression *expr;
	struct ExpressionCaseClauseList *switchBody;
};

struct ExpressionCaseClauseList {
	struct ExpressionCaseClause *expressionCaseClauseList;
	struct ExpressionCaseClauseList *nextExpressionCaseClauseList;
};

struct ExpressionCaseClause {
	struct ExpressionList *expressionSwitchCase;
	struct StatementList *statementList;
};

struct SimpleStatement {
	enum StatementType Type;
	struct Expression *expr;
	struct ExpressionList *exprList;
};

struct ForStatement {
	struct StatementList *block;
	struct Expression *expr;
	struct ForClause *forClause;
};

struct ForClause {
	struct SimpleStatement *simpleStmt;
	struct Expression *expr;
};

struct FunctionDeclaration {
	char* identifier;
	struct Signature *signature;
	struct StatementList *block;
};

struct Signature {
	struct ParametersList *parametersInParenthesis;
	struct Result *result;
};

struct ParametersList {
	struct ParameterDeclare *parameterDeclare;
	struct ParametersList *nextParameter;
};

struct ParameterDeclare {
	struct Type *type;
	char* identifier;
};

struct Result {
	struct ParametersList *parametersInParenthesis;
	struct Type *type;
};

#endif// _TREE_H_