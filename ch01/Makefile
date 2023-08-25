# SPDX-License-Identifier: GPL-2.0
.PHONY: all
OBJS   := main.o
CFLAGS := -Wall -Werror -O2
LFLAGS :=
TARGET := $(notdir $(CURDIR))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean c:
	@$(RM) -f $(TARGET) $(OBJS)
