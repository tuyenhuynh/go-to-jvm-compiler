%defines
%error-verbose

%{
	int yylex(void);

%}

%code requires {
	#include "parser.h"
}

%union {
	int INT;
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
%token DECIMAL_NUMBER FLOAT_NUMBER STRING_LITERAL 
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
%right ID_LIST

%precedence "type"
%precedence "identifier_list"

%%

program: 
	package	imports	declaration_list 
	;

package:
	PACKAGE IDENTIFIER ';'
	; 

imports:
	|	imports import
	; 

import:
	IMPORT import_statement
	|	IMPORT '(' ')'
	|	IMPORT '(' import_statement_list ')'
	; 

import_statement:
	STRING_LITERAL
	; 

import_statement_list:
	import_statement
	|	import_statement_list ';' import_statement 
	; 

declaration_list:
	|	declaration_list declaration ';'
	; 

declaration:
	|	var_declare
	|	const_declare
	|	function_declaration
	; 

const_declare :
	CONST const_spec
	|	CONST '(' const_spec ')' 
	;

const_spec:
	identifier_list '=' expression_list
	| identifier_list_type '=' expression_list 
	; 


type: 
	IDENTIFIER 
	|	'[' expression ']' IDENTIFIER  
	; 

identifier_list_type:
	identifier_list type %prec "identifier_list" 
	; 

var_declare:	
	VAR var_specification
	|	VAR '(' ')'
	|	VAR '(' var_specification_list  ')'
	;

var_specification: 
	identifier_list_type
	|	identifier_list_type '=' expression_list 
	|	identifier_list '=' expression_list 
	;  
	
var_specification_list: 
	var_specification
	|	var_specification_list ';' var_specification
	; 

unary_expression:
	primary_expression
	|	'!' primary_expression %prec UNARY_OP
	|	'+' primary_expression %prec UNARY_PLUS
	|	'-' primary_expression %prec UNARY_MINUS
	; 

primary_expression:
	literal
	|	IDENTIFIER
	|	primary_expression '[' expression ']'
	|	function_call 
	|	'(' expression ')'
	; 

function_call:
	IDENTIFIER '(' ')'
	|	IDENTIFIER '(' expression_list	optional_comma')'
	;

optional_comma:
	|	COMMA
	; 


literal:
	DECIMAL_NUMBER
	|	FLOAT_NUMBER
	|	STRING_LITERAL
	;

expression: 
	unary_expression 
	|	expression AND expression
	|	expression OR expression
	|	expression EQU expression
	|	expression NE expression
	|	expression GT expression
	|	expression GTE expression 
	|	expression LT expression
	|	expression LTE expression
	|	expression '+' expression
	|	expression '-' expression
	|	expression '*' expression
	|	expression '/' expression
	|	expression '%' expression
	; 

expression_list: 
	expression 
	|	expression_list ',' expression 
	; 

statement:
	simple_statement
	|	var_declare
	|	const_declare	
	|	return_statement
	|	BREAK
	|	CONTINUE
	|	block
	|	if_statement
	|	switch_statement	
	|	for_statement
	; 

identifier_list: 
	IDENTIFIER
	|	identifier_list ',' IDENTIFIER
	; 

return_statement: 
	RETURN expression_list 
	; 

assign_op: 
	ASSIGN_OP
	|	PLUS_ASSIGN_OP
	|	MINUS_ASSIGN_OP
	|	MUL_ASSIGN_OP
	|	DIV_ASSIGN_OP
	; 

if_statement: 
	IF if_statement_expression block 
	| IF if_statement_expression block ELSE else_block 
	; 
	
if_statement_expression :
	expression 
	|	 simple_statement ';' expression 
	; 
	
else_block : 
	if_statement 
	|	block 
	; 
	
block: 
	'{'	'}'
	|	'{' statement_list '}'
	;

statement_list : 
	statement	
	|	statement_list ';' statement
	; 
 
switch_statement: 
	SWITCH simple_statement ';' '{' switch_body '}'
	|	SWITCH expression '{' switch_body '}' 
	; 
switch_body:
	|	expression_case_clause_list
	;
 
expression_case_clause_list: 
	expression_case_clause
	|	expression_case_clause_list expression_case_clause
	; 

expression_case_clause: 
	expression_switch_case ':' statement_list 
	; 

expression_switch_case: 
	CASE expression_list 
	|	DEFAULT 
	; 
	
simple_statement:
	expression 
	|	expression "++"
	|	expression "--"
	|	expression_list assign_op expression_list 
	;

for_statement:	
	FOR block
	|	FOR expression block 
	|	FOR for_clause block 
	;

for_clause: 
	simple_statement ';' expression ';' simple_statement 
	; 

function_declaration:
	FUNC	IDENTIFIER  signature
	|	FUNC	IDENTIFIER  signature block
	;
	
signature:
	parameters_in_parentheses
	|	parameters_in_parentheses result
	; 

parameters_in_parentheses:
	'(' ')'
	|	'(' parameter_list ')'
	; 

parameter_list : 
	parameter_declare 
	|	parameter_list ',' parameter_declare
	;	
 
parameter_declare: 
	type 
	|	IDENTIFIER type 
	; 
	
result :
	parameters_in_parentheses
	|	type
	;

%%

