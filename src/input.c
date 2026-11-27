#include "input.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define LAUNCHER_INPUT_SIZE 20

/* Purpose: Discards every character left on the current input line so the
 * next read starts clean.
 * Parameters: None.
 * Returns: Nothing. */
void flush_input_buffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }
}

/* Purpose: Compares the player's token with one accepted word, ignoring case.
 * Parameters: input (by value) is the NUL-terminated token the player typed;
 * word (by value) is the accepted command.
 * Returns: true when both strings match ignoring ASCII case. */
static bool token_matches(const char *input, const char *word)
{
    while (*input != '\0' && *word != '\0') {
        if (tolower((unsigned char)*input) != tolower((unsigned char)*word)) {
            return false;
        }
        input++;
        word++;
    }

    return *input == '\0' && *word == '\0';
}

/* Purpose: Maps one launcher token to a choice.
 * Parameters: input (by value) is the token the player typed.
 * Returns: LAUNCHER_NEW_GAME, LAUNCHER_QUIT, or -1 when the token is
 * invalid. */
static int parse_choice(const char *input)
{
    if (token_matches(input, "1") || token_matches(input, "n") ||
        token_matches(input, "new") || token_matches(input, "play")) {
        return LAUNCHER_NEW_GAME;
    }

    if (token_matches(input, "0") || token_matches(input, "q") ||
        token_matches(input, "quit") || token_matches(input, "exit")) {
        return LAUNCHER_QUIT;
    }

    return -1;
}

/* Purpose: Shows the console launcher and validates the player's answer.
 * Parameters: None. Reads from stdin.
 * Returns: the chosen launcher_choice; end of input ends as Quit. */
launcher_choice launcher_run(void)
{
    char input[LAUNCHER_INPUT_SIZE];

    for (;;) {
        printf("\n=== Lee Go! ===\n");
        printf("[1] New Game\n");
        printf("[0] Quit\n");
        printf("Enter your choice: ");
        fflush(stdout);

        // Continue appears here once save.c can report an existing save.
        const int read = scanf("%19s", input);
        if (read == EOF) {
            printf("\nNo input available. Closing.\n");
            return LAUNCHER_QUIT;
        }

        if (read != 1) {
            flush_input_buffer();
            printf("Invalid choice. Enter 1 for a new game or 0 to quit.\n");
            continue;
        }

        flush_input_buffer();

        const int choice = parse_choice(input);
        if (choice != -1) {
            return (launcher_choice)choice;
        }

        printf("Invalid choice '%s'. Enter 1 for a new game or 0 to quit.\n",
               input);
    }
}
