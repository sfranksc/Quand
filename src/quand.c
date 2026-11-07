#include "quand.h"

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
