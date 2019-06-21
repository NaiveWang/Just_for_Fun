
#include "db.h"
const char *db_name = "base";
const char *tb_post = "post";
const char *tb_block = "content";
const char *tb_chunk = "chunks";
const char *tb_block_tmp = "_blocks";
const char *tb_chunk_tmp = "_chunks";
const wchar_t *delimiter = L",.．?!、:;；。，\n：;；？！ ";

static int sqlite_callback_test(void *data, int argc, char **argv, char **ColName){
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);
   wchar_t wbuf[100];
   swprintf(wbuf, 100, L"%hs", argv[i]);
   for(i=0; i<argc; i++){
      printf("%s = %s --> %d\n", ColName[i], argv[i], wcslen(wbuf));
   }
   printf("\n");
   return 0;
}
static int sqlite_callback_gen_block(void *data, int argc, char **argv, char **col){
    
    printf("%s\n", argv[1]);
    
    char *token = strtok(argv[1], delimiter);
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, delimiter);
    }
    //return 1;
}
sqlite3* db_init(){
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(db_name, &db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        return db;
    }
}
void db_close(sqlite3* db){
    sqlite3_close(db);
}
void utf8_test(sqlite3* db){
    void* data;
    int rc;
    char *err_msg;
    rc = sqlite3_exec(db, "select id, content from chunks", sqlite_callback_test, data, &err_msg);
    
    if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error : %s\n", err_msg);
      sqlite3_free(err_msg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
}

void gen_block(sqlite3* db){
    void* data;
    
    sqlite3_exec(db, "select id, blah from post", sqlite_callback_gen_block, data, NULL);
}





