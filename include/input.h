#ifndef INPUT_H
#define INPUT_H

/* What the console launcher decided to do. */
typedef enum launcher_choice {
    LAUNCHER_QUIT = 0,
    LAUNCHER_NEW_GAME = 1
} launcher_choice;

/* Asks for New Game or Quit until the player enters a valid answer.
 * End of input counts as Quit, so piped runs always finish. */
launcher_choice launcher_run(void);

/* Throws away the rest of the current input line. */
void flush_input_buffer(void);

#endif
