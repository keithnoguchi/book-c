/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

static int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x >>= 1)
		if (x & 01)
			b++;

	return b;
}

int main()
{
	printf("0x%x = %d\n", ~0, bitcount(~0)); // 32 or 64
						 // depending on
						 // the unsigned
						 // type, e.g
						 // int or long.
}
