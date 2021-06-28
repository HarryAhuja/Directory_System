OBJDIR  = output
SRC     = src
CC      = gcc
CFLAGS  = -g
LFLAGS  = -lm
target  = directory

SOURCES := $(notdir $(shell find . -name "*.c"))
OBJECTS := $(SOURCES:.c=.o)
OBJECTS := $(addprefix $(OBJDIR)/,$(OBJECTS))

all: obj_dir $(target)

DIRS := $(sort $(dir $(SOURCES)))
DIRS := $(addsuffix $(OBJDIR)/,$(DIRS))

$(target): $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

obj_dir:
	@mkdir -p $(DIRS)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(target)

show:
	@echo  $(SOURCES)
	@echo  $(OBJECTS)