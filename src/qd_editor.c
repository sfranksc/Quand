#include "quand.h"

/*** terminal ***/

// read character wrote in the STDI
char	editor_read_key(void)
{
    int	nread;
    char	c;

    // checks for error while reading
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
            die("(86) read");
    }
    // returns read character
    return (c);
}

/*** output ***/

void	editor_refresh_screen(void)
{
    // clear the entire screen
    write(STDOUT_FILENO, "\x1b[2J", 4);
    // position the cursor at the top left corner
    write(STDOUT_FILENO, "\x1b[H", 3);
}

/*** input ***/

// process character received from editor_read_key
void	editor_process_keypress(void)
{
    char	c;

    // set the char at the return of editor_read_key
    c = editor_read_key();
    switch (c)
    {
        case CTRL_KEY('q'):
            editor_refresh_screen();
            exit(0);
            break;
    }
}
