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

struct Program* program;

static unsigned short
ACC_SUPER = 0x02,
ACC_PUBLIC = 0x01;

static int objectClass = 0; 

int fd;
unsigned char u1;
unsigned short int u2;
unsigned int u4;
short int s2;
int s4;
float sf4;

int fh; 
struct Constant* constantCode; 

void Write(void* data, int count);
void writeU1(); 
void writeU2(); 
void writeU4(); 
void writeS2(); 
void writeS4(); 
void writeSf4(); 
void writeString(char* str);
void writeU1ToArray(int * code, int* offset);
void writeU2ToArray(int* code, int* offset);
void writeU4ToArray(int* code, int* offset);
void writeS2ToArray(int* code, int* offset);
void writeS4ToArray(int* code, int* offset);
void writeSf4ToArray(int* code, int* offset);

void writeConstantsTable(); 
void writeClassMetadata(); 
void writeFieldsTable(); 
void writeMethodsTable(); 
void writeMethod(struct Method* method); 
void generateCode(struct Program* root); 
void writeConstant(struct Constant* constant); 
void writeField(struct Field* field); 

int* generateCodeForMethod(struct Method* method);  
void generateCodeForVarDecl(struct Method* method, struct VarDecl* varDecl, int* code, int *offset);  
void generateCodeForVarSpec(struct Method* method, struct VarSpec* varSpec, int* code, int* offset);  
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl, int* code, int* offset);  
void generateCodeForConstSpec(struct Method* method,struct ConstSpec* constSpec, int* code, int* offset);  
void generateCodeForStmtList(struct Method* method, struct StatementList* stmtList, int* code, int* offset); 
void generateCodeForStmt(struct Method* method, struct Statement* stmt, int* code, int* offset); 
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt, int* code, int* offset);  
void generateCodeForIfStmt(struct Method* method, struct IfStmt* ifStmt, int* code, int* offset);  
void generateCodeForSwitchStmt(struct Method* method, struct SwitchStmt* switchStmt, int* code, int* offset);  
void generateCodeForForStmt(struct Method* method, struct ForStmt* forStmt, int* code, int* offset);  
void generateCodeForPrintStmt(struct Method* method, struct PrintStmt* printStmt, int* code, int* offset);  
void generateCodeForScanStmt(struct Method* method, struct ScanStmt* scanStmt, int* code, int*  offset);  
void generateCodeForExpression(struct Method* method, struct Expression* expr, int* code, int* offset);  
void generateCodeForPrimaryExpression(struct Method* method, struct PrimaryExpression* primaryExpr, int* code, int* offset);  
void generateCodeForSingleAssignment(struct Method*  method, struct Identifier* id, struct Expression* expr, int* code, int* offset);

#endif //_CODE_GENERATION_H_