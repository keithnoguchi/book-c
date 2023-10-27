/* SPDX-License-Identifier: GPL-2.0 */
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 10
#define PERMS 0666

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

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

static int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag & (_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = fp->flag & _NOBUF ? 1 : BUFSIZ;
	if (fp->base == NULL)
		if ((fp->base = (char *)malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

static int _flushbuf(int x, FILE *fp)
{
	int bufsize, len;

	if (fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE)
		return EOF;
	bufsize = (fp->flag & _NOBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *)malloc(bufsize)) == NULL) {
			fp->flag |= _ERR;
			return EOF;
		}
	}
	fp->ptr = fp->base;
	*fp->ptr++ = (char)x;
	fp->cnt = bufsize  - 1;
	len = fp->ptr - fp->base;
	if (write(fp->fd, fp->base, len) != len) {
		fp->flag |= _ERR;
		return EOF;
	}
	return x;
}

int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	int c;

	if (argc != 3)
		return 1;
	if ((fp1 = fopen(argv[1], "r")) == NULL)
		return 2;
	if ((fp2 = fopen(argv[2], "w")) == NULL)
		return 3;
	while ((c = getc(fp1)) != EOF)
		if (putc(c, fp2) == EOF)
			return 4;

	return 0;
}
