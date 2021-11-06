# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 14:26:03 by slathouw          #+#    #+#              #
#    Updated: 2021/11/06 10:58:56 by slathouw         ###   ########.fr        #
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
OBJDIR	= obj

# ADD "SRCS" FILES HERE
SOURCES	= minishell.c
SRCDIR 	= srcs
SRCS 	= ${addprefix $(SRCDIR)/, $(SOURCES)}
OBJS	= ${addprefix $(OBJDIR)/srcs_, $(SOURCES:.c=.o)}

# ADD "LEXER" FILES HERE 
LEXER		= 
LEXER_DIR 	= srcs/lexer
LEXER_SRCS = ${addprefix $(LEXER_DIR)/, $(LEXER)}
LEXER_OBJS	= ${addprefix $(OBJDIR)/lexe_, $(LEXER:.c=.o)}

# ADD "PARSER" FILES HERE
PARSER		=  
PARSER_DIR 	= srcs/parser
PARSER_SRCS = ${addprefix $(PARSER_DIR)/, $(PARSER)}
PARSER_OBJS	= ${addprefix $(OBJDIR)/pars_, $(PARSER:.c=.o)}

# ADD "EXPANDER" FILES HERE
EXPANDER		=
EXPANDER_DIR 	= srcs/expander
EXPANDER_SRCS = ${addprefix $(EXPANDER_DIR)/, $(EXPANDER)}
EXPANDER_OBJS	= ${addprefix $(OBJDIR)/expa_, $(EXPANDER:.c=.o)}

# ADD "EXECUTOR" FILES HERE
EXECUTOR		= 
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
	@${CC} ${CFLAGS} -I ${INCLUDES} ${OBJS} $(LEXER_OBJS) $(PARSER_OBJS) $(EXPANDER_OBJS) $(EXECUTOR_OBJS) libftprintf.a -o ${NAME}
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
	@rm -f $(OBJS) $(PARSER_OBJS)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)
	@echo "minishell objects removed..."

fclean: clean
	@rm -f $(NAME) libftprintf.a
	@make fclean -C $(LIBFT)
	@echo "minishell objects removed..."


re :		fclean all

.PHONY: all clean fclean re
