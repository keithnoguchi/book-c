/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

/* prints out the leap years between year 1 and 3000 */
int main()
{
	int start = 1, end = 3000;
	int year;

	for (year = start; year <= end; year++)
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			printf("%4d\n", year);
}
