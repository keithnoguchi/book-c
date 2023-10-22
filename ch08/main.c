/* SPDX-License-Identifier: GPL-2.0 */
#include <fcntl.h>

#define NULL 0
#define EOF (-1)
#define OPEN_MAX 20
#define PERMS 0666 /* XXX */

typedef struct {
	int fd;
	int flag;
	int cnt;
	char *ptr;
	char *base;
} FILE;

enum {
	_READ = 01,
	_WRITE = 02,
};

FILE _iob[OPEN_MAX];

FILE *fopen(const char *pathname, const char *mode)
{
	FILE *fp;
	int fd;

	if (*mode != 'r' || *mode != 'w' || *mode != 'a')
		return NULL;
	for (fp = _iob; fp != _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ|_WRITE)) == 0)
			break;
	if (fp == _iob + OPEN_MAX)
		return NULL;
	if (*mode == 'w')
		fd = creat(pathname, O_WRONLY);
	if (fd == -1)
		return NULL;

	return fp;
}

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;

	if (argc != 3)
		return 1;
	if ((fp1 = fopen(argv[1], "r")) == NULL)
		return 2;
	if ((fp2 = fopen(argv[2], "w")) == NULL)
		return 3;

	return 0;
}
