
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
/*
 * This c file shows how to operate a decent utf-8 string,
 * with some glib function and wchar tokenlizer.
 * mainly about get length, substring and tokenlize a string;
 * I bascially use the glib function to convert the raw string
 * to the ucs4, which has the same fixed char length as linux wchar_t.
 */

const char *delimiter = ",.．?!、:;；。，\n：;；？！ ";
int main(void){
    glong c;
    wchar_t *wd = (wchar_t*)g_utf8_to_ucs4_fast(delimiter, -1, NULL);
    char cn[100] = "老爷爷无药可救a, 儒雅随和.恶性通货膨胀";
    char *cwcn, *sub;
    gchar* p=cn;
    wchar_t *wcn;
    wchar_t *token, *resv;


    //print raw string
    printf("char  : %s --> %d\n", cn, strlen(cn));
    //print raw gstring
    g_printf("gchar : %s -> %d\n", p, g_utf8_strlen(p, -1));
    //convert to ucs4
    wcn = (wchar_t*)g_utf8_to_ucs4_fast(p, -1, &c);
    //convert back
    cwcn = (char*)g_ucs4_to_utf8(wcn, -1, NULL, NULL, NULL);
    //operate utf-8 string directly
    sub = g_utf8_substring(cwcn, 1, 3);
    printf("%ld %s$%s$\n", c, cwcn, sub);
    //tokenlizer demo
    token=wcstok(wcn, wd, &resv);
    while(token != NULL){

        gchar *tmp =  (gchar*)g_ucs4_to_utf8(token, -1, NULL, NULL, NULL);
        g_printf("%s\n", tmp);
        g_free(tmp);
        token = wcstok(NULL, wd, &resv);
    }

    g_free(wcn);
    g_free(cwcn);
    g_free(sub);
    g_free(wd);

    return 0;
}
