/*
Assignment name	: ft_strcspn
Expected files	: ft_strcspn.c
Allowed functions: None
---------------------------------------------------------------

Reproduce exactly the behavior of the function strcspn
(man strcspn).

The function should be prototyped as follows:

size_t	ft_strcspn(const char *s, const char *reject);
*/

// STRCSPN(3) (simplified)

// NAME
//     strcspn -- span a string
// LIBRARY
//     Standard C Library (libc, -lc)
// SYNOPSIS
//     #include <string.h>
//     size_t strcspn(const char *s, const char *charset);
// DESCRIPTION
//     The strcspn() function spans the initial part of the null-terminated
// string s as long as the characters from s do not occur in the null-
// terminated string charset (it spans the complement of the charset). In
// other words, it computes the string array index of the first character
// of s which is also in charset, else the index of the first null character.
// RETURN VALUES
//     The strcspn() functions return the number of characters spanned.

#include <stdio.h>

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (reject[++j])
			if (s[i] == reject[j])
				return (i);
	}
	return (i);
}

int	main(void)
{
	printf("ft_strcspn(\"hello world\", \" \") =%zu (預期 5,因為空格是第一個拒絕字元)\n",
		ft_strcspn("hello world", " "));
	printf("ft_strcspn(\"abcde\", \"xyz\")      = %zu (預期 5, 因為沒有匹配的拒絕字元)\n",
		ft_strcspn("abcde", "xyz"));
	printf("ft_strcspn(\"abcde\", \"d\")        = %zu (預期 3)\n",
		ft_strcspn("abcde", "d"));
	printf("ft_strcspn(\"hello\", \"aeiou\")     = %zu (預期 1, 因為'e'是第一個匹配的)\n",
		ft_strcspn("hello", "aeiou"));
	printf("ft_strcspn(\"programming\", \"gm\") = %zu (預期 4, 因為'g'是第一個匹配的)\n",
		ft_strcspn("programming", "gm"));
	printf("ft_strcspn(\"\", \"abc\")         = %zu (預期 0, 空字串長度為0)\n",
		ft_strcspn("", "abc"));
	printf("ft_strcspn(\"abc\", \"\")         = %zu (預期 3, 拒絕字元集為空，沒有字元會被拒絕)\n",
		ft_strcspn("abc", ""));
	printf("ft_strcspn(\"123abc456\", \"abcdef\") = %zu (預期 3, 因為'a'是第一個匹配的)\n",
		ft_strcspn("123abc456", "abcdef"));
	printf("\n標準庫 strcspn 比較:\n");
	printf("strcspn(\"hello world\", \" \")      = %zu\n",
		strcspn("hello world", " "));
	printf("strcspn(\"abcde\", \"xyz\")      = %zu\n", strcspn("abcde", "xyz"));
	printf("strcspn(\"abcde\", \"d\")        = %zu\n", strcspn("abcde", "d"));
	printf("strcspn(\"hello\", \"aeiou\")     = %zu\n", strcspn("hello",
			"aeiou"));
	return (0);
}
