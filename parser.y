%defines
%error-verbose

%{
	#include "parser.h"
	#include "trees.h"
	#include <malloc.h>
	extern int yylex(void);
	
	struct Imports *imports;
	
	struct DeclarationList *declList;

	struct Program *root;

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






%}

%union {
	char* string;
	int decValue;
	float floatValue;

	struct Program *s_program;
	
	struct Package *s_package;
	
	struct Imports *s_imports;
	
	struct DeclarationList *s_declList;

	struct Import *s_import;
	
	struct Declaration *s_declaration;

	struct ImportStmtList *s_importStmtList;

	struct VarDecl *s_varDecl;

	struct ConstDecl *s_constDecl;

	struct FunctionDecl *s_functionDecl;

	struct ConstSpec *s_constSpec;

	struct IdentifierList *s_IdList;

	struct IdentifierListType *s_IdListType;

	struct ExpressionList *s_exprList;

	struct Type *s_type;

	struct Expression *s_expr;

	struct VarSpec *s_varSpec;

	struct VarSpecList *s_varSpecList;

	struct Statement *s_stmt;

	struct SimpleStmt *s_simple_stmt;

	struct ReturnStmt *s_return_stmt;

	struct Block *s_block;

	struct IfStmt *s_if_stmt;

	struct SwitchStmt *s_switch_stmt;

	struct ForStmt *s_for_stmt;

	struct IfStmtExpression *s_ifstmtExpr;

	struct ElseBlock *s_elseBlock;

	struct StatementList *s_stmt_list;

	struct SwitchBody *s_switch_body;

	struct ExpressionCaseClauseList *s_eccl;

	struct ExpressionCaseClause *s_ecc;

	struct ExpressionSwitchCase *s_exprSwitchCase;

	struct ForClause *s_forClause;

	struct Signature *s_signature;

	struct ParamInParen *s_paramInParen;

	struct ParameterList *s_paramList;

	struct ParameterDeclare *s_paramDecl;

	struct Result *s_result;

	struct PrimaryExpression *s_primary_expr;

	struct FunctionCall *s_func_call;
}

%type<s_program> program
%type<s_package> package
%type<s_imports> imports
%type<s_declList> declaration_list
%type<s_import> import
%type<s_declaration> declaration
%type<string> import_statement
%type<s_importStmtList> import_statement_list
%type<s_varDecl> var_declare
%type<s_constDecl> const_declare
%type<s_functionDecl> function_declaration
%type<s_constSpec> const_spec
%type<s_IdList> identifier_list
%type<s_IdListType> identifier_list_type
%type<s_exprList> expression_list
%type<s_type> type
%type<s_expr> expression 
%type<s_primary_expr> primary_expression 
%type<s_func_call> function_call
%type<s_varSpec> var_specification
%type<s_varSpecList> var_specification_list
%type<s_stmt> statement
%type<s_simple_stmt> simple_statement
%type<s_return_stmt> return_statement
%type<s_block> block
%type<s_if_stmt> if_statement
%type<s_switch_stmt> switch_statement
%type<s_for_stmt> for_statement
%type<s_ifstmtExpr> if_statement_expression
%type<s_elseBlock> else_block
%type<s_stmt_list> statement_list
%type<s_switch_body> switch_body
%type<s_eccl> expression_case_clause_list
%type<s_ecc> expression_case_clause
%type<s_exprSwitchCase> expression_switch_case
%type<s_forClause> for_clause
%type<s_signature> signature
%type<s_paramInParen> parameters_in_parentheses
%type<s_paramList> parameter_list
%type<s_paramDecl> parameter_declare
%type<s_result> result

%start program

%token COMMA
%token<string> IDENTIFIER
%token FUNC RETURN 
%token ASSIGN_OP PLUS_ASSIGN_OP MINUS_ASSIGN_OP MUL_ASSIGN_OP DIV_ASSIGN_OP
%token BREAK CONTINUE 
%token SWITCH CASE DEFAULT 
%token FOR 
%token IF ELSE 
%token CONST VAR 
%token AND OR
%token GT GTE LT LTE EQU NE
%token NOT
%token STRUCT
%token<decValue> DECIMAL_NUMBER HEXADECIMAL_NUMBER OCTAL_NUMBER
%token<floatValue> FLOAT_NUMBER 
%token<string> STRING_LITERAL 
%token PACKAGE
%token IMPORT
%token INT_TYPE FLOAT32_TYPE STRING_TYPE BOOL_TYPE NIL
%token TRUE FALSE

