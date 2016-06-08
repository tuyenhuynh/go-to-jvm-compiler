#include "code_generation.h"
// ===== JVM OPCODES

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
FLOAD = 0x17, 
ALOAD = 0x19,
ALOAD_0 = 0x2a,
ISTORE = 0x36,
FSTORE = 0x38, 
ASTORE = 0x3A,
POP = 0x57,
DUP = 0x58,
DUP2 = 0x5C,
IADD = 0x60,
FADD = 0x62,
IMUL = 0x64,
FMUL = 0x6A,
ISUB = 0x68,
FSUB = 0x66,
IDIV = 0x6C,
FDIV = 0x6e,
IINC = 0x84,
FNEG = 0x76,
INEG = 0x74,
IREM = 0x70,
IF_ICMPEQ = 0x9F,
IF_ICMPNE = 0xA0,
IF_ICMPLT = 0xA1,
IF_ICMPLE = 0xA4,
IF_ICMPGT = 0xA3,
IF_ICMPGE = 0xA2,
FCMPG = 0x96,
FCMPL = 0x95,
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
FALOAD = 0x30, 
IASTORE = 0x4F,
AASTORE = 0x53,
FASTORE = 0x51, 
NEW = 0xBB, // create new object 
GETFIELD = 0xB4,
PUTFIELD = 0xB5,
INSTANCE = 0xC1,
INVOKEVIRTUAL = 0xB6,
INVOKESPECIAL = 0xB7,
INVOKESTATIC = 0xB8,
IRETURN = 0xAC,
FRETURN = 0xAE, 
ARETURN = 0xB0,
RETURN = 0xB1
;


void generateCode(struct Program* root){
	program = root;
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

		//major version of jdk 5
		u2 = htons(49);
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
	int accessFlags = ACC_SUPER | ACC_PUBLIC; 
	u2 = htons(accessFlags);
	writeU2();

	//write constants class
	u2 = htons(constantClass->id);
	writeU2();

	//write parent class(Object); 
	u2 = htons(objectClass);
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

	//write methods
	HashTableIter i;
	hashtable_iter_init(&i, methodsTable);
	int size = hashtable_size(methodsTable);
	while (hashtable_iter_has_next(&i)) {
		TableEntry *e;
		hashtable_iter_next(&i, &e);
		struct Method* method = (struct Method*) e->value; 
		writeMethod(method);
	}
}

