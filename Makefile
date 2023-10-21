CC=gcc -lm -lpthread -lcheck -lrt -lsubunit -fsanitize=address
PKGCONFIG = $(shell which pkg-config) 
CFLAGS=-Wall -Wextra -Werror $(shell $(PKGCONFIG) --cflags gtk4)
FILES = s21_calc_funcs/*.c
OUT=exec
TESTFILES= tests/*.c 
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
CHECKFLAGS=-lcheck 

all: install

tests: test gcov_report

gcov_report:
	$(CC) -o exec $(GCOV_FLAGS) $(FILES) $(TESTFILES) $(CHECKFLAGS)
	./$(OUT)
	lcov -capture --directory . --output-file main_coverage.info
	genhtml *.info -o ./gcov_report
	rm -rf *.gcda *.gcno *.info exec a.out

test:
	$(CC) $(FILES) $(TESTFILES) $(CHECKFLAGS)

install: uninstall
	mkdir build
	cd build && qmake ../qt_smart_calc
	make -C ./build/

uninstall:
	rm -Rf build/
	rm -rf s21_smart_calc.tar.gz

dvi:
	open README.html

dist: install
	tar -czf s21_smart_calc.tar.gz --directory=s21_smart_calc/ .

style:
	clang-format -style=google -i s21_calc_funcs/*.c s21_calc_funcs/*.h
	clang-format -style=google -i qt_smart_calc/*.h qt_smart_calc/*.cpp
	clang-format -style=google -i tests/*.c tests/*.h

style_check:
	clang-format -style=google -n s21_calc_funcs/*.c s21_calc_funcs/*.h
	clang-format -style=google -n qt_smart_calc/*.h qt_smart_calc/*.cpp
	clang-format -style=google -n tests/*.c tests/*.h

clean: uninstall
	rm -rf obj *.a ./gcov_report program *.o *.gch s21_calc_funcs/*.gch *.gcno *.gcda s21_smart_calc.tar.gz s21_smart_calc exec ./a.out main_coverage.info
	
