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

struct node *add(struct node *p, const char *word)
{
	struct node *alloc(void);
	char *strdup(const char *);
	int strcmp(const char *, const char *);
	int cond;

	if (p == NULL) {
		p = alloc();
		p->word = strdup(word);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(word, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = add(p->left, word);
	else
		p->right = add(p->right, word);
	return p;
}

struct node *alloc(void)
{
	return (struct node *)malloc(sizeof(struct node));
}

char *strdup(const char *s)
{
	unsigned long strlen(const char *);
	char *strcpy(char *, const char *);
	char *t;

	t = (char *)malloc(strlen(s) + 1);
	if (t != NULL)
		strcpy(t, s);
	return t;
}

int strcmp(const char *s, const char *t)
{
	int i;

	for (i = 0; s[i] == t[i]; i++)
		if (t[i] == '\0')
			return 0;
	return s[i] - t[i];
}

unsigned long strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != '\0'; len++)
		;
	return len;
}

char *strcpy(char *s, const char *t)
{
	while (*t != '\0')
		*s++ = *t++;
	*s = '\0';
	return s;
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
