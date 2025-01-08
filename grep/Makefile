CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 

all: s21_grep

clean:
	rm -rf s21_grep
	
s21_grep: clean
	$(CC) $(CFLAGS) grep.c -o s21_grep

test:
	chmod +x test_grep.sh
	./test_grep.sh

clang-check:
	clang-format -n grep.c

clang-done:
	clang-format -i grep.c