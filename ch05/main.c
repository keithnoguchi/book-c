/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define MAXLINE 4
static char *lines[MAXLINE];

static int readlines(char *[], int);
static void writelines(char *[], int);

int main(int argc, char *argv[])
{
	const char *progname = argv[0];
	int c, n, numeric = 0, ret = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
			case 'n':
				numeric = 1;
				break;
			default:
				fprintf(stderr, "invalid option: %c\n", c);
				argc = 0;
				ret = 1;
				break;
			}
	if (argc != 1)
		printf("usage: %s -n pattern\n", progname);
	else
		while ((n = readlines(lines, MAXLINE)) > 0)
			writelines(lines, n);

	printf("numeric=%d\n", numeric);
	return ret;
}

static int readlines(char *lines[], int nr)
{
	char *alloc(int), *strcpy(char *, char *);
#define LINESIZE 80
	char line[LINESIZE], *p, *limit;
	int n, c;

	limit = line + LINESIZE - 1;
	for (n = 0; n < nr; n++) {
		for (p = line; p < limit && (c = getchar()) != EOF; p++) {
			*p = c;
			if (c == '\n')
				break;
		}
		if (c == EOF)
			break;
		else if (c == '\n')
			p++;
		*p++ = '\0';
		lines[n] = alloc(p - line);
		strcpy(lines[n], line);
	}
	return n;
}

static void writelines(char *lines[], int nr)
{
	void afree(char *);
	int n;

	for (n = 0; n < nr; n++)
		printf("%s", lines[n]);

	/* free lines in reverse order */
	for (n = nr - 1; n >= 0; n--) {
		afree(lines[n]);
		lines[n] = NULL;
	}
}

char *strcpy(char *s, char *t)
{
	char *start = s;
	while ((*s++ = *t++))
		;
	return start;
}

#define BUFSIZE 1000
static char allocbuf[BUFSIZE];
static char *allocp = allocbuf;

char *alloc(int nr)
{
	if (allocp + nr <= allocbuf + BUFSIZE) {
		allocp += nr;
		return allocp - nr;
	} else {
		fprintf(stderr, "alloc: overflow with nr=%d\n", nr);
		return NULL;
	}
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocp)
		allocp = p;
	else
		fprintf(stderr, "free: invalid pointer p=%p\n", p);
}
