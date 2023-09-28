/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int c;
	int (*f)(int) = tolower;

	if (strcmp(argv[0], "./toupper") == 0)
		f = toupper;

	while ((c = getchar()) != EOF)
		putchar((*f)(c));

	return 0;
}
