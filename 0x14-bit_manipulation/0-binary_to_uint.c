#include "main.h"

/**
 * binary_to_uint - converts a binary number to unsigned int
 * @b: pointer to a string of 0 and 1
 *
 * Return: the converted number or 0 if there is one or more characters
 * in the string b that is not 0 or 1, or if b is NULL
 */

unsigned int binary_to_uint(const char *b)
{
	unsigned int dec = 0;
	int i, base;

	if (b == NULL)
		return (0);

	for (i = 0; b[i] != '\0'; ++i)
		;

	for (--i, base = 1; i >= 0; --i, base *= 2)
	{
		if (b[i] != '0' && b[i] != '1')
			return (0);

		if (b[i] & 1)
			dec += base;
	}
	return (dec);
}
