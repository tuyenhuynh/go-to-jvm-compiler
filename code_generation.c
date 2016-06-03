#include "code_generation.h"
struct Program* program; 

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
		writeU4();

		//minor version
		u2 = htons(0); 
		writeU2();

		//major version
		u2 = htons(53);
		writeU2();

		writeConstantsTable(); 

		writeClassMetadata(); 
		
		writeFieldsTable(); 

		writeMethodsTable(); 

		//write number of class's attributes(usally 0)
		u2 = 0; 
		writeU2(); 
		//write class's attributes(nothing to do)
		
	}
	program = root; 
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
	
	//generate and write method's bytecode 
	struct FunctionDecl* functionDecl = findFuncionDeclByName(program, method->constMethodref->const2->const1->utf8); 
	char* code = generateCodeForMethod(method, functionDecl->block->stmtList); 
	//define method's bytecode size
	u4 = htons(strlen(code));
	writeU4();
	//write bytecode of method
	writeString(code); 

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


char* generateCodeForMethod(struct Method* method, struct StatementList* stmtList){
	char* code = (char*)malloc(1000 * sizeof(char)); 
	struct Statement* stmt = stmtList->firstStmt; 
	while (stmt != NULL) {
		generateCodeForStmt(method, stmt, code); 
		stmt = stmt->nextStatement; 
	}
	return code; 
}
void generateCodeForVarDecl(struct Method* method, struct VarDecl* varDecl, char* code){
}
void generateCodeForVarSpec(struct Method* method, struct VarSpec* varSpec, char* code){
}
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl, char* code){
}
void generateCodeForConstSpec(struct Method* method, struct ConstSpec* constSpec, char* code){
}
void generateCodeForStmtList(struct Method* method, struct StatementList* stmtList, char* code){
}
void generateCodeForStatement(struct Method* method, struct Statement* stmt, char* code){
}
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt, char* code){
}
void generateCodeForIfStmt(struct Method* method, struct IfStmt* ifStmt, char* code){
}
void generateCodeForSwitchStmt(struct Method* method, struct SwitchStmt* switchStmt, char* code){
}
void generateCodeForForStmt(struct Method* method, struct ForStmt* forStmt, char* code){
}
void generateCodeForPrintStmt(struct Method* method, struct PrintStmt* printStmt, char* code){
}
void generateCodeForScanStmt(struct Method* method, struct ScanStmt* scanStmt, char* code){
}
void generateCodeForExpression(struct Method* method, struct Expression* expr, char* code){
}
void generateCodeForPrimaryExpression(struct Method* method, struct PrimaryExpression* primaryExpr, char* code){
}

