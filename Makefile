CC			=	cc
CFLAGS		=	-Wall -Wextra -g
RM			=	rm -rf
MOD 		=	dependencies/modules/ft_realloc.c dependencies/modules/prompt.c\
				dependencies/modules/free2d.c dependencies/modules/replace_word.c

PARSING 	=	dependencies/parsing/cmd_tree_ops.c dependencies/parsing/parsing.c\
				dependencies/parsing/input_split.c dependencies/parsing/check_separator.c\
				dependencies/parsing/parse_args.c dependencies/parsing/extract_redirections.c\
				dependencies/parsing/parse_redirections.c dependencies/parsing/replace_variables.c
CFILES		=	core.c
PARSINGOBJ	=	$(PARSING:.c=.o)
COBJS		=	$(CFILES:.c=.o)
MODOBJ		=	$(MOD:.c=.o)
LIBFT		=	dependencies/libft/libft.a
NAME		=	minishell

all			:	$(NAME)

$(NAME)		:	$(COBJS) $(PARSINGOBJ) $(MODOBJ) $(LIBFT)
				$(CC) $(CFLAGS) -o $(NAME) $(COBJS) $(MODOBJ) $(PARSINGOBJ) $(LIBFT) -lreadline
$(LIBFT)	:
				cd dependencies/libft && $(MAKE)
clean		:
				$(RM) $(COBJS) $(PARSINGOBJ) $(MODOBJ)
				cd dependencies/libft && $(MAKE) clean
fclean		:	clean
				$(RM) $(NAME) $(LIBFT)
re			:	fclean all