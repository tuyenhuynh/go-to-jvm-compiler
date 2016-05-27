#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_
#include "semantic.h"
#include "astfunctions.h"
#include "trees.h"
//what need to generate code ????
//constants table
//class table -> methods table
void generateCodeForFunction(struct FunctionDecl* functionDecl); 
void generateCodeForVarDecl(struct VarDecl* varDecl); 
void generateCodeForVarSpec(struct VarSpec* varSpec); 
void generateCodeForConstDecl(struct ConstDecl* constDecl); 
void generateCodeForConstSpec(struct ConstSpec* constSpec); 
void generateCodeForStatementList(struct StatementList* stmtList); 
void generateCodeForStatement(struct Statement* stmt); 
#endif //_CODE_GENERATION_H_