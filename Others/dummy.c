#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	unsigned int i;
	sscanf(argv[2],"%d",&i);
	usleep(i);
	printf("%s\n",argv[1]);
	return 0;
}
