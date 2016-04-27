%defines
%error-verbose
%locations

%code requires
{
    typedef struct YYLTYPE
    {
        int first_line;
        int first_column;
        int last_line;
        int last_column;
        char *filename;
    } YYLTYPE;

    #define YYLTYPE_IS_DECLARED 1

    #define YYLLOC_DEFAULT(Current, Rhs, N) \
        do \
            if (N) \
            { \
                (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;   \
                (Current).first_column = YYRHSLOC (Rhs, 1).first_column; \
                (Current).last_line    = YYRHSLOC (Rhs, N).last_line;    \
                (Current).last_column  = YYRHSLOC (Rhs, N).last_column;  \
                (Current).filename     = YYRHSLOC (Rhs, 1).filename;     \
            } \
            else \
            {                                                            \
                (Current).first_line   = (Current).last_line   =         \
                YYRHSLOC (Rhs, 0).last_line;                             \
                (Current).first_column = (Current).last_column =         \
                YYRHSLOC (Rhs, 0).last_column;                           \
                (Current).filename  = NULL;                              \
            }                                                            \
        while (0)
}


%{
	#include "parser.h"
	#include "astfunctions.h"
	extern int yylex(void);
	extern void yyerror(const char *msg);

	struct DeclarationList *declList;
	struct Program *root;
%}

%union {
	char* string;
	int decValue;
	float floatValue;
	int boolValue;

	struct Program *ProgramUnion;
	
	struct DeclarationList *DeclListUnion;
	
	struct Declaration *DeclarationUnion;

	struct StringList *StringListUnion;

	struct IdentifierList* IdentifierListUnion; 

	struct VarDecl *VarDeclUnion;

	struct ConstDecl *ConstDeclUnion;

	struct FunctionDecl *FunctionDeclUnion;

	struct IdentifierList *IdListUnion;

	struct IdentifierListType *IdListTypeUnion;

	struct ExpressionList *ExprListUnion;

	struct Type *TypeUnion;

	enum TypeNames TypeNameUnion; 

	struct Expression *ExprUnion;

	struct VarSpec *VarSpecUnion;

	struct VarSpecList *VarSpecListUnion;

	struct ConstSpec *ConstSpecUnion;

	struct ConstSpecList *ConstSpecListUnion;

	struct Statement *StmtUnion;

	struct SimpleStmt *SimpleStmtUnion;

	struct ReturnStmt *ReturnStmtUnion;

	struct Block *BlockUnion;

	struct IfStmt *IfStmtUnion;

	struct SwitchStmt *SwitchStmtUnion;

	struct ForStmt *ForStmtUnion;

	struct IfStmtExpression *IfStmtExprUnion;

	struct ElseBlock *ElseBlockUnion;

	struct StatementList *StmtListUnion;

	struct SwitchBody *SwitchBodyUnion;

	struct ExpressionCaseClauseList *EcclUnion;

	struct ExpressionCaseClause *EccUnion;

	struct ExpressionSwitchCase *ExpressionSwtichCaseUnion;

	struct ForClause *ForClauseUnion;

	struct Signature *SignatureUnion;

	struct ParamInParen *ParamInParenUnion;

	struct ParameterList *ParamListUnion;

	struct ParameterDeclare *ParamDeclUnion;

	struct Result *ResultUnion;

	struct PrimaryExpression *PrimaryExprUnion;

	struct FunctionCall *FunctionCallUnion;

	struct SwitchInitialAndExpression *SwitchInitialAndExpressionUnion;

	struct ForInitStmt *ForInitStmtUnion ; 

	struct ForCondition *ForConditionUnion;
	
	struct ForPostStmt *ForPostStmtUnion ; 

	struct PrintStatement * PrintStatementUnion ; 

	struct ScanStatement * ScanStatementUnion ; 
 
}

%type<ProgramUnion> program
%type<DeclListUnion> declaration_list
%type<DeclarationUnion> declaration
%type<VarDeclUnion> var_declare
%type<ConstDeclUnion> const_declare
%type<FunctionDeclUnion> function_declaration
%type<IdentifierListUnion> identifier_list
%type<IdListTypeUnion> identifier_list_type
%type<ExprListUnion> expression_list
%type<TypeUnion> type
%type<TypeNameUnion> type_name
%type<ExprUnion> expression 
%type<PrimaryExprUnion> primary_expression 
%type<FunctionCallUnion> function_call
%type<VarSpecUnion> var_specification
%type<VarSpecListUnion> var_specification_list
%type<ConstSpecUnion> const_specification
%type<ConstSpecListUnion> const_specification_list
%type<StmtUnion> statement
%type<SimpleStmtUnion> simple_statement
%type<ReturnStmtUnion> return_statement
%type<BlockUnion> block
%type<IfStmtUnion> if_statement
%type<SwitchStmtUnion> switch_statement
%type<ForStmtUnion> for_statement
%type<IfStmtExprUnion> if_statement_expression
%type<ElseBlockUnion> else_block
%type<StmtListUnion> statement_list
%type<SwitchBodyUnion> switch_body
%type<EcclUnion> expression_case_clause_list
%type<EccUnion> expression_case_clause
%type<ExpressionSwtichCaseUnion> expression_switch_case
%type<ForClauseUnion> for_clause
%type<SignatureUnion> signature
%type<ParamInParenUnion> parameters_in_parentheses
%type<ParamListUnion> parameter_list
%type<ParamDeclUnion> parameter_declare
%type<ResultUnion> result
%type<SwitchInitialAndExpressionUnion> switch_initial_and_expression
%type<ForInitStmtUnion> for_init_statement ; 
%type<ForConditionUnion> for_condition; 
%type<ForPostStmtUnion> for_post_statement ; 
%type<PrintStatementUnion> print_statement ; 
%type<ScanStatementUnion> scan_statement ; 

%start program

%token NEW_LINE TAB
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
%token INT_TYPE FLOAT32_TYPE STRING_TYPE BOOL_TYPE NIL
%token<boolValue> TRUE FALSE
%token PLUS_PLUS MINUS_MINUS
%token PRINTLN SCANLN 

%right ASSIGN_OP
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
	declaration_list					{$$ = root = CreateProgram($1);}
	;	

declaration_list:
	declaration												{$$ = CreateDeclarationList($1);}
	|	declaration_list declaration						{$$ = AppendToDeclarationList($1, $2);}
	; 

declaration:
	var_declare											{$$ = CreateDeclarationFromVarDecl(VAR_DECL, $1);}
	|	const_declare									{$$ = CreateDeclarationFromConstDecl(CONST_DECL, $1);}
	|	function_declaration							{$$ = CreateDeclarationFromFuncDecl(FUNC_DECL, $1);}
	; 

const_declare:
	CONST const_specification										{$$ = CreateConstDecl($2);}
	|	CONST	'('	')'												{$$ = CreateConstDecl(NULL);}							
	|	CONST	'(' const_specification_list ')'						{$$ = CreateConstDeclFromList($3);}
	;

type: 
	type_name											{$$ = CreateTypeFromTypeName($1);}
	|	'[' expression ']' type_name					{$$ = CreateCompositeType($2, $4);}
	; 
	
type_name:
		IDENTIFIER										{$$ = IDENTIFIER_TYPE_NAME;}
	|	FLOAT32_TYPE									{$$ = FLOAT32_TYPE_NAME;}
	|	INT_TYPE										{$$ = INT_TYPE_NAME;}
	|	STRING_TYPE										{$$ = STRING_TYPE_NAME;}
	|	BOOL_TYPE										{$$ = BOOL_TYPE_NAME;}
	; 

identifier_list_type:
	identifier_list type %prec "identifier_list"		{$$ = CreateIdListWithType($1, $2);}
	; 

var_declare:	
	VAR var_specification								{$$ = CreateSimpleVarDecl($2);}
	|	VAR '(' ')'										{$$ = NULL;}
	|	VAR '(' var_specification_list  ')'				{$$ = CreateCompositeVarDecl($3);}
	;

var_specification: 
	identifier_list_type							{$$ = CreateSimpleVarSpecWType($1);}
	|	identifier_list_type ASSIGN_OP expression_list	{$$ = CreateCompositeVarSpecWtype($1, $3);}
	|	identifier_list_type ASSIGN_OP '{' expression_list '}'	{$$ = CreateCompositeVarSpecWtype($1, $4);}
	|	identifier_list ASSIGN_OP expression_list		{$$ = CreateCompositeVarSpecWOType($1, $3);}
	;  
	
var_specification_list: 
	var_specification ';' 								{$$ = CreateVarSpecList($1);}
	|	var_specification_list  var_specification ';'	{$$ = AppendToVarSpecList($1, $2);}
	; 

const_specification: 
	identifier_list_type ASSIGN_OP expression_list		{$$ = CreateCompositeConstSpecWtype($1, $3);}
	|	identifier_list ASSIGN_OP expression_list		{$$ = CreateCompositeConstSpecWOType($1, $3);}
	;  
	
const_specification_list: 
	const_specification ';' 								{$$ = CreateConstSpecList($1);}
	|	const_specification_list  const_specification ';'	{$$ = AppendToConstSpecList($1, $2);}
	; 

primary_expression:
		TRUE											{$$ = CreateBoolExpr(BOOL_TRUE_EXPRESSION, $1);}
	|	FALSE											{$$ = CreateBoolExpr(BOOL_FALSE_EXPRESSION, $1);}
	|	DECIMAL_NUMBER									{$$ = CreateDecimalExpression(DECIMAL_EXPR, $1);}
	|	FLOAT_NUMBER									{$$ = CreateFloatExpression(FLOAT_EXPR, $1);}
	|	STRING_LITERAL									{$$ = CreateStringExpression(STRING_EXPR, $1);}
	|	IDENTIFIER										{$$ = CreateIdExpression(ID_EXPRESSION, $1);}
	|	primary_expression '[' expression ']'			{$$ = CreateCompositePrimaryExpression(PE_COMPOSITE, $1, $3);}
	|	function_call									{$$ = CreatePrimaryExpressionFromFuncCall(FUNCTION_CALL, $1);}
	|	'(' expression ')'								{$$ = CreatePrimaryExpressionFromExpression(EXPRESSION, $2);}
	; 

function_call:
	primary_expression '(' ')'									   {$$ = CreateEmptyFunctionCall($1);}
	|	primary_expression '(' expression_list  optional_comma')'  {$$ = CreateFunctionCallExpr($1, $3);}
	;

optional_comma:
														{}
	|	','												{}
	; 

expression: 
	primary_expression									{$$ = CreateUnaryExpression(PRIMARY, $1);}
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
	simple_statement									{$$ = CreateStmtFromSimpleStmt(SIMPLE_STMT, $1);}
	|	var_declare										{$$ = CreateVarDeclStmt(VAR_DECL_STMT, $1);}
	|	const_declare									{$$ = CreateConstDeclStmt(CONST_DECL_STMT, $1);}
	|	return_statement								{$$ = CreateStmtFromReturnStmt(RETURN_STMT, $1);}
	|	BREAK											{$$ = CreateStatement(BREAK_STMT);}
	|	CONTINUE										{$$ = CreateStatement(CONTINUE_STMT);}
	|	block											{$$ = CreateStmtFromBlock(BLOCK, $1);}
	|	if_statement									{$$ = CreateStmtFromIfStmt(IF_STMT, $1);}
	|	switch_statement								{$$ = CreateStmtFromSwitchStmt(SWITCH_STMT, $1);}
	|	for_statement									{$$ = CreateStmtFromForStmt(FOR_STMT, $1);}
	|	print_statement									{$$ = CreateStmtFromPrintStmt(PRINT_STMT, $1);}
	|	scan_statement									{$$ = CreateStmtFromScanStmt(SCAN_STMT, $1);}
	; 

identifier_list: 
	IDENTIFIER											{$$ = CreateIdList($1);}
	|	identifier_list ',' IDENTIFIER					{$$ = AppendToIdList($1, $3);}
	; 

return_statement: 
	RETURN expression_list								{$$ = CreateReturnStatement($2);}
	; 

if_statement: 
	IF if_statement_expression block					{$$ = CreateIfStatement($2, $3);}
	| IF if_statement_expression block ELSE else_block  {$$ = CreateIfElseStatement($2, $3, $5);}
	; 
	
if_statement_expression:
	expression											{$$ = CreateIfStmtExpression($1);}
	|	 simple_statement ';' expression				{$$ = CreateCompositeIfStmtExpression($1, $3);}
	; 
	
else_block : 
	if_statement										{$$ = CreateElseBlockFromIfStmt($1);}
	|	block											{$$ = CreateElseBlockFromBlock($1);}
	; 
	
block: 
	'{' '}'												{$$ = CreateBlock(NULL);}
	|	'{' statement_list '}'							{$$ = CreateBlock($2);}
	;

statement_list: 
	statement ';'											{$$ = CreateStmtList($1);}
	|	statement_list statement ';'						{$$ = AppendToStmtList($1, $2);}
	; 
 
switch_statement: 
	SWITCH switch_initial_and_expression '{' switch_body '}'	{$$ = CreateSwitchStatement($2, $4);}
	; 

switch_initial_and_expression:							
														{$$ = CreateSwitchInitialAndExpression(ALWAYS_TRUE, NULL, NULL) ;}
	|	simple_statement ';'							{$$ = CreateSwitchInitialAndExpression(WITH_INITIAL_STMT, $1, NULL) ;}
	|	expression										{$$ = CreateSwitchInitialAndExpression(WITH_EXPRESSION, NULL, $1) ;}
	|	simple_statement ';' expression					{$$ = CreateSwitchInitialAndExpression(WITH_INITIAL_AND_EXPRESSION, $1, $3) ;}
	; 


switch_body:
														{$$ = CreateSwitchBody(NULL);}
	|	expression_case_clause_list						{$$ = CreateSwitchBody($1);}
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
	|	DEFAULT												{$$ = CreateExprSwitchCase(NULL);}												
	; 
	
simple_statement:
	expression												{$$ = CreateSimpleStmt(EXPR_SIMPLE_STMT, $1);}
	|	expression PLUS_PLUS								{$$ = CreateSimpleStmt(INC_SIMPLE_STMT, $1);}
	|	expression MINUS_MINUS								{$$ = CreateSimpleStmt(DEC_SIMPLE_STMT, $1);}
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
	for_init_statement ';' for_condition ';' for_post_statement	{$$ = CreateForClause($1, $3, $5);}
	; 


for_init_statement:	
															{$$ = CreateForInitStmt (NULL) ; }
	|	simple_statement									{$$ = CreateForInitStmt ($1) ; }
	;  

for_condition:											
															{$$ = CreateForCondition (NULL) ; }
	|	expression											{$$ = CreateForCondition ($1) ; }
	; 

for_post_statement:
															{$$ = CreateForPostStmt(NULL) ;}	
	|	simple_statement									{$$ = CreateForPostStmt($1) ;}
	; 


function_declaration:
	FUNC IDENTIFIER signature								{$$ = CreateFunctionDeclaration($2, $3);}
	| FUNC IDENTIFIER signature block						{$$ = CreateFunctionDeclarationWithBlock($2, $3, $4);}
	;
	
signature:
	parameters_in_parentheses								{$$ = CreateSignature($1);}
	|	parameters_in_parentheses result					{$$ = CreateSignatureWithResult($1, $2);}
	; 

parameters_in_parentheses:
	'(' ')'													{$$ = CreateParametersInParens(NULL);}
	|	'(' parameter_list ')'								{$$ = CreateParametersInParens($2);}
	; 

parameter_list: 
	parameter_declare										{$$ = CreateParameterDeclareList($1);}
	|	parameter_list ',' parameter_declare				{$$ = AppendToParameterDeclareList($1, $3);}
	;	
 
parameter_declare: 
	type													{$$ = CreateParameterDeclareWithoutId($1);}
	|	IDENTIFIER type										{$$ = CreateParameterDeclareWithId($1, $2);}
	; 
	
result:
	parameters_in_parentheses								{$$ = CreateResultFromParameters($1);}
	|	type												{$$ = CreateResultFromType($1);}
	;

print_statement:
	PRINTLN '(' expression_list ')'							{$$ = CreatePrintStmt ($3) ;}
	; 

scan_statement:
	SCANLN '(' identifier_list ')'						{$$ = CreateScanStmt ($3) ; }
	; 									

%%

