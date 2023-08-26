/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int main()
{
	int c;

	while ((c = getchar()) != EOF)
		putchar(c);
}
