OS := $(shell uname -s)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

H_FILES = s21_decimal.h

ifeq ($(OS), Darwin)
	CHKFLAGS = -lcheck
else
	CHKFLAGS = -lcheck -lrt -lm -lpthread -lsubunit
endif

all: clean s21_decimal.a test1
	make clean
	rm s21_decimal.a

s21_decimal.a: s21_decimal.o
	ar rc s21_decimal.a s21_*.o
	ranlib s21_decimal.a

s21_decimal.o:
	$(CC) $(CFLAGS) -c s21_*.c

test1: decimal_test.o s21_decimal.o
	$(CC) $(CFLAGS) s21_*.o decimal_test.o -o test.out $(CHKFLAGS)
	./test.out

# another_test: another_test.o s21_decimal.o
# 	$(CC) $(CFLAGS) s21_*.o another_test.o -o test.out $(CHKFLAGS)
# 	./test.out

test:
	@make test1

gcov_report: decimal_test.o s21_decimal.o test
	chmod 777 tests.check
	checkmk clean_mode=1 tests.check > decimal_test.c
	$(CC) $(CFLAGS) --coverage -l check s21_*.c decimal_test.c -o test $(CHKFLAGS)
	./test
	lcov -t "./test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	rm decimal_test.c

# another_test.o:
# 	checkmk clean_mode=1 tests1.check > another_test.c
# 	$(CC) $(CFLAGS) -c another_test.c -o another_test.o $(CHKFLAGS)
# 	rm another_test.c

decimal_test.o:
	chmod 777 tests.check
	checkmk clean_mode=1 tests.check > decimal_test.c
	$(CC) $(CFLAGS) -c decimal_test.c -o decimal_test.o $(CHKFLAGS)
	rm decimal_test.c

style: 
	clang-format -style=Google -i *.c *.h
	clang-format -style=Google -n *.c *.h

check:
	cp ../materials/linters/.clang-format .
	cppcheck s21_*.c *.h
	clang-format -n s21_*.c *.h
    

clean: 
	@rm -rf *.o *.gcda *.gcno *.out *.gch *.info
	@rm -rf test
	@rm -rf report
