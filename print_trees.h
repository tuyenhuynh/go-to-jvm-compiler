#ifndef _PRINT_TREE_
#define _PRINT_TREE_

#include "trees.h"
#include "astfunctions.h" 

void print_indent();
int level = 0; 

void print_program(struct Program* program);
void print_package(struct Package* package);
void print_declaration_list(struct DeclarationList* program);
void print_declaration(struct Declaration* declaration);
void print_import_statement_list(struct ImportStmtList* importStmtList);
void print_import(struct Import* import);
void print_var_decl(struct VarDecl * varDecl);
void print_const_decl(struct ConstDecl * constDecl);
void print_function_decl(struct FunctionDecl functionDecl);
void print_identifier_list(struct IdentifierList * identifierList);
void print_type_name(struct TypeName* typeName);
void print_expression(struct Expression* expression);
void print_var_spec(struct VarSpec* varSpec);
void print_var_spec_list(struct VarSpecList* varSpecList);
void print_statement(struct Statement* statement);
void print_simple_stmt(struct SimpleStmt* simpleStmt);
void print_return_stmt(struct ReturnStmt* returnStmt);
void print_block(struct Block* block);
void print_switch_stmt(struct SwitchStmt* switchStmt);
void print_if_stmt(struct IfStmt* ifStmt);
void print_for_stmt(struct ForStmt* forStmt);
void print_if_stmt_expression(struct IfStmtExpression* ifStmtExpr);
void print_else_block(struct ElseBlock* elseBlock);
void print_stmt_list(struct StatementList* stmtList);
void print_switch_body(struct SwitchBody* switchBody);
void print_expression_case_clause_list(struct ExpressionCaseClauseList* eccl);
void print_expression_case_clause(struct ExpressionCaseClause* ecc);
void print_expression_switch_case(struct ExpressionSwitchCase* expressionSwitchCase);
void print_for_clause(struct ForClause* ForClause);
void print_signature(struct Signature* signature);
void print_param_in_paren(struct ParamInParen* paramInParen);
void print_param_list(struct ParameterList* paramList);
void print_param_declare(struct ParameterDeclare* paramDeclare);
void print_result(struct Result* result);
void print_primary_expression(struct PrimaryExpression* primaryExpr);
void print_function_call(struct FunctionCall* functionCall);
void print_switch_initial_expression(struct SwitchInitialAndExpression* switchInitialAndExpression);
void print_for_init_stmt(struct ForInitStmt* forInitStmt);
void print_for_condition(struct ForCondition* forCondition);
void print_for_post_stmt(struct ForPostStmt* forPostStmt);
void print_print_stmt(struct PrintStatement* printStmt);
void print_scan_stmt(struct ScanStatement* scanStmt);



#endif //_PRINT_TREE_