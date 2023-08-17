# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --trace-children=yes --track-fds=yes --log-file=valgrind.log ./test
CC = g++
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g
SOURSES = s21_matrix_oop.cc
OBJECTS = $(SOURSES:.cc=.o)
SOURSE_TEST = test.cc
LIB = s21_matrix_oop.a
FLAGS = -lgtest -pthread


all: test	

test: $(LIB) $(SOURSE_TEST)
	$(CC) $(SOURSE_TEST) $(LIB) $(CFLAGS) -o test $(FLAGS)
	./test

s21_matrix_oop.a: $(OBJECTS)
	ar rc $(LIB) $(OBJECTS)
	ranlib $(LIB)
	rm -rf *.o

s21_matrix_oop.o: s21_matrix_oop.cc
	$(CC) $(CFLAGS) s21_matrix_oop.cc -c -o s21_matrix_oop.o

gcov_report: $(LIB)
	$(CC) $(CFLAGS) $(SOURSE_TEST) -o testlcov --coverage $(SOURSES) $(FLAGS)
	./testlcov
	lcov  -t "a.out" -o test.info  -c -d .
	lcov --remove test.info '/usr/local/include/c++/10.3.0/*' '/usr/local/include/gtest/*' '$(PWD)/my_exception.h' '$(PWD)/test.cc' -o test_filtered.info 
	genhtml -o report test_filtered.info
	open ./report/index.html
	rm -rf test *.o *.a *gcda *gcno *info

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc *.h


valgrind: clean $(LIB)
	$(CC) $(SOURSE_TEST) $(CFLAGS) $(LIB) -o testvalg $(FLAGS)
	valgrind --leak-check=full --track-origins=yes --track-fds=yes -s ./testvalg
	# grep ERROR valgrind.log

clean:
	rm -rf *.o *.a a.out *.dSYM test testlcov testvalg *gcda report *gcno *info *.log .clang-format
