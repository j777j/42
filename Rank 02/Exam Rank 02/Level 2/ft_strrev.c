/*
Assignment name  : ft_strrev
Expected files   : ft_strrev.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that reverses (in-place) a string.

It must return its parameter.

Your function must be declared as follows:

char	*ft_strrev(char *str);
*/

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len - 1)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	return (str);
}

// another way?
// char	*ft_strrev(char *str)
// {
// 	char	tmp;
// 	int		len;
// 	int		i;

// 	len = -1;
// 	i = -1;
// 	while (str[++len])
// 		;
// 	while (len / 2 > ++i)
// 	{
// 		tmp = str[i];
// 		str[i] = str[len - 1];
// 		str[len - 1] = tmp;
// 		len--;
// 	}
// 	return (str);
// }

int	main(void)
{
	char	str2[] = "world";
	char	str3[] = "a";
	char	str4[] = "";
	char	str5[] = "abcdef";

	char str1[] = "hello"; // 必須是可寫的字元陣列，不能是字串字面量 "hello"
	printf("原始字串: %s\n", str1);
	printf("反轉後: %s\n", ft_strrev(str1)); // 預期 olleh
	printf("原始字串: %s\n", str2);
	printf("反轉後: %s\n", ft_strrev(str2)); // 預期 dlrow
	printf("原始字串: %s\n", str3);
	printf("反轉後: %s\n", ft_strrev(str3)); // 預期 a
	printf("原始字串: %s\n", str4);
	printf("反轉後: %s\n", ft_strrev(str4)); // 預期 (空字串)
	printf("原始字串: %s\n", str5);
	printf("反轉後: %s\n", ft_strrev(str5)); // 預期 fedcba
	return (0);
}
