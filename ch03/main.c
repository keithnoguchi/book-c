/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

/* https://en.wikipedia.org/wiki/Shellsort */
void shellsort(int v[], int n)
{
	int gap, i, j, temp;

	for (gap = n/2; gap > 0; gap >>= 1)
		for (i = gap; i < n; i++)
			for (j = i - gap; j >= 0 && v[j] > v[j+gap]; j -= gap)
				temp = v[j], v[j] = v[j+gap], v[j+gap] = temp;
}

/* https://en.wikipedia.org/wiki/Insertion_sort */
void insertionsort(int v[], int n)
{
	int i, j, temp;

	for (i = 1; i < n; i++) {
		temp = v[i];
		for (j = i - 1; j >= 0; j--)
			if (v[j] > temp)
				v[j+1] = v[j]; /* push back */
			else
				break;
		v[j+1] = temp;
	}
}

/* https://en.wikipedia.org/wiki/Bubble_sort */
void bubblesort(int v[], int n)
{
	int i, j, temp;

	for (i = n-1; i > 0; i--)
		for (j = 0; j < i; j++)
			if (v[j] > v[j+1])
				temp = v[j], v[j] = v[j+1], v[j+1] = temp;
}

int main()
{
	int i, n, v[24];

	n = sizeof(v) / sizeof(int);
	for (i = 0; i < n; i++)
		v[i] = ~i;

	shellsort(v, n);
	for (i = 0; i < n; i++)
		printf("%d%c", v[i], (i % 7 == 6 || i == n - 1) ? '\n' : ' ');
}
