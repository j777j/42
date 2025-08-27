/*

Assignment name  : ft_rrange
Expected files   : ft_rrange.c
Allowed functions: malloc
--------------------------------------------------------------------------------

Write the following function:

int	*ft_rrange(int start, int end);

It must allocate (with malloc()) an array of integers, fill it with consecutive
values that begin at end and end at start (Including start and end !), then
return a pointer to the first value of the array.

Examples:

- With (1, 3) you will return an array containing 3, 2 and 1
- With (-1, 2) you will return an array containing 2, 1, 0 and -1.
- With (0, 0) you will return an array containing 0.
- With (0, -3) you will return an array containing -3, -2, -1 and 0.

*/

#include <stdlib.h>

int	*ft_rrange(int start, int end)
{
	int	i;
	int	len;
	int	*rrange;

	i = 0;
	if (start <= end)
		len = end - start + 1;
	else
		len = start - end + 1;
	rrange = malloc(sizeof(int) * len);
	if (!rrange)
		return (NULL);
	while (i < len)
	{
		if (start <= end)
			rrange[i] = end--;
		else
			rrange[i] = end++;
		i++;
	}
	return (rrange);
}

// from abesan
// #include <stdlib.h>

// int ft_rrange(int start, int end)
// {
//     int *range;
//     int i = 0;
//     int step = 1;
//     int n = end - start;

//     if (n < 0)
//         (n = -1);
//     n++;

//     range = (int)malloc(sizeof(int) * n);
//     if (range)
//     {
//         if (start < end)
//             step = -1;
//         while (i < n)
//         {
//             range[i] = end;
//             end = end + step;
//             i++;
//         }
//     }
//     return (range);
// }

// #include <stdio.h>
// #include <stdlib.h>

// static int	ft_absolute_value(int number)
// {
// 	if (number < 0)
// 		return (-number);
// 	return (number);
// }

// int	*ft_rrange(int start, int end)
// {
// 	int	len;
// 	int	*res;
// 	int	i;
// 	int	current_val;

// 	len = ft_absolute_value(end - start) + 1;
// 	res = (int *)malloc(sizeof(int) * len);
// 	if (res == NULL)
// 		return (NULL);
// 	i = 0;
// 	current_val = end;
// 	while (i < len)
// 	{
// 		res[i] = current_val;
// 		if (end > start)
// 			current_val--;
// 		else if (end < start)
// 			current_val++;
// 		i++;
// 	}
// 	return (res);
// }

// int	main(void)
// {
// 	int	*tab;
// 	int	i;
// 	int	start_val;
// 	int	end_val;
// 	int	actual_len;

// 	start_val = 1;
// 	end_val = 3;
// 	actual_len = ft_absolute_value(end_val - start_val) + 1;
// 	tab = ft_rrange(start_val, end_val);
// 	printf("ft_rrange(%d, %d) 應為 3, 2, 1:\n", start_val, end_val);
// 	if (tab != NULL)
// 	{
// 		i = 0;
// 		while (i < actual_len)
// 		{
// 			printf("%d ", tab[i]);
// 			i++;
// 		}
// 		printf("\n");
// 		free(tab);
// 	}
// 	else
// 	{
// 		printf("ft_rrange 記憶體分配失敗或邏輯錯誤！\n");
// 	}
// 	return (0);
// }
