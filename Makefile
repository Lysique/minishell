# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 14:26:03 by slathouw          #+#    #+#              #
#    Updated: 2021/12/22 13:06:40 by slathouw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#############
# VARIABLES #
#############

NAME 	= minishell
LIBFT 	= libs/libftprintf
INCLUDES= includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBFLAGS = -lreadline -I$(HOME)/.brew/opt/readline/include -L$(HOME)/.brew/opt/readline/lib
OBJDIR	= obj

# ADD "SRCS" FILES HERE
SOURCES	= minishell.c execute_minishell.c signal_management.c ft_malloc.c check_cmdline.c
SRCDIR 	= srcs
SRCS 	= ${addprefix $(SRCDIR)/, $(SOURCES)}
OBJS	= ${addprefix $(OBJDIR)/srcs_, $(SOURCES:.c=.o)}

# ADD "LEXER" FILES HERE 
LEXER		= lexer.c nb_tokens.c tokens_in_arr.c
LEXER_DIR 	= srcs/lexer
LEXER_SRCS = ${addprefix $(LEXER_DIR)/, $(LEXER)}
LEXER_OBJS	= ${addprefix $(OBJDIR)/lexe_, $(LEXER:.c=.o)}

# ADD "PARSER" FILES HERE
PARSER		= parser.c create_cmdline.c cmds_add_lstfile.c create_command.c
PARSER_DIR 	= srcs/parser
PARSER_SRCS = ${addprefix $(PARSER_DIR)/, $(PARSER)}
PARSER_OBJS	= ${addprefix $(OBJDIR)/pars_, $(PARSER:.c=.o)}

# ADD "EXPANDER" FILES HERE
EXPANDER		=
EXPANDER_DIR 	= srcs/expander
EXPANDER_SRCS = ${addprefix $(EXPANDER_DIR)/, $(EXPANDER)}
EXPANDER_OBJS	= ${addprefix $(OBJDIR)/expa_, $(EXPANDER:.c=.o)}

# ADD "EXECUTOR" FILES HERE
EXECUTOR		= pipex.c pipex_utils.c pipex_utils2.c ft_exit.c ft_echo.c ft_pwd.c ft_cd.c executor.c 
EXECUTOR_DIR 	= srcs/executor
EXECUTOR_SRCS = ${addprefix $(EXECUTOR_DIR)/, $(EXECUTOR)}
EXECUTOR_OBJS	= ${addprefix $(OBJDIR)/exec_, $(EXECUTOR:.c=.o)}

all : 		${NAME}

###############
# COMPILATION #
###############

# Minishell linking compilation
$(NAME) :	$(OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(EXPANDER_OBJS) $(EXECUTOR_OBJS)
	@make -C $(LIBFT)
	@cp $(LIBFT)/libftprintf.a .
	@${CC} ${CFLAGS} -I ${INCLUDES} ${OBJS} $(LEXER_OBJS) $(PARSER_OBJS) $(EXPANDER_OBJS) $(EXECUTOR_OBJS) $(LIBFLAGS) libftprintf.a -o ${NAME}
	@echo "minishell binary created!"

# SRCS object compilation
$(OBJDIR)/srcs_%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@
	
# LEXER object compilation
$(OBJDIR)/lexe_%.o: $(LEXER_DIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

# PARSER object compilation
$(OBJDIR)/pars_%.o: $(PARSER_DIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

# EXPANDER object compilation
$(OBJDIR)/expa_%.o: $(EXPANDER_DIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

# EXECUTOR object compilation
$(OBJDIR)/exec_%.o: $(EXECUTOR_DIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

clean:
	@rm -f $(OBJS) $(LEXER_OBJS) $(PARSER_OBJS) $(EXPANDER_OBJS) $(EXECUTOR_OBJS)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)
	@echo "minishell objects removed..."

fclean: clean
	@rm -f $(NAME) libftprintf.a
	@make fclean -C $(LIBFT)
	@echo "minishell objects removed..."


re :		fclean all

.PHONY: all clean fclean re
