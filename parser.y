%defines
%error-verbose

%{
	#include "parser.h"
	#include "trees.h"
	int yylex(void);
%}

%union {



}


%start program

%token COMMA
%token IDENTIFIER
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
%token DECIMAL_NUMBER FLOAT_NUMBER 
%token STRING_LITERAL 
%token PACKAGE
%token IMPORT

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


%%

program: 
	package imports declaration_list					{$$ = CreateProgram($1, $2, $3);}
	;

package:
	PACKAGE IDENTIFIER ';'								{$$ = CreatePackage($2);}
	; 

imports:
														{}
	|	imports import									{}
	; 

import:
	IMPORT import_statement								{$$ = CreateImportFromStatement(SIMPLE_IMPORT, $2);}
	|	IMPORT '(' ')'									{$$ = CreateEmptyImport(EMPTY_IMPORT);}
	|	IMPORT '(' import_statement_list ')'			{$$ = CreateCompositeImportFromStatementList(COMPOSITE_IMPORT, $3);}
	; 

import_statement:
	STRING_LITERAL										{$$ = CreateImportStatement($1);}							
	; 

import_statement_list:
	import_statement									{$$ = CreateImportStatementList($1);}			
	|	import_statement_list ';' import_statement		{$$ = AppendToImportStatementList($1, $3);}
	; 

declaration_list:
														{}
	|	declaration_list declaration ';'				{}
	; 

declaration:
	|	var_declare										{$$ = CreateDeclarationOfVar(VAR_DECL, $1);}
	|	const_declare									{$$ = CreateDeclarationOfConst(CONST_DECL, $1);}
	|	function_declaration							{$$ = CreateDeclarationOfFunc(FUNCTION_DECL, $1);}
	; 

const_declare :
	CONST const_spec									{$$ = CreateConstDecl(WO_PAREN, $2);}
	|	CONST '(' const_spec ')'						{$$ = CreateConstDecl(W_PAREN, $2);}
	;

const_spec:
	identifier_list '=' expression_list					{$$ = CreateConstSpecFromIdList($1, $3);}
	| identifier_list_type '=' expression_list			{$$ = CreateConstSpecFromIdListWithType($1, $3);}
	; 


type: 
	IDENTIFIER											{$$ = CreateTypeFromId(SIMPLE_TYPE, $1);}
	|	'[' expression ']' IDENTIFIER					{$$ = CreateCompositeType(COMPOSITE_TYPE, $2, $4);}
	; 

identifier_list_type:
	identifier_list type %prec "identifier_list"		{$$ = CreateIdListWithType($1, $2);}
	; 

var_declare:	
	VAR var_specification								{$$ = CreateSimpleVarDecl(SIMPLE_VAR_DECL, $2);}
	|	VAR '(' ')'										{$$ = CreateEmptyVarDecl(EMPTY_VAR_DECL);}
	|	VAR '(' var_specification_list  ')'				{$$ = CreateCompositeVarDecl(COMPOSITE_VAR_DECL, $3);}
	;

var_specification: 
	identifier_list_type								{$$ = CreateSimpleVarSpecWType(SIMPLE_VAR_SPEC_W_TYPE, $1);}
	|	identifier_list_type '=' expression_list		{$$ = CreateCompositeVarSpecWtype(COMPOSITE_VAR_SPEC_W_TYPE, $1, $3);}
	|	identifier_list '=' expression_list				{$$ = CreateCompositeVarSpecWOType(COMPOSITE_VAR_SPEC_WO_TYPE, $1, $3);}
	;  
	
var_specification_list: 
	var_specification									{$$ = CreateVarSpecList($1);}
	|	var_specification_list ';' var_specification	{$$ = AppendToVarSpecList($1, $3);}
	; 

