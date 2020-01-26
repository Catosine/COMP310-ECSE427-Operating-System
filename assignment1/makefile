prom = mysh
obj = shell.o interpreter.o shellmemory.o

crazy_test: $(prom)
	bash crazy_tester_generator.sh 100

test: $(prom)
	./$(prom) < testfile.txt

$(prom): $(obj)
	gcc -o $(prom) $(obj)

%.o: %.c
	gcc -c $<

pack: $(prom)
	zip ecse427_comp310_assignment1_pengnan_260768510.zip shell.c shell.h shellmemory.c shellmemory.h interpreter.c interpreter.h README.txt makefile testfile.txt crazy_tester_generator.sh $(prom)

clean:
	rm -f $(obj) $(prom)