# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 09:55:38 by slathouw          #+#    #+#              #
#    Updated: 2021/12/24 05:40:12 by slathouw         ###   ########.fr        #
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

#FT_ARRAY files 
ARRSOURCES	= array.c int_array.c ft_realloc.c
ARRDIR 	= srcs/ft_array
ARRSRCS = ${addprefix $(ARRDIR)/, $(ARRSOURCES)}
ARROBJS	= ${addprefix $(OBJDIR)/arr_, $(ARRSOURCES:.c=.o)}


all : 		${NAME}

$(NAME) :	$(OBJS) ${ARROBJS}
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS) ${ARROBJS}
	@ranlib $(NAME)
	@echo "Libftprintf.a created!"


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p obj
	@${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

#FT_ARRAY object compilation
$(OBJDIR)/arr_%.o: $(ARRDIR)/%.c
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
