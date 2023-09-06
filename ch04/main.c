/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define MAXLINE 100

extern int getline2(char s[], int limit);

int main()
{
	char line[MAXLINE];

	while (getline2(line, sizeof(line)) > 0)
		printf("%s", line);
}
