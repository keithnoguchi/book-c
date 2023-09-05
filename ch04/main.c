/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define MAXLINE 120

extern int getline2(const char s[], int limit);
extern int strindex(const char s[], const char t[]);

const char pattern[] = "ould";

int main()
{
	char line[MAXLINE];
	int found = 0;

	while (getline2(line, MAXLINE) > 0)
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}

	return found;
}
