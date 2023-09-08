/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

#define NUMBER '\0'
#define MAXOP 100

extern int getop(void);

int main(void)
{
	int type;
	char s[MAXOP];

	while ((type = getop()) != EOF) {
		switch (type) {
		case NUMBER:
			break;
		case '+':
			break;
		case '*':
			break;
		case '-':
			break;
		case '/':
			break;
		case '\n':
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
