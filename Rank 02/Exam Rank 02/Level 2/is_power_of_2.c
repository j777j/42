/*

Assignment name  : is_power_of_2
Expected files   : is_power_of_2.c
Allowed functions: None
--------------------------------------------------------------------------------

Write a function that determines if a given number is a power of 2.

This function returns 1 if the given number is a power of 2,
	otherwise it returns 0.

Your function must be declared as follows:

int	is_power_of_2(unsigned int n);

*/


int	is_power_of_2(unsigned int n)
{
	return ((n &&(n & (n - 1)) == 0)); // binary example 4: 0100 & 0011 = 0100
}




int	is_power_of_2(unsigned int n)
{
	if (n == 0)
		return (0);
	return ((n & (n - 1)) == 0); // binary example 4: 0100 & 0011 = 0100
}

int	main(void)
{
	printf("is_power_of_2(0) = %d (預期 0)\n", is_power_of_2(0));       // 不是 2 的冪
	printf("is_power_of_2(1) = %d (預期 1)\n", is_power_of_2(1));       // 2^0
	printf("is_power_of_2(2) = %d (預期 1)\n", is_power_of_2(2));       // 2^1
	printf("is_power_of_2(3) = %d (預期 0)\n", is_power_of_2(3));       // 不是 2 的冪
	printf("is_power_of_2(4) = %d (預期 1)\n", is_power_of_2(4));       // 2^2
	printf("is_power_of_2(8) = %d (預期 1)\n", is_power_of_2(8));       // 2^3
	printf("is_power_of_2(7) = %d (預期 0)\n", is_power_of_2(7));       // 不是 2 的冪
	printf("is_power_of_2(16) = %d (預期 1)\n", is_power_of_2(16));     // 2^4
	printf("is_power_of_2(1024) = %d (預期 1)\n", is_power_of_2(1024)); // 2^10
	printf("is_power_of_2(1023) = %d (預期 0)\n", is_power_of_2(1023)); // 不是 2 的冪
	// 測試一個大數，接近 int 最大值
	// unsigned int max_val_test = 2147483648U; // 2^31 (對於 32-bit unsigned int)
	// printf("is_power_of_2(2147483648U) =%d (預期 1)\n",is_power_of_2(max_val_test));
	return (0);
}
