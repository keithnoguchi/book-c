/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '\0'
#define MAXOP 100

extern int getop(char [], int);

static void push(double);
static double pop(void);

int main(void)
{
	double op2;
	int type;
	char s[MAXOP];

	while ((type = getop(s, MAXOP)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			push(pop() / op2);
			break;
		case '\n':
			printf("\t%g\n", pop());
			break;
		default:
			fprintf(stderr, "error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

#define MAX 12

static double stack[MAX];
static int sp;

static void push(double f)
{
	if (sp < MAX)
		stack[sp++] = f;
	else
		fprintf(stderr, "error: full of stack\n");
}

static double pop(void)
{
	if (sp > 0)
		return stack[--sp];
	else {
		fprintf(stderr, "error: empty stack\n");
		return 0.0;
	}
}
