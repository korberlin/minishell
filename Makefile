NAME = minishell

CC = cc
CFLAGS =  -Werror -Wextra -Wall -g

RM = rm -rf

SRCS =  src/minishell.c src/env.c src/execute.c src/free.c src/free_2.c src/print.c\
		src/builtins/env.c src/builtins/export.c src/parse.c src/parse_utils.c\
		src/signals.c src/init.c src/errors.c src/lexer_utils.c  src/access.c\
		src/lexer.c src/heredoc.c src/heredoc_utils.c src/expander.c \
		src/execute_utils.c src/execute_utils_2.c src/redirection.c \
		src/builtins/echo.c src/builtins/exit.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

LIBFT_PATH = libft/

LIBFT = $(LIBFT_PATH)libft.a

OBJECTS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    READLINE_LIB = -lreadline
else ifeq ($(UNAME_S),Darwin)
    READLINE_LIB = -lReadline
endif

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
		$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) $(READLINE_LIB) -L$(LIBFT_PATH) -lft

$(LIBFT):
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libraries: $(LIBFT)

clean:
	make -C $(LIBFT_PATH) clean
	$(RM) $(OBJECTS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: re clean fclean libraries all
