/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

static int binarysearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main()
{
	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int len = sizeof(v) / sizeof(int);
	int i;

	for (i = 0; i < 12; i++)
		printf("%2d is in index=%d\n", i, binarysearch(i, v, len));
}
