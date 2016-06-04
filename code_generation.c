#include "code_generation.h"


void generateCode(struct Program* root){
	// 0200 user can only write file
	if ((fh = open(classFileName, O_BINARY | O_WRONLY | O_TRUNC | O_CREAT, 0200)) == -1) {
		freopen("CON", "w", stdout); 
		printf("Failed to open class file\n"); 
		return; 
	}
	else {
		//magic number
		u4 = htonl(0xCAFEBABE);
		writeU4();

		//minor version
		u2 = htons(0); 
		writeU2();

		//major version
		u2 = htons(53);
		writeU2();

		writeConstantsTable(); 

		writeClassMetadata(); 
		
		//writeFieldsTable(); TODO

		//writeMethodsTable(); TODO

		//write number of class's attributes(usally 0)
		u2 = 0; 
		writeU2(); 
		//write class's attributes(nothing to do)
		
	}
	close(fh);
	
}

void writeConstantsTable() {
	//constant's size +1
	int constantCount = list_size(constantsTable);
	u2 = htons(constantCount + 1);
	writeU2();

	//constants
	struct Constant* constant = NULL;
	for (int i = 0; i < constantCount; ++i) {
		list_get_at(constantsTable, i, &constant);
		writeConstant(constant);
	}
}

void writeClassMetadata() {
	//access flags 
	u2 = htons(ACC_SUPER);
	writeU2();

	//write constants class
	u2 = htons(constantClass->id);
	writeU2();

	//write parent class(Object); 
	u2 = 0;
	writeU2();

	//number of interface
	u2 = 0;
	writeU2();

	//write interfaces (nothing to write =)) )
}

void writeFieldsTable() {
	//write number of field 
	int fieldCount = hashtable_size(fieldsTable);
	u2 = htons(fieldCount);
	writeU2(); 

	//write field table 
	HashTableIter i;
	hashtable_iter_init(&i, fieldsTable);
	while (hashtable_iter_has_next(&i)) {
		TableEntry *e;
		hashtable_iter_next(&i, &e);
		struct  Field* field = (struct Field*)e;
		writeField(field); 
	}
}


//not very sure. this function need to be tested
void writeField(struct Field* field) {
	//write access flag
	u2 = htons(ACC_PUBLIC); 
	writeU2(); 
	
	//write number of CONSTANT_utf8, which contains field's name
	char* fieldName = field->constFieldref->const2->const1->utf8; 
	struct Constant* constant = getConstantUtf8(fieldName); 
	u2 = htons(constant->id); 
	writeU2(); 

	//write numbef of CONSTANT_utf8, which contains field's description (aka field's type)
	char* fieldDescription = field->constFieldref->const2->const2->utf8; 
	constant = getConstantUtf8(fieldDescription); 
	u2 = htons(constant->id); 
	writeU2(); 

	//write number of field's attribue
	u2 = 0; 
	writeU2(); 

	//write attribute's description(nothing to write, as usually)

}

void writeMethodsTable() {
	int methodCount = hashtable_size(methodsTable);
	u2 = htons(methodCount);
	writeU2();
	
	//add Code constants table
	constantCode = addUtf8ToConstantsTable("Code"); 
	
	
	//write methods
	HashTableIter i;
	hashtable_iter_init(&i, methodsTable);
	while (hashtable_iter_has_next(&i)) {
		TableEntry *e;
		hashtable_iter_next(&i, &e);
		struct Method* method = (struct Method*) e; 
		writeMethod(method);
	}

	/*
	struct DeclarationList* declList = root->declList;
	struct Declaration* decl = declList->firstDecl;
	while (decl != NULL) {
		if (decl->declType == FUNC_DECL) {
			struct Method* method = getMethod(decl->funcDecl->identifier);
			generateCodeForMethod(method, decl->funcDecl->block->stmtList);
		}
		decl = decl->nextDecl;
	}*/

}

void writeMethod(struct Method* method) {
	u2 = htons(ACC_PUBLIC);
	writeU2(); 

	//write id of  constant utf8, which contains method's name
	struct Constant* constant = getConstantUtf8(method->constMethodref->const2->const1->utf8); 
	u2 = htons(constant->id);
	writeU2(); 

	//write id of constant utf8, which contains method's description 
	constant = getConstantUtf8(method->constMethodref->const2->const2->utf8); 
	u2 = htons(constant->id); 
	writeU2(); 

	//method's attribute count
	u2 = htons(1); 
	writeU2(); 

	//write method's attribute table
	//constant utf8's id
	u2 = htons(constantCode->id); 
	writeU2(); 
	//attribute's length
	//TODO: find the value of u4
	u4 = htons(0); 
	writeU4(); 
	//stack's size
	u2 = 1000; 
	writeU2(); 
	//local variable count
	int localVarsCount = list_size(method->localVariablesTable); 
	u2 = htons(localVarsCount); 
	writeU2(); 
	//TODO: define method's bytecode size
	u4 = htons(0); 
	writeU4();
	//TODO: generate and write method's bytecode 

	//write number of exception
	u2 = htons(0); 
	writeU2(); 
	//write exception table(no exception)

	//write number of attribute's attribute
	u2 = htons(0); 
	writeU2(); 
	
}

void writeString(char* str) {
	Write((void*)str, strlen(str)); 
}

void writeU1() {
	Write((void*)&u1, 1); 
}

void writeU2() {
	Write((void*)&u2, 2);	
}

void writeU4() {
	Write((void*)&u4, 4);
}

void writeS2() {
	Write((void*)&s2, 2);
}

void writeS4() {
	Write((void*)&s4, 4);
}

void writeSf4() {
	Write((void*)&sf4, 4);
}

void writeConstant(struct Constant* constant) {
	u1 = constant->type; 
	Write((void*)&u1, 1); 
	int length; 
	switch (constant->type) {
	case CONSTANT_Utf8:
		length = strlen(constant->utf8);
		u2 = htons(length);
		//length
		Write((void*)&u2, 2);
		//data
		Write((void*)constant->utf8, length);
		break; 
	case CONSTANT_Integer:
		s4 = htonl(constant->intValue);
		Write((void*)&s4, 4);
		break;
	case CONSTANT_Float:
		sf4 = htonl(constant->floatValue); 
		Write((void*)&sf4, 4); 
		break; 
	case CONSTANT_String: 
	case CONSTANT_Class:
		u2 = htons(constant->const1->id); 
		Write((void*)&u2, 2); 
		break; 
	case CONSTANT_Fieldref:
	case CONSTANT_Methodref:
	case CONSTANT_NameAndType:
		//first constant's id
		u2 = htons(constant->const1->id); 
		Write((void*)&u2, 2); 
		//second constant's id
		u2 = htons(constant->const2->id);
		Write((void*)&u2, 2); 
		break; 
	}
}

void Write(void* data, int count) {
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

	if (ifStmt->ifStmtExpr->simpleStmt != NULL)
	{
		generateCodeForSimpleStmt(method, ifStmt->ifStmtExpr->simpleStmt);
		
	}
	else if(ifStmt->ifStmtExpr->expr != NULL)
	{
		generateCodeForExpression(method, ifStmt->ifStmtExpr->expr);
	}
	
	generateCodeForBlock(method, ifStmt->block);

	if (ifStmt->elseBlock != NULL)
	{
		if (ifStmt->elseBlock->ifStmt != NULL)
		{
			generateCodeForIfStmt(method, ifStmt->elseBlock->ifStmt);
		}
		generateCodeForBlock(ifStmt->elseBlock->block);
	}

}

void generateCodeForBlock(struct Method* method, struct Block* block){

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

