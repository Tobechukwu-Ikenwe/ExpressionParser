/*
 * ast.c
 *
 * Purpose:
 *   Implements functions to create and free Abstract Syntax Tree (AST) nodes.
 *   Each node represents an element of the language:
 *     - Integer literals
 *     - Variables
 *     - Binary operations
 *     - Assignments
 *
 * Design Philosophy:
 *   - Memory ownership is explicit: if you allocate a node, you are responsible for freeing it.
 *   - The code is heavily commented to help learners understand the flow, memory handling, and structure.
 *   - Each function initializes all fields explicitly to prevent undefined behavior.
 *
 * Notes:
 *   - Use ast_free() to recursively free nodes and avoid memory leaks.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"

/*
 * Create a new AST node representing an integer literal.
 *
 * Parameters:
 *   value - the integer value for this node
 *
 * Returns:
 *   A pointer to a newly allocated ASTNode.
 *
 * Responsibility:
 *   Caller must free with ast_free() when done.
 */
ASTNode *ast_int(int value)
{
    ASTNode *node = malloc(sizeof(ASTNode));  // Allocate memory for the node
    if (!node) { perror("malloc"); exit(1); } // Check allocation
    node->type = AST_INT;                     // Mark node as integer type
    node->value = value;                       // Store integer value
    node->name[0] = '\0';                      // No name for integer nodes
    node->op = 0;                              // No operator
    node->left = node->right = NULL;           // No children
    return node;                               // Return allocated node
}

/*
 * Create a new AST node representing a variable.
 *
 * Parameters:
 *   name - the variable name
 *
 * Returns:
 *   Pointer to a newly allocated ASTNode.
 *
 * Responsibility:
 *   Caller must free with ast_free().
 */
ASTNode *ast_var(const char *name)
{
    ASTNode *node = malloc(sizeof(ASTNode));  // Allocate memory
    if (!node) { perror("malloc"); exit(1); }
    node->type = AST_VAR;                     // Node type: variable
    node->value = 0;                           // No literal value
    strncpy(node->name, name, 31);            // Copy variable name safely
    node->name[31] = '\0';                     // Ensure null termination
    node->op = 0;                              // No operator
    node->left = node->right = NULL;           // No children
    return node;
}

/*
 * Create a new AST node representing a binary operation.
 *
 * Parameters:
 *   op - operator character ('+', '-', '*', '/')
 *   l  - left child ASTNode pointer
 *   r  - right child ASTNode pointer
 *
 * Returns:
 *   Pointer to a newly allocated ASTNode.
 *
 * Responsibility:
 *   Caller must free node and children using ast_free().
 */
ASTNode *ast_binop(char op, ASTNode *l, ASTNode *r)
{
    ASTNode *node = malloc(sizeof(ASTNode));  // Allocate memory
    if (!node) { perror("malloc"); exit(1); }
    node->type = AST_BINOP;                   // Node type: binary operation
    node->value = 0;                           // Value will be computed at evaluation
    node->name[0] = '\0';                      // Not a variable
    node->op = op;                             // Store operator
    node->left = l;                            // Assign left operand
    node->right = r;                           // Assign right operand
    return node;
}

/*
 * Create a new AST node representing a variable assignment.
 *
 * Parameters:
 *   name  - name of the variable being assigned
 *   value - ASTNode representing the value to assign
 *
 * Returns:
 *   Pointer to a newly allocated ASTNode.
 *
 * Responsibility:
 *   Caller must free node and value using ast_free().
 */
ASTNode *ast_assign(const char *name, ASTNode *value)
{
    ASTNode *node = malloc(sizeof(ASTNode));  // Allocate memory
    if (!node) { perror("malloc"); exit(1); }
    node->type = AST_ASSIGN;                  // Node type: assignment
    node->value = 0;                           // Value will be computed at runtime
    strncpy(node->name, name, 31);            // Copy variable name
    node->name[31] = '\0';                     // Null-terminate
    node->op = 0;                              // No operator
    node->left = NULL;                          // Left child unused
    node->right = value;                        // Right child stores value AST
    return node;
}

/*
 * Recursively frees an AST node and all of its children.
 *
 * Parameters:
 *   node - pointer to ASTNode to free
 *
 * Notes:
 *   - Uses post-order traversal: free left, right, then node itself
 *   - Prevents memory leaks by freeing entire tree
 */
void ast_free(ASTNode *node)
{
    if (!node) return;                        // Base case: nothing to free
    ast_free(node->left);                     // Free left subtree
    ast_free(node->right);                    // Free right subtree
    free(node);                               // Free this node
}
