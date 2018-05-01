#ifndef PVMAPILIB_H
#define PVMAPILIB_H
/**
 * This library contains system call of this VM
 **/
#include "PCoreBase.h"
#include <stdio.h>
void basicIO_Buffer(PBase* p);
void basicIO_File(PBase* p);
//decoder
void *APIHandler(void* vp);
#endif