void writeMethod(struct Method* method) {
	u2 = htons(ACC_PUBLIC);
	writeU2(); 

	//write id of  constant utf8, which contains method's name 
	u2 = htons(method->constMethodref->const2->const1->id);
	writeU2(); 

	//write id of constant utf8, which contains method's description 
	u2 = htons(method->constMethodref->const2->const2->id);
	writeU2(); 

	//method's attribute count
	u2 = htons(1); 
	writeU2(); 

	//write method's attribute table
	//constant utf8's id
	u2 = htons(constantCode->id); 
	writeU2(); 

	//generate code for method
	int codeLength;
	char* code = generateCodeForMethod(method, &codeLength);

	//define length of attribute code
	int attributeCodeLength = 12 + codeLength; 
	u4 = htonl(attributeCodeLength); 
	writeU4(); 
	//stack's size
	u2 = 1000; 
	writeU2(); 
	//local variable count
	int localVarsCount = list_size(method->localVariablesTable)+1; //include variable this(id = 0)
	u2 = htons(localVarsCount); 
	writeU2(); 
	 
	//write method's bytecode size
	u4 = htonl(codeLength);
	writeU4();
	//write bytecode of method
	for (int i = 0; i < codeLength; ++i) {
		u1 = code[i]; 
		writeU1(); 
	}

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

void writeU1ToArray(char* code, int* offset) { 
	code[*offset] = u1;
	*offset += 1; 
}

void writeU2ToArray(char* code, int* offset) {
	unsigned char bytes[2];	
	bytes[0] = (u2 >> 8) & 0xFF;
	bytes[1] = u2 & 0xFF;
	code[*offset] = bytes[0];
	code[*offset + 1] = bytes[1];
	*offset += 2; 
}

void writeU4ToArray(char* code, int* offset) {
	unsigned char bytes[4];
	bytes[0] = (u4 >> 24) & 0xFF;
	bytes[1] = (u4 >> 16) & 0xFF;
	bytes[2] = (u4 >> 8) & 0xFF;
	bytes[3] = u4 & 0xFF;
	code[*offset] = bytes[0];
	code[*offset + 1] = bytes[1];
	code[*offset + 2] = bytes[2]; 
	code[*offset + 3] = bytes[3]; 
	*offset += 4; 
}

void writeS2ToArray(char* code, int* offset) {
	char bytes[2];
	bytes[0] = (u2 >> 8) & 0xFF;
	bytes[1] = u2 & 0xFF;
	code[*offset] = bytes[0];
	code[*offset + 1] = bytes[1];
	*offset += 2; 
}

void writeS4ToArray(char* code, int* offset) {
	char bytes[4];
	bytes[0] = (u4 >> 24) & 0xFF;
	bytes[1] = (u4 >> 16) & 0xFF;
	bytes[2] = (u4 >> 8) & 0xFF;
	bytes[3] = u4 & 0xFF;
	code[*offset] = bytes[0];
	code[*offset + 1] = bytes[1];
	code[*offset + 2] = bytes[2];
	code[*offset + 3] = bytes[3];
	*offset += 4; 
}
void writeSf4ToArray(char* code, int* offset) {
	writeS4ToArray(code, offset); 
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


char* generateCodeForMethod(struct Method* method,int* codeLength){
	char* code = (char*)malloc(2000 * sizeof(char)); 
	int* offset = (int*)malloc(sizeof(int)); 
	*offset = 0; 
	struct Statement* stmt = method->functionDecl->block->stmtList->firstStmt; 
	while (stmt != NULL) {
		generateCodeForStmt(method, stmt, code, offset);
		if (stmt->stmtType != RETURN_STMT) {
			stmt = stmt->nextStatement;
		}
		else {
			stmt = NULL; 
		}
	}
	if (method->returnType->typeName == VOID_TYPE_NAME) {
		u1 = RETURN; 
		writeU1ToArray(code, offset); 
	}
	*codeLength = *offset; 
	return code; 
}

void generateCodeForVarDecl(struct Method* method, struct VarDecl* varDecl, char* code, int* offset){
	bool isOk = true;
	//one line declaration
	if (varDecl->varSpec != NULL) {
		generateCodeForVarSpec(method, varDecl->varSpec, code, offset);
	}
	else {
		//multiline declaration ( in parenthesises)
		struct VarSpec * varSpec = varDecl->varSpecList->firstVarSpec;
		while (varSpec != NULL) {
			generateCodeForVarSpec(method, varSpec, code, offset);
			varSpec = varSpec->nextVarSpec;
		}
	}
}

void generateCodeForVarSpec(struct Method* method, struct VarSpec* varSpec, char* code, int* offset){
	struct Type* type = varSpec->idListType->type; 
	//array declaration
	if (type->expr != NULL) {
		struct SemanticType* semanticType = type->expr->semanticType;
		//allocation new array 
		//generate code to load array size to stack operand 
		generateCodeForExpression(method, type->expr, code, offset); 

		//write instruction 
		if (type->typeName == STRING_TYPE_NAME) {
			u1 = ANEWARRAY; 
			writeU1ToArray(code, offset); 
			struct Constant* classString = addClassToConstantsTable("Ljava/lang/String;");
			u2 = htons(classString->id); 
			writeU2ToArray(code, offset); 
		}
		else {
			u1 = NEWARRAY; 
			writeU1ToArray(code, offset); 
			if (type->typeName == INT_TYPE_NAME) {
				u1 = 10; 
			}
			else if (type->typeName == FLOAT32_TYPE_NAME) {
				u1 = 6; 
			}
			writeU1ToArray(code, offset); 
		}
	}
	else { //none array declaration
		struct IdentifierList* idList = varSpec->idListType->identifierList; 
		struct ExpressionList* exprList = varSpec->exprList; 
		if (exprList != NULL) {//declare and assign values to local variables
			struct Identifier* id = idList->firstId; 
			struct Expression* expr = exprList->firstExpression; 
			while (id != NULL) {
				
				generateCodeForSingleAssignment(method, id->idNum, expr, code, offset); 
				id = id->nextId; 
				expr = expr->nextExpr; 
			}
		}
	}
}
	
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl, char* code, int* offset){
	
}

void generateCodeForConstSpec(struct Method* method, struct ConstSpec* constSpec, char* code, int* offset){
	
}

void generateCodeForStmtList(struct Method* method, struct StatementList* stmtList, char* code, int* offset){
	struct Statement* stmt = stmtList->firstStmt; 
	while (stmt != NULL) {
		generateCodeForStmt(method, stmt, code, offset); 
		stmt = stmt->nextStatement; 
	}
}

void generateCodeForStmt(struct Method* method, struct Statement* stmt, char* code, int* offset){
	switch (stmt->stmtType) {
		case SIMPLE_STMT: {
			generateCodeForSimpleStmt(method, stmt->simpleStmt, code, offset); 
			break; 
		}
		case VAR_DECL_STMT: {
			generateCodeForVarDecl(method, stmt->varDecl, code, offset); 
			break; 
		}
		case CONST_DECL_STMT: {
			generateCodeForConstDecl(method, stmt->constDecl, code, offset); 
			break; 
		}
		case RETURN_STMT: {
			struct ReturnStmt* returnStmt = stmt->returnStmt; 
			if (method->returnType->typeName == VOID_TYPE_NAME) {
				u1 = RETURN; 
				writeU1ToArray(code, offset); 
			}
			else {
				//generate return value 
				generateCodeForExpression(method, returnStmt->exprList->firstExpression, code, offset);
				//write return instruction
				if (method->returnType->arrayType == NONE_ARRAY &&
					method->returnType->typeName != STRING_TYPE_NAME) {
					if (method->returnType->typeName == INT_TYPE_NAME) {
						u1 = IRETURN; 
					}
					else {
						//FLOAT32_TYPE_NAME
						u1 = FRETURN; 
					}
				}
				else {
					u1 = ARETURN; 
				}
				writeU1ToArray(code, offset);
			}

			break; 
		}
		case BREAK_STMT: {
			//TODO: implement this
			break; 
		}
		case CONTINUE_STMT: {
			//TODO: implement this
			break; 
		}
		case BLOCK: {
			//generate code for stmt list
			generateCodeForStmtList(method, stmt->block->stmtList, code, offset); 
			break; 
		}
		case IF_STMT: {
			generateCodeForIfStmt(method, stmt->ifStmt, code, offset); 
			break; 
		}
		case SWITCH_STMT: {
			generateCodeForSwitchStmt(method, stmt->switchStmt, code, offset); 
			break; 
		}
		case FOR_STMT: {
			generateCodeForForStmt(method, stmt->forStmt, code, offset); 
			break; 
		}
		case PRINT_STMT: {
			generateCodeForPrintStmt(method, stmt->printStatement, code, offset); 
			break; 
		}
		case SCAN_STMT: {
			generateCodeForScanStmt(method, stmt->scanStatement, code, offset); 
			break; 
		}			  
	}
}
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt, char* code, int* offset){
	switch (simpleStmt->stmtType) {
		case EXPR_SIMPLE_STMT: {
			generateCodeForExpression(method, simpleStmt->expr, code, offset); 
			break; 
		}
		case INC_SIMPLE_STMT: {
			//TODO: implement situation when operand of this operation is class's field 
			u1 = IINC;
			writeU1(); 
			//get id of variable in local var table 
			u1 = simpleStmt->expr->primaryExpr->semanticType->idNum; 
			writeU1(); 
			//write constant 1 
			u1 = 1; 
			writeU1(); 
			break; 
		}
		case DEC_SIMPLE_STMT: {
			//TODO: implement situation when operand of this operation is class's field 
			u1 = IINC;
			writeU1();
			//get id of variable in local var table 
			u1 = simpleStmt->expr->primaryExpr->semanticType->idNum;
			writeU1();
			//write constant 1 
			u1 = 1;
			writeU1();
			break; 
		}
		case ASSIGN_STMT: {			
			struct Expression* leftExpr = simpleStmt->exprListLeft->firstExpression; 
			struct Expression* rightExpr = simpleStmt->exprListRight->firstExpression; 
			while (leftExpr != NULL) {
				if (leftExpr->exprType == PRIMARY && leftExpr->primaryExpr->exprType == PE_COMPOSITE) {
					//assign value to array element
					generateCodeForArrayElementAssignment(method,
						leftExpr->primaryExpr->primaryExpr, leftExpr->primaryExpr->expr,rightExpr, code, offset); 
				}
				else {
					generateCodeForSingleAssignment(method, leftExpr->primaryExpr->semanticType->idNum, rightExpr, code, offset);
				}
				leftExpr = leftExpr->nextExpr; 
				rightExpr = rightExpr->nextExpr; 
			} 
			break; 
		}
		default: {
			// other type of assignment statements currently not supported
		}
	}
}

