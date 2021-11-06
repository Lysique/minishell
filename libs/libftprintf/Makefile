# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 09:55:38 by slathouw          #+#    #+#              #
#    Updated: 2021/11/06 09:32:02 by slathouw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libftprintf.a
LIBFT 	= libft
INCLUDES= includes
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
OBJDIR	= obj

SOURCES =   ft_printf.c ft_print_hex.c ft_print_int.c \
			ft_print_char.c ft_print_str.c ft_field_parse.c \
			get_next_line.c
SRCDIR = srcs
SRCS = ${addprefix $(SRCDIR)/, $(SOURCES)}
OBJS = ${addprefix $(OBJDIR)/, $(SOURCES:.c=.o)}


all : 		${NAME}

$(NAME) :	$(OBJS)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Libftprintf.a created!"


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT)
	@echo "libftprintf objects removed..."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)
	@echo "libftprintf.a removed..."

re :		fclean all

.PHONY: all clean fclean re simple
