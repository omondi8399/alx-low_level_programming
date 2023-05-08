#include "main.h"

/**
 * flip_bits - number of bit you need to flip to get from
 * one number to another
 * @n: the number to be flipped
 * @m: the number to get to
 *
 * Return: number of bits to be flipped
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned int bits;

	for (bits = 0; n || m; n >>= 1, m >>= 1)
	{
		if ((n & 1) != (m & 1))
			bits++;
	}
	return (bits);
}
