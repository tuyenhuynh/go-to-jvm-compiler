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
ALOAD = 0x19,
ALOAD_0 = 0x2a, 
ISTORE = 0x36,
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
ARETURN = 0xB0,
RETURN = 0xB1
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
				expr = expr->nextExpr; 
			}
		}
	}
}
	
void generateCodeForConstDecl(struct Method* method, struct ConstDecl* constDecl, char* code){
	
}

void generateCodeForConstSpec(struct Method* method, struct ConstSpec* constSpec, char* code){
	
}

void generateCodeForStmtList(struct Method* method, struct StatementList* stmtList, char* code){
	struct Statement* stmt = stmtList->firstStmt; 
	while (stmt != NULL) {
		generateCodeForStmt(method, stmt, code); 
		stmt = stmt->nextStatement; 
	}
}

void generateCodeForStmt(struct Method* method, struct Statement* stmt, char* code){
	switch (stmt->stmtType) {
		case SIMPLE_STMT: {
			generateCodeForSimpleStmt(method, stmt->simpleStmt, code); 
			break; 
		}
		case VAR_DECL_STMT: {
			generateCodeForVarDecl(method, stmt->varDecl, code); 
			break; 
		}
		case CONST_DECL_STMT: {
			generateCodeForConstDecl(method, stmt->constDecl, code); 
			break; 
		}
		case RETURN_STMT: {
			struct ReturnStmt* returnStmt = stmt->returnStmt; 
			//TODO: generate code for this statement
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
			generateCodeForStmtList(method, stmt->block->stmtList, code); 
			break; 
		}
		case IF_STMT: {
			generateCodeForIfStmt(method, stmt->ifStmt, method); 
			break; 
		}
		case SWITCH_STMT: {
			generateCodeForSwitchStmt(method, stmt->switchStmt, method); 
			break; 
		}
		case FOR_STMT: {
			generateCodeForForStmt(method, stmt->forStmt, method); 
			break; 
		}
		case PRINT_STMT: {
			generateCodeForPrintStmt(method, stmt->printStatement, method); 
			break; 
		}
		case SCAN_STMT: {
			generateCodeForScanStmt(method, stmt->scanStatement, method); 
			break; 
		}			  
	}
}
void generateCodeForSimpleStmt(struct Method* method, struct SimpleStmt*  simpleStmt, char* code){
	switch (simpleStmt->stmtType) {
		case EXPR_SIMPLE_STMT: {
			generateCodeForExpression(method, simpleStmt->expr, code); 
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
				generateCodeForSingleAssignment(method, leftExpr->primaryExpr->identifier, rightExpr, code);
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


void generateCodeForSingleAssignment(struct Method*  method, struct Identifier* id, struct Expression* expr, char* code) {
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

//totally 13 types of expression supported 
void generateCodeForExpression(struct Method* method, struct Expression* expr, char* code){
	switch (expr->exprType) {
		case PRIMARY: {
			generateCodeForPrimaryExpression(method, expr->primaryExpr, code);
			break; 
		}
		case PLUS_UNARY_EXPR: {
			generateCodeForExpression(method, expr->primaryExpr->expr, code); // for right expression or for left or for primary expression?
			break; 
		}
		case MINUS_UNARY_EXPR : {
			generateCodeForExpression(method, expr->primaryExpr->expr, code); // for right expression or for left or for primary expression?
			if (expr->rightExpr->primaryExpr->expr->exprType == FLOAT_EXPR)
			{
				u1 = FNEG;
			}
			else if (expr->rightExpr->primaryExpr->expr->exprType == DECIMAL_EXPR)
			{
				u1 = INEG;
			}
			writeU1();
			break; 
		}
		case EQU_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code); 
			generateCodeForExpression(method, expr->rightExpr, code);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				// TODO Need to store byte offset to jump on if condition is true or false
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IF_ICMPEQ;
			}
			writeU1();
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
			writeU1();
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
			writeU1();
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
			writeU1();
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
			writeU1();
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
			writeU1();
			break;
		}
		case PLUS_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code); // load left expr to stack
			generateCodeForExpression(method, expr->rightExpr, code); // load right expr to stack
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
			writeU1();
			break;
		}
		case MINUS_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code);
			generateCodeForExpression(method, expr->rightExpr, code);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				u1 = FSUB;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = ISUB;
			}
			writeU1();
			break;
		}
		case MUL_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code);
			generateCodeForExpression(method, expr->rightExpr, code);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				u1 = FMUL;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IMUL;
			}
			writeU1();
			break;
		}
		case DIV_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code);
			generateCodeForExpression(method, expr->rightExpr, code);
			if (expr->leftExpr->exprType == FLOAT_EXPR && expr->rightExpr->exprType == FLOAT_EXPR)
			{
				u1 = FDIV;
			}
			else if (expr->leftExpr->exprType == DECIMAL_EXPR && expr->rightExpr->exprType == DECIMAL_EXPR)
			{
				u1 = IDIV;
			}
			writeU1();
			break;
		}
		case MOD_EXPRESSION: {
			generateCodeForExpression(method, expr->leftExpr, code);
			generateCodeForExpression(method, expr->rightExpr, code);
			u1 = IREM;
			writeU1();
			break;
		}
		default: {
			//some expressions are currently unsupported
		}
	}
	
}

