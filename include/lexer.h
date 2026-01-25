/*
 * lexer.h
 *
 * Purpose:
 *   Declares the interface for the lexical analyzer (lexer) used by the interpreter.
 *   The lexer converts raw input strings into a stream of Tokens for the parser.
 *
 * Function:
 *   - Provides function declarations for initializing the lexer and retrieving the next token.
 *   - Other modules (parser, main) include this header to interact with the lexer without
 *     knowing its internal implementation details.
 *
 * Notes:
 *   - Tokens are defined in "token.h" and include integers, identifiers, operators, and EOF.
 *   - The lexer keeps internal state (position in input string) hidden from users.
 *   - Heavy documentation ensures clarity for readers and maintainers.
 */

#ifndef LEXER_H   // Include guard start: prevents multiple inclusion of this header
#define LEXER_H

#include "token.h"  // Provides the definition of the Token structure and token types

/*
 * lexer_init
 *
 * Purpose:
 *   Initialize the lexer with a new input string.
 *
 * Parameters:
 *   input - a null-terminated string containing the source code to tokenize
 *
 * Behavior:
 *   - Sets internal lexer state (source string pointer and current position)
 *   - Must be called before calling lexer_next()
 */
void lexer_init(const char *input);

/*
 * lexer_next
 *
 * Purpose:
 *   Retrieves the next token from the input stream.
 *
 * Returns:
 *   A fully initialized Token structure.
 *
 * Behavior:
 *   - Skips whitespace automatically.
 *   - Recognizes integer literals, identifiers, single-character operators, and EOF.
 *   - Prints an error and returns TOKEN_EOF for unexpected characters.
 *   - Maintains internal state so successive calls return the next token in sequence.
 */
Token lexer_next(void);

#endif  // Include guard end
