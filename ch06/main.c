/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <ctype.h>

struct key {
	char *name;
	int count;
} keytab[] = {
	{ "auto", 0, },
	{ "break", 0, },
};

#define NKEYS sizeof keytab / sizeof keytab[0]
#define MAXWORD 100

static int getword(char *, int);
static int binsearch(char *, struct key *, int);

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
			printf("%04d %s\n", keytab[n].count, keytab[n].name);

	return 0;
}

static int getword(char *word, int limit)
{
	return EOF;
}

static int binsearch(char *word, struct key *keytab, int nkey)
{
	return -1;
}
