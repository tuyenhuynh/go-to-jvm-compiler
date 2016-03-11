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
	UNARY_NOT
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
	FOR_STATEMENT
};

enum DeclarationType {
	VAR_DECL,
	CONST_DECL,
	FUNCTION_DECL
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
	enum ExpressionType Type;
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


// TODO STARTS HERE
struct Declaration {
	enum DeclarationType Type;
	struct VarDeclaration *varDecl;
	struct ConstDeclaration *constDecl;
	struct FunctionDeclaration *functionDecl;
};



struct Expression {
	enum ExpressionType Type;
	double num;
	char *identifier;
	struct Expression *left;
	struct Expression *right;
};

struct ExpressionList {
	struct Expression *expr;
	struct ExpressionList *nextExpression;
};



#endif// _TREE_H_