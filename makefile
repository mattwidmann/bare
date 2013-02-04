EXE = 
SOURCES = 
CC = clang
CFLAGS = -pedantic -Wextra -Werror

default: debug

$(EXE): 

%.o: %.c %.d

.PHONY = debug release

debug: CFLAGS += -g
debug: CPPFLAGS += -DDEBUG
debug: $(EXE)

release: CPPFLAGS += -DNDEBUG
release: $(EXE)

.PHONY = clean

clean:
	rm -f *.o *.d $(EXE)

include $(subst .c,.d,$(SOURCES))

%.d: %.c
	$(CC) $(CPPFLAGS) -MM -MG $< | sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' > $@

