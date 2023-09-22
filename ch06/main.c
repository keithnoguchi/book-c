/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <stdlib.h>

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
	return EOF;
}
