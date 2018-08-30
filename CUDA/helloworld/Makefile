cuda:
	nvcc -c gpu_lib.cu -o g.o
host:
	gcc -o a helloworld.c g.o -lcudart -lstdc++ -lcuda -L/usr/local/cuda/lib64
