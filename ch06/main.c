/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <ctype.h>

struct key {
	char *name;
	int count;
} keytab[] = {
	{ "auto", 0, },
	{ "break", 0, },
	{ "char", 0, },
	{ "continue", 0, },
	{ "while", 0, },
	{ "int", 0, },
};

#define NKEYS sizeof keytab / sizeof keytab[0]
#define MAXWORD 100

static int binsearch(char *, struct key *, int);
static int getword(char *, int);

int main(void)
{
	char word[MAXWORD];
	int n;

	while (getword(word, sizeof word) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;

	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].name);

	return 0;
}

static int binsearch(char *word, struct key *keytab, int n)
{
	int strcmp(const char [], const char []);
	int low, high, mid;
	int cond;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if ((cond = strcmp(word, keytab[mid].name)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int strcmp(const char s[], const char t[])
{
	int i;

	for (i = 0; s[i] == t[i]; i++)
		if (s[i] == '\0')
			return 0;

	return s[i] - t[i];
}

static int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

static char buf[BUFSIZ];
static char *bufp = buf;

int getch(void)
{
	if (bufp != buf)
		return *--bufp;
	else
		return getchar();
}

void ungetch(int c)
{
	if (bufp >= buf + sizeof buf)
		fprintf(stderr, "ungetch: not more buffer space\n");
	else {
		fprintf(stderr, "ungetch: push(%c)\n", c);
		*bufp++ = c;
	}
}
