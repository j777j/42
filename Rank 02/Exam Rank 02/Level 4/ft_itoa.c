// #include "libft.h"

// size_t	let_me_count(long long n)
// {
// 	size_t	len;

// 	len = 1;
// 	if (n < 0)
// 	{
// 		n = -n;
// 		len++;
// 	}
// 	while (n > 9)
// 	{
// 		n /= 10;
// 		len++;
// 	}
// 	return (len);
// }

// char	*ft_itoa(int n)
// {
// 	size_t		i;
// 	size_t		len;
// 	long long	new_n;
// 	char		*s;

// 	len = let_me_count(n);
// 	new_n = n;
// 	s = (char *)malloc((sizeof(char)) * (len + 1));
// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	if (new_n < 0)
// 	{
// 		s[i] = '-';
// 		new_n = -new_n;
// 	}
// 	while (new_n > 9)
// 	{
// 		s[len - i - 1] = (new_n % 10) + '0';
// 		new_n /= 10;
// 		i++;
// 	}
// 	s[len - i - 1] = (new_n % 10) + '0';
// 	s[len] = '\0';
// 	return (s);
// }

// another one!!!

// #include <stdlib.h>

// char	*ft_itoa(int nbr)
// {
// 	int		n;
// 	int		len;
// 	char	*result;

// 	if (nbr == -2147483648)
// 		return ("-2147483648\0"); // max int
// 	n = nbr;
// 	len = 0;
// 	if (nbr <= 0)
// 		len++;
// 	while (n)
// 	{
// 		n /= 10;
// 		len++;
// 	}
// 	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
// 		return (NULL);
// 	result[len] = '\0';
// 	if (nbr == 0)
// 	{
// 		result[0] = '0';
// 		return (result);
// 	}
// 	if (nbr < 0)
// 	{
// 		result[0] = '-';
// 		nbr = -nbr;
// 	}
// 	while (nbr)
// 	{
// 		result[--len] = nbr % 10 + '0';
// 		nbr /= 10;
// 	}
// 	return (result);
// }

// weird one !
// #include <stdlib.h>

// // 🔵 計算數字有幾位
// int	count_digits(int nbr)
// {
// 	int	count;

// 	count = 0; // 🟢 初始化計數
// 	if (nbr == 0)
// 		return (1); // 🟠 特殊情況：0 也算 1 位
// 	while (nbr != 0)
// 	{
// 		nbr = nbr / 10; // 🔵 去掉最後一位
// 		count++;        // 🟢 計數器增加
// 	}
// 	return (count);
// }

// // 🔵 主函數：把整數轉成字串
// char	*ft_itoa(int nbr)
// {
// 	int		len;
// 	char	*result;

// 	long n; // 🔵 用 long，避免處理 -2147483648 出錯
// 	n = nbr;
// 	len = count_digits(n); // 🟢 先算出數字的長度
// 	if (n < 0)
// 	{
// 		n = -n; // 🔵 轉成正數來處理
// 		len++;  // 🟢 多一格留給負號
// 	}
// 	result = (char *)malloc(sizeof(char) * (len + 1)); // 🟢 多一格留給 '\0'
// 	if (!result)
// 		return (NULL);
// 	result[len] = '\0'; // 🟢 字串結尾
// 	while (len > 0)
// 	{
// 		len--;                        // 🟢 先減 len，因為字元要從後面開始放
// 		result[len] = (n % 10) + '0'; // 🔵 取最後一位數字轉成字元
// 		n = n / 10;                   // 🔵 繼續處理下一位
// 		if (n == 0 && nbr < 0 && len == 0)
// 			result[0] = '-'; // 🟢 處理負號
// 	}
// 	return (result);
// }

// #include <stdlib.h>

// char	*ft_itoa(int nbr)
// {
// 	int		len;
// 	int		n;
// 	char	*result;

// 	if (nbr == -2147483648)
// 		return ("-2147483648\0");
// 	n = nbr;
// 	len = 0;
// 	if (nbr <= 0)
// 		len++;
// 	while (n)
// 	{
// 		n /= 10;
// 		len++;
// 	}
// 	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
// 		return (NULL);
// 	result[len] = '\0';
// 	if (nbr == 0)
// 	{
// 		result[0] = '0';
// 		return (result);
// 	}
// 	if (nbr < 0)
// 	{
// 		result[0] = '-';
// 		nbr = -nbr;
// 	}
// 	while (nbr)
// 	{
// 		result[--len] = nbr % 10 + 48;
// 		nbr /= 10;
// 	}
// 	return (result);
// }

// shorter and with less variation and without writing int_min itself but safe
#include <stdlib.h>

char	*ft_itoa(int nbr)
{
	int			len;
	long int	n;
	char		*result;

	n = nbr;
	len = 0;
	if (nbr <= 0)
		len++;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	result[len] = '\0';
	if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (n < 0)
	{
		result[0] = '-';
		n = -n; // it seems do not use the long type
	}
	while (n)
	{
		result[--len] = n % 10 + 48;
		n /= 10;
	}
	return (result);
}
