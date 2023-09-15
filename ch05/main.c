/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int ret, i, getint(int *);

	while ((ret = getint(&i)) != EOF) {
		if (ret == 0) {
			fprintf(stderr, "not a number\n");
			break;
		}
		printf("\t%d = getint(%d)\n", ret, i);
	}
	return !ret;
}

int getint(int *np)
{
	int getch(void);
	void ungetch(int);
	int c, sign;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = c == '-' ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*np = 0; isdigit(c); c = getch())
		*np = *np * 10 + (c - '0');
	*np *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define SIZE 10

static int stack[SIZE];
static int sp;

int getch(void)
{
	if (sp > 0)
		return stack[--sp];
	else
		return getchar();
}

void ungetch(int c)
{
	if (sp >= SIZE)
		fprintf(stderr, "ungetch: stack is full\n");
	else
		stack[sp++] = c;
}
