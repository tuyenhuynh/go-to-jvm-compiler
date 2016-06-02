#include "code_generation.h"


void generateCode(struct Program* root){
	fh = open(classFileName, O_BINARY | O_WRONLY | O_TRUNC | O_CREAT); 
	if (fh < 0) {
		freopen("CON", "w", stdout); 
		printf("Failed to open class file\n"); 
		return; 
	}
	else {


		//magic number
		u4 = htonl(0xCAFEBABE);
		_write((void*)&u4, 4); 

		//minor version
		u2 = htons(0); 
		_write((void*)&u2, 2);

		//major version
		u2 = htons(53);
		_write((void*)&u2, 2); 

		int constantCount = list_size(constantsTable); 
		u2 = htons(constantCount +1 );
		_write((void*)&u2, 2); 

		struct Constant* constant = NULL; 
		for (int i = 0; i < constantCount; ++i) {
			
		}

		struct DeclarationList* declList = root->declList; 
		struct Declaration* decl = declList->firstDecl; 
		while (decl != NULL){
			if (decl->declType == FUNC_DECL) {
				struct Method* method = getMethod(decl->funcDecl->identifier); 
				generateCodeForMethod(method, decl->funcDecl->block->stmtList); 
			}
			decl = decl->nextDecl; 
		}
	}
	
}

void writeConstant(struct Constant* constant) {
	u1 = constant->type; 
	_write((void*)&u1, 1); 
	int length; 
	switch (constant->type) {
	case CONSTANT_Utf8:
		length = strlen(constant->utf8);
		u2 = htons(length);
		//length
		_write((void*)&u2, 2);
		//data
		_write((void*)constant->utf8, length);
		break; 
	case CONSTANT_Integer:
		s4 = htonl(constant->intValue);
		_write((void*)&s4, 4);
		break;
	case CONSTANT_Float:
		sf4 = htonl(constant->floatValue); 
		_write((void*)&sf4, 4); 
		break; 
	case CONSTANT_String: 
	case CONSTANT_Class:
		u2 = htons(constant->const1->id); 
		_write((void*)&u2, 2); 
		break; 
	case CONSTANT_Fieldref:
	case CONSTANT_Methodref:
	case CONSTANT_NameAndType:
		//first constant's id
		u2 = htons(constant->const1->id); 
		_write((void*)&u2, 2); 
		//second constant's id
		u2 = htons(constant->const2->id);
		_write((void*)&u2, 2); 
		break; 
	}
}

void _write(void* data, int count) {
	int result = write(fh, data, count); 
	if (result < 0) {
		printf("Failed to write data to file\n"); 
	}
}


void generateCodeForMethod(struct Method* method, struct StatementList* stmtList){
}
void generateCodeForVarDecl(struct Method* method, struct VarDecl* varDecl){
}
void generateCodeForVarSpec(struct Method* method, struct VarSpec* varSpec){
}
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl){
}
void generateCodeForConstSpec(struct Method* method, struct ConstSpec* constSpec){
}
void generateCodeForStatementList(struct Method* method, struct StatementList* stmtList){
}
void generateCodeForStatement(struct Method* method, struct Statement* stmt){
}
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt){
}
void generateCodeForIfStmt(struct Method* method, struct IfStmt* ifStmt){
}
void generateCodeForSwitchStmt(struct Method* method, struct SwitchStmt* switchStmt){
}
void generateCodeForForStmt(struct Method* method, struct ForStmt* forStmt){
}
void generateCodeForPrintStmt(struct Method* method, struct PrintStmt* printStmt){
}
void generateCodeForScanStmt(struct Method* method, struct ScanStmt* scanStmt){
}
void generateCodeForExpression(struct Method* method, struct Expression* expr){
}
void generateCodeForPrimaryExpression(struct Method* method, struct PrimaryExpression* primaryExpr){
}

