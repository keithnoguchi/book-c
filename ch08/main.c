/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *malloc(unsigned), free(void *);

int main(int argc, char *argv[])
{
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

typedef double Align;
typedef union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
} Header;

static Header base;
static Header *freep = NULL;

void *malloc(unsigned nbytes)
{
	Header *prevp, *p, *morecore(unsigned);
	unsigned nunits;

	nunits = (sizeof(Header) + nbytes - 1)/sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = prevp = freep = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

Header *morecore(unsigned nu)
{
#define NALLOC 1024
	Header *up;
	void *p;

	if (nu < NALLOC)
		nu = NALLOC;
	p = sbrk(nu * sizeof(Header));
	if (p == (void *)-1)
		return NULL;
	up = (Header *)p;
	up->s.size = nu;
	free((void *)(up + 1));
	return freep;
}

void free(void *)
{
	return;
}
