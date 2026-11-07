#ifndef QUAND_H
# define QUAND_H

// INCLUDES
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

// MACROS
#define CTRL_KEY(k) ((k) & 0x1f)

// EDITOR'S FUNCTIONS - qd_editor.c
char	editor_read_key(void);
void	editor_refresh_screen(void);
void	editor_process_keypress(void);

// TERMINALS FUNCITONS - qd_terminal.c
void	die(const char *s);
void	disable_raw_mode(void);
void	enable_raw_mode(void);

#endif
