/*
 * lexer.c
 *
 * Purpose:
 *   Implements lexical analysis (tokenization) of input strings.
 *
 * Function:
 *   - Converts raw input characters into Tokens that the parser can consume.
 *   - Supports integers, identifiers (variables), single-character operators (+, -, *, /, =), and EOF.
 *
 * Notes:
 *   - All Token fields are explicitly initialized to satisfy strict compiler flags (-Werror).
 *   - Whitespace is skipped automatically.
 *   - Digits are combined into integer literals.
 *   - Letters (and digits after the first letter) are combined into identifiers.
 *   - Single-character operators are recognized and returned as distinct token types.
 *   - Unexpected characters are treated as lexer errors and cause EOF tokens to be returned after printing an error.
 */

#include <ctype.h>   // isdigit(), isspace(), isalpha(), isalnum()
#include <stdio.h>   // fprintf()
#include <string.h>  // memset()
#include "lexer.h"   // Token type and definitions

/*
 * Pointer to the source string being tokenized
 * and current position within it.
 *
 * Note: static makes these variables private to this file.
 */
static const char *src;  // Points to the input string
static int pos;          // Current index in src

/*
 * Initializes the lexer with a new input string.
 *
 * Parameters:
 *   input - the raw string to tokenize
 *
 * Behavior:
 *   - Resets the internal position to 0.
 *   - Stores a pointer to the input string for use by lexer_next().
 */
void lexer_init(const char *input)
{
    src = input;
    pos = 0;
}

/*
 * Returns the next Token from the input string.
 *
 * Behavior:
 *   - Skips whitespace.
 *   - Recognizes integer literals (TOKEN_INT) and constructs their value.
 *   - Recognizes identifiers (TOKEN_IDENT) and stores the name.
 *   - Recognizes single-character operators (+, -, *, /, =) and returns the corresponding token.
 *   - Returns TOKEN_EOF when the end of the string is reached.
 *   - Prints an error and returns TOKEN_EOF for any unexpected characters.
 *
 * Notes:
 *   - All fields of Token are explicitly initialized to prevent compiler warnings.
 */
Token lexer_next(void)
{
    // Skip any whitespace characters
    while (isspace(src[pos])) pos++;

    // End of input reached
    if (src[pos] == '\0') {
        return (Token){ .type = TOKEN_EOF, .value = 0, .name = {0} };
    }

    // Handle integer literals
    if (isdigit(src[pos])) {
        int value = 0;
        while (isdigit(src[pos])) {              // Accumulate digits
            value = value * 10 + (src[pos++] - '0');
        }
        // Return a fully initialized integer token
        return (Token){ .type = TOKEN_INT, .value = value, .name = {0} };
    }

    // Handle identifiers (variables)
    if (isalpha(src[pos])) {
        Token t = { .type = TOKEN_IDENT, .value = 0, .name = {0} }; // Initialize token
        int i = 0;
        while (isalnum(src[pos]) && i < (int)sizeof(t.name) - 1) { // Collect letters and digits
            t.name[i++] = src[pos++];
        }
        t.name[i] = '\0';  // Null-terminate the identifier
        return t;
    }

    // Handle single-character operators
    char c = src[pos++];  // Read the current character and advance
    switch (c) {
        case '+': return (Token){ .type = TOKEN_PLUS,  .value = 0, .name = {0} };
        case '-': return (Token){ .type = TOKEN_MINUS, .value = 0, .name = {0} };
        case '*': return (Token){ .type = TOKEN_STAR,  .value = 0, .name = {0} };
        case '/': return (Token){ .type = TOKEN_SLASH, .value = 0, .name = {0} };
        case '=': return (Token){ .type = TOKEN_ASSIGN,.value = 0, .name = {0} };
        default:
            // Any unexpected character is a lexer error
            fprintf(stderr, "Lexer error: unexpected character '%c'\n", c);
            return (Token){ .type = TOKEN_EOF, .value = 0, .name = {0} };
    }
}