unary_expression:
	primary_expression									{$$ = CreateUnaryExpression(UNARY_EXPR, $1);}
	|	'!' primary_expression %prec UNARY_OP			{$$ = CreateUnaryExpression(NOT_UNARY_EXPR, $2);}
	|	'+' primary_expression %prec UNARY_PLUS			{$$ = CreateUnaryExpression(PLUS_UNARY_EXPR, $2);}
	|	'-' primary_expression %prec UNARY_MINUS		{$$ = CreateUnaryExpression(MINUS_UNARY_EXPR, $2);}
	; 

primary_expression:
	literal												{$$ = CreatePrimaryExpressionFromLiteral(PE_LITERAL, $1);}
	|	IDENTIFIER										{$$ = CreatePrimaryExpressionFromIdentifier(PE_IDENTIFIER, $1);}
	|	primary_expression '[' expression ']'			{$$ = CreateCompositePrimaryExpression(PE_COMPOSITE, $1, $3);}
	|	function_call									{$$ = CreatePrimaryExpressionFromFucntionCall(PE_FUNCTION_CALL, $1);}
	|	'(' expression ')'								{$$ = CreatePrimaryExpressionFromExpression(PE_EXPRESSION, $2);}
	; 

function_call:
	IDENTIFIER '(' ')'									   {$$ = CreateFunctionCallEmptyParameters(FUNCTION_CALL_EMPTY, $1);}
	|	IDENTIFIER '(' expression_list	optional_comma')'  {$$ = CreateFunctionCall(FUNCTION_CALL, $1, $3, $4);}
	;

optional_comma:
	|	COMMA											{$$ = $1;}
	; 


literal:
		DECIMAL_NUMBER									{$$ = CreateLiteral(DECIMAL_LITERAL, $1);}
	|	FLOAT_NUMBER									{$$ = CreateLiteral(FLOAT_LITERAL, $1);}
	|	STRING_LITERAL									{$$ = CreateLiteral(STRING_LITERAL, $1);}
	;	

expression: 
	unary_expression									{$$ = CreateExpressionFromUnary(UNARY_EXPRESSION, $1);}
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
	|	var_declare										{$$ = $1;}
	|	const_declare									{$$ = $1;}
	|	return_statement								{$$ = $1;}
	|	BREAK											{$$ = $1;}
	|	CONTINUE										{$$ = $1;}
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

assign_op: 
	ASSIGN_OP											{$$ = CreateAssignOp(ASSIGN, $1);}
	|	PLUS_ASSIGN_OP									{$$ = CreateAssignOp(PLUS_ASSIGN, $1);}
	|	MINUS_ASSIGN_OP									{$$ = CreateAssignOp(MINUS_ASSIGN, $1);}
	|	MUL_ASSIGN_OP									{$$ = CreateAssignOp(MUL_ASSIGN, $1);}
	|	DIV_ASSIGN_OP									{$$ = CreateAssignOp(DIV_ASSIGN, $1);}
	; 

if_statement: 
	IF if_statement_expression block					{$$ = CreateIfStatement(IF_STMT, $2, $3);}
	| IF if_statement_expression block ELSE else_block  {$$ = CreateIfElseStatement(IF_ELSE_STMT, $2, $3, $5);}
	; 
	
if_statement_expression :
	expression											{$$ = CreateIfStmtExpression($1);}
	|	 simple_statement ';' expression				{$$ = AppendToIfStmtExpression($1, $3);}
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
	CASE expression_list									{$$ = $2;}
	|	DEFAULT												{$$ = $1;}												
	; 
	
simple_statement:
	expression												{$$ = CreateSimpleStmt(EXPR_SIMPLE_STMT, $1);}
	|	expression "++"										{$$ = CreateSimpleStmt(INC_SIMPLE_STMT, $1);}
	|	expression "--"										{$$ = CreateSimpleStmt(DEC_SIMPLE_STMT, $1);}
	|	expression_list assign_op expression_list			{$$ = CreateCompositeSimpleStmt(COMPOSITE_SIMPLE_STMT, $1, $2, $3);}
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
	|	'(' parameter_list ')'								{$$ = $1;}
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