%right '='
%left OR
%left AND 
%left EQU NE GT GTE LT LTE 
%left '+' '-'
%left '*' '/' '%'
%left '!'
%left '[' ']'
%left '(' 
%left ')'
%left UNARY_OP UNARY_MINUS UNARY_PLUS
%right ID_LIST

%precedence "type"
%precedence "identifier_list"

%%

program: 
	package imports declaration_list					{$$ = root = CreateProgram($1, $2, $3);}
	;

package:
	PACKAGE IDENTIFIER ';'								{$$ = CreatePackage($2);}
	; 

imports:
														{}
	|	imports import									{
															imports = (struct Imports *)malloc(sizeof(struct Imports));
															$$ = AppendToImportsList(imports, $2);
														}
	; 

import:
	IMPORT import_statement								{$$ = CreateImportFromStatement($2);}
	|	IMPORT '(' ')'									{}
	|	IMPORT '(' import_statement_list ')'			{$$ = CreateCompositeImportFromStatementList($3);}
	; 

import_statement:
	STRING_LITERAL										{$$ = $1;}							
	; 

import_statement_list:
	import_statement									{$$ = CreateImportStatementList($1);}			
	|	import_statement_list ';' import_statement		{$$ = AppendToImportStatementList($1, $3);}
	; 

declaration_list:
														{}
	|	declaration_list declaration ';'				{
															declList = (struct DeclarationList *)malloc(sizeof(struct DeclarationList));
															$$ = AppendToDeclarationList(declList, $2);
														}
	; 

declaration:
														{}
	|	var_declare										{$$ = $1;}
	|	const_declare									{$$ = $1;}
	|	function_declaration							{$$ = $1;}
	; 

const_declare :
	CONST const_spec									{$$ = CreateConstDecl(CONST_DECL, $2);}
	|	CONST '(' const_spec ')'						{$$ = CreateConstDecl(CONST_DECL, $3);}
	;

const_spec:
	identifier_list '=' expression_list					{$$ = CreateConstSpecFromIdList($1, $3);}
	| identifier_list_type '=' expression_list			{$$ = CreateConstSpecFromIdListWithType($1, $3);}
	; 


type: 
	IDENTIFIER											{$$ = CreateTypeFromId($1);}
	|	'[' expression ']' IDENTIFIER					{$$ = CreateCompositeType($2, $4);}
	; 

identifier_list_type:
	identifier_list type %prec "identifier_list"		{$$ = CreateIdListWithType($1, $2);}
	; 

var_declare:	
	VAR var_specification								{$$ = CreateSimpleVarDecl(VAR_DECL, $2);}
	|	VAR '(' ')'										{}
	|	VAR '(' var_specification_list  ')'				{$$ = CreateCompositeVarDecl(VAR_DECL, $3);}
	;

var_specification: 
	identifier_list_type								{$$ = CreateSimpleVarSpecWType($1);}
	|	identifier_list_type '=' expression_list		{$$ = CreateCompositeVarSpecWtype($1, $3);}
	|	identifier_list '=' expression_list				{$$ = CreateCompositeVarSpecWOType($1, $3);}
	;  
	
var_specification_list: 
	var_specification									{$$ = CreateVarSpecList($1);}
	|	var_specification_list ';' var_specification	{$$ = AppendToVarSpecList($1, $3);}
	; 

primary_expression:
		DECIMAL_NUMBER									{$$ = CreateDecimalExpression(DECIMAL_EXPR, $1);}
	|	FLOAT_NUMBER									{$$ = CreateFloatExpression(FLOAT_EXPR, $1);}
	|	STRING_LITERAL									{$$ = CreateStringExpression(STRING_EXPR, $1);}
	|	IDENTIFIER										{$$ = CreateIdExpression(ID_EXPRESSION, $1);}
	|	primary_expression '[' expression ']'			{$$ = CreateCompositePrimaryExpression(PE_COMPOSITE, $1, $3);}
	|	function_call									{$$ = CreatePrimaryExpressionFromFuncCall(FUNCTION_CALL, $1);}
	|	'(' expression ')'								{$$ = CreatePrimaryExpressionFromExpression(EXPRESSION, $2);}
	; 

