/*
 * ast.h
 *
 * Purpose:
 *   This header defines the Abstract Syntax Tree (AST) structure used
 *   in the interpreter. AST nodes represent components of expressions
 *   and statements, such as integers, variables, binary operations,
 *   and assignments.
 *
 * Function:
 *   - Provides the structure definition for AST nodes.
 *   - Declares functions to create nodes for different types.
 *   - Declares a function to recursively free nodes to avoid memory leaks.
 *
 * Notes:
 *   - Each node tracks ownership of its children through pointers.
 *   - It is the caller’s responsibility to use ast_free() on nodes
 *     when they are no longer needed.
 *   - This header separates the interface (AST API) from the implementation
 *     (ast.c) so other modules can interact with AST nodes safely.
 */

#ifndef AST_H   // Include guard start: prevents multiple inclusion
#define AST_H

/*
 * Enumeration of possible AST node types.
 *
 * AST_INT    : Represents an integer literal (e.g., 42)
 * AST_VAR    : Represents a variable (e.g., x)
 * AST_BINOP  : Represents a binary operation (e.g., a + b)
 * AST_ASSIGN : Represents an assignment (e.g., x = 5)
 *
 * Usage:
 *   The 'type' field in ASTNode will store one of these values,
 *   allowing the interpreter to switch behavior based on node type.
 */
typedef enum {
    AST_INT,
    AST_VAR,
    AST_BINOP,
    AST_ASSIGN
} ASTType;

/*
 * Structure representing a single node in the AST.
 *
 * Fields:
 *   type  : Stores the type of node (ASTType)
 *   value : Holds integer value for AST_INT nodes
 *   name  : Holds variable names for AST_VAR or AST_ASSIGN nodes (null-terminated)
 *   op    : Holds operator character for AST_BINOP nodes ('+', '-', '*', '/')
 *   left  : Pointer to the left child ASTNode (used in binary operations)
 *   right : Pointer to the right child ASTNode (used in binary operations and assignments)
 *
 * Memory notes:
 *   - left and right are owned by this node. When ast_free() is called,
 *     all child nodes are recursively freed.
 */
typedef struct ASTNode {
    ASTType type;        // Type of this node
    int value;           // Integer value (used for AST_INT)
    char name[32];       // Name of variable (used for AST_VAR or AST_ASSIGN)
    char op;             // Operator for AST_BINOP nodes
    struct ASTNode *left;  // Pointer to left child (NULL if not used)
    struct ASTNode *right; // Pointer to right child (NULL if not used)
} ASTNode;

/*
 * Function declarations for AST node creation and destruction.
 *
 * Each function allocates memory for a new node and initializes fields
 * explicitly. The caller is responsible for freeing the node with ast_free().
 */

/* Creates an AST node representing an integer literal */
ASTNode *ast_int(int value);

/* Creates an AST node representing a variable with the given name */
ASTNode *ast_var(const char *name);

/* Creates an AST node representing a binary operation with operator 'op' and child nodes 'l' and 'r' */
ASTNode *ast_binop(char op, ASTNode *l, ASTNode *r);

/* Creates an AST node representing an assignment of 'value' to variable 'name' */
ASTNode *ast_assign(const char *name, ASTNode *value);

/* Recursively frees an AST node and all its children to prevent memory leaks */
void ast_free(ASTNode *node);

#endif  // Include guard end
