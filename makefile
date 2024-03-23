CC := gcc

CFLAGS := -std=c99 -g -Wall -Wextra -pedantic-errors -fstrict-aliasing -fstack-protector-all -fPIE -Werror -Wfatal-errors -Iinclude -MMD -MP
LDFLAGS := -lm
VALGRIND_FLAGS := --leak-check=full --show-leak-kinds=all --track-origins=yes -s

SRCDIR := srcc
BINDIR := bin
OBJDIR := $(BINDIR)/obj

SOURCES := $(wildcard $(SRCDIR)/**/**//**/*.c $(SRCDIR)/**//**/*.c $(SRCDIR)/**/*.c $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))
TARGET := test

.PHONY: all clean valgrind sanitize

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(BINDIR)/$@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJECTS:.o=.d)

.PHONY: run clean valgrind sanitize 
#.PHONY: lint valgrind clean run

#lint:
#	cppcheck $(SRC)
#	clang-format -i $(SRC)

valgrind: 
	valgrind $(VALGRIND_FLAGS) ./$(BINDIR)/$(TARGET)

clean:
	rm -r $(BINDIR)/*

run: 
	./$(BINDIR)/$(TARGET)

sanitize: clean compile_sanitize

#CFLAGSSANITIZER := -g -Wall -Wextra -pedantic-errors -Werror -Wfatal-errors -Iinclude -fsanitize=address -static-libasan -MMD -MP
LDFLAGSSANITIZER := -lm -fsanitize=address -static-libasan

compile_sanitize: CFLAGS += -fsanitize=address
compile_sanitize: LDFLAGS += -fsanitize=address
compile_sanitize: $(OBJECTS)
	$(CC) $^ -o $(BINDIR)/$(TARGET) $(LDFLAGSSANITIZER) 

#./$(BINDIR)/$(TARGET)
#$(OBJDIR)/%.o: $(SRCDIR)/%.c
#@mkdir -p $(@D)
#$(CC) $(CFLAGS) -c $< -o $@

