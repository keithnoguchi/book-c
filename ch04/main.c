/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

static void quicksort(int v[], int left, int right);

static void push(double);
static double pop(void);

int main(void)
{
	int v[50];
	int i;

	srand(time(NULL));
	for (i = 0; i < sizeof(v) / sizeof(int); i++)
		v[i] = rand() % 100;

	quicksort(v, 0, sizeof(v) / sizeof(int) - 1);

	for (i = 0; i < sizeof(v) / sizeof(int); i++)
		printf("%2d%c", v[i], i % 10 == 9 ? '\n' : ' ');
}

static void swap(int [], int, int);

static void quicksort(int v[], int left, int right)
{
	int i, last;

	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);
	quicksort(v, left, last - 1);
	quicksort(v, last  + 1, right);
}

void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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
