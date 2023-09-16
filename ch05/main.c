/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 4
static char *lines[MAXLINE];
static char *sorted[MAXLINE];

static void quicksort(void *[], int, int, int (*)(void *, void *));
static int readlines(char *[], int);
static void writelines(char *[], int);

int main(int argc, char *argv[])
{
	int strcmp(char *, char *), numcmp(char *, char *);
	int (*comp)(void *, void *) = (int (*)(void *, void *))strcmp;
	void afree(char *);
	int ret = EXIT_SUCCESS;
	int i, c, n;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
			case 'n':
				comp = (int (*)(void *, void *))numcmp;
				break;
			default:
				fprintf(stderr, "invalid option: %c\n", c);
				ret = EXIT_FAILURE;
				argc = 0;
				break;
			}
	while ((n = readlines(lines, MAXLINE)) > 0) {
		for (i = 0; i < n; i++)
			sorted[i] = lines[i];
		quicksort((void **)sorted, 0, n - 1, comp);
		writelines(sorted, n);
		for (i = n - 1; i >= 0; i--)
			afree(lines[i]);
	}
	return ret;
}

static void quicksort(void *v[], int left, int right,
		      int (*comp)(void *, void *))
{
	void swap(void *[], int, int);
	int i, last;

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, i, ++last);
	swap(v, left, last);
	quicksort(v, left, last - 1, comp);
	quicksort(v, last + 1, right, comp);
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
	int n;

	for (n = 0; n < nr; n++)
		printf("%s", lines[n]);
}

char *strcpy(char *s, char *t)
{
	char *start = s;
	while ((*s++ = *t++))
		;
	return start;
}

int strcmp(char *s, char *t)
{
	int i;

	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;
	return s[i] - t[i];
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	return v1 - v2;
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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
		fprintf(stderr, "afree: invalid pointer p=%p\n", p);
}
