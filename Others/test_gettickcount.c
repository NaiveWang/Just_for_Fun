


    #include <windows.h>
    #include <stdio.h>

    int main() {
        DWORD start, stop;
        start = GetTickCount();
        Sleep(3000);
        stop = GetTickCount();
        printf("time: %ld ms\n", stop - start);
        return 0;
    }

