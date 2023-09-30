/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int main(void)
{
	int getaline(char *, int);
	int day, month, year;
	char monthname[20];
	char line[BUFSIZ];

	while (getaline(line, sizeof(line)) > 0)
		if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
			printf("valid: %s\n", line);
		else if (sscanf(line, "%d/%d/%d", &year, &month, &day) == 3)
			printf("valid: %s\n", line);
		else
			printf("invalid: %s\n", line);

	return 0;
}

int getaline(char *line, int lim)
{
	char *p;
	int c;

	p = line;
	while ((c = getchar()) != EOF) {
		if ((p - line) >= lim || c == '\n') {
			*p = '\0';
			break;
		}
		*p++ = c;
	}
	return p - line;
}
