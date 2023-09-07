/* SPDX-License-Identifier: GPL-2.0 */
#include <ctype.h>

double atof(const char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isblank(s[i]); i++)
		;
	sign = s[i] == '-' ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = val * 10.0 + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = val * 10.0 + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}
