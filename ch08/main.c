/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PERM 0660

int main(int argc, char *argv[])
{
	void error(char *, ...);
	int f1, f2, n;
	char buf[BUFSIZ];

	if (argc != 3)
		error("usage: cp from to");
	if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
		error("cp: can't open %s", argv[1]);
	if ((f2 = creat(argv[2], PERM)) == -1)
		error("cp: can't create %s with %03o", argv[2], PERM);
	while ((n = read(f1, buf, sizeof buf)) > 0)
		if (write(f2, buf, n) == -1)
			error("cp: can't write %s", argv[2]);

	return 0;
}

void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);

	exit(1);
}
