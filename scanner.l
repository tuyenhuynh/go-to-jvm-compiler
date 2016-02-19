%option noyywrap
%option never-interactive
%option header-file="scanner.h"

%{
	#include <stdio.h>
	#include <math.h>
	int line = 1;
%}

FLOAT		[0-9]*\.[0-9]+[eE]*[-+]*[0-9]*	
DECIMAL		[0-9]+
	
%x MULTILINE_COMMENT

%x MULTILINE_STRING_LITERAL

%%


\/\/.*			{printf("ONE_LINE_COMMENT - \"%s\", line: %i\n", yytext, line);}

\/\*					   {BEGIN(MULTILINE_COMMENT);}
<MULTILINE_COMMENT>\*\/    {BEGIN(INITIAL);}
<MULTILINE_COMMENT>\n      { ++line; } 
<MULTILINE_COMMENT>.       {printf("MULTILINE_COMMENT - \"%s\", line: %i\n", yytext, line);}   


"break"			{printf("BREAK - \"%s\", line: %i\n", yytext, line);}
"default"		{printf("DEFAULT - \"%s\", line: %i\n", yytext, line);}
"func"			{printf("FUNC - \"%s\", line: %i\n", yytext, line);}
"interface"		{printf("INTERFACE - \"%s\", line: %i\n", yytext, line);}
"select"		{printf("SELECT - \"%s\", line: %i\n", yytext, line);}
"case"          {printf("CASE - \"%s\", line: %i\n", yytext, line);}
"defer"         {printf("DEFER - \"%s\", line: %i\n", yytext, line);}
"go"            {printf("GOROUTINE - \"%s\", line: %i\n", yytext, line);}
"map"           {printf("MAP - \"%s\", line: %i\n", yytext, line);}
"struct"	    {printf("STRUCT - \"%s\", line: %i\n", yytext, line);}
"chan"          {printf("CHANNEL - \"%s\", line: %i\n", yytext, line);}
"else"          {printf("ELSE - \"%s\", line: %i\n", yytext, line);}
"goto"          {printf("GOTO - \"%s\", line: %i\n", yytext, line);}
"package"       {printf("PACKAGE - \"%s\", line: %i\n", yytext, line);}
"switch"		{printf("SWITCH - \"%s\", line: %i\n", yytext, line);}
"const"         {printf("CONST - \"%s\", line: %i\n", yytext, line);}
"fallthrough"   {printf("FALLTHROUGH - \"%s\", line: %i\n", yytext, line);}
"if"            {printf("IF - \"%s\", line: %i\n", yytext, line);}
"range"         {printf("RANGE - \"%s\", line: %i\n", yytext, line);}
"type"		    {printf("TYPE - \"%s\", line: %i\n", yytext, line);}
"continue"      {printf("CONTINUE - \"%s\", line: %i\n", yytext, line);}
"for"           {printf("FOR - \"%s\", line: %i\n", yytext, line);}
"import"        {printf("IMPORT - \"%s\", line: %i\n", yytext, line);}
"return"        {printf("RETURN - \"%s\", line: %i\n", yytext, line);}
"var"			{printf("VAR - \"%s\", line: %i\n", yytext, line);}

"bool"			{printf("BOOL_TYPE - \"%s\", line: %i\n", yytext, line);}
"byte"			{printf("BYTE_TYPE (uint8) - \"%s\", line: %i\n", yytext, line);}
"complex64"		{printf("COMPLEX64_TYPE - \"%s\", line: %i\n", yytext, line);}
"complex128"	{printf("COMPLEX128_TYPE - \"%s\", line: %i\n", yytext, line);}
"error"			{printf("ERROR_TYPE - \"%s\", line: %i\n", yytext, line);} 
"float32"		{printf("FLOAT32_TYPE - \"%s\", line: %i\n", yytext, line);}
"float64"		{printf("FLOAT64_TYPE - \"%s\", line: %i\n", yytext, line);}
"int"			{printf("INT_TYPE - \"%s\", line: %i\n", yytext, line);}
"int8"			{printf("INT8_TYPE - \"%s\", line: %i\n", yytext, line);}
"int16"			{printf("INT16_TYPE - \"%s\", line: %i\n", yytext, line);}
"int32"			{printf("INT32_TYPE - \"%s\", line: %i\n", yytext, line);}
"int64"			{printf("INT64_TYPE - \"%s\", line: %i\n", yytext, line);}
"rune"			{printf("RUNE_TYPE (int32) - \"%s\", line: %i\n", yytext, line);}
"string"		{printf("STRING_TYPE - \"%s\", line: %i\n", yytext, line);}
"uint"			{printf("UINT_TYPE - \"%s\", line: %i\n", yytext, line);}
"uint8"			{printf("UINT8_TYPE - \"%s\", line: %i\n", yytext, line);}
"uint16"		{printf("UINT16_TYPE - \"%s\", line: %i\n", yytext, line);}
"uint32"		{printf("UINT32_TYPE - \"%s\", line: %i\n", yytext, line);}
"uint64"		{printf("UINT64_TYPE - \"%s\", line: %i\n", yytext, line);}
"uintptr"		{printf("UINTPTR_TYPE - \"%s\", line: %i\n", yytext, line);}

