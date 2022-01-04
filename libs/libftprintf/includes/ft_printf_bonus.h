/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 10:12:18 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/04 13:25:58 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stdlib.h>
# include <stdarg.h>
# include "../libft/libft.h"
# include "../includes/get_next_line.h"

typedef struct s_format
{
	const char	*fstr;
	int			fd;
	int			num_printed;
}				t_format;

typedef struct s_field
{
	char		*percent_ptr;
	char		*parse_ptr;
	size_t		length;
	int			left_align;
	int			zero_padding;
	int			min_width;
	int			precision;
	int			alt_form;
	int			space;
	int			plus_sign;
}				t_field;

int		ft_printf(const char *format, ...);
int		ft_fdprintf(int fd, const char *format, ...);
void	ft_print_int(t_field *fld, t_format *fmt, va_list ap);
void	ft_print_hex(t_field *fld, t_format *fmt, va_list ap);
void	ft_print_char(t_field *fld, t_format *fmt, va_list ap);
void	ft_print_str(t_field *fld, t_format *fmt, va_list ap);
void	ft_field_parse(t_field *fld, char *pcnt_ptr);
#endif