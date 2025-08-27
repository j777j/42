/*

Assignment name	: ft_strpbrk
Expected files	: ft_strpbrk.c
Allowed functions: None
---------------------------------------------------------------
Reproduce exactly the behavior of the function strpbrk
(man strpbrk).

The function should be prototyped as follows:

char	*ft_strpbrk(const char *s1, const char *s2);

*/

/*
STRPBRK(3) (simplified)

NAME
		strpbrk –- locate multiple characters in string
LIBRARY
		Standard C Library (libc, -lc)
SYNOPSIS
		#include <string.h>
		char *strpbrk(const char *s, const char *charset);

DESCRIPTION
		The strpbrk() function locates in the null-terminated string s the first
		occurrence of any character in the string charset and returns a pointer to this
		character.  If no characters from charset occur anywhere in s strpbrk()
		returns NULL.
RETURN VALUES
		The strpbrk() function return a pointer to the first occurence of any character
		in the string,if no characters occur anywhere in s,
			strpbrk() returns NULL.
*/

#include <stdio.h>
#include <string.h>

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	while (*s1)
	{
		i = -1;
		while (s2[++i])
		{
			if (*s1 == s2[i])
				return ((char *)s1);
		}
		s1++;
	}
	return (0);
}

int	main(void)
{
	char	*s1_test1;
	char	*result1;
	char	*s1_test2;
	char	*result2;
	char	*s1_test3;
	char	*result3;
	char	*s2_test4;
	char	*result4;
	char	*s1_test5;
	char	*result5;

	s1_test1 = "hello world";
	char *s2_test1 = "aeiou"; // 尋找母音
	result1 = ft_strpbrk(s1_test1, s2_test1);
	if (result1)
		printf("ft_strpbrk(\"%s\", \"%s\") = \"%s\" (預期 \"e\")\n", s1_test1,
			s2_test1, result1);
	else
		printf("ft_strpbrk(\"%s\", \"%s\") = NULL (預期 \"e\")\n", s1_test1,
			s2_test1);
	s1_test2 = "programming";
	char *s2_test2 = "xyz"; // 尋找不存在的字元
	result2 = ft_strpbrk(s1_test2, s2_test2);
	if (result2)
		printf("ft_strpbrk(\"%s\", \"%s\") = \"%s\" (預期 NULL)\n", s1_test2,
			s2_test2, result2);
	else
		printf("ft_strpbrk(\"%s\", \"%s\") = NULL (預期 NULL)\n", s1_test2,
			s2_test2);
	s1_test3 = "testing";
	char *s2_test3 = ""; // 空的字元集
	result3 = ft_strpbrk(s1_test3, s2_test3);
	if (result3)
		printf("ft_strpbrk(\"%s\", \"%s\") = \"%s\" (預期 NULL)\n", s1_test3,
			s2_test3, result3);
	else
		printf("ft_strpbrk(\"%s\", \"%s\") = NULL (預期 NULL)\n", s1_test3,
			s2_test3);
	char *s1_test4 = ""; // 空的主字串
	s2_test4 = "abc";
	result4 = ft_strpbrk(s1_test4, s2_test4);
	if (result4)
		printf("ft_strpbrk(\"%s\", \"%s\") = \"%s\" (預期 NULL)\n", s1_test4,
			s2_test4, result4);
	else
		printf("ft_strpbrk(\"%s\", \"%s\") = NULL (預期 NULL)\n", s1_test4,
			s2_test4);
	s1_test5 = "abcd";
	char *s2_test5 = "dcba"; // 找到 'd'
	result5 = ft_strpbrk(s1_test5, s2_test5);
	if (result5)
		printf("ft_strpbrk(\"%s\", \"%s\") = \"%s\" (預期 \"d\")\n", s1_test5,
			s2_test5, result5);
	else
		printf("ft_strpbrk(\"%s\", \"%s\") = NULL (預期 \"d\")\n", s1_test5,
			s2_test5);
	// 標準庫 strpbrk 比較 (你可以取消註解來比較)
	// printf("\n標準庫 strpbrk 比較:\n");
	// printf("strpbrk(\"%s\", \"%s\") = \"%s\"\n", s1_test1, s2_test1,
	// 標準庫 strpbrk 比較 (你可以取消註解來比較)
	// printf("\n標準庫 strpbrk 比較:\n");
	// printf("strpbrk(\"%s\", \"%s\") = \"%s\"\n", s1_test1,
		s2_test1,strpbrk(s1_test1, s2_test1));
	// printf("strpbrk(\"%s\", \"%s\") = %p\n", s1_test2,
		s2_test2,strpbrk(s1_test2, s2_test2)); // NULL會印成 0x0
	// printf("strpbrk(\"%s\", \"%s\") = %p\n", s1_test3,
		s2_test3,strpbrk(s1_test3, s2_test3));
	// printf("strpbrk(\"%s\", \"%s\") = %p\n", s1_test4,
		s2_test4,strpbrk(s1_test4, s2_test4));
	return (0);
}
