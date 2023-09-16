/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <string.h>

static int getaline(char *, int);

int main(int argc, char *argv[])
{
#define MAXLINE 80
	const char *progname = argv[0];
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				fprintf(stderr, "illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}

	if (argc != 1)
		printf("usage: %s -x -n pattern\n", progname);
	else
		while (getaline(line, sizeof(line)) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				found++;
				if (number)
					printf("%ld: ", lineno);
				printf("%s", line);
			}
		}
	return found;
}

static int getaline(char *line, int limit)
{
	char *p;
	int c;

	for (p = line; (c = getchar()) != EOF && p - line < limit - 1; p++) {
		*p = c;
		if (c == '\n')
			break;
	}
	if (c == '\n')
		++p;
	*p = '\0';
	return p - line;
}