void generateCodeForSingleAssignment(struct Method*  method, int localVarId, struct Expression* expr, char* code, int* offset) {
	//generate code for right expression
	generateCodeForExpression(method, expr, code, offset);

	//store value on top of stack to local variable
	//TODO: generate code id is field, not local variable
	switch (expr->semanticType->typeName) {
		case INT_TYPE_NAME: {
			u1 = ISTORE;
			break;
		}
		case FLOAT32_TYPE_NAME: {
			u1 = FSTORE;
			break;
		}
		case STRING_TYPE_NAME: {
			u1 = ASTORE;
			break;
		}
	}
	writeU1ToArray(code, offset);
	//id of local variable
	u1 = localVarId; 
	writeU1ToArray(code, offset);
}

void generateCodeForArrayElementAssignment(struct Method*  method, 
	struct PrimaryExpression* arrayExpr, struct Expression* indexExpr , struct Expression* expr, char* code, int* offset) {
	//TODO: generate code id is field, not local variable
	
	//gen code to load array reference to stack operand
	u1 = ALOAD; 
	writeU1ToArray(code, offset); 
	u1 = arrayExpr->semanticType->idNum; 
	writeU1ToArray(code, offset); 

	//gen code to define array index ; 
	generateCodeForExpression(method, indexExpr, code, offset); 

	//generate code for right expression
	generateCodeForExpression(method, expr, code, offset);

	//store value on top of stack to local variable
	switch (expr->semanticType->typeName) {
		case INT_TYPE_NAME: {
			u1 = IASTORE;
			break;
		}
		case FLOAT32_TYPE_NAME: {
			u1 = FASTORE;
			break;
		}
		case STRING_TYPE_NAME: {
			u1 = AASTORE;
			break;
		}
	}
	writeU1ToArray(code, offset);
}


