/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int getline2(char s[], int limit)
{
	int c, i;

	for (i = 0; (c = getchar()) != EOF && i < limit; i++) {
		s[i] = c;
		if (c == '\n')
			break;
	}

	return i;
}
