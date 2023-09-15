/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int main(void)
{
	double d, *a, *b, *p, *alloc(int);
	void afree(double *);
	int i;

	a = alloc(50);
	for (p = a, d = 0.0; d < 50.0; d += 1.0)
		*p++ = d;
	b = alloc(50);
	for (p = b, d = 50.0; d < 100.0; d += 1.0)
		*p++ = d;

	for (p = a, i = 0; i < 100; i++)
		printf("%2g%c", *p++, i % 10 == 9 ? '\n' : ' ');

	afree(b);
	afree(a);
}

#define SIZE 100
static double allocbuf[SIZE];
static double *allocp = allocbuf;

double *alloc(int n)
{
	if (allocp + n <= allocbuf + SIZE) {
		allocp += n;
		return allocp - n;
	} else
		return 0;
}

void afree(double *p)
{
	if (p >= allocbuf && p < allocp)
		allocp = p;
}
