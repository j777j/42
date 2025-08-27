/*
Assignment name  : ft_strdup
Expected files   : ft_strdup.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Reproduce the behavior of the function strdup (man strdup).

Your function must be declared as follows:

char	*ft_strdup(char *src);
*/

#include <stdlib.h>

char	*ft_strdup(char *src)
{
	char	*tmp;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (src[len])
		len++;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (src[i])
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	main(void)
{
	char	*my_string;

	my_string = "Hello 42 School!";
	char *duplicate_string;                  // 宣告一個指標來接收 ft_strdup 的回傳值
	duplicate_string = ft_strdup(my_string); // 呼叫 ft_strdup 並儲存回傳的指標
	if (duplicate_string == NULL)            // 總是檢查 malloc 是否成功
	{
		printf("記憶體分配失敗！\n");
		return (1); // 回傳非零值表示錯誤
	}
	printf("原始字串: %s\n", my_string);
	printf("複製字串: %s\n", duplicate_string);
	// 當你不再需要 duplicate_string 指向的記憶體時，釋放它
	free(duplicate_string);
	duplicate_string = NULL; // 設置為 NULL 是個好習慣
	printf("記憶體已釋放。\n");
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*a;
	a = "Hello42";
	printf("%s\n",ft_strdup(a));
}*/
