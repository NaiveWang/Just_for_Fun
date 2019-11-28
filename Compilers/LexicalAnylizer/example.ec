int main(void)
{
    int n;
    char s[65536];
    int h,t;

    scanf("",&n);
    while(n--)
    {
        scanf("",s);
        h=0;
        t=strlen(s)-1;
        while(h<=t)
        {
            if(s[t]==s[h])
            {
                h++;
                t--;
                continue;
            }
            else
            {
                printf("");
                goto E;
            }
        }
        printf("");
        E:printf("");
    }
    return 0;
}