void generateCodeForPrimaryExpression(struct Method* method, struct PrimaryExpression* primaryExpr, char* code){
	switch (primaryExpr->exprType) {
		case DECIMAL_EXPR:
		case FLOAT_EXPR: {
			//write command
			u1 = LDC_W; 
			writeU1(); 
			//write constant id number
			u2 = htons(primaryExpr->semanticType->constantExpressionNum); 
			writeU2(); 
			break;
		}
		case STRING_EXPR: {
			//TODO: verify this
			//load constant String from constants table 
			u1 = ALOAD; 
			writeU1(); 
			//get id of string in constants table
			u1 = primaryExpr->semanticType->constantExpressionNum; 
			writeU1(); 
			break;
		}
		case ID_EXPRESSION: {
			//TODO: implementation loading field if ID_EXPRESSION is class's field

			//write command
			u1 = ILOAD; 
			writeU1(); 
			//write the id number of id_expression from local var table
			u1 = primaryExpr->semanticType->idNum; 
			writeU1(); 
			break;
		}
		case PE_COMPOSITE: {
			//write command
			u1 = ALOAD; 
			writeU1(); 
			//write array 's id 
			u1 = primaryExpr->primaryExpr->semanticType->idNum; 
			writeU1(); 
			//write index of array's element using enerateCodeForExpression
			generateCodeForExpression(method, primaryExpr->expr, code); 
			//write load command to load element to stack's top
			switch (primaryExpr->semanticType->typeName) {
				case INT_TYPE_NAME: {
					u1 = IALOAD;
					break;
				}case FLOAT32_TYPE_NAME: {
					u1 = FALOAD; 
					break; 
				}case STRING_TYPE_NAME: {
					//TODO: implement situation when array type is string
					break; 
				}
			}
			writeU1();
			break;
		}
		case FUNCTION_CALL: {
			//load referece to object of called method
			u1 = ALOAD_0; 
			writeU1(); 
			//write arguments
			struct Expression* expr = primaryExpr->funcCall->exprList->firstExpression; 
			while (expr != NULL) {
				generateCodeForExpression(method, expr, code); 
				expr = expr->nextExpr; 
			}
			//
			u1 = INVOKESPECIAL; 
			writeU1(); 
			//find constant method ref from constants table
			struct Method*  method = getMethod(primaryExpr->funcCall->primaryExpr->identifier); 
			//write id of constant method ref
			u2 = htons(method->constMethodref->id);
			writeU2(); 
			break;
		}
		case EXPRESSION: {
			//nested expression (by parenthesies)
			generateCodeForExpression(method, primaryExpr->expr, code); 
			break;
		}
		default: {
			//true/false expressions not supported
		}
	}
}

