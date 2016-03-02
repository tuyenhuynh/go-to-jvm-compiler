

%%

programa: statement_list
; 

statement_list : 
		statement	
	|	statementlist statement
; 


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

//SIMPLE STATEMENT 
simple_statement: 
		empty_statement
	|	expression 
	|	inc_dec_statement
	|	assignment
	;

//DECLARATION
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
		identifier
	|	identifier_list ',' identifier
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
	identifier
	|	qualified_ident
	; 

type_lit : 
	array_type 
	|	struct_type 
	|	function_type
	;	 

qualified_ident: 
	package_name '.' identifier
	; 

package_name: 
	identifier
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

	//VARIABLE DECLARATION
var_declare :	
	VAR var_specification
	| VAR '(' var_specification_list  ')'
	;

var_specification: 
	identifier_list type
	|	identifier_list type '=' expression_list 
	|	identifier_list '=' expression_list 
	;  

var_specification_list : 
	/*empty*/
	|	var_specification ENDL
	|	var_specification_list var_specication
	; 

empty_statement:
	/*empty*/	
	;


//the operand must be addresable 
inc_dec_statement: 
	expession "++"
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

//RETURN STATEMENT 
return_statement: 
	RETURN expression_list 
	; 

block: 
	'{' statement_list '}'
	;

//IF STATEMENT
if_statement: 
	IF if_statement_expression block 
	| if_statement_expression block else_block 
	; 

if_statement_expression :
	expression 
	|	 statement ';' expression 
	; 

else_statement : 
	if_statement 
	|	block 
	; 


//SWITCH STATEMENT 
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
	|	identifier_list ':='
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
	|	expression AND_OP expression
	|	expression ADD_OP expression
	|	expression MINUS_OP expression
	|	expression BITWISE_OR_OP expression
	|	expression BITWISE_XOR_OP expression
	|	expression ASTERISK_OP expression
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


operand: 
	literal
	|	operand_name 
	|	method_expression
	|	'(' expression ')'
	;

method_expression: 
	receiver_type '.' method_name 
	; 

receiver_type: 
	type_name 
	; 

method_name:
	identifier 
	; 

%%

