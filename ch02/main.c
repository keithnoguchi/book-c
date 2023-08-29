/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

/* getbits: machine independent bit retriever. */
static unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main()
{
	printf("0%o\n", ~0); // 037777777777 on 32bit word machine
	printf("0%o\n", getbits(0x0f, 4, 3)); // 03
	printf("0%o\n", getbits(0x1f, 4, 3)); // 07
}
