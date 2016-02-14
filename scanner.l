%option noyywrap
%option never-interactive
%option header-file="scanner.h"

%{
	#include <stdio.h>
	int line = 0;
%}

%x C_COMMENT

%%


"/*"            { BEGIN(C_COMMENT); }
<C_COMMENT>"*/" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
"//".*			{ }


"break"			{printf("BREAK - %s, line: %i\n", yytext, line);}
"default"		{printf("DEFAULT - %s, line: %i\n", yytext, line);}
"func"			{printf("FUNC - %s, line: %i\n", yytext, line);}
"interface"		{printf("INTERFACE - %s, line: %i\n", yytext, line);}
"select"		{printf("SELECT - %s, line: %i\n", yytext, line);}
"case"          {printf("CASE - %s, line: %i\n", yytext, line);}
"defer"         {printf("DEFER - %s, line: %i\n", yytext, line);}
"go"            {printf("GOROUTINE - %s, line: %i\n", yytext, line);}
"map"           {printf("MAP - %s, line: %i\n", yytext, line);}
"struct"	    {printf("STRUCT - %s, line: %i\n", yytext, line);}
"chan"          {printf("CHANNEL - %s, line: %i\n", yytext, line);}
"else"          {printf("ELSE - %s, line: %i\n", yytext, line);}
"goto"          {printf("GOTO - %s, line: %i\n", yytext, line);}
"package"       {printf("PACKAGE - %s, line: %i\n", yytext, line);}
"switch"		{printf("SWITCH - %s, line: %i\n", yytext, line);}
"const"         {printf("CONST - %s, line: %i\n", yytext, line);}
"fallthrough"   {printf("FALLTHROUGH - %s, line: %i\n", yytext, line);}
"if"            {printf("IF - %s, line: %i\n", yytext, line);}
"range"         {printf("RANGE - %s, line: %i\n", yytext, line);}
"type"		    {printf("TYPE - %s, line: %i\n", yytext, line);}
"continue"      {printf("CONTINUE - %s, line: %i\n", yytext, line);}
"for"           {printf("FOR - %s, line: %i\n", yytext, line);}
"import"        {printf("IMPORT - %s, line: %i\n", yytext, line);}
"return"        {printf("RETURN - %s, line: %i\n", yytext, line);}
"var"			{printf("VAR - %s, line: %i\n", yytext, line);}




"bool"			{printf("BOOL_TYPE - %s, line: %i\n", yytext, line);}
"byte"			{printf("BYTE_TYPE (uint8) - %s, line: %i\n", yytext, line);}
"complex64"		{printf("COMPLEX64_TYPE - %s, line: %i\n", yytext, line);}
"complex128"	{printf("COMPLEX128_TYPE - %s, line: %i\n", yytext, line);}
"error"			{printf("ERROR_TYPE - %s, line: %i\n", yytext, line);} 
"float32"		{printf("FLOAT32_TYPE - %s, line: %i\n", yytext, line);}
"float64"		{printf("FLOAT64_TYPE - %s, line: %i\n", yytext, line);}
"int"			{printf("INT_TYPE - %s, line: %i\n", yytext, line);}
"int8"			{printf("INT8_TYPE - %s, line: %i\n", yytext, line);}
"int16"			{printf("INT16_TYPE - %s, line: %i\n", yytext, line);}
"int32"			{printf("INT32_TYPE - %s, line: %i\n", yytext, line);}
"int64"			{printf("INT64_TYPE - %s, line: %i\n", yytext, line);}
"rune"			{printf("RUNE_TYPE (int32) - %s, line: %i\n", yytext, line);}
"string"		{printf("STRING_TYPE - %s, line: %i\n", yytext, line);}
"uint"			{printf("UINT_TYPE - %s, line: %i\n", yytext, line);}
"uint8"			{printf("UINT8_TYPE - %s, line: %i\n", yytext, line);}
"uint16"		{printf("UINT16_TYPE - %s, line: %i\n", yytext, line);}
"uint32"		{printf("UINT32_TYPE - %s, line: %i\n", yytext, line);}
"uint64"		{printf("UINT64_TYPE - %s, line: %i\n", yytext, line);}
"uintptr"		{printf("UINTPTR_TYPE - %s, line: %i\n", yytext, line);}

"true"			{printf("TRUE - %s, line: %i\n", yytext, line);}
"false"			{printf("FALSE - %s, line: %i\n", yytext, line);}
"iota"			{printf("IOTA - %s, line: %i\n", yytext, line);}

"nil"			{printf("NIL - %s, line: %i\n", yytext, line);}

"append" 
"cap" 
"close" 
"complex" 
"copy" 
"delete" 
"imag" 
"len"
"make" 
"new" 
"panic" 
"print" 
"println" 
"real" 
"recover"

"+"    
"&"     
"+="    
"&="     
"&&"    
"=="    
"!="    
"("    
")"
"-"    
"|"     
"-="    
"|="     
"||"    
"<"     
"<="    
"["    
"]"
"*"    
"^"     
"*="    
"^="     
"<-"    
">"     
">="    
"{"    
"}"
"/"    
"<<"    
"/="    
"<<="    
"++"    
"="     
":="    
","    
";"
"%"   
">>"    
"%="    
">>="    
"--"    
"!"     
"..."   
"."    
":"
"&^"          
"&^="

.			{printf("unknown: %s, line: %i\n", yytext, line);}
"\n"		{line++;}
%%