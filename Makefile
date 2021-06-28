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

HEADERS := $(sort $(dir $(shell find -L . -name "*.h")))
INCLUDE := $(patsubst %,-I%,$(HEADERS))

DIRS := $(sort $(dir $(SOURCES)))
DIRS := $(addsuffix $(OBJDIR)/,$(DIRS))

#DEPS := $(patsubst %.o,%.d,%(OBJECTS))

DEPS := DEP = $(OBJECTS:%.o=%.d)
-include $(DEPS)

DEPFLAG = -MMD -MF $(@:.o=.d)

$(target): $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

$(OBJDIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) $(DEPFLAG) -c $< -o $@ 

obj_dir:
	@mkdir -p $(DIRS)

clean:
	rm -rf $(OBJDIR)
	rm -rf $(target)
	rm -rf $(DEPS)

show:
	@echo "SOURCES" $(SOURCES)
	@echo "OBJECTS" $(OBJECTS)
	@echo "HEADERS" $(HEADERS)
	@echo "INCLUDE" $(INCLUDE)
	@echo "DEPS" $(DEPS)