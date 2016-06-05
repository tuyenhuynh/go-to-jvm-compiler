#include "code_generation.h"
struct Program* program; 
unsigned short
ICONST_M1 = 0x2, // REMOVE THIS (SIGNED) 
ICONST_0 = 0x3,
ICONST_1 = 0x4,
ICONST_2 = 0x5,
ICONST_3 = 0x6,
ICONST_4 = 0x7,
ICONST_5 = 0x8,
BIPUSH = 0x10,
SIPUSH = 0x11,
LDC = 0x12,
LDC_W = 0x13,
ILOAD = 0x15,
ALOAD = 0x19,
ISTORE = 0x36,
ASTORE = 0x3A,
POP = 0x57,
DUP = 0x58,
DUP2 = 0x5C,
IADD = 0x60,
IMUL = 0x64,
ISUB = 0x68,
IDIV = 0x6C,
IINC = 0x84,
IF_ICMPEQ = 0x9F,
IF_ICMPNE = 0xA0,
IF_ICMPLT = 0xA1,
IF_ICMPLE = 0xA4,
IF_ICMPGT = 0xA3,
IF_ICMPGE = 0xA2,
IFEQ = 0x99,
IFNE = 0x9A,
IFLT = 0x55,
IFLE = 0x9E,
IFGT = 0x9D,
IFGE = 0x9C,
IF_ACMPEQ = 0xA5,
IF_ACMPNE = 0xA6,
GOTO = 0xA7,
TABLESWITCH = 0xAA,
LOOKUPSWITCH = 0xAB,
NEWARRAY = 0xBC,
T_BOOLEAN = 4,
T_CHAR = 5,
T_FLOAT = 6,
T_DOUBLE = 7,
T_BYTE = 8,
T_SHORT = 9,
T_INT = 10,
T_LONG = 11,
ANEWARRAY = 0xBD,
ARRAY_LENGTH = 0xBE,
IALOAD = 0x2E,
AALOAD = 0x32,
IASTORE = 0x4F,
AASTORE = 0x53,
NEW = 0xBB, // create new object 
GETFIELD = 0xB4,
PUTFIELD = 0xB5,
INSTANCE = 0xC1,
INVOKEVIRTUAL = 0xB6,
INVOKESPECIAL = 0xB7,
INVOKESTATIC = 0xB8,
IRETURN = 0xAC,
ARETURN = 0xB0,
RETURN = 0xB1
; 




; 
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
	program = root; 
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
	bool isOk = true;
	//one line declaration
	if (varDecl->varSpec != NULL) {
		generateCodeForVarSpec(method, varDecl->varSpec, code);
	}
	else {
		//multiline declaration ( in parenthesises)
		struct VarSpec * varSpec = varDecl->varSpecList->firstVarSpec;
		while (varSpec != NULL) {
			generateCodeForVarSpec(method, varSpec, code);
			varSpec = varSpec->nextVarSpec;
		}
	}
}

void generateCodeForVarSpec(struct Method* method, struct VarSpec* varSpec, char* code){
	//array declaration
	if (varSpec->idListType->type->expr != NULL) {
		struct SemanticType* semanticType = varSpec->idListType->type->expr->semanticType; 
		//TODO: implement this


	}
	else { //none array declaration
		struct IdentifierList* idList = varSpec->idListType->identifierList; 
		struct ExpressionList* exprList = varSpec->exprList; 
		if (exprList != NULL) {//declare and assign values to local variables
			struct Identifier* id = idList->firstId; 
			struct Expression* expr = exprList->firstExpression; 
			while (id != NULL) {
				
				id = id->nextId; 
			}
		}
	}
}
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl, char* code){
}
void generateCodeForConstSpec(struct Method* method, struct ConstSpec* constSpec, char* code){
}
void generateCodeForStmtList(struct Method* method, struct StatementList* stmtList, char* code){
}
void generateCodeForStmt(struct Method* method, struct Statement* stmt, char* code){
	
}
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt, char* code){
	
}


void generateCodeForAssignment(struct Method*  method, struct Identifier* id, struct Expression* expr, char* code) {
	//generate code for right expression
	//INCLUDE LOADING value to stack ???
	generateCodeForExpression(method, expr, code); 
	
	//load value on top of stack to local variable
	//TODO: generate code id is field, not local variable
	switch (expr->semanticType->typeName) {
		case INT_TYPE_NAME:
		case FLOAT32_TYPE_NAME:{
			u1 = ISTORE; 
			writeU1(); 
			u1 = id->idNum; 
			writeU1(); 
			break; 
		}
		case STRING_TYPE_NAME: {
			//TODO: impelement this	
			break; 
		}
	}
}

void generateCodeForIfStmt(struct Method* method, struct IfStmt* ifStmt, char* code){

	if (ifStmt->ifStmtExpr->simpleStmt != NULL)
	{
		generateCodeForSimpleStmt(method, ifStmt->ifStmtExpr->simpleStmt, code);
		
	}
	else if(ifStmt->ifStmtExpr->expr != NULL)
	{
		generateCodeForExpression(method, ifStmt->ifStmtExpr->expr, code);
	}
	
	generateCodeForStmtList(method, ifStmt->block->stmtList, code);

	if (ifStmt->elseBlock != NULL)
	{
		if (ifStmt->elseBlock->ifStmt != NULL)
		{
			generateCodeForIfStmt(method, ifStmt->elseBlock->ifStmt, code);
		}
		generateCodeForStmtList(method, ifStmt->elseBlock->block->stmtList, code);
	}
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

