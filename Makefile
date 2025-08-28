COMPILER = gcc
FLAGS = -Wall

.PHONY: clean

run_test: test
	./executable/test
	$(MAKE) clean

test: executable/test

TEST_SOURCE = \
test/dictionarytest.c\
source/dictionary.c

executable/test: $(TEST_SOURCE) | executable
	$(COMPILER) $(FLAGS) $(TEST_SOURCE) -o $@

executable:
	mkdir -p $@

clean:
	rm -rf executable