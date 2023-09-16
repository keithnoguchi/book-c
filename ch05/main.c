/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[])
{
	int getaline(char *, int);
	char line[MAXLINE];
	int found = 0;

	if (argc < 2)
		printf("usage: %s pattern\n", argv[0]);
	else
		while (getaline(line, sizeof(line)) > 0)
			if (strstr(line, argv[1]) != NULL) {
				printf("%s", line);
				found++;
			}

	return found;
}

int getaline(char *line, int limit)
{
	char *p = line;
	int c = EOF;

	for (p = line; line - p < limit - 1 && (c = getchar()) != EOF; p++) {
		*p = c;
		if (c == '\n')
			break;
	}
	if (c == '\n')
		p++;
	*p = '\0';

	return p - line;
}
