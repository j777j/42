/*

Assignment name  : swap_bits
Expected files   : swap_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that takes a byte, swaps its halves (like the example) and
returns the result.

Your function must be declared as follows:

unsigned char	swap_bits(unsigned char octet);

Example:

  1 byte
_____________
 0100 | 0001
		\ /
		/ \
 0001 | 0100

*/

unsigned char	swap_bits(unsigned char octet)
{
	return ((octet >> 4) | (octet << 4));
}

// // 輔助函式：用於印出 unsigned char 的二進位表示，方便驗證
// void	print_binary(unsigned char n)
// {
// 	int	i;

// 	i = 7;
// 	while (i >= 0)
// 	{
// 		printf("%d", (n >> i) & 1);
// 		i--;
// 	}
// }

// int	main(void)
// {
// 	unsigned char test1 = 0b00001111; // 十進位 15
// 	unsigned char test2 = 0b11110000; // 十進位 240
// 	unsigned char test3 = 0b10100101; // 十進位 165
// 	unsigned char test4 = 0b01011010; // 十進位 90
// 	unsigned char test5 = 0b00000000; // 十進位 0
// 	unsigned char test6 = 0b11111111; // 十進位 255
// 	printf("原始: ");
// 	print_binary(test1);
// 	printf(" -> 交換: ");
// 	print_binary(swap_bits(test1));
// 	printf(" (預期 11110000 / 240)\n");
// 	printf("原始: ");
// 	print_binary(test2);
// 	printf(" -> 交換: ");
// 	print_binary(swap_bits(test2));
// 	printf(" (預期 00001111 / 15)\n");
// 	printf("原始: ");
// 	print_binary(test3);
// 	printf(" -> 交換: ");
// 	print_binary(swap_bits(test3));
// 	printf(" (預期 01011010 / 90)\n");
// 	printf("原始: ");
// 	print_binary(test4);
// 	printf(" -> 交換: ");
// 	print_binary(swap_bits(test4));
// 	printf(" (預期 10100101 / 165)\n");
// 	printf("原始: ");
// 	print_binary(test5);
// 	printf(" -> 交換: ");
// 	print_binary(swap_bits(test5));
// 	printf(" (預期 00000000 / 0)\n");
// 	printf("原始: ");
// 	print_binary(test6);
// 	printf(" -> 交換: ");
// 	print_binary(swap_bits(test6));
// 	printf(" (預期 11111111 / 255)\n");
// 	return (0);
// }
