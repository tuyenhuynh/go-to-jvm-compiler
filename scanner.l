%option noyywrap
%option never-interactive
%option header-file="scanner.h"
%option yylineno

%{
	#include <stdio.h>
	#include <math.h>
	#include "parser.h"
	int line = 1;


	int yycolumn = 1;
    char *filename;

    #define YY_USER_ACTION \
        yylloc.filename = filename; \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;

    void yyerror(const char *msg)
    {
        printf("%s:%d.%d: %s\n", yylloc.filename, yylloc.first_line, yylloc.first_column, msg);
    }
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
"case"          {return CASE;}
"struct"	    {return STRUCT;}
"else"          {return ELSE;}
"switch"		{return SWITCH;}
"const"         {return CONST;}
"if"            {return IF;}
"continue"      {return CONTINUE;}
"for"           {return FOR;}
"return"        {return RETURN;}
"var"			{return VAR;}



"float32"		{return FLOAT32_TYPE;}
"int"			{return INT_TYPE;}
"string"		{return STRING_TYPE;}
"bool"			{return BOOL_TYPE;}

"true"			{
					yylval.boolValue = 1;
					return TRUE;
				}
"false"			{
					yylval.boolValue = 0;
					return FALSE;
				}
"nil"			{return NIL;}

"scan"	{return	SCANLN; }
"print"	{return PRINTLN; }

\"(\\.|[^\\"])*\"	{ 		
							int textLength = strlen(yytext);
							yylval.string = (char*)malloc(textLength);
							strncpy(yylval.string, yytext+1, textLength - 2);
							yylval.string[textLength-2] = 0;  
							return STRING_LITERAL;
					}


\'(\\.|[^\\"])*\'	{ 		
							int textLength = strlen(yytext);
							yylval.string = (char*)malloc(textLength);
							strncpy(yylval.string, yytext+1, textLength - 2);
							yylval.string[textLength-2] = 0;  
							return STRING_LITERAL;
					}

"+="						{return PLUS_ASSIGN_OP;}
"-="						{return MINUS_ASSIGN_OP;}
"*="						{return MUL_ASSIGN_OP;}
"/="						{return DIV_ASSIGN_OP;}
"="							{return ASSIGN_OP;}
","							{return ',';}
"("							{return '(';}
")"							{return ')';}
";"							{return ';';}
"{"							{return '{';}
"}"							{return '}';}
"["							{return '[';}
"]"							{return ']';}
"&&"						{return AND;}
"||"						{return OR;}
">"							{return GT;}
"<"							{return LT;}
">="						{return GTE;}
"<="						{return LTE;}
"=="						{return EQU;}
"!="						{return NE;}
"!"							{return '!';}
"+"							{return '+';}
"-"							{return '-';}
"*"							{return '*';}
"/"							{return '/';}
"."							{return '.';}
"%"							{return '%';}
":"							{return ':';}
"++"						{return PLUS_PLUS;}
"--"						{return MINUS_MINUS;}
"&"							{return '&';}



[a-zA-Z_][a-zA-Z0-9_]*			{
									yylval.string = (char*)malloc(strlen(yytext) + 1);
									strcpy(yylval.string, yytext);
									return IDENTIFIER;
								}
{FLOAT}							{
									yylval.floatValue = atof(yytext);
									return FLOAT_NUMBER;
								}
0[xX][0-9a-fA-F]+				{
									yylval.decValue = hex_decimal(yytext); 
									return DECIMAL_NUMBER;
									
								}
0[1-7][0-7]*					{
									return OCTAL_NUMBER;
								}
{DECIMAL}						{
									yylval.decValue = atoi(yytext);
									return DECIMAL_NUMBER;
								}

"\n"							{line++;}
"\t"							{}
[ \a\b\f\r\v\\]+				{}
.								{printf(".unknown<-: \"%s\", line: %i\n", yytext, line);}

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