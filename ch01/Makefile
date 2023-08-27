# SPDX-License-Identifier: GPL-2.0
.PHONY: all c clean

SOURCE := $(wildcard *.c)
OBJECT := $(SOURCE:%.c=%.o)
TARGET := $(notdir $(CURDIR))
CFLAGS := -Wall -Werror -O2
LFLAGS :=

all: $(TARGET)
$(TARGET): $(OBJECT)
	$(CC) $(LFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $<
c clean:
	@$(RM) -f $(OBJECT) $(TARGET)
