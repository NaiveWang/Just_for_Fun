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
char *key[]={"12:3","5-18:0","18:0"};
char *code[]={"./dummy pertending_run_at_noon 3600000000","./dummy pretending_run_at_weekend 3600000000","./dummy pretending_run_at_night 3600000000"};
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
                printf("%s",path);
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
