/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define MAXLINE 80

static int getline2(char s[], int lim)
{
	int i, c;

	for (i = 0; i < lim - 1
	     && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i] = '\0';
		i++;
	}
	return i;
}

static void copy(char to[], char from[])
{
	int i = 0;

	while ((to[i] = from[i]) != '\0')
		i++;
}

int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];

	max = 0;
	while ((len = getline2(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}

	if (max > 0)
		printf("%s", longest);

	return 0;
}
