/*
Assignment name  : ft_atoi
Expected files   : ft_atoi.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that converts the string argument str to an integer (type int)
and returns it.

It works much like the standard atoi(const char *str) function, see the man.

Your function must be declared as follows:

int	ft_atoi(const char *str);
*/

int	ft_atoi(const char *str)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	return (sign * n);
}

/*
int	main(void)
{
	printf("ft_atoi(\"123\")        = %d\n", ft_atoi("123"));
	printf("ft_atoi(\"-456\")       = %d\n", ft_atoi("-456"));
	printf("ft_atoi(\"+789\")       = %d\n", ft_atoi("+789"));
	printf("ft_atoi(\"  100\")      = %d\n", ft_atoi("  100"));
	printf("ft_atoi(\"\\t\\n-200\")   = %d\n", ft_atoi("\t\n-200"));
	printf("ft_atoi(\"hello\")      = %d\n", ft_atoi("hello"));      // 預期 0
	printf("ft_atoi(\"123hello\")   = %d\n", ft_atoi("123hello"));   // 預期 123
	printf("ft_atoi(\"\")          = %d\n", ft_atoi(""));           // 預期 0
	printf("ft_atoi(\"  -  5\")    = %d\n", ft_atoi("  -  5"));
		// 預期 0 (因為處理完空白後遇到 ' ')
	printf("ft_atoi(\" - 5\")     = %d\n", ft_atoi(" - 5"));
		// 預期 0 (因為處理完空白後遇到 ' ')
	printf("ft_atoi(\"-50\")       = %d\n", ft_atoi("-50"));
	printf("ft_atoi(\"\\f\\r 42\")    = %d\n", ft_atoi("\f\r 42"));
	return (0);
}
*/
