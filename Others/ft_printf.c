/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/07 17:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
		s = "(null)";
	while (s[len])
		len++;
	write(1, s, len);
	return (len);
}

static int	ft_putnbr(int n)
{
	int		len;
	char	c;

	len = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		len++;
	}
	if (n >= 10)
		len += ft_putnbr(n / 10);
	c = n % 10 + '0';
	write(1, &c, 1);
	len++;
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 's')
				len += ft_putstr(va_arg(args, char *));
			else if (*format == 'd')
				len += ft_putnbr(va_arg(args, int));
			else if (*format == 'c')
			{
				char c = va_arg(args, int);
				write(1, &c, 1);
				len++;
			}
		}
		else
		{
			write(1, format, 1);
			len++;
		}
		format++;
	}
	va_end(args);
	return (len);
}
