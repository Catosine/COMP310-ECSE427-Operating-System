prom = mysh
obj = shell.o interpreter.o shellmemory.o

$(prom): $(obj)
	gcc -o $(prom) $(obj)

%.o: %.c
	gcc -c $<

clean:
	rm -f $(obj) $(prom)