void generateCodeForIfStmt(struct Method* method, struct IfStmt* ifStmt, char* code, int* offset){

	//generate code for condition-expression of if stmt
	//if type if statement; expression is eliminated in semantic checking
	generateCodeForExpression(method, ifStmt->ifStmtExpr->expr, code, offset); 
	int ifeqPos = strlen(code); 
	//write command ifeq
	u1 = IFEQ; 
	writeU1(); 
	//define and value of displacement
	/*
	TODO: WHAT THE HELL TO DO WITH THIS ????
	save address of command ifeq to specify length of jump operand later;*/

	//generate code for block if condition is correct
	generateCodeForStmtList(method, ifStmt->block->stmtList, code, offset);
	
	if (ifStmt->elseBlock == NULL) {
		//TODO:
		//gen operator goto and save it address for future process

	}
	//TODO: implement else if
	if (ifStmt->elseBlock != NULL) {
		generateCodeForStmtList(method, ifStmt->elseBlock->block->stmtList, code, offset); 
		//
	}

	//save address of command ALREADY DONE ???

	
	if (ifStmt->elseBlock != NULL)
	{
		if (ifStmt->elseBlock->ifStmt != NULL)
		{
			generateCodeForIfStmt(method, ifStmt->elseBlock->ifStmt, code, offset);
		}
		generateCodeForStmtList(method, ifStmt->elseBlock->block->stmtList, code, offset);
	}
}

void generateCodeForSwitchStmt(struct Method* method, struct SwitchStmt* switchStmt, char* code, int* offset){
		
}
void generateCodeForForStmt(struct Method* method, struct ForStmt* forStmt, char* code, int* offset){

}
void generateCodeForPrintStmt(struct Method* method, struct PrintStatement* printStmt, char* code, int* offset){

}
void generateCodeForScanStmt(struct Method* method, struct ScanStatement* scanStmt, char* code, int* offset){
		
}

