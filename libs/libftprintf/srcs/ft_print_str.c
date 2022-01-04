/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 10:30:19 by slathouw          #+#    #+#             */
/*   Updated: 2022/01/04 13:19:17 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	print_padding(t_format *fmt, size_t len)
{
	while (len--)
		ft_putchar_fd(' ', fmt->fd);
}

static void	print_s(t_field *fld, t_format *fmt, char *str)
{
	size_t	padding;

	padding = 0;
	if ((size_t)fld->min_width > ft_strlen(str))
		padding = fld->min_width - ft_strlen(str);
	if (fld->left_align)
		fmt->num_printed += ft_putstrl_fd(str, ft_strlen(str), fmt->fd);
	print_padding(fmt, padding);
	fmt->num_printed += padding;
	if (!fld->left_align)
		fmt->num_printed += ft_putstrl_fd(str, ft_strlen(str), fmt->fd);
}

void	ft_print_str(t_field *fld, t_format *fmt, va_list ap)
{
	char	*str;
	char	*trunc;
	int		len;

	str = va_arg(ap, char *);
	if (fld->precision > -1)
		len = fld->precision;
	else
		len = ft_strlen(str);
	trunc = ft_strldup(str, len);
	if (!str)
		fmt->num_printed += ft_putstrl_fd("(null)", 6, fmt->fd);
	else
		print_s(fld, fmt, trunc);
	free(trunc);
	fmt->fstr = fld->parse_ptr + 1;
}
