/* SPDX-License-Identifier: GPL-2.0 */
#define NULL 0

typedef struct {
	int fd;
} FILE;

FILE *fopen(const char *pathname, const char *mode)
{
	return NULL;
}

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;

	if (argc != 3)
		goto err;
	if ((fp1 = fopen(argv[1], "r")) == NULL)
		goto err;
	if ((fp2 = fopen(argv[2], "w")) == NULL)
		goto err;

	return 0;
err:
	return 1;
}
