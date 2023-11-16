CC = gcc
SIMPLE_FLAGS = -Wall -Wextra -Werror -std=c11
FLAGS += $(SIMPLE_FLAGS) \
				 $(shell pkg-config --cflags check)
TST_LIBS = $(shell pkg-config --libs check)
LIB = s21_objloader
STACK = stack
TRANS = transformations
PARSER = parser
SEC = secondary
ASC = ./viewer/
GARBAGE = *.o $(ASC)*.o \
					$(ASC)moc_* \
					$(ASC).qmake.stash \
					test *.a test.info \
					test.info report \
					*.gcda *.gcno \
					$(ASC)Makefile.Debug \
					$(ASC)Makefile.Release \
					$(ASC)viewer.exe \
					$(ASC)release/moc_* \
					$(ASC)release/*.o  \
					$(ASC).tmp  \
					$(ASC)log.txt  \
					log.txt

all: gcov_report install dist dvi play

build:
	@if [ ! -d ../build ] ; then mkdir ../build ; fi

install: build
	qmake6 $(ASC)viewer.pro -o $(ASC)viewer_makefile
	cd $(ASC) && make install -f viewer_makefile 2>log.txt 1>log.txt
	rm -rf $(ASC)viewer log.txt
	make clean

play: create_obj
	./start_app.sh

uninstall:
	cd $(ASC) && make uninstall -f viewer_makefile

dvi:
	doxygen dvi_file 2>log.txt 1>log.txt
	./show_dvi.sh

dviclean:
	rm -rf html 

dist: build
	cd $(ASC) && make dist -f viewer_makefile 2>log.txt 1>log.txt
	mv $(ASC)*.tar* ../build

distclean: clean
	cd $(ASC) && make distclean -f viewer_makefile
	rm -rf ../build/*.tar*

clean:
	rm -rf $(GARBAGE)

realclean:
	make uninstall
	make distclean
	make dviclean
	make delete_obj
	rm -rf ../build

rebuild: realclean all

create_obj:
	cp ./obj/cube.txt ./obj/cube.obj

delete_obj:
	rm -rf ./obj/cube.obj

test: gcov$(LIB).a create_obj
	$(CC) s21_check/*.c -c $(SIMPLE_FLAGS)
	$(CC) $(ASC)$(TRANS).c -c --coverage $(FLAGS)
	$(CC) $(FLAGS) *.o -L. gcov$(LIB).a --coverage $(TST_LIBS) -o test
	rm -rf *.o

gcov$(LIB).a:
	$(CC) -c $(ASC)$(LIB).c $(ASC)$(STACK).c $(ASC)$(PARSER).c $(ASC)$(SEC).c --coverage $(FLAGS)
	ar rc gcov$(LIB).a $(LIB).o $(STACK).o $(PARSER).o $(SEC).o
	ranlib gcov$(LIB).a
	rm -rf *.o

gcov_report: test
	./test
	./lcov_script.sh

memory_test_linux: test
	./mem_script.sh

memory_test_mac: test
	leaks -atExit -- ./test

all_tests_linux: clean style_test memory_test_linux
	./lcov_script.sh

all_tests_mac: clean style_test memory_test_mac
	./lcov_script.sh

style:
	clang-format -i -style=Google s21_check/*.c s21_check/*.h $(ASC)*.c $(ASC)*.h $(ASC)*.cpp

style_test:
	clang-format -n -style=Google s21_check/*.c s21_check/*.h $(ASC)*.c $(ASC)*.h $(ASC)*.cpp

let_rule:
	chmod +x show_dvi.sh
	chmod +x mem_script.sh
	chmod +x lcov_script.sh
	chmod +x show.sh
	chmod +x start_app.sh