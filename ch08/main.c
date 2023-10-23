/* SPDX-License-Identifier: GPL-2.0 */
#include <fcntl.h>
#include <unistd.h>

#define OPEN_MAX 10
#define PERMS 0666

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
	_NOBUF = 03,
	_EOF = 010,
	_ERR = 020,
};

static FILE _iob[OPEN_MAX] = {
	{ 0, _READ, 0, NULL, NULL },
	{ 1, _WRITE, 0, NULL, NULL },
	{ 2, _WRITE|_NOBUF, 0, NULL, NULL },
};

FILE *fopen(const char *name, const char *mode)
{
	FILE *fp;
	int fd;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;

	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ|_WRITE)) == 0)
		    break;
	if (fp == _iob + OPEN_MAX)
		return NULL;

	/* open/create file descripter */
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY);
	if (fd == -1)
		return NULL;

	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = *mode == 'r' ? _READ : _WRITE;

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
