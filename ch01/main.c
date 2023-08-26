/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */
int main()
{
	int fahr;

	for (fahr = 0; fahr < 300; fahr += 20)
		printf("%3d %6.1f\n", fahr, (5.0/9.0) * (fahr - 32.0));

	return 0;
}
