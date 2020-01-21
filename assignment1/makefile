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

clean:
	rm -f $(obj) $(prom)