/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXWORD 20

struct node {
	char *word;
	int count;
	struct node *left;
	struct node *right;
};

int main(void)
{
	struct node *add(struct node *, const char *);
	void print(const struct node *);
	int getword(char *, int);
	char word[MAXWORD];
	struct node *root;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		root = add(root, word);

	print(root);

	return 0;
}

struct node *add(struct node *root, const char *word)
{
	return NULL;
}

void print(const struct node *root)
{
	if (root != NULL) {
		print(root->left);
		printf("%4d %s\n", root->count, root->word);
		print(root->right);
	}
}

int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *p = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*p++ = c;
	if (!isalpha(c)) {
		*p = '\0';
		return c;
	}
	for ( ; --lim > 0; p++)
		if (!isalnum(*p = getch())) {
			ungetch(*p);
			break;
		}
	*p = '\0';
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
	if (bufp == buf + BUFSIZ)
		fprintf(stderr, "ungetch: buffer full\n");
	else
		*bufp++= c;
}
