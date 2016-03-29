#ifndef _SEMANTIC_STRUCT_H_
#define _SEMANTIC_STRUCT_H_
#include "hashtable.h"
#include "list.h"

enum ConstantType {
	CONSTANT_Utf8 = 1,
	CONSTANT_Integer = 3,
	CONSTANT_Float = 4,
	CONSTANT_String = 8,
	CONSTANT_NameAndType = 12,
	CONSTANT_Class = 7,
	CONSTANT_Fieldref = 9,
	CONSTANT_Methodref = 10
};

struct Constant {
	enum ConstantType type;
	union {
		int intValue;
		float floatValue;
		char* utf8;
		struct {
			int classId; 
			int methodId; 
		}methodRef;
	}value;
	int id; 
	 
};


struct LocalVariable {
	int id; 
	struct Type* type; 
};

struct Field {
	struct Constant* constFieldref; 
	struct SemanticType* type; 
};

struct Method {
	//method name, because class is unique
	struct Constant* constMethodref;
	//key: varname, value : LocalVariable
	HashTable* localVariablesTable; 
};

struct Class {
	struct Constant* className; 
	//node of list : struct Constant*
	List* constantsTable; 
	//key: char*, value: Field*; 
	HashTable* fieldsTable; 
	//key: char*, value: struct Method* ; 
	HashTable* methodsTable; 

};



#endif //_SEMANTIC_STRUCT_H_