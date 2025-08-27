/*
Assignment name  : ft_strcmp
Expected files   : ft_strcmp.c
Allowed functions:
--------------------------------------------------------------------------------

Reproduce the behavior of the function strcmp (man strcmp).

Your function must be declared as follows:

int	ft_strcmp(char *s1, char *s2);
*/

// //this one
// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while ((s1[i] && s2[i]) && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

// STRCMP(3) (simplified)

// NAME
//     strcmp -- compare strings
// SYNOPSIS
//     #include <string.h>
//     int strcmp(const char *s1, const char *s2);
// DESCRIPTION
//     The strcmp() and strncmp() functions lexicographically compare the null-
// terminated strings s1 and s2.
// RETURN VALUES
//      The strcmp() and strncmp() functions return an integer greater than,
//  equal to, or less than 0, according as the string s1 is greater than,
//  equal to, or less than the string s2.  The comparison is done using
//  unsigned characters, so that ‘\200’ is greater than ‘\0’.

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

/*
int	main(void)
{
	printf("ft_strcmp(\"hello\", \"hello\") = %d (預期 0)\n", ft_strcmp("hello",
			"hello"));
	printf("ft_strcmp(\"hello\", \"hellp\") = %d (預期負數)\n", ft_strcmp("hello",
			"hellp"));
	printf("ft_strcmp(\"hellp\", \"hello\") = %d (預期正數)\n", ft_strcmp("hellp",
			"hello"));
	printf("ft_strcmp(\"apple\", \"apply\") = %d (預期負數)\n", ft_strcmp("apple",
			"apply"));
	printf("ft_strcmp(\"apply\", \"apple\") = %d (預期正數)\n", ft_strcmp("apply",
			"apple"));
	printf("ft_strcmp(\"apple\", \"applepie\") = %d (預期負數)\n",
		ft_strcmp("apple", "applepie"));
	printf("ft_strcmp(\"applepie\", \"apple\") = %d (預期正數)\n",
		ft_strcmp("applepie", "apple"));
	printf("ft_strcmp(\"\", \"abc\")     = %d (預期負數)\n", ft_strcmp("", "abc"));
	printf("ft_strcmp(\"abc\", \"\")     = %d (預期正數)\n", ft_strcmp("abc", ""));
	printf("ft_strcmp(\"\", \"\")       = %d (預期 0)\n", ft_strcmp("", ""));
	printf("ft_strcmp(\"TEST\", \"test\") = %d (預期負數，因為ASCII大寫比小寫小)\n",
		ft_strcmp("TEST", "test"));
	return (0);
}
*/
