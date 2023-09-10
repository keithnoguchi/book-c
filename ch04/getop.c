/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <ctype.h>

#include "getop.h"

#define BUFSIZE 200

static int getch(void);
static void ungetch(int);

int getop(char s[], int limit)
{
	int i, c;

	/* skip white spaces */
	if (limit < 1)
		return -1;
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; /* not a number */
	i = 0;
	if (isdigit(c)) /* collect the integer part */
		while (i < limit - 1 && isdigit(s[++i] = c = getch()))
			;
	if (c == '.') /* collect the fraction part */
		while (i < limit - 1 && isdigit(s[++i] = c = getch()))
		       ;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

static char buf[BUFSIZE];
static int bufp = 0;

static int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

static void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
