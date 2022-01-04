/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:08:45 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/04 13:19:55 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	print_c(t_field *fld, t_format *fmt, va_list ap)
{
	if (*fld->parse_ptr == '%')
		ft_putchar_fd('%', fmt->fd);
	else
		ft_putchar_fd((char) va_arg(ap, int), fmt->fd);
	fmt->num_printed++;
}

static void	print_width(t_field *fld, t_format *fmt, char c)
{
	ft_putchar_fd(c, fmt->fd);
	fmt->num_printed++;
	fld->min_width--;
}

void	ft_print_char(t_field *fld, t_format *fmt, va_list ap)
{
	char	padding;

	if ((fld->zero_padding) && (*fld->parse_ptr == '%') && !(fld->left_align))
		padding = '0';
	else
		padding = ' ';
	if (fld->left_align)
		print_c(fld, fmt, ap);
	while (fld->min_width > 1)
		print_width(fld, fmt, padding);
	if (!fld->left_align)
		print_c(fld, fmt, ap);
	fmt->fstr = fld->parse_ptr + 1;
}
