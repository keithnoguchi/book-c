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

int readlines(char *lineptr[], int maxline)
{
	return -1;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

void quicksort(char *v[], int left, int right)
{
	return;
}
