CFLAGS=-g -c -Wall -Wextra -Werror -std=c++17 -pedantic
FLAGS=-Wall -Wextra -Werror -std=c++17 -pedantic
GTEST=-lgtest -lgtest_main -pthread
ASAN=#-fsanitize=address -fanalyzer
COVER=-fprofile-arcs -ftest-coverage


all: s21_matrix.a

s21_matrix.a:
	g++ $(FLAGS) $(ASAN) $(COVER) -o s21_matrix_oop_constructors.o -c s21_matrix_oop_constructors.cc
	g++ $(FLAGS) $(ASAN) $(COVER) -o s21_matrix_oop_methods.o -c s21_matrix_oop_methods.cc
	g++ $(FLAGS) $(ASAN) $(COVER) -o s21_matrix_oop_operators.o -c s21_matrix_oop_operators.cc
	g++ $(FLAGS) $(ASAN) $(COVER) -o s21_matrix_oop_helpers.o -c s21_matrix_oop_helpers.cc
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a

clean:
	rm -f test
	rm -f *.a *.o
	rm -f *.info *.gcda *.gcno *.gcov
	rm -rf coverage

test: s21_matrix.a
	g++ $(FLAGS) $(ASAN) $(GTEST) $(COVER) ./tests/tests_for_matrix_oop.cc -o test -L. s21_matrix.a
	./test

gcov_report:
	geninfo . -b . -o ./coverage.info --no-external
	genhtml coverage.info -o ./coverage
	open coverage/index.html

leaks:
	leaks -atExit -- ./test

.PHONY: s21_matrix.a