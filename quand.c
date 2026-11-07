/*** includes ***/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

/*
	KEYWORDS LIST:
	
	STDI	= standard input
	BUFR	= buffer
	ATTR	= attributes
*/

/*** defines ***/

// creates a macro for the control key.
#define CTRL_KEY(k) ((k) & 0x1f)

//this functions will mode into an utility file soon.
int iscntrl(int c)
{
	if ((c >= 0 && c <= 31) || c == 127)
		return(1);
	return (0);	
}

//end of utilities

/*** data ***/

//struct that will contains the default mode of the STDI
struct	termios orig_termios;

/*** terminal ***/

//this function is called whenever an error happens
void	die(const char *s)
{
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

void	editor_refresh_screen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
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
			exit(0);
			break;
	}
}

/*** init ***/

int	main(void)
{
	enable_raw_mode();

	while (1)
	{
		editor_refresh_screen();
		editor_process_keypress();
	}
}
