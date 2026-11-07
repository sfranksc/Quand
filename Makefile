C_FLAGS = -Wall -Wextra -Werror - pedantic -std=c99
NAME = Quand
SRCS = quand.c

quand: $(SRCS)
	$(CC) $(SRCS) -o $(NAME) -Wall -Wextra -Werror -pedantic -std=c99
