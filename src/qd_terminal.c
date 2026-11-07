#include "quand.h"

// TERMIOS STRUCT
struct	termios orig_termios;

/*** terminal ***/

//this function is called whenever an error happens
void	die(const char *s)
{
    editor_refresh_screen();

    //print the last error in errno
    perror(s);
    exit(1);
}

//disable raw mode
void	disable_raw_mode(void)
{
    //check for error after calling the function
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
        die("(52) tcsetattr");
}

//set mode to raw for the STDI
void	enable_raw_mode(void)
{
    //write the ATTR of the STDI in orig_termios
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("(60) tcgetattr");
    atexit(disable_raw_mode);

    //create a new struct for our raw mode that will first contain the original ATTR
    struct termios raw = orig_termios;
    //modifiy the flags with bitwise operations until we get to raw mode
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag &= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    //set the MIN byte to read and MAX time before read returns
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    //apply the changes
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("(76) tcsetattr");
}
