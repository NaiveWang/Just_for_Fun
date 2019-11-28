#include <windows.h>
/**
 * This head file aims to compute
 * how much time taken by block of code.
 */
DWORD timer_c;
void timerStart()
{
    timer_c=GetTickCount();
}
long timerEnd()
{
    return GetTickCount()-timer_c;
}
