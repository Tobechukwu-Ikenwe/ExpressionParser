/*
 * ast.h
 *
 * Purpose: Defines the Abstract Syntax Tree (AST) node structure and constructors.
 * Function: Provides functions to create nodes for integers, variables, binary operations, and assignments.
 * Notes: Each node tracks ownership of child nodes. `ast_free` must be called to prevent memory leaks.
 */


#ifndef AST_H
#define AST_H

typedef enum {
    AST_INT,
    AST_VAR,
    AST_BINOP,
    AST_ASSIGN
} ASTType;

typedef struct ASTNode {
    ASTType type;
    int value;
    char name[32];
    char op;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode *ast_int(int value);
ASTNode *ast_var(const char *name);
ASTNode *ast_binop(char op, ASTNode *l, ASTNode *r);
ASTNode *ast_assign(const char *name, ASTNode *value);
void ast_free(ASTNode *node);

#endif
