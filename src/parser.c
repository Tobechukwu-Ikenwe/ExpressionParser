/*
 * parser.c
 *
 * Purpose:
 *   Implements a recursive descent parser for the "Close to the Compiler" interpreter.
 *
 * Function:
 *   - Converts a stream of tokens produced by the lexer into an Abstract Syntax Tree (AST).
 *   - Follows a simple grammar:
 *       stmt  → IDENT '=' expr | expr
 *       expr  → term ((+|-) term)*
 *       term  → factor ((*|/) factor)*
 *       factor→ INT | IDENT
 *   - Operator precedence is maintained structurally via nested parse functions.
 *
 * Notes:
 *   - Only basic arithmetic and variable assignments are supported.
 *   - Parser errors exit the program immediately.
 *   - Designed for clarity and learning: demonstrates recursion, token handling, and AST construction.
 */

#include <stdio.h>   // fprintf()
#include <stdlib.h>  // exit()
#include "parser.h"  // ASTNode definition and ast_* constructors
#include "lexer.h"   // lexer_next() function and Token definitions

/*
 * Recursive descent parser variables and forward declarations
 */
static Token current;              // The current token being processed
static void advance(void) { current = lexer_next(); } // Move to the next token
static ASTNode *parse_expr(void);  // Forward declaration for parse_expr (used in statements)

/*
 * parse_factor
 *
 * Grammar:
 *   factor → INT | IDENT
 *
 * Returns:
 *   ASTNode* representing an integer literal or variable
 *
 * Behavior:
 *   - Converts the current token into an AST node.
 *   - Advances the token stream after consuming the factor.
 *   - Prints an error and exits if the token is not a valid factor.
 */
static ASTNode *parse_factor(void)
{
    if (current.type == TOKEN_INT) {
        ASTNode *n = ast_int(current.value); // Create integer node
        advance();                           // Consume the token
        return n;
    }

    if (current.type == TOKEN_IDENT) {
        ASTNode *n = ast_var(current.name);  // Create variable node
        advance();                           // Consume the token
        return n;
    }

    // Invalid token for a factor
    fprintf(stderr, "Parser error: invalid factor\n");
    exit(1);
}

/*
 * parse_term
 *
 * Grammar:
 *   term → factor ((*|/) factor)*
 *
 * Returns:
 *   ASTNode* representing a term with proper operator precedence for *, /
 *
 * Behavior:
 *   - Recursively parses factors connected by * or /
 *   - Constructs AST nodes with binary operators maintaining left-to-right associativity
 */
static ASTNode *parse_term(void)
{
    ASTNode *node = parse_factor(); // Parse the first factor

    while (current.type == TOKEN_STAR || current.type == TOKEN_SLASH) {
        char op = (current.type == TOKEN_STAR) ? '*' : '/'; // Determine operator
        advance();                                        // Consume operator token
        node = ast_binop(op, node, parse_factor());       // Combine with next factor
    }

    return node;
}

/*
 * parse_expr
 *
 * Grammar:
 *   expr → term ((+|-) term)*
 *
 * Returns:
 *   ASTNode* representing an expression with proper operator precedence for +, -
 *
 * Behavior:
 *   - Recursively parses terms connected by + or -
 *   - Constructs AST nodes with binary operators maintaining left-to-right associativity
 */
static ASTNode *parse_expr(void)
{
    ASTNode *node = parse_term(); // Parse the first term

    while (current.type == TOKEN_PLUS || current.type == TOKEN_MINUS) {
        char op = (current.type == TOKEN_PLUS) ? '+' : '-'; // Determine operator
        advance();                                        // Consume operator token
        node = ast_binop(op, node, parse_term());         // Combine with next term
    }

    return node;
}

/*
 * parse_statement
 *
 * Grammar:
 *   stmt → IDENT '=' expr | expr
 *
 * Returns:
 *   ASTNode* representing a statement (either an assignment or an expression)
 *
 * Behavior:
 *   - Advances to the first token
 *   - If the statement starts with an identifier followed by '=', parses an assignment
 *   - Otherwise, treats the input as an expression
 *   - Ensures proper AST node construction for variable assignments
 */
ASTNode *parse_statement(void)
{
    advance(); // Initialize current token

    if (current.type == TOKEN_IDENT) {
        Token ident = current; // Save identifier in case it's an assignment
        advance();             // Move past the identifier
        if (current.type == TOKEN_ASSIGN) {
            advance();                  // Consume '='
            ASTNode *value = parse_expr(); // Parse the right-hand side expression
            return ast_assign(ident.name, value); // Construct assignment AST node
        }
        current = ident; // Not an assignment, reset to identifier for expression parsing
    }

    return parse_expr(); // Parse as a standard expression if not an assignment
}
