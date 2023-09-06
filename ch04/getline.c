/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int getline2(char s[], int limit)
{
	int i, c = 0;

	for (i = 0; i < limit - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		i++;
	}
	s[i] = '\0';
	return i;
}
