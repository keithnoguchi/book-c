/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

static char *month_name(int);

int main(void)
{
	int n;

	for (n = 0; n < 20; n++)
		printf("%02d: %s\n", n, month_name(n));

	return 0;
}

static char *month_name(int n)
{
	static char *name[] = {
		"Illegal month", "January", "February", "March",
		"April", "May", "June", "July", "August", "September",
		"October", "November", "December",
	};
	return (n < 1 || n > 12) ? name[0] : name[n];
}
