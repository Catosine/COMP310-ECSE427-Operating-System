prom=mykernel

dir_bin=./bin
dir_src=./src
dir_inc=./inc

src_file=$(wildcard ${dir_src}/*.c)
obj_file=$(patsubst %.c,%.o,$(notdir ${src_file}))
obj=$(patsubst %.c,${dir_bin}/%.o,$(notdir ${src_file}))

zip = ecse427_comp310_assignment2_pengnan_260768510.zip

crazy_test: $(prom)
	bash crazy_tester_generator.sh 100

test: $(prom)
	./$(prom) < testfile.txt

build: ${obj_file}
	gcc -o $(prom) ${obj_file}
	mv ${obj_file} ${dir_bin}

${obj_file}:
	gcc -c ${src_file} -I ${dir_inc}

pack: $(prom)
	zip $(zip) $(src_file) $(inc_file) README.txt $(prom) testfile.txt

clean:
	rm ${dir_bin}/* ./*.o