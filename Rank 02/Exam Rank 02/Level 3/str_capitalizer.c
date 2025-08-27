/*
Assignment name  : str_capitalizer
Expected files   : str_capitalizer.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes one or several strings and, for each argument,
capitalizes the first character of each word (If it's a letter, obviously),
puts the rest in lowercase, and displays the result on the standard output,
followed by a \n.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string. If a word only has one letter, it must be
capitalized.

If there are no arguments, the progam must display \n.

Example:

$> ./str_capitalizer | cat -e
$
$> ./str_capitalizer "a FiRSt LiTTlE TESt" | cat -e
A First Little Test$
$> ./str_capitalizer "__SecONd teST A LITtle BiT   Moar comPLEX" "   But... This iS not THAT COMPLEX" "     Okay,
	this is the last 1239809147801 but not    the least    t" | cat -e
__second Test A Little Bit   Moar Complex$
   But... This Is Not That Complex$
		Okay, This Is The Last 1239809147801 But Not    The Least    T$
$>
*/

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac == 1)
		write(1, "\n", 1);
	else
		// Loop over all params starting at 1 (we don't want the name of
		// the executable to be written to the screen)
		while (i < ac)
		{
			{
				j = 0;
				while (av[i][j])
				{
					// If the character is uppercase, make it lowercase
					if (av[i][j] >= 'A' && av[i][j] <= 'Z')
						av[i][j] += 32;
					// Now check for lowercase character and if the next char
					// is a space character, make it uppercase again
					if ((av[i][j] >= 'a' && av[i][j] <= 'z') && (av[i][j
							- 1]) <= 32)
						av[i][j] -= 32;
					// Now print every char
					write(1, &av[i][j++], 1);
				}
			}
			write(1, "\n", 1);
			i++;
		}
}

// #include <unistd.h> // For write

// // 輔助函式：檢查字元是否為空白字元 (只考慮空格和 tab)
// static int	ft_isspace(char c)
// {
// 	if (c == ' ' || c == '\t')
// 		return (1);
// 	return (0);
// }

// // 輔助函式：將字元轉換為小寫
// static int	ft_tolower(int c)
// {
// 	if ((c >= 'A') && (c <= 'Z'))
// 		c += ('a' - 'A');
// 	return (c);
// }

// // 輔助函式：將字元轉換為大寫
// static int	ft_toupper(int c)
// {
// 	if ((c >= 'a') && (c <= 'z'))
// 		c -= ('a' - 'A');
// 	return (c);
// }

// // 輔助函式：檢查字元是否為字母 (大寫或小寫)
// // 為了避免重複定義 ft_islower 和 ft_isalpha，我們使用 ft_isalpha 更通用
// // 因為題目定義 A letter is a character in the set [a-zA-Z]
// static int	ft_isalpha(char c)
// {
// 	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
// 		return (1);
// 	return (0);
// }

// // 核心處理函式：將字串中的每個單詞的第一個字母大寫，其他字母小寫
// // 符合規範：無註解，只使用 while 迴圈，變數定義與賦值分離
// void	capitalizer(char *s)
// {
// 	int	i;

// 	i = 0;       // 先定義，再賦值
// 	while (s[i]) // 遍歷字串
// 	{
// 		// 將當前字母轉換為小寫 (這是處理原則的第一步)
// 		s[i] = ft_tolower(s[i]);
// 		// 判斷是否為單詞的第一個字母，並將其大寫
// 		// 條件：當前字元是字母 AND (是字串的第一個字元 OR 前一個字元是空白字元)
// 		if (ft_isalpha(s[i]) && (i == 0 || ft_isspace(s[i - 1])))
// 			s[i] = ft_toupper(s[i]); // 轉換為大寫
// 		write(1, &s[i], 1);          // 印出處理後的字元
// 		i++;                         // 推進索引
// 	}
// }

// int	main(int ac, char **av)
// {
// 	int i;                 // 先定義，再賦值
// 	i = 1;                 // 賦值
// 	if (ac == 1)           // 如果沒有參數 (只有程式名)
// 		write(1, "\n", 1); // 則只印出換行符 (使用 write 效率更高且避免 printf 依賴)
// 	else
// 	{
// 		while (i < ac) // 遍歷所有命令列參數字串
// 		{
// 			capitalizer(av[i]); // 處理當前參數字串
// 			write(1, "\n", 1);  // 每個參數字串處理完後印出換行符
// 			i++;                // 推進到下一個參數
// 		}
// 	}
// 	return (0); // main 函式回傳 0 表示成功
// }