"true"			{printf("TRUE - \"%s\", line: %i\n", yytext, line);}
"false"			{printf("FALSE - \"%s\", line: %i\n", yytext, line);}
"iota"			{printf("IOTA - \"%s\", line: %i\n", yytext, line);}
"nil"			{printf("NIL - \"%s\", line: %i\n", yytext, line);}

"append"		{printf("APPEND_FUNC - \"%s\", line: %i\n", yytext, line);}
"cap"			{printf("CAP_FUNC - \"%s\", line: %i\n", yytext, line);}
"close"			{printf("CLOSE_FUNC - \"%s\", line: %i\n", yytext, line);}
"complex"		{printf("COMPLEX_FUNC - \"%s\", line: %i\n", yytext, line);}
"copy"			{printf("COPY_FUNC - \"%s\", line: %i\n", yytext, line);}
"delete"		{printf("DELETE_FUNC - \"%s\", line: %i\n", yytext, line);}
"imag"			{printf("IMAG_FUNC - \"%s\", line: %i\n", yytext, line);}
"len"			{printf("LEN_FUNC - \"%s\", line: %i\n", yytext, line);}	
"make"			{printf("MAKE_FUNC - \"%s\", line: %i\n", yytext, line);}
"new"			{printf("NEW_FUNC - \"%s\", line: %i\n", yytext, line);}
"panic"			{printf("PANIC_FUNC - \"%s\", line: %i\n", yytext, line);}
"print"			{printf("PRINT_FUNC - \"%s\", line: %i\n", yytext, line);}
"println"		{printf("PRINTLN_FUNC - \"%s\", line: %i\n", yytext, line);}
"real"			{printf("REAL_FUNC - \"%s\", line: %i\n", yytext, line);}
"recover"		{printf("RECOVER_FUNC - \"%s\", line: %i\n", yytext, line);}

\"(\\.|[^\\"])*\"	{printf("STRING_LITERAL - \"%s\", line: %i\n", yytext, line);}

"`"									{BEGIN(MULTILINE_STRING_LITERAL);}
<MULTILINE_STRING_LITERAL>"`"			{BEGIN(INITIAL);}
<MULTILINE_STRING_LITERAL>\n		{ ++line; } 
<MULTILINE_STRING_LITERAL>.			{printf("MULTILINE_STRING_LITERAL - \"%s\", line: %i\n", yytext, line);}   

