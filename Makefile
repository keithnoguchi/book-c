# SPDX-License-Identifier: GPL-2.0
.PHONY: all
CHAPTERS := ch01

all:
	$(MAKE) -C ch01 $@
%:
	$(MAKE) -C ch01 $@