//totally 13 types of expression supported 
void generateCodeForExpression(struct Method* method, struct Expression* expr, char* code, int* offset){
	switch (expr->exprType) {
		case PRIMARY: {
			generateCodeForPrimaryExpression(method, expr->primaryExpr, code, offset);
			break; 
		}
		case PLUS_UNARY_EXPR: {
			generateCodeForPrimaryExpression(method, expr->primaryExpr, code, offset); // for right expression or for left or for primary expression?
			break; 
		}
		case MINUS_UNARY_EXPR : {
			generateCodeForPrimaryExpression(method, expr->primaryExpr, code, offset); // for right expression or for left or for primary expression?
			if (expr->primaryExpr->exprType == FLOAT_EXPR)
			{
				u1 = FNEG;
			}
			else if (expr->primaryExpr->exprType == DECIMAL_EXPR)
			{
				u1 = INEG;
			}
			writeU1ToArray(code, offset);
			break; 
		}
		case EQU_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code, offset); 
			generateCodeForExpression(method, expr->rightExpr, code, offset);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				// TODO Need to store byte offset to jump on if condition is true or false
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPEQ;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case NE_EXPRESSION: {
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
			// TODO

			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPNE;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case GT_EXPRESSION: {
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				// TODO
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPGT;
			}
			writeU1ToArray(code, offset);
			break; 
		}
		case GTE_EXPRESSION: {
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				// TODO
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPGE;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case LT_EXPRESSION: {
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				// TODO
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPLT;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case LTE_EXPRESSION: {
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				// TODO
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPLE;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case PLUS_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code, offset); // load left expr to stack
			generateCodeForExpression(method, expr->rightExpr, code, offset); // load right expr to stack
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR) // perform operations
			{
				u1 = FADD;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IADD;
			}
			else if (expr->leftExpr->exprType == STRING_EXPR && expr->rightExpr->exprType == STRING_EXPR)
			{
				// TODO
			}
			writeU1ToArray(code, offset);
			break;
		}
		case MINUS_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code, offset);
			generateCodeForExpression(method, expr->rightExpr, code, offset);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				u1 = FSUB;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = ISUB;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case MUL_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code, offset);
			generateCodeForExpression(method, expr->rightExpr, code, offset);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				u1 = FMUL;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IMUL;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case DIV_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code, offset);
			generateCodeForExpression(method, expr->rightExpr, code, offset);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				u1 = FDIV;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IDIV;
			}
			writeU1ToArray(code, offset);
			break;
		}
		case MOD_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code, offset);
			generateCodeForExpression(method, expr->rightExpr, code, offset);
			u1 = IREM;
			writeU1ToArray(code, offset);
			break;
		}
		default: {
			//some expressions are currently unsupported
		}
	}	
}

void generateCodeForPrimaryExpression(struct Method* method, struct PrimaryExpression* primaryExpr, char* code, int* offset){
	switch (primaryExpr->exprType) {
		case DECIMAL_EXPR:
		case FLOAT_EXPR:
		case STRING_EXPR: {
			//write instruction LDC (to load int/float/string reference) 
			u1 = LDC; 
			writeU1ToArray(code, offset); 
			//get id of constant int/float/string reference from constants table
			u1 = primaryExpr->semanticType->constantExpressionNum; 
			writeU1ToArray(code, offset); 
			break;
		}
		case ID_EXPRESSION: {
			//TODO: implementation loading field if ID_EXPRESSION is class's field
			switch (primaryExpr->semanticType->typeName) {
				case INT_TYPE_NAME: {
					//write command
					u1 = ILOAD;
					break; 
				}
				case FLOAT32_TYPE_NAME: {
					//write command
					u1 = FLOAD;
					break; 
				}
				case STRING_TYPE_NAME: {
					//write command
					u1 = ALOAD;
					break; 
				}
			} 
			//write load instruction
			writeU1ToArray(code, offset);
			//write the id number of id_expression from local var table
			u1 = primaryExpr->semanticType->idNum;
			writeU1ToArray(code, offset);
			break;
		}
		case PE_COMPOSITE: {
			//gen code to load array reference to stack operand
			//load array reference to stack operand
			u1 = ALOAD; 
			writeU1ToArray(code, offset);
			u1 = primaryExpr->primaryExpr->semanticType->idNum; 
			writeU1ToArray(code, offset); 

			//generate code to define index 
			generateCodeForExpression(method, primaryExpr->expr, code, offset); 
			switch (primaryExpr->semanticType->typeName) {
				case INT_TYPE_NAME: {
					u1 = IALOAD; 
					break; 
				}
				case FLOAT32_TYPE_NAME: {
					u1 = FALOAD; 
				}
				default: {
					u1 = AALOAD; 
				}
			}
			
			//write command
			writeU1ToArray(code, offset); 
			break;
		}
		case FUNCTION_CALL: {
			//load referece to object of called method
			u1 = ALOAD_0; 
			writeU1ToArray(code, offset); 
			//write arguments
			struct Expression* expr = primaryExpr->funcCall->exprList->firstExpression; 
			while (expr != NULL) {
				generateCodeForExpression(method, expr, code, offset); 
				expr = expr->nextExpr; 
			}
			//
			u1 = INVOKESPECIAL; 
			writeU1ToArray(code, offset); 
			//find constant method ref from constants table
			struct Method*  method = getMethod(primaryExpr->funcCall->primaryExpr->identifier); 
			//write id of constant method ref
			u2 = htons(method->constMethodref->id);
			writeU2ToArray(code, offset); 
			break;
		}
		case EXPRESSION: {
			//nested expression (by parenthesies)
			generateCodeForExpression(method, primaryExpr->expr, code, offset); 
			break;
		}
		default: {
			//true/false expressions not supported
		}
	}
}

