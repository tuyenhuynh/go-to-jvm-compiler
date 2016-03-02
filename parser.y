


%token IDENTIFIER
%token FUNC RETURN 
%token ASSIGN_OP PLUS_ASSIGN_OP MINUS_ASSIGN_OP MUL_ASSIGN_OP DIV_ASSIGN_OP
%token BREAK CONTINUE 
%token SWITCH CASE DEFAULT 
%token FOR 
%token IF ELSE 
%token CONST VAR 
%token AND_OP OR_OP BITWISE_OR_OP BITWISE_AND_OP BITWISE_XOR_OP
%token HIGHER_OP LOWER_OP HIGHER_OR_EQU_OP LOWER_OR_EQU_OP 
%token ADD_OP MINUS_OP MUL_OP DIV_OP  MOD_OP EQU_OP NOT_EQU_OP 
%token RANGE 
%token ENDL
%token NOT_OP
%token STRUCT

%%

programa: function_declaration
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
	empty_statement
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
	| identifier_list type '=' expression_list 
	; 

identifier_list: 
		IDENTIFIER
	|	identifier_list ',' IDENTIFIER
	; 

expression_list: 
	expression 
	|	expression_list ',' expression 
	; 

type : 
	type_name 
	|	type_lit 
	|	'(' type ')'
	; 

type_name : 
	IDENTIFIER
	|	qualified_ident
	; 

type_lit : 
	array_type 
	|	struct_type 
	|	function_type
	;	 

struct_type:
	STRUCT '{' '}'
	|	STRUCT '{' field_declaration '}'
	; 

field_declaration:
	identifier_list type 

qualified_ident: 
	package_name '.' IDENTIFIER
	; 

package_name: 
	IDENTIFIER
	; 

array_type : 
	'[' array_length ']' element_type 
	; 

array_length : 
	expression 
	; 

element_type : 
	type 
	; 

function_type : 
	FUNC signature 
	; 

signature:	
	parameters
	|	parameters result
	; 

parameters 
	:	'(' ')'
	|	'('	parameter_list ')'
	; 

parameter_list : 
	parameter_declare 
	|	parameter_declare ',' parameter_declare
	;	 

parameter_declare: 
	type 
	|	identifier_list type 
	; 

result :
	parameters
	| type
	; 

//variable declaration
var_declare :	
	VAR var_specification
	|	VAR '(' ')'
	|	VAR '(' var_specification_list  ')'
	;

var_specification: 
	identifier_list type
	|	identifier_list type '=' expression_list 
	|	identifier_list '=' expression_list 
	;  

var_specification_list : 
	var_specification ENDL
	|	var_specification_list var_specification
	; 

empty_statement:
	/*empty*/	
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

//block 
block: 
	'{'	'}'
	|	'{' statement_list '}'
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
	SWITCH simple_statement ';' '{' expression_case_clause '}'
	|	SWITCH expression '{' expression_case_clause '}' 
	; 

expression_case_clause: 
	expression_switch_case ':' statement_list 
	; 

expression_switch_case : 
	CASE expression_list
	|	DEFAULT
	; 


//FOR STATEMENT 

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
	|	expression HIGHER_OP expression
	|	expression LOWER_OP expression 
	|	expression HIGHER_OR_EQU_OP expression
	|	expression LOWER_OR_EQU_OP expression
	|	expression BITWISE_OR_OP expression
	|	expression BITWISE_XOR_OP expression
	|	expression ADD_OP expression
	|	expression MINUS_OP expression
	|	expression MUL_OP expression
	|	expression DIV_OP expression
	|	expression MOD_OP expression
	; 

unary_expression :
	primary_expression 
	|	ADD_OP unary_expression 
	|	MINUS_OP unary_expression 
	|	NOT_OP unary_expression
	; 

//Primary expressions are the operands for unary and binary expressions.
primary_expression :
	operand 
	| primary_expression index 
	; 

index: 
	'[' expression']'
operand: 
	literal
	|	operand_name 
	|	method_expression
	|	'(' expression ')'
	;

literal: 
	basic_literal
	|	composite_literal
	|	function_literal
	; 

basic_literal:
	; 

composite_literal:
	; 

function_literal:
	FUNC function
	; 
function:
	signature function_body
	; 
function_body:
	block
	; 

operand_name: 
	IDENTIFIER 
	|	qualified_ident
	; 

method_expression: 
	receiver_type '.' method_name 
	; 

receiver_type: 
	type_name 
	; 

method_name:
	IDENTIFIER 
	; 

function_declaration:
	FUNC function_name function
	|	FUNC function_name signature
	; 
function_name: 
	IDENTIFIER
	; 

%%

