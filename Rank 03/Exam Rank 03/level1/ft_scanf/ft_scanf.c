#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int	match_space(FILE *f)
{
	int	c;

	c = fgetc(f);
	while (isspace(c))
		c = fgetc(f);
	if (c != EOF)
		ungetc(c, f);
	return (1);
}

int	match_char(FILE *f, char c)
{
	int	d;

	d = fgetc(f);
	if (d == (int)c)
		return (1);
	if (d != EOF)
		ungetc(d, f);
	return (0);
}

int	scan_char(FILE *f, va_list ap)
{
	char	*c_ptr;
	int		d;

	c_ptr = va_arg(ap, char *);
	d = fgetc(f);
	if (d == EOF)
		return (0);
	*c_ptr = (char)d;
	return (1);
}

int	scan_int(FILE *f, va_list ap)
{
	int		*i_ptr;
	int		c;
	int		sign;
	long	res;

	i_ptr = va_arg(ap, int *);
	sign = 1;
	res = 0;
	c = fgetc(f);
	if (c == '+' || c == '-')
	{
		if (c == '-')
			sign = -1;
		c = fgetc(f);
	}
	if (!isdigit(c))
	{
		if (c != EOF)
			ungetc(c, f);
		return (0);
	}
	while (isdigit(c))
	{
		res = res * 10 + (c - '0');
		c = fgetc(f);
	}
	if (c != EOF)
		ungetc(c, f);
	*i_ptr = (int)(res * sign);
	return (1);
}

int	scan_string(FILE *f, va_list ap)
{
	char	*s_ptr;
	int		c;
	int		i;

	s_ptr = va_arg(ap, char *);
	i = 0;
	c = fgetc(f);
	while (c != EOF && !isspace(c))
	{
		s_ptr[i] = (char)c;
		i++;
		c = fgetc(f);
	}
	s_ptr[i] = '\0';
	if (c != EOF)
		ungetc(c, f);
	return (1);
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	int	ret;

	ret = -1;
	if (**format == 'c')
		ret = scan_char(f, ap);
	else if (**format == 'd')
	{
		match_space(f);
		ret = scan_int(f, ap);
	}
	else if (**format == 's')
	{
		match_space(f);
		ret = scan_string(f, ap);
	}
	return (ret);
}

int	ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int	nconv;
	int	match_result;

	nconv = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			match_result = match_conv(f, &format, ap);
			if (match_result == 1)
				nconv++;
			else if (feof(f) && nconv == 0)
				return (EOF);
			else if (match_result == 0)
				break ;
		}
		else if (isspace(*format))
			match_space(f);
		else
		{
			if (match_char(f, *format) != 1)
				break ;
		}
		format++;
	}
	return (nconv);
}

int	ft_scanf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return (ret);
}
