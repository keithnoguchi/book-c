/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

int main(int argc, char *argv[])
{
	void filecopy(FILE *, FILE *);
	const char *progname = *argv;
	FILE *fp;

	if (argc == 1)
		filecopy(stdin, stdout);
	else
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open file %s\n",
					progname, *argv);
				return 1;
			} else {
				filecopy(fp, stdout);
				fclose(fp);
			}

	if (ferror(stdout)) {
		fprintf(stderr, "%s: error on stdout\n", progname);
		return 2;
	}
	return 0;
}

void filecopy(FILE *ip, FILE *op)
{
	int c;

	while ((c = getc(ip)) != EOF)
		putc(c, op);
}

char *fgets(char *s, int n, FILE *iop)
{
	register int c;
	register char *p = s;

	while (--n > 0 && (c = getc(iop)) != EOF)
	       if ((*p++ = c) == '\n')
		       break;
	*p = '\0';

	return (c == EOF && p == s) ? NULL : s;
}
