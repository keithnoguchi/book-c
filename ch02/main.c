/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int main()
{
	char a[64];
	int n, i;

	n = sizeof(a) / sizeof(char);
	for (i = 0; i < n; i++)
		a[i] = i + 1;

	/* the ternary operator example */
	for (i = 0; i < n; i++)
		printf("%3d%c", a[i],
		       (i % 7 == 6 || i == n - 1) ? '\n' : ' ');
}
