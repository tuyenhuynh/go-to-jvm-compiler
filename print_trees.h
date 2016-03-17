#ifndef _PRINT_TREE_
#define _PRINT_TREE_
#include "dot.h"
#include "trees.h"
#include "astfunctions.h" 

void print_indent( );
int maxId = 0; 

void print_program(int parentId, struct Program* program);
void print_package(int parentId, struct Package* package);
void print_declaration_list(int parentId, struct DeclarationList* program);
void print_declaration(int parentId, struct Declaration* declaration);
void print_import_statement_list(int parentId, struct ImportStmtList* importStmtList);
void print_import(int parentId, struct Import* import);
void print_var_decl(int parentId, struct VarDecl * varDecl);
void print_const_decl(int parentId, struct ConstDecl * constDecl);
void print_function_decl(int parentId, struct FunctionDecl functionDecl);
void print_identifier_list(int parentId, struct IdentifierList * identifierList);
void print_type_name(int parentId, struct TypeName* typeName);
void print_expression(int parentId, struct Expression* expression);
void print_var_spec(int parentId, struct VarSpec* varSpec);
void print_var_spec_list(int parentId, struct VarSpecList* varSpecList);
void print_statement(int parentId, struct Statement* statement);
void print_simple_stmt(int parentId, struct SimpleStmt* simpleStmt);
void print_return_stmt(int parentId, struct ReturnStmt* returnStmt);
void print_block(int parentId, struct Block* block);
void print_switch_stmt(int parentId, struct SwitchStmt* switchStmt);
void print_if_stmt(int parentId, struct IfStmt* ifStmt);
void print_for_stmt(int parentId, struct ForStmt* forStmt);
void print_if_stmt_expression(int parentId, struct IfStmtExpression* ifStmtExpr);
void print_else_block(int parentId, struct ElseBlock* elseBlock);
void print_stmt_list(int parentId, struct StatementList* stmtList);
void print_switch_body(int parentId, struct SwitchBody* switchBody);
void print_expression_case_clause_list(int parentId, struct ExpressionCaseClauseList* eccl);
void print_expression_case_clause(int parentId, struct ExpressionCaseClause* ecc);
void print_expression_switch_case(int parentId, struct ExpressionSwitchCase* expressionSwitchCase);
void print_for_clause(int parentId, struct ForClause* ForClause);
void print_signature(int parentId, struct Signature* signature);
void print_param_in_paren(int parentId, struct ParamInParen* paramInParen);
void print_param_list(int parentId, struct ParameterList* paramList);
void print_param_declare(int parentId, struct ParameterDeclare* paramDeclare);
void print_result(int parentId, struct Result* result);
void print_primary_expression(int parentId, struct PrimaryExpression* primaryExpr);
void print_function_call(int parentId, struct FunctionCall* functionCall);
void print_switch_initial_expression(int parentId, struct SwitchInitialAndExpression* switchInitialAndExpression);
void print_for_init_stmt(int parentId, struct ForInitStmt* forInitStmt);
void print_for_condition(int parentId, struct ForCondition* forCondition);
void print_for_post_stmt(int parentId, struct ForPostStmt* forPostStmt);
void print_print_stmt(int parentId, struct PrintStatement* printStmt);
void print_scan_stmt(int parentId, struct ScanStatement* scanStmt);



#endif //_PRINT_TREE_