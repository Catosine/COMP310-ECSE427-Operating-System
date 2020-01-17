prom = mysh
obj = shell.o interpreter.o shellmemory.o

$(prom): $(obj)
	gcc -o $(prom) $(obj)

%.o: %.c
	gcc -c $<

test: $(prom)
	prom < testfile.txt

clean:
	rm -f $(obj) $(prom)