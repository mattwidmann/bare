EXE = main
OBJECTS = main.o

CC = clang
CFLAGS = -std=c11 -pedantic -Wextra -Werror

MAKEDEPEND = $(CC) $(CPPFLAGS) -MM -MG $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $*.d

default: debug

$(EXE): $(OBJECTS)

%.o: %.c
	$(MAKEDEPEND)
	$(COMPILE.c) -o $@ $<

.PHONY = debug release

debug: CFLAGS += -g
debug: CPPFLAGS += -DDEBUG
debug: $(EXE)

release: CPPFLAGS += -DNDEBUG
release: $(EXE)

.PHONY = clean install

clean:
	rm -f *.o *.d $(EXE)

DIR ?= ~/.bin/

install: release
	cp $(EXE) $(DIR)

-include $(OBJECTS:.o=.d)