function_call:
	IDENTIFIER '(' ')'									   {}
	|	IDENTIFIER '(' expression_list	optional_comma')'  {$$ = CreateFunctionCallExpr($1, $3);}
	;

optional_comma:
														{}
	|	COMMA											{}
	; 

expression: 
		primary_expression								{$$ = CreateExpressionFromPrimary(PRIMARY, $1);}
	|	'!' primary_expression %prec UNARY_OP			{$$ = CreateUnaryExpression(NOT_UNARY_EXPR, $2);}
	|	'+' primary_expression %prec UNARY_PLUS			{$$ = CreateUnaryExpression(PLUS_UNARY_EXPR, $2);}
	|	'-' primary_expression %prec UNARY_MINUS		{$$ = CreateUnaryExpression(MINUS_UNARY_EXPR, $2);}
	|	expression AND expression						{$$ = CreateBinaryExpression(AND_EXPRESSION, $1, $3);}
	|	expression OR expression						{$$ = CreateBinaryExpression(OR_EXPRESSION, $1, $3);}
	|	expression EQU expression						{$$ = CreateBinaryExpression(EQU_EXPRESSION, $1, $3);}
	|	expression NE expression						{$$ = CreateBinaryExpression(NE_EXPRESSION, $1, $3);}
	|	expression GT expression						{$$ = CreateBinaryExpression(GT_EXPRESSION, $1, $3);}
	|	expression GTE expression						{$$ = CreateBinaryExpression(GTE_EXPRESSION, $1, $3);}
	|	expression LT expression						{$$ = CreateBinaryExpression(LT_EXPRESSION, $1, $3);}
	|	expression LTE expression						{$$ = CreateBinaryExpression(LTE_EXPRESSION, $1, $3);}
	|	expression '+' expression						{$$ = CreateBinaryExpression(PLUS_EXPRESSION, $1, $3);}
	|	expression '-' expression						{$$ = CreateBinaryExpression(MINUS_EXPRESSION, $1, $3);}
	|	expression '*' expression						{$$ = CreateBinaryExpression(MUL_EXPRESSION, $1, $3);}
	|	expression '/' expression						{$$ = CreateBinaryExpression(DIV_EXPRESSION, $1, $3);}
	|	expression '%' expression						{$$ = CreateBinaryExpression(MOD_EXPRESSION, $1, $3);}
	; 

expression_list: 
	expression											{$$ = CreateExpressionList($1);}
	|	expression_list ',' expression					{$$ = AppendToExpressionList($1, $3);}
	; 

statement:
	simple_statement									{$$ = $1;}
	|	var_declare										{$$ = CreateVarDeclStmt(VAR_DECL_STMT, $1);}
	|	const_declare									{$$ = CreateConstDeclStmt(CONST_DECL_STMT, $1);}
	|	return_statement								{$$ = $1;}
	|	BREAK											{$$ = CreateStatement(BREAK_STMT);}
	|	CONTINUE										{$$ = CreateStatement(CONTINUE_STMT);}
	|	block											{$$ = $1;}
	|	if_statement									{$$ = $1;}
	|	switch_statement								{$$ = $1;}
	|	for_statement									{$$ = $1;}
	; 

identifier_list: 
	IDENTIFIER											{$$ = CreateIdList($1);}
	|	identifier_list ',' IDENTIFIER					{$$ = AppendToIdList($1, $3);}
	; 

return_statement: 
	RETURN expression_list								{$$ = CreateReturnStatement(RETURN_STMT, $2);}
	; 

if_statement: 
	IF if_statement_expression block					{$$ = CreateIfStatement(IF_STMT, $2, $3);}
	| IF if_statement_expression block ELSE else_block  {$$ = CreateIfElseStatement(IF_ELSE_STMT, $2, $3, $5);}
	; 
	
if_statement_expression :
	expression											{$$ = CreateIfStmtExpression($1);}
	|	 simple_statement ';' expression				{$$ = CreateCompositeIfStmtExpression($1, $3);}
	; 
	
