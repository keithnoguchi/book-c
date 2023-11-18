/* SPDX-License-Identifier: GPL-2.0 */
#include <string.h>

int main(int argc, char *argv[])
{
	void *malloc(unsigned), free(void *);
	char *buf[100];
	int i, j;

	for (i = 0; i < 100; i++) {
		buf[i] = malloc(8000 + i);
	}
	for (i = 0; i < 100; i++)
		memset(buf[i], i, 8000 + i);
	for (j = 0; j < 3; j++)
		for (i = 100 - j; i > 0; i -= 3)
			free(buf[i - 1]);
}

void *malloc(unsigned nbytes)
{
	return NULL;
}

void free(void *)
{
	return;
}
