/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msennane <msennane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:53:24 by msennane          #+#    #+#             */
/*   Updated: 2024/01/21 19:34:56 by msennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	prt_char(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	parse_flags(const char *format, va_list args)
{
	int	len;

	len = 0;
	if (*format == 'c')
		len += prt_char(va_arg(args, int));
	else if (*format == 's')
		len += prt_str(va_arg(args, char *));
	else if (*format == 'p')
		len += prt_pointer(va_arg(args, void *));
	else if (*format == 'd' || *format == 'i')
		len += prt_int(va_arg(args, int));
	else if (*format == 'u')
		len += prt_unsigned(va_arg(args, unsigned int));
	else if (*format == 'x')
		len += prt_hexa(va_arg(args, unsigned int), 0);
	else if (*format == 'X')
		len += prt_hexa(va_arg(args, unsigned int), 1);
	else if (*format == '%')
		len += prt_char('%');
	else
		len += prt_char(*format);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, format);
	len = 0;
	i = 0;
	if (!format)
		return (0);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
				break ;
			len += parse_flags(&format[i], args);
		}
		else
			len += prt_char(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
