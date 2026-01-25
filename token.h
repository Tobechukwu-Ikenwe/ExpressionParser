/*
 * token.h
 *
 * Purpose:
 *   Defines the TokenType enum and Token struct used throughout the interpreter.
 *
 * Function:
 *   - Standardizes how lexical elements (integers, identifiers, operators) are represented.
 *   - Provides a unified structure for the lexer to output and the parser to consume.
 *
 * Notes:
 *   - Every token contains:
 *       * type  - the kind of token (integer, operator, identifier, or EOF)
 *       * value - integer value for TOKEN_INT tokens (0 otherwise)
 *       * name  - name for identifiers (TOKEN_IDENT) or empty for other tokens
 *   - Ensures safe initialization to prevent compiler warnings with strict flags.
 */

#ifndef TOKEN_H   // Include guard start: prevents multiple inclusion
#define TOKEN_H

/*
 * TokenType
 *
 * Enumerates all possible token types that the lexer can produce.
 */
typedef enum {
    TOKEN_INT,    // Integer literal
    TOKEN_PLUS,   // '+'
    TOKEN_MINUS,  // '-'
    TOKEN_STAR,   // '*'
    TOKEN_SLASH,  // '/'
    TOKEN_ASSIGN, // '='
    TOKEN_IDENT,  // Identifier (variable name)
    TOKEN_EOF     // End of input
} TokenType;

/*
 * Token
 *
 * Represents a single lexical element produced by the lexer.
 *
 * Fields:
 *   - type  : TokenType indicating what kind of token this is
 *   - value : Integer value (used only for TOKEN_INT)
 *   - name  : Null-terminated string (used only for TOKEN_IDENT)
 */
typedef struct {
    TokenType type;
    int value;
    char name[32]; // Buffer for identifiers, empty for non-identifier tokens
} Token;

#endif  // Include guard end
