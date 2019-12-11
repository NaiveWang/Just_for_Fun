host: g.o
	gcc -o a helloworld.c g.o -lcudart -lstdc++ -lcuda -L/opt/cuda/targets/x86_64-linux/lib
g.o:
	nvcc -c gpu_lib.cu -o g.o
