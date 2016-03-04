%defines
%error-verbose
%locations

%{
	int yylex(void);

%}

%code requires {
	#include <parser.h>
}

%union {
	int INT;
}

//%start program


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

%right '='
%left OR
%left AND 
%left EQU NE GT GTE LT LTE
%left '>' '<'  
%left '+' '-'
%left '*' '/' '%'
%left '!'
%left '[' ']'
%left '(' 
%left ')'
%left UNARY_OP
%right ID_LIST

%precedence "type"
%precedence "identifier_list"

%%

/*
	program: 
	function_list 
	;
*/
function_list :
	function_declaration 
	|	function_list function_declaration
	;

//Declaration
declaration:
	const_declare
	|	var_declare
	; 

parameter_declare: 
	type 
	|	identifier_list_type 
	; 

//CONST_DECL
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
	|	array_type 
	; 

array_type : 
	'[' array_length ']' type 
	; 

array_length : 
	expression 
	; 

identifier_list_type:
	identifier_list type %prec "identifier_list" 
	; 


//variable declaration
var_declare :	
	VAR var_specification
	|	VAR '(' ')'
	|	VAR '(' var_specification_list  ')'
	;

var_specification: 
	identifier_list_type
	|	identifier_list_type '=' expression_list 
	|	identifier_list '=' expression_list 
	;  
	
var_specification_list : 
	var_specification
	|	var_specification_list ';' var_specification
	; 

unary_expression:
	primary_expression 
	|	'+' unary_expression %prec UNARY_OP
	|	'-' unary_expression %prec UNARY_OP
	|	'!' unary_expression %prec UNARY_OP
	; 

//Primary expressions are the operands for unary and binary expressions.
primary_expression:
	operand 
	|	primary_expression index	
	|	primary_expression arguments
	; 

arguments:
	'(' ')'
	|	'(' expression_list ')' 
	; 

index: 
	'[' expression']'
	;

operand:
	literal
	|	'(' expression ')'
	;

literal:
	DECIMAL_NUMBER
	|	FLOAT_NUMBER
	|	STRING_LITERAL
	;

expression : 
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

//statement 
statement :
	declaration 
	|	return_statement
	|	BREAK
	|	CONTINUE
	|	block 
	|	simple_statement
	|	if_statement
	|	switch_statement	
	|	for_statement
	; 

identifier_list: 
		IDENTIFIER
	|	identifier_list ',' IDENTIFIER
	; 

//return statement
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

//if statement 
if_statement: 
	IF if_statement_expression block 
	| IF if_statement_expression block ELSE else_block 
	; 
	
if_statement_expression :
	expression 
	|	 statement ';' expression 
	; 
	
else_block : 
	if_statement 
	|	block 
	; 
	

//block 
block: 
	'{'	'}'
	|	'{' statement_list '}'
	;

statement_list : 
		statement	
	|	statement_list statement
	; 

//switch statement  
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
	
//Simple statement 
simple_statement:
	|	expression 
	|	inc_dec_statement
	|	assignment
	;

assignment: 
	expression_list assign_op expression_list 
	; 

	
//the operand must be addresable 
inc_dec_statement: 
	expression "++"
	|	expression "--"
	;

//for statement
for_statement:	
	FOR block
	|	FOR expression block 
	|	FOR for_clause block 
	;

for_clause : 
	simple_statement ';' expression ';' simple_statement 
	; 


function_declaration:
	FUNC IDENTIFIER function
	|	FUNC IDENTIFIER signature
	; 

function:
	signature function_body
	; 

function_body:
	block
	; 

signature:
	parameters_in_braces
	|	parameters_in_braces result
	; 

parameters_in_braces:
	'(' ')'
	|	'(' parameter_list ')'
	; 

parameter_list : 
	parameter_declare 
	|	parameter_list ',' parameter_declare
	;	 

result :
	parameters_in_braces
	|	type
	;

%%

