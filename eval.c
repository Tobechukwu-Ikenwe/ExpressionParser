/*
 * eval.c
 *
 * Purpose:
 *   Evaluates an Abstract Syntax Tree (AST) into integer results.
 *
 * Function:
 *   - Supports integer arithmetic (+, -, *, /)
 *   - Supports variables and assignments with a flat environment
 *
 * Notes:
 *   - Assignments update a fixed-size variable environment.
 *   - Division by zero or using an undefined variable results in immediate program exit.
 *   - Designed to be simple and educational: shows evaluation, recursion, and environment handling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

/*
 * Simple flat variable environment.
 *
 * - Uses a static array of Variable structs to store variable names and values.
 * - Maximum of 64 variables supported (can be adjusted if needed).
 * - Variable lookup and assignment are done via linear search for simplicity.
 */

typedef struct {
    char name[32];  // Variable name (null-terminated string)
    int value;      // Value associated with the variable
} Variable;

static Variable vars[64]; // Array storing all variables in the environment
static int var_count = 0; // Number of variables currently defined

/*
 * lookup - searches for a variable by name and returns its value
 *
 * Parameters:
 *   name - the name of the variable to look up
 *
 * Returns:
 *   The integer value of the variable
 *
 * Behavior:
 *   - If the variable does not exist, prints an error and exits the program
 */
static int lookup(const char *name)
{
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) return vars[i].value;
    }
    // Variable not found: runtime error
    fprintf(stderr, "Runtime error: undefined variable '%s'\n", name);
    exit(1);
}

/*
 * assign - adds or updates a variable in the environment
 *
 * Parameters:
 *   name  - variable name
 *   value - integer value to assign
 *
 * Behavior:
 *   - If variable already exists, updates its value.
 *   - If variable does not exist, creates a new entry (up to 64 variables max).
 *   - Exits with error if too many variables are defined.
 */
static void assign(const char *name, int value)
{
    // Search for existing variable
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            vars[i].value = value; // Update existing variable
            return;
        }
    }

    // Create a new variable if room allows
    if (var_count >= 64) {
        fprintf(stderr, "Runtime error: too many variables\n");
        exit(1);
    }
    strncpy(vars[var_count].name, name, 31); // Copy name safely
    vars[var_count].name[31] = '\0';        // Ensure null-termination
    vars[var_count++].value = value;        // Assign value and increment count
}

/*
 * eval - recursively evaluates an AST node
 *
 * Parameters:
 *   node - pointer to the AST node to evaluate
 *
 * Returns:
 *   Integer result of evaluating the node
 *
 * Behavior:
 *   - Evaluates integers, variables, assignments, and binary operations
 *   - For assignments, returns the assigned value
 *   - For binary operations, handles +, -, *, /
 *   - Division by zero exits immediately with an error
 *   - Undefined variables also exit immediately
 */
int eval(ASTNode *node)
{
    if (!node) return 0; // Safety check: null node returns 0

    switch (node->type) {
        case AST_INT: 
            return node->value; // Return literal integer

        case AST_VAR: 
            return lookup(node->name); // Look up variable value

        case AST_ASSIGN: {
            int v = eval(node->right); // Evaluate right-hand side first
            assign(node->name, v);     // Assign value to variable
            return v;                  // Return assigned value
        }

        case AST_BINOP: {
            int l = eval(node->left);   // Evaluate left operand
            int r = eval(node->right);  // Evaluate right operand
            switch (node->op) {
                case '+': return l + r; // Addition
                case '-': return l - r; // Subtraction
                case '*': return l * r; // Multiplication
                case '/':
                    if (r == 0) {      // Check for division by zero
                        fprintf(stderr, "Runtime error: division by zero\n");
                        exit(1);
                    }
                    return l / r;      // Division
            }
        }
    }

    // Default: should not reach here; return 0 for safety
    return 0;
}