else_block : 
	if_statement										{$$ = $1;}
	|	block											{$$ = $1;}
	; 
	
block: 
	'{'	'}'												{}
	|	'{' statement_list '}'							{$$ = CreateBlock(BLOCK, $2);}
	;

statement_list : 
	statement											{$$ = CreateStmtList($1);}
	|	statement_list ';' statement					{$$ = AppendToStmtList($1, $3);}
	; 
 
switch_statement: 
	SWITCH simple_statement ';' '{' switch_body '}'		{$$ = CreateSwitchStatementWSimpleStmt(SWITCH_STMT, $2, $5);}
	|	SWITCH expression '{' switch_body '}'			{$$ = CreateSwitchStatementWExpression(SWITCH_STMT, $2, $4);}
	; 

switch_body:
														{}
	|	expression_case_clause_list						{$$ = $1;}
	;
 
expression_case_clause_list: 
	expression_case_clause									{$$ = CreateExpressionCaseClauseList($1);}
	|	expression_case_clause_list expression_case_clause	{$$ = AppendToExpressionCaseClauseList($1, $2);}
	; 

expression_case_clause: 
	expression_switch_case ':' statement_list				{$$ = CreateExpressionCaseClause($1, $3);}
	; 

expression_switch_case: 
	CASE expression_list									{$$ = CreateExprSwitchCase($2);}
	|	DEFAULT												{}												
	; 
	
simple_statement:
	expression												{$$ = CreateSimpleStmt(EXPR_SIMPLE_STMT, $1);}
	|	expression "++"										{$$ = CreateSimpleStmt(INC_SIMPLE_STMT, $1);}
	|	expression "--"										{$$ = CreateSimpleStmt(DEC_SIMPLE_STMT, $1);}
	|   expression_list ASSIGN_OP expression_list			{$$ = CreatAssignSimpleStmt(ASSIGN_STMT, $1, $3);}
	|	expression_list PLUS_ASSIGN_OP expression_list		{$$ = CreatAssignSimpleStmt(PLUS_ASSIGN_STMT, $1, $3);}
	|	expression_list MINUS_ASSIGN_OP expression_list		{$$ = CreatAssignSimpleStmt(MINUS_ASSIGN_STMT, $1, $3);}
	|	expression_list MUL_ASSIGN_OP expression_list		{$$ = CreatAssignSimpleStmt(MUL_ASSIGN_STMT, $1, $3);}
	|	expression_list DIV_ASSIGN_OP expression_list		{$$ = CreatAssignSimpleStmt(DIV_ASSIGN_STMT, $1, $3);} 
	;

for_statement:	
	FOR block												{$$ = CreateForStmt($2);}
	|	FOR expression block								{$$ = CreateForStmtWExpr($2, $3);}
	|	FOR for_clause block								{$$ = CreateForStmtWClause($2, $3);}
	;

for_clause: 
	simple_statement ';' expression ';' simple_statement	{$$ = CreateForClause($1, $3, $5);}
	; 

function_declaration:
	FUNC IDENTIFIER signature								{$$ = CreateFunctionDeclaration(FUNC_DECL,$2, $3);}
	| FUNC IDENTIFIER signature block						{$$ = CreateFunctionDeclaration(FUNC_DECL, $2, $3, $4);}
	;
	
signature:
	parameters_in_parentheses								{$$ = CreateSignature($1);}
	|	parameters_in_parentheses result					{$$ = CreateSignatureWithResult($1, $2);}
	; 

parameters_in_parentheses:
	'(' ')'													{}
	|	'(' parameter_list ')'								{$$ = $2;}
	; 

parameter_list : 
	parameter_declare										{$$ = CreateParameterList($1);}
	|	parameter_list ',' parameter_declare				{$$ = AppendToParameterDeclareList($1, $3);}
	;	
 
parameter_declare: 
	type													{$$ = CreateParameterDeclareWithoutId($1);}
	|	IDENTIFIER type										{$$ = CreateParameterDeclareWithId($1, $2);}
	; 
	
result :
	parameters_in_parentheses								{$$ = CreateResultFromParameters($1);}
	|	type												{$$ = CreateResultFormType($1);}
	;

%%

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

