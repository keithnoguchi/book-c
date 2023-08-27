# SPDX-License-Identifier: GPL-2.0
.PHONY: all

CFLAGS := -Wall -Werror -O2
LFLAGS :=
TARGET := $(notdir $(CURDIR))
OBJECT := main.o

all: $(TARGET)
$(TARGET): $(OBJECT)
	$(CC) $(LFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $<
c clean:
	@$(RM) -f $(OBJS) $(TARGET)
