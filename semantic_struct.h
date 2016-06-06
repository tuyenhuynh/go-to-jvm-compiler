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
	int intValue; 
	float floatValue; 
	char* utf8; 
	int id; 
	//constant for class name, in case method references or field references
	struct Constant* const1; 
	//constant type name and type, in case method references or field references
	struct Constant* const2;  
};

struct LocalVariable {
	int id; 
	struct SemanticType* semanticType; 
	char* name; 
	int scope; 
	bool isActive; 
	bool isMutable; 
};

struct Field {
	struct Constant* constFieldref; 
	struct SemanticType* type;
	int id; 
	bool isMutable; 
};

struct Method {
	//method name, because class is unique
	struct Constant* constMethodref;
	//key: varname, value : LocalVariable
	struct SemanticType* returnType; 
	List* localVariablesTable; 
	struct ParameterList* paramList; 
	struct FunctionDecl* functionDecl; 
};

struct Class {
	char* className; 
	//node of list : struct Constant*
	List* constantsTable; 
	//key: char*, value: Field*; 
	HashTable* fieldsTable; 
	//key: char*, value: struct Method* ; 
	HashTable* methodsTable; 
};



#endif //_SEMANTIC_STRUCT_H_