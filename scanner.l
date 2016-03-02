%option noyywrap
%option never-interactive
%option header-file="scanner.h"

%{
	#include <stdio.h>
	#include <math.h>
	#include "parser.h"
	int line = 1;
%}

FLOAT		[0-9]*\.[0-9]+[eE]*[-+]*[0-9]*	
DECIMAL		[0-9]+
	
%x MULTILINE_COMMENT

%x MULTILINE_STRING_LITERAL

%%


\/\/.*			{}

\/\*					   {BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>\*\/    {BEGIN(INITIAL);}
<MULTILINE_COMMENT>\n      {++line; } 
<MULTILINE_COMMENT>.       {}   


"break"			{return BREAK;}
"default"		{return DEFAULT;}
"func"			{return FUNC;}
"interface"		{return INTERFACE;}
"select"		{return SELECT;}
"case"          {return CASE;}
"defer"         {return DEFER;}
"go"            {return GOROUTINE;}
"map"           {return MAP;}
"struct"	    {return STRUCT;}
"chan"          {return CHANNEL;}
"else"          {return ELSE;}
"goto"          {return GOTO;}
"package"       {return PACKAGE;}
"switch"		{return SWITCH;}
"const"         {return CONST;}
"fallthrough"   {return FALLTHROUGH;}
"if"            {return IF;}
"range"         {return RANGE;}
"type"		    {return TYPE;}
"continue"      {return CONTINUE;}
"for"           {return FOR;}
"import"        {return IMPORT;}
"return"        {return RETURN;}
"var"			{return VAR;}

"bool"			{return BOOL;}
"byte"			{return BYTE_TYPE;}
"complex64"		{return COMPLEX64_TYPE;}
"complex128"	{return COMPLEX128_TYPE;}
"error"			{return ERROR_TYPE;} 
"float32"		{return FLOAT32_TYPE;}
"float64"		{return FLOAT64_TYPE;}
"int"			{return INT_TYPE;}
"int8"			{return INT8_TYPE;}
"int16"			{return INT16_TYPE;}
"int32"			{return INT32_TYPE;}
"int64"			{return INT64_TYPE;}
"rune"			{return RUNE_TYPE;}
"string"		{return STRING_TYPE;}
"uint"			{return UINT_TYPE;}
"uint8"			{return UINT8_TYPE;}
"uint16"		{return UINT16_TYPE;}
"uint32"		{return UINT32_TYPE;}
"uint64"		{return UINT64_TYPE;}
"uintptr"		{return UINTPTR_TYPE;}

"true"			{return TRUE;}
"false"			{return FALSE;}
"iota"			{return IOTA;}
"nil"			{return NIL;}

"append"		{return APPEND_FUNC;}
"cap"			{return CAP_FUNC;}
"close"			{return CLOSE_FUNC;}
"complex"		{return COMPLEX_FUNC;}
"copy"			{return COPY_FUNC;}
"delete"		{return DELETE_FUNC;}
"imag"			{return IMAG_FUNC;}
"len"			{return LEN_FUNC;}	
"make"			{return MAKE_FUNC;}
"new"			{return NEW_FUNC;}
"panic"			{return PANIC_FUNC;}
"print"			{return PRINT_FUNC;}
"println"		{return PRINTLN_FUNC;}
"real"			{return REAL_FUNC;}
"recover"		{return RECOVER_FUNC;}

\"(\\.|[^\\"])*\"	{return STRING_LITERAL;}

"`"									{BEGIN(MULTILINE_STRING_LITERAL);}
<MULTILINE_STRING_LITERAL>"`"		{BEGIN(INITIAL);}
<MULTILINE_STRING_LITERAL>\n		{ ++line; } 
<MULTILINE_STRING_LITERAL>.			{return MULTILINE_STRING_LITERAL;}   

