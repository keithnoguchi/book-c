/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define MAXLINE 10

/* sort(1) program */
int main(void)
{
	int readlines(char *[], int);
	void writelines(char *[], int), quicksort(char *[], int, int);
	static char *lineptr[MAXLINE];
	int nlines;

	if ((nlines = readlines(lineptr, MAXLINE)) > 0) {
		quicksort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
	}

	return 0;
}

int readlines(char *lineptr[], int maxlines)
{
#define MAXLEN 10
	char *p, *alloc(int), line[MAXLEN], *strcpy(char *, char *);
	int len, nlines, getaline(char *, int);

	nlines = 0;
	while ((len = getaline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			/* drop the newline character */
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			printf("lineptr[%d]='%s'\n", nlines - 1, lineptr[nlines - 1]);
		}
	}
	return nlines;
}

void quicksort(char *v[], int left, int right)
{
	return;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int getaline(char *line, int nlimit)
{
	char *p, *limit;
	int c = EOF;

	for (p = line, limit = p + nlimit; p < limit - 1 && (c = getchar()) != EOF && c != '\n'; p++)
		*p = c;
	if (c == '\n' && p < limit - 2)
		*p++ = c;
	*p = '\0';
	return p - line;
}

#define ALLOCSIZE 1000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if (allocp + n < allocbuf + ALLOCSIZE) {
		allocp += n;
		return allocp - n;
	} else
		return NULL;
}

void afree(char *p)
{
	if (p >= allocbuf && p < allocp)
		allocp = p;
}

char *strcpy(char *s, char *t)
{
	while ((*s++ = *t++))
		;
	return s;
}
