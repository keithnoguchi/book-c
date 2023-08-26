/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int main()
{
	int c;

	c = getchar();
	while (c != EOF) {
		putchar(c);
		c = getchar();
	}
}
