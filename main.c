/*
 * main.c
 *
 * Purpose:
 *   Implements the REPL (Read-Eval-Print Loop) for the "Close to the Compiler" interpreter.
 *   Users can type expressions or assignments, which are then evaluated immediately.
 *
 * Function:
 *   - Reads input lines from standard input (stdin)
 *   - Passes the input to the lexer to tokenize
 *   - Parses the tokens into an Abstract Syntax Tree (AST)
 *   - Evaluates the AST to produce an integer result
 *   - Prints the result to standard output (stdout)
 *
 * Notes:
 *   - Each AST is freed after evaluation to prevent memory leaks.
 *   - Only expressions and assignments are supported in this simple REPL.
 *   - Designed for clarity and learning: shows the full pipeline from text to evaluation.
 */

#include <stdio.h>      // For fgets(), printf()
#include "parser.h"     // Provides parse_statement() function
#include "lexer.h"      // Provides lexer_init() and Token handling

/*
 * Declaration of the eval function.
 * 
 * Purpose:
 *   Evaluates a given ASTNode and returns the integer result.
 *   Defined in eval.c.
 */
int eval(ASTNode *node);

/*
 * main - entry point of the program
 *
 * Behavior:
 *   - Prints a welcome message
 *   - Loops indefinitely to read input from the user
 *   - Lexes, parses, evaluates, prints results
 *   - Frees each AST after evaluation to prevent memory leaks
 */
int main(void)
{
    char line[256];  // Buffer to hold user input

    // Welcome message for the user
    printf("ParseWorld\nType expressions or assignments (only).\n");

    // Infinite REPL loop
    while (1) {
        printf("> ");  // Prompt symbol

        // Read a line from standard input; exit loop on EOF (Ctrl+D)
        if (!fgets(line, sizeof(line), stdin)) break;

        // Initialize lexer with the current input line
        lexer_init(line);

        // Parse the tokens into an AST representing the statement
        ASTNode *ast = parse_statement();

        // Evaluate the AST and get the result
        int result = eval(ast);

        // Print the evaluation result to the user
        printf("%d\n", result);

        // Free the AST to prevent memory leaks
        ast_free(ast);
    }

    // Return 0 to indicate normal program termination
    return 0;
}
