RED		=\033[0;31m
BLUE	=\033[0;34m
WHITE	=\033[0;37m
YELLOW	=\033[0;33m

CC		= gcc
NAME	= minishell
LIBFT	= ./Librarys/libft/libft.a
CFLAGS	= -Werror -Wall -Wextra -g

SRCS =	Source/commands/cd.c			\
		Source/commands/clear.c			\
		Source/commands/echo.c			\
		Source/commands/env.c			\
		Source/commands/exit.c			\
		Source/commands/export.c		\
		Source/commands/pwd.c			\
		Source/commands/unset.c			\
		Source/executor/executor.c		\
		Source/executor/executor2.c		\
		Source/utils/free.c				\
		Source/lexer/lexer.c			\
		Source/minishell.c				\
		Source/parser/parser.c			\
		Source/parser/parser2.c			\
		Source/signals/signals.c		\
		Source/split/split.c			\
		Source/split/split2.c			\
		Source/split/split3.c			\
		Source/utils/utils.c			\
		Source/utils/utils2.c			\
		Source/utils/utils3.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
			@echo "$(YELLOW)>>>> Compiling Libft Librarys <<<<$(WHITE)"
			@make -sC ./Librarys/libft
			@echo "$(YELLOW)>>>> Compiling minishell <<<<$(WHITE)"
#			FOR MAC
#			$(CC) $(CFLAGS) -I./Librarys/readline/include -L./Librarys/readline/lib $(LIBFT) $(OBJS) -lreadline -o $(NAME)
#			FOR LINUX
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -lncurses -o $(NAME)
			@echo "$(BLUE)>>>> Done <<<<$(WHITE)"

clean:
		@make clean -sC ./Librarys/libft
		@rm -rf $(OBJS)
		@echo "$(RED)>>>> Deleted <<<<$(WHITE)"

fclean:	clean
		@make fclean -sC ./Librarys/libft
		@rm -rf $(NAME)
		@echo "$(RED)>>>> Full Deleted <<<<$(WHITE)"

norm:
	@norminette ./Librarys/libft
	@norminette ./Source

re:	fclean all

.PHONY:	all clean fclean re
