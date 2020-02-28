prom=mykernel

dir_bin=./bin
dir_src=./src
dir_inc=./inc

src_file=$(wildcard ${dir_src}/*.c)
obj_file=$(patsubst %.c,%.o,$(notdir ${src_file}))
inc_file=$(wildcard ${dir_inc}/*.h)

zip = ecse427_comp310_assignment2_pengnan_260768510.zip
test = testfile.txt script1.txt script2.txt script3.txt

crazy_test: $(prom)
	bash crazy_tester_generator.sh 100 1000

test: $(prom)
	./$(prom) < testfile.txt

${dir_bin}:
	mkdir ${dir_bin}

build: ${obj_file} ${dir_bin}
	gcc -o $(prom) ${obj_file}
	mv ${obj_file} ${dir_bin}

${obj_file}:
	gcc -c ${src_file} -I ${dir_inc}

pack: $(prom)
	rm $(zip)
	zip $(zip) $(src_file) $(inc_file) README.txt $(prom) $(test) makefile

clean:
	find . -type f -name '*.o' -delete