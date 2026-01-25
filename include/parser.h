/*
 * parser.h
 *
 * Purpose:
 *   Declares the public interface for the parser module of the "Close to the Compiler" interpreter.
 *
 * Function:
 *   - Provides the function parse_statement() which converts a stream of tokens
 *     (from the lexer) into an Abstract Syntax Tree (AST) representing a statement.
 *   - Handles expressions, assignments, and maintains proper operator precedence.
 *
 * Notes:
 *   - The parser implements a recursive descent approach.
 *   - Operator precedence is handled structurally via parse_expr, parse_term, parse_factor.
 *   - Other modules include this header to interact with the parser without knowing internal details.
 */

#ifndef PARSER_H   // Include guard start: prevents multiple inclusion
#define PARSER_H

#include "ast.h"  // Provides the ASTNode structure and AST constructor functions

/*
 * parse_statement
 *
 * Purpose:
 *   Converts the next statement in the token stream into an AST.
 *
 * Returns:
 *   Pointer to the root ASTNode representing the parsed statement.
 *
 * Behavior:
 *   - Parses either an assignment (IDENT '=' expr) or a standalone expression.
 *   - Recursively calls parse_expr(), parse_term(), and parse_factor to handle operator precedence.
 *   - Advances the lexer internally using lexer_next().
 */
ASTNode *parse_statement(void);

#endif  // Include guard end
