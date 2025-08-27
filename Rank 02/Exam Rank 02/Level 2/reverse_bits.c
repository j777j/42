/*

Assignment name  : reverse_bits
Expected files   : reverse_bits.c
Allowed functions:
--------------------------------------------------------------------------------

Write a function that takes a byte, reverses it, bit by bit (like the
example) and returns the result.

Your function must be declared as follows:

unsigned char	reverse_bits(unsigned char octet);

Example:

  1 byte
_____________
 0100  0001
		||
		\/
 1000  0010

*/

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned int	i;
	unsigned char	res;

	res = 0;
	i = 8;
	while (i--)
	{
		// shift all the bits of res by 1 to the left
		// i.e. res: 0000 0101 => 0000 1010
		// perform a bitwise AND on LSB of octet AND 1
		// Least Significant Bit is the right most one
		// i.e octet: 0000 0101 => 1
		// it then performs a bitwise OR between the
		// two LSB and stores the result in res
		// 0000 1010 | 0000 0001 => res: 0000 1011
		res = (res << 1) | (octet & 1);
		// shifting the original octet by 1 to the right
		// so that in next iteration we have the next bit
		octet = octet >> 1;
	}
	return (res);
}

// //another another
// unsigned char	reverse_bits_2(unsigned char octet)
// {
// 	int				i;
// 	unsigned char	res;

// 	i = 8;
// 	res = 0;
// 	while (i > 0)
// 	{
// 		res = res * 2 + (octet % 2);
// 		octet = octet / 2;
// 		i--;
// 	}
// 	return (res);
// }

// // another way
// unsigned char	reverse_bits(unsigned char octet)
// {
// 	int				idx;
// 	unsigned char	bit;

// 	idx = 0x8;
// 	while (idx--)
// 	{
// 		bit = ((bit * 0x2) + (octet % 0x2));
// 		octet /= 0x2;
// 	}
// 	return (bit);
// }
// another way

// unsigned char reverse_bits(unsigned char octet)
// {
//     unsigned char   reversed_octet;
//     int             i;

//     reversed_octet = 0;
//     i = 0;
//     while (i < 8)
//     {
//         // 提取原始字节的当前位 (从右到左，即从第0位到第7位)
//         unsigned char current_bit = (octet >> i) & 1;

//         // 将提取到的位放置到结果字节的对应颠倒位置
//         // 原始位是第 i 位，它在颠倒后的字节中应该位于第 (7 - i) 位
//         reversed_octet = reversed_octet | (current_bit << (7 - i));

//         i = i + 1;
//     }
//     return (reversed_octet);
// }

// best way
unsigned char	reverse_bits(unsigned char octet)
{
	unsigned int	i;
	unsigned char	reverse_octet;

	i = 8;
	reverse_octet = 0;
	while (i--)
	{
		reverse_octet = (reverse_octet << 1) | (octet & 1);
		octet = octet >> 1;
	}
	return (reverse_octet);
}

int	main(void)
{
	printf("%d\n", reverse_bits(2));
	printf("%d\n", reverse_bits_2(2));
}
