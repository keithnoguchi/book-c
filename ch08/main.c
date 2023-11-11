/* SPDX-License-Identifier: GPL-2.0 */
#include <stdio.h>

typedef long Align;

typedef union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
} Header;

static Header base;
static Header *freep = NULL;

int main(int argc, char *argv[])
{
	printf("base=%8p\n", &base);
	printf("freep=%p\n", freep);
}

void free(void *ap)
{
	Header *bp, *p;

	/* find spot to add */
	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p->s.ptr && bp < p->s.ptr->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (p > bp || p->s.ptr < bp))
			break;

	if (bp + bp->s.size == p) {
		/* join to upper nbr */
		bp->s.size += p->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;

	if (p + p->s.size == bp) {
		/* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;

	freep = p;
}