"+"							{printf("PLUS_OP - \"%s\", line: %i\n", yytext, line);}  
"&"							{printf("AMPERSAND_OP - \"%s\", line: %i\n", yytext, line);}
"+="						{printf("PLUS_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"&="						{printf("BITWISE_AND_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"&&"						{printf("AND_OP - \"%s\", line: %i\n", yytext, line);}
"=="						{printf("EQU_OP - \"%s\", line: %i\n", yytext, line);}
"!="						{printf("NOT_EQU_OP - \"%s\", line: %i\n", yytext, line);}
"("							{printf("LEFT_PAREN - \"%s\", line: %i\n", yytext, line);}
")"							{printf("RIGHT_PAREN - \"%s\", line: %i\n", yytext, line);}
"-"							{printf("MINUS_OP - \"%s\", line: %i\n", yytext, line);}
"|"							{printf("BITWISE_OR_OP - \"%s\", line: %i\n", yytext, line);}
"-="						{printf("MINUS_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"|="						{printf("BITWISE_OR_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"||"						{printf("OR_OP - \"%s\", line: %i\n", yytext, line);}
"<"							{printf("LOWER_OP - \"%s\", line: %i\n", yytext, line);}
"<="						{printf("LOWER_OR_EQU_OP - \"%s\", line: %i\n", yytext, line);}
"["							{printf("LEFT_BRACKET - \"%s\", line: %i\n", yytext, line);}
"]"							{printf("RIGHT_BRACKET - \"%s\", line: %i\n", yytext, line);}
"*"							{printf("ASTERISK_OP - \"%s\", line: %i\n", yytext, line);}
"^"							{printf("BITWISE_XOR_OP - \"%s\", line: %i\n", yytext, line);}
"*="						{printf("MUL_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"^="						{printf("BITWISE_XOR_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"<-"						{printf("SEND_RECIEVE_OP - \"%s\", line: %i\n", yytext, line);}
">"							{printf("HIGHER_OP - \"%s\", line: %i\n", yytext, line);}
">="						{printf("HIGHER_OR_EQU_OP - \"%s\", line: %i\n", yytext, line);}
"{"							{printf("LEFT_CURLY_BRACE - \"%s\", line: %i\n", yytext, line);}
"}"							{printf("RIGHT_CURLY_BRACE - \"%s\", line: %i\n", yytext, line);}
"/"							{printf("DIV_OP - \"%s\", line: %i\n", yytext, line);}
"<<"						{printf("LEFT_SHIFT_OP - \"%s\", line: %i\n", yytext, line);}
"/="						{printf("DIV_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"<<="						{printf("LEFT_SHIFT_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"++"						{printf("INCREMENT_OP - \"%s\", line: %i\n", yytext, line);}
"="							{printf("ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
":="						{printf("SHORTHAND_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
","							{printf("COMMA - \"%s\", line: %i\n", yytext, line);}
";"							{printf("SEMICOLON - \"%s\", line: %i\n", yytext, line);}
"%"							{printf("MOD_OP - \"%s\", line: %i\n", yytext, line);}
">>"						{printf("RIGHT_SHIFT_OP - \"%s\", line: %i\n", yytext, line);}
"%="						{printf("MOD_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
">>="						{printf("RIGHT_SHIFT_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}
"--"						{printf("DECREMENT_OP - \"%s\", line: %i\n", yytext, line);}
"!"							{printf("NOT_OP - \"%s\", line: %i\n", yytext, line);}
"..."						{printf("ELIPSIS_OP - \"%s\", line: %i\n", yytext, line);}
"."							{printf("DOT_OP - \"%s\", line: %i\n", yytext, line);}
":"							{printf("COLON_OP - \"%s\", line: %i\n", yytext, line);}
"&^"						{printf("AND_NOT_BITWISE_OP - \"%s\", line: %i\n", yytext, line);}
"&^="						{printf("AND_NOT_BITWISE_ASSIGN_OP - \"%s\", line: %i\n", yytext, line);}


[a-zA-Z_][a-zA-Z0-9_]*			{printf("IDENTIFIER - \"%s\", line: %i\n", yytext, line);}
{FLOAT}[i]						{printf("COMPLEX_FLOAT_NUMBER - \"%s\", line: %i\n", yytext, line);}
{DECIMAL}[i]					{printf("COMPLEX_DECIMAL_NUMBER - \"%s\", line: %i\n", yytext, line);}
{FLOAT}							{printf("FLOAT_NUMBER - \"%s\", line: %i\n", yytext, line);}
0[xX][0-9a-fA-F]+				{printf("HEXADECIMAL_NUMBER - \"%d\", line: %i\n", hex_decimal(yytext), line);}
0[1-7][0-7]*					{printf("OCTAL_NUMBER - \"%d\", line: %i\n", octal_decimal(atoi(yytext)), line);}
{DECIMAL}						{printf("DECIMAL_NUMBER - \"%s\", line: %i\n", yytext, line);}

"\n"						{line++;}
[ \t\a\b\f\r\v\\]+			{}
.							{printf("->unknown<-: \"%s\", line: %i\n", yytext, line);}

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