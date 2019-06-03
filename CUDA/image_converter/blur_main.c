#include <stdio.h>
#include <stdlib.h>

#include "bmp_lib.h"

void blur_cpu(bmpa *bp)
{
    //allocate buffer
    unsigned char *temp = malloc(sizeof(unsigned char)*3*bp->h*bp->w);
    //convert central
    //convert four edges
    //convert four corners
    //swap array pointers & release buffer
    free(bp->array);
    bp->array = temp;
}

int main(int argc, char **argv)
{
    bmpa *bp=loadimage_rgb(argv[1]);
    saveimage(bp, "out.bmp");
    free_image(bp);
    return 0;
}
