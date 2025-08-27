/*

Assignment name  : max
Expected files   : max.c
Allowed functions:
--------------------------------------------------------------------------------

Write the following function:

int	max(int* tab, unsigned int len);

The first parameter is an array of int, the second is the number of elements in
the array.

The function returns the largest number found in the array.

If the array is empty, the function returns 0.

*/

int	max(int *tab, unsigned int len)
{
	unsigned int	i;
	int				max;

	if (len == 0)
		return (0);
	i = -1;
	max = tab[0];
	while (++i < len)
	{
		if (tab[i] > max)
			max = tab[i];
	}
	return (max);
}

int	main(void)
{
	int				arr1[] = {1, 5, 2, 8, 3};
	unsigned int	len1;
	int				arr2[] = {10, 20, 5, 30, 15};
	unsigned int	len2;
	int				arr3[] = {-1, -5, -2, -8, -3};
	unsigned int	len3;
	int				arr4[] = {7};
	unsigned int	len4;
	unsigned int	len5;
	int				arr6[] = {0, -10, 5, 0, 100, -200};
	unsigned int	len6;

	len1 = 5;
	printf("陣列: {1, 5, 2, 8, 3}, 最大值: %d (預期 8)\n", max(arr1, len1));
	len2 = 5;
	printf("陣列: {10, 20, 5, 30, 15}, 最大值: %d (預期 30)\n", max(arr2, len2));
	len3 = 5;
	printf("陣列: {-1, -5, -2, -8, -3}, 最大值: %d (預期 -1)\n", max(arr3, len3));
	len4 = 1;
	printf("陣列: {7}, 最大值: %d (預期 7)\n", max(arr4, len4));
	int arr5[] = {}; // 空陣列
	len5 = 0;
	printf("陣列: {}, 最大值: %d (預期 0)\n", max(arr5, len5));
	len6 = 6;
	printf("陣列: {0, -10, 5, 0, 100, -200}, 最大值: %d (預期 100)\n", max(arr6,
			len6));
	return (0);
}

int	max(int *tab, unsigned int len)
{
	unsigned int i;
	int result;

	i = 1;
	if (len > 0)
	{
		result = tab[0];
		while (i < len)
		{
			if (result < tab[i])
				result = tab[i];
			i++;
		}
		return (result);
	}
	return (0);
}
