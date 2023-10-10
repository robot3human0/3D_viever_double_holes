CFLAGS=-std=c11 -Wall -Werror -Wshadow -Wextra

ifeq ($(shell uname), Linux)
	CHKFLAGS=-pthread -lcheck_pic -pthread -lrt -lm -lsubunit
else
	CHKFLAGS=-lcheck
endif

.PHONY: all test clean gcov_report dvi run install uninstall dist style

all: clean install

install:
	@mkdir -p build
	qmake Viewer/Viewer.pro -o build/
	@cd build; make
	@cd ../
	@mkdir -p app
	@cp -r build/Viewer.app app/
	@cp -r readme.html app/Viewer.app/Contents/MacOS/

run: install
	./app/Viewer.app/Contents/MacOS/Viewer

uninstall:
	@rm -rf app

test:
	gcc $(CFLAGS) --coverage c_source_test.c Viewer/afina.c Viewer/giga.c $(CHKFLAGS) 
	./a.out

dvi: 
	@open readme.html

gcov_report:
	gcc $(CFLAGS) --coverage Viewer/afina.c -c -o affine_coverage.o
	gcc $(CFLAGS) --coverage Viewer/giga.c -c -o parse_coverage.o
	gcc $(CFLAGS) --coverage c_source_test.c -c -o c_source_test_coverage.o
	gcc $(CFLAGS) affine_coverage.o parse_coverage.o c_source_test_coverage.o -o $@ $(CHKFLAGS)  -lgcov
	./$@
	gcovr --html --html-details -o report.html
	open report.html

dist:
	@mkdir -p 3D_Viewer
	@cp -r Viewer 3D_Viewer
	@cp Makefile 3D_Viewer
	@cp c_source_test.c 3D_Viewer
	@cp readme.html 3D_Viewer
	@tar -czf 3D_Viewer.tar 3D_Viewer
	@rm -rf 3D_Viewer

clean:
	@rm -rf *.a *.o *.out gcov_report *.gcda *.gcno *.tar
	@rm -rf report.*
	@rm -rf build

style:
	clang-format -style=google -i Viewer/*.c
	clang-format -style=google -i Viewer/*.h
	clang-format -style=google -n Viewer/*.c
	clang-format -style=google -n Viewer/*.h
	clang-format -style=google -i Viewer/*.cpp
