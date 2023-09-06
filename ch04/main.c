/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define MAXLINE 100

extern int getline2(char [], int limit);
extern double atof(const char []);

int main()
{
	char line[MAXLINE];
	double sum = 0;

	while (getline2(line, sizeof(line)) > 0)
		printf("\t%g\n", sum += atof(line));

	return 0;
}
