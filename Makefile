NAME = minishell

HEADER = ./inc/

SRCS = minishell.c execute.c parser.c pathfinder.c builtin_commands.c\
	   env_utils.c builtin_env.c builtin_unset.c builtin_export.c builtin_cd.c\
	   exit_shell.c preparser.c utilsforparser.c exec_piped.c

OBJSDIR = ./objs
SRCSDIR = ./srcs
HDRDIR = ./inc
LIBFTDIR = ./libft

LIBFT = $(LIBFTDIR)libft.a

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

OBJS = $(addprefix $(OBJSDIR)/,$(SRCS:.c=.o))

all: lib $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADER)
	@$(CC) $(FLAGS) -I $(HDRDIR) -I $(LIBFTDIR) -c $< -o $@

lib:
	@make bonus -C $(LIBFTDIR)

$(NAME): $(OBJSDIR) $(OBJS)
	$(CC) -L$(LIBFTDIR) -lft $(OBJS) -lreadline -o $(NAME)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJSDIR)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re
