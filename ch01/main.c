/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

/* power: raise base to n-th power; n >= 0 */
int power(int base, int n)
{
	int i, p;

	p = 1;
	for (i = 1; i <= n; i++)
		p *= base;

	return p;
}

int main()
{
	int i;

	for (i = 0; i < 10; i++)
		printf("%d %d %7d\n", i, power(2, i), power(-3, i));

	return 0;
}