"+"							{return PLUS_OP;}  
"&"							{return AMPERSAND_OP;}
"+="						{return PLUS_ASSIGN_OP;}
"&="						{return BITWISE_AND_ASSIGN_OP;}
"&&"						{return AND_OP;}
"=="						{return EQU_OP;}
"!="						{return NOT_EQU_OP;}
"("							{return LEFT_PAREN;}
")"							{return RIGHT_PAREN;}
"-"							{return MINUS_OP;}
"|"							{return BITWISE_OR_OP;}
"-="						{return MINUS_ASSIGN_OP;}
"|="						{return BITWISE_OR_ASSIGN_OP;}
"||"						{return OR_OP;}
"<"							{return LOWER_OP;}
"<="						{return LOWER_OR_EQU_OP;}
"["							{return LEFT_SQUARE_BRACKET;}
"]"							{return RIGHT_SQUARE_BRACKET;}
"*"							{return ASTERISK_OP;}
"^"							{return BITWISE_XOR_OP;}
"*="						{return MUL_ASSIGN_OP;}
"^="						{return BITWISE_XOR_ASSIGN_OP;}
"<-"						{return SEND_RECIEVE_OP;}
">"							{return HIGHER_OP;}
">="						{return HIGHER_OR_EQU_OP;}
"{"							{return LEFT_CURLY_BRACE;}
"}"							{return RIGHT_CURLY_BRACE;}
"/"							{return DIV_OP;}
"<<"						{return LEFT_SHIFT_OP;}
"/="						{return DIV_ASSIGN_OP;}
"<<="						{return LEFT_SHIFT_ASSIGN_OP;}
"++"						{return INCREMENT_OP;}
"="							{return ASSIGN_OP;}
":="						{return SHORTHAND_ASSIGN_OP;}
","							{return COMMA;}
";"							{return SEMICOLON;}
"%"							{return MOD_OP;}
">>"						{return RIGHT_SHIFT_OP;}
"%="						{return MOD_ASSIGN_OP;}
">>="						{return RIGHT_SHIFT_ASSIGN_OP;}
"--"						{return DECREMENT_OP;}
"!"							{return NOT_OP;}
"..."						{return ELIPSIS_OP;}
"."							{return DOT_OP;}
":"							{return COLON_OP;}
"&^"						{return AND_NOT_BITWISE_OP;}
"&^="						{return AND_NOT_BITWISE_ASSIGN_OP;}


[a-zA-Z_][a-zA-Z0-9_]*			{return IDENTIFIER;}
{FLOAT}[i]						{return COMPLEX_FLOAT_NUMBER;}
{DECIMAL}[i]					{return COMPLEX_DECIMAL_NUMBER;}
{FLOAT}							{return FLOAT_NUMBER;}
0[xX][0-9a-fA-F]+				{return HEXADECIMAL_NUMBER;}
0[1-7][0-7]*					{return OCTAL_NUMBER;}
{DECIMAL}						{return DECIMAL_NUMBER;}

"\n"							{line++;}
[ \t\a\b\f\r\v\\]+				{}
.								{printf("->unknown<-: \"%s\", line: %i\n", yytext, line);}

%%

int octal_decimal(int n) 
{
    int decimal=0, i=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(8,i);
        ++i;
    }
    return decimal;
}

long hex_decimal(char hex[])
{
    char *hexstr;
    int length = 0;
    const int base = 16; // Base of Hexadecimal Number
    unsigned long decnum = 0;
    int i;
    // Find length of Hexadecimal Number
    for (hexstr = hex; *hexstr != '\0'; hexstr++)
    {
		length++;
    }
    // Find Hexadecimal Number
    hexstr = hex;
    for (i = 0; *hexstr != '\0' && i < length; i++, hexstr++)
    {
		// Compare *hexstr with ASCII values
		if (*hexstr >= 48 && *hexstr <= 57)   // is *hexstr Between 0-9
		{
			decnum += (((int)(*hexstr)) - 48) * pow(base, length - i - 1);
		}
		else if ((*hexstr >= 65 && *hexstr <= 70))   // is *hexstr Between A-F
		{
			decnum += (((int)(*hexstr)) - 55) * pow(base, length - i - 1);
		}
		else if (*hexstr >= 97 && *hexstr <= 102)   // is *hexstr Between a-f
		{
			decnum += (((int)(*hexstr)) - 87) * pow(base, length - i - 1);
		}
    }
    return decnum;
}