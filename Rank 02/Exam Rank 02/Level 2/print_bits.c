/*

Assignment name  : print_bits
Expected files   : print_bits.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a function that takes a byte, and prints it in binary WITHOUT A NEWLINE
AT THE END.

Your function must be declared as follows:

void	print_bits(unsigned char octet);

Example, if you pass 2 to print_bits, it will print "00000010"

*/

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int i = 8;             // Initialize a counter variable i to 8
	unsigned char bit = 0; // Initialize a variable bit to 0
	while (i--)            // Loop through each bit of octet
	{
		bit = (octet >> i & 1) + 48;
		// Shift the bit of octet to the right i times and use the bitwise AND operator with 1 to get the bit value. Then add 48 to convert the bit value to its ASCII representation ('0' or '1')
		write(1, &bit, 1);
		// Write the ASCII representation of the bit to the standard output (stdout)
	}
}

// another
// void	print_bits(unsigned char octet)
// {
// 	int				maxbits;
// 	unsigned char	bit;

// 	maxbits = 8;
// 	while (maxbits--)
// 	{
// 		bit = (octet >> maxbits & 1) + '0';
// 		write(1, &bit, 1);
// 	}
// }

// another another

int	main(void)
{
	unsigned char test1 = 0;   // 00000000
	unsigned char test2 = 1;   // 00000001
	unsigned char test3 = 2;   // 00000010
	unsigned char test4 = 128; // 10000000
	unsigned char test5 = 255; // 11111111
	unsigned char test6 = 42;  // 00101010
	printf("0 的二進位表示: ");
	print_bits(test1);
	printf("\n"); // 印出換行以分隔輸出
	printf("1 的二進位表示: ");
	print_bits(test2);
	printf("\n");
	printf("2 的二進位表示: ");
	print_bits(test3);
	printf("\n");
	printf("128 的二進位表示: ");
	print_bits(test4);
	printf("\n");
	printf("255 的二進位表示: ");
	print_bits(test5);
	printf("\n");
	printf("42 的二進位表示: ");
	print_bits(test6);
	printf("\n");
	return (0);
}

#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int				i;
	unsigned char	bit;

	i = 8;
	bit = 0;
	while (i--)
	{
		bit = (octet >> i & 1) + 48;
		write(1, &bit, 1);
	}
}
