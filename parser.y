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

%start program


%token IDENTIFIER
%token FUNC RETURN 
%token ASSIGN_OP PLUS_ASSIGN_OP MINUS_ASSIGN_OP MUL_ASSIGN_OP DIV_ASSIGN_OP
%token BREAK CONTINUE 
%token SWITCH CASE DEFAULT 
%token FOR 
%token IF ELSE 
%token CONST VAR 
%token AND_OP OR_OP
%token HIGHER_OP LOWER_OP HIGHER_OR_EQU_OP LOWER_OR_EQU_OP 
%token ADD_OP MINUS_OP ASTERISK_OP DIV_OP  MOD_OP EQU_OP NOT_EQU_OP 
%token RANGE 
%token ENDL
%token NOT_OP
%token STRUCT
%token DECIMAL_NUMBER FLOAT_NUMBER STRING_LITERAL 
%token TEST 


%right '='
%left AND_OP OR_OP 
%left EQU_OP
%left HIGHER_OP LOWER_OP HIGHER_OR_EQU_OP LOWER_OR_EQU_OP 
%left '+' '-'
%left '*' '/' '%'
%left '!'
%left '[' ']'
//??? 
%nonassoc ')'
%left UNARY_OP
%right ID_LIST

%precedence "type"
%precedence "identifier_list"


%%

program: function_declaration
	; 

function_declaration:
	FUNC function_name function
	|	FUNC function_name signature
	; 
function_name: 
	IDENTIFIER
	; 

function:
	signature function_body
	; 
function_body:
	block
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

//statement 
statement :
	declaration 
	|	simple_statement
	|	return_statement
	|	BREAK
	|	CONTINUE
	|	block 
	|	if_statement
	|	switch_statement	
	|	for_statement
	; 

//Simple statement 
simple_statement:
	/*empty*/ 
	|	expression 
	|	inc_dec_statement
	|	assignment
	;

//Declaration
declaration: 
		const_declare
	|	var_declare
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

identifier_list: 
		IDENTIFIER
	|	identifier_list ',' IDENTIFIER
	; 

expression_list: 
	expression 
	|	expression_list ',' expression 
	; 

type: 
	IDENTIFIER 
	| IDENTIFIER '.' IDENTIFIER
	|	type_lit 
	|	'(' type ')'
	; 

type_name:
	IDENTIFIER 
	| IDENTIFIER '.' IDENTIFIER 
	; 
type_lit : 
	array_type 
	|	function_type
	;	 

	/*
//the first identifier is package name
qualified_ident: 
	IDENTIFIER '.' IDENTIFIER
	; 
	*/

array_type : 
	'[' array_length ']' type 
	; 

array_length : 
	expression 
	; 


function_type : 
	FUNC signature 
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

parameter_declare: 
	type 
	|	identifier_list_type 
	; 

result :
	parameters_in_braces
	|	type
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


identifier_list_type:
	identifier_list type %prec "identifier_list" 
	; 
var_specification_list : 
	var_specification ENDL
	|	var_specification_list var_specification
	; 

//the operand must be addresable 
inc_dec_statement: 
	expression "++"
	|	expression "--"
	;

assignment: 
	expression_list assign_op expression_list 
	; 

assign_op: 
	ASSIGN_OP
	|	PLUS_ASSIGN_OP
	|	MINUS_ASSIGN_OP
	|	MUL_ASSIGN_OP
	|	DIV_ASSIGN_OP
	; 

//return statement  
return_statement: 
	RETURN expression_list 
	; 



//if statement 
if_statement: 
	IF if_statement_expression block 
	| if_statement_expression block ELSE else_block 
	; 

if_statement_expression :
	expression 
	|	 statement ';' expression 
	; 

else_block : 
	if_statement 
	|	block 
	; 


//switch statement  
switch_statement: 
	SWITCH simple_statement ';' '{' switch_body '}'
	|	SWITCH expression '{' switch_body '}' 
	; 

switch_body:
	/*empty*/
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

//for statement
for_statement:	
	FOR condition block 
	|	FOR for_clause block 
	|	FOR range_clause block
	;

condition: 
	/*empty*/ 
	|expression
	; 

for_clause : 
	initial_statement ';' 	condition ';' post_statement 
	; 

initial_statement :	
	simple_statement 
	; 

post_statement: 
	simple_statement 
	;	 


range_clause : 
	range_initial RANGE expression
	; 
range_initial: 
	/*empty*/
	|	expression_list '=' 
	|	identifier_list ":="
	; 

expression : 
	unary_expression 
	|	expression AND_OP expression
	|	expression OR_OP expression
	|	expression EQU_OP expression
	|	expression NOT_EQU_OP expression
	|	expression '>' expression
	|	expression '<' expression 
	|	expression HIGHER_OR_EQU_OP expression
	|	expression LOWER_OR_EQU_OP expression
	|	expression '+' expression
	|	expression '-' expression
	|	expression '*' expression
	|	expression '/' expression
	|	expression '%' expression
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
	|	primary_expression '.' IDENTIFIER
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
	|	method_expression
	|	'(' expression ')'
	;

literal: 
	basic_literal
	|	function_literal
	; 

basic_literal:
	DECIMAL_NUMBER
	|	FLOAT_NUMBER
	|	STRING_LITERAL
	; 

/*
composite_literal:
	; 
	*/
function_literal:
	FUNC function
	; 

method_expression: 
	receiver_type '.' IDENTIFIER 
	; 

receiver_type: 
	IDENTIFIER
	|	IDENTIFIER '.' IDENTIFIER
	| '(' receiver_type')'
	; 

%%

