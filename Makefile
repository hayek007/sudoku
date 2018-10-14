main: main.o sudoku.o
	clang -Wall -Werror $^ -o $@

main.o: main.c sudoku.h
	clang -Wall -Werror -c $<

sudoku.o: sudoku.c sudoku.h
	clang -Wall -Werror -c $<

clean:
	rm -rf *.o
cleanall:
	rm -rf main *.o
