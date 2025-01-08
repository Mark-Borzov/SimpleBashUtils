CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: s21_cat

clean:
	rm -rf s21_cat
	
s21_cat: clean
	$(CC) $(CFLAGS) cat.c -o s21_cat

test:
	chmod +x test_cat.sh
	./test_cat.sh

clang-check:
	clang-format -n cat.c

clang-done:
	clang-format -i cat.c