#ifndef _CODE_GENERATION_H_
#define _CODE_GENERATION_H_
#include "semantic.h"
#include "astfunctions.h"
#include "trees.h"
#include <fcntl.h>
#include <io.h>
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

static char* classFileName = "Go.class"; 

static int objectClass = 0; 

static unsigned short
ACC_SUPER = 0x02,
ACC_PUBLIC = 0x01; 




int fd;
unsigned char u1;
unsigned short int u2;
unsigned int u4;
short int s2;
int s4;
float sf4;

int fh; 

void Write(void* data, int count); 

void generateCode(struct Program* root); 
void generateCodeForMethod(struct Method* method, struct StatementList* stmtList); 
void generateCodeForVarDecl(struct Method* method, struct VarDecl* varDecl); 
void generateCodeForVarSpec(struct Method* method, struct VarSpec* varSpec); 
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl); 
void generateCodeForConstSpec(struct Method* method,struct ConstSpec* constSpec); 
void generateCodeForStatementList(struct Method* method, struct StatementList* stmtList);
void generateCodeForStatement(struct Method* method, struct Statement* stmt);
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt); 
void generateCodeForIfStmt(struct Method* method, struct IfStmt* ifStmt); 
void generateCodeForSwitchStmt(struct Method* method, struct SwitchStmt* switchStmt); 
void generateCodeForForStmt(struct Method* method, struct ForStmt* forStmt); 
void generateCodeForPrintStmt(struct Method* method, struct PrintStmt* printStmt); 
void generateCodeForScanStmt(struct Method* method, struct ScanStmt* scanStmt); 
void generateCodeForExpression(struct Method* method, struct Expression* expr); 
void generateCodeForPrimaryExpression(struct Method* method, struct PrimaryExpression* primaryExpr); 



#endif //_CODE_GENERATION_H_