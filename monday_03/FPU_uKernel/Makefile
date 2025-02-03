
ISA ?= UNKNOWN
include makefiles/$(ISA).mk

SRCDIR := src
BINDIR := bin

SOURCES := $(SRCDIR)/work.c $(SRCDIR)/stats.c

all: $(addprefix $(BINDIR)/, $(addsuffix .x, $(TARGETS)))

NITERS ?= 100000

$(BINDIR)/%.x: $(SRCDIR)/%.c 
	$(CC) $(CFLAGS) $(SOURCES) $^ -o $@ -lm -lpthread -fopenmp -DNITERS=$(NITERS) $(LDFLAGS)

clean:
	rm -rf $(BINDIR)/*.x

.PHONY: 
