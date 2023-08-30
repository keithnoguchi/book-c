# SPDX-License-Identifier: GPL-2.0
CHAPTERS := ch01 ch02

all:
%:
	$(foreach CHAPTER, $(CHAPTERS), $(MAKE) -C $(CHAPTER) $@;)
