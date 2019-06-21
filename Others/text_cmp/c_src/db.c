
#include "db.h"
const char *db_name = "base";

const char *delimiter = ",.．?!、:;；。，\n：;；？！ 		";
wchar_t *wdelimiter;

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

    static wchar_t *token, *appx, *wblock;
    static char buffer[512];

    wblock = (wchar_t*)g_utf8_to_ucs4_fast(argv[1], -1, NULL);
    token=wcstok(wblock, wdelimiter, &appx);
    //printf("%s ", argv[0]);
    while(token != NULL){
      /*
       * Notice : conflicts happends select from a table and update the same constraint column at the same time.
       *
       */

        gchar *tmp =  (gchar*)g_ucs4_to_utf8(token, -1, NULL, NULL, NULL);
        //sqlite3_bind_int(((sqlite3_stmt**)data)[1], 1, atoi(argv[0]));
        sqlite3_bind_int(((sqlite3_stmt**)data)[0], 1, atoi(argv[0]));
        sqlite3_bind_text(((sqlite3_stmt**)data)[0], 2, tmp, -1, SQLITE_TRANSIENT);

        sqlite3_step(((sqlite3_stmt**)data)[0]);
        sqlite3_clear_bindings(((sqlite3_stmt**)data)[0]);
        //sqlite3_step(((sqlite3_stmt**)data)[1]);
        //sqlite3_clear_bindings(((sqlite3_stmt**)data)[1]);

        sqlite3_reset(((sqlite3_stmt**)data)[0]);
        //sqlite3_reset(((sqlite3_stmt**)data)[1]);


        //printf("%s\n", tmp);
        g_free(tmp);
        token = wcstok(NULL, wdelimiter, &appx);
    }
    g_free(wblock);

    return 0;
}
static int sqlite_callback_gen_chunk(void *data, int argc, char **argv, char **col){
  int _;

  for(_= 0; _ <= g_utf8_strlen(argv[1], -1)-*(((int**)data)[1]);_++){
    //
    char* sub = g_utf8_substring(argv[1], _, _+*(((int**)data)[1]));
    int __, checksum=0;
    for(__=1;__<=*((int**)data)[1];__++){
      wchar_t *tmp = g_utf8_to_ucs4_fast(g_utf8_offset_to_pointer(sub, __-1),4,NULL);
      checksum += __*__* *((int*)tmp) * *((int*)tmp);
      g_free(tmp);
    }
    sqlite3_bind_int(((sqlite3_stmt**)data)[0], 1, atoi(argv[0]));
    sqlite3_bind_int(((sqlite3_stmt**)data)[0], 2, _);
    sqlite3_bind_text(((sqlite3_stmt**)data)[0], 3, sub, -1, SQLITE_TRANSIENT);
    //printf("%s\t", sub);
    sqlite3_bind_int(((sqlite3_stmt**)data)[0], 4, checksum);
    sqlite3_step(((sqlite3_stmt**)data)[0]);
    sqlite3_clear_bindings(((sqlite3_stmt**)data)[0]);
    sqlite3_reset(((sqlite3_stmt**)data)[0]);
    g_free(sub);
  }
  return 0;
}
sqlite3* db_init(){
    sqlite3 *db;
    //initialize the delimiter
    wdelimiter = (wchar_t*)g_utf8_to_ucs4_fast(delimiter, -1, NULL);
    int rc;
    rc = sqlite3_open(db_name, &db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        return db;
    }
    sqlite3_exec(db, "PRAGMA synchronous = OFF", NULL, NULL, NULL);
    sqlite3_exec(db, "PRAGMA journal_mode = MEMORY", NULL, NULL, NULL);
}
void db_close(sqlite3* db){
    sqlite3_close(db);
    g_free(wdelimiter);
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
    sqlite3_stmt *stmt[2];
    sqlite3_prepare_v2(db, "insert into content(pid, content)values(@pid, @block)", -1, &stmt[0], NULL);
    sqlite3_prepare_v2(db, "update content set is split=1 where id=@pid", -1, &stmt[1], NULL);
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    sqlite3_exec(db, "select id, blah from post where is_split=0", sqlite_callback_gen_block, &stmt, NULL);
    sqlite3_exec(db, "END TRANSACTION", NULL, NULL, NULL);
    sqlite3_finalize(stmt[0]);
    sqlite3_finalize(stmt[1]);
}
void gen_chunk(sqlite3* db, int size_chunk){
  void* data[2];
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, "insert into chunks(cid, pos, content, checksum)values(@cid, @pos, @chunk, @checksum)", -1, &stmt, NULL);
  data[0]=stmt;
  data[1]=&size_chunk;
  sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
  sqlite3_exec(db, "select id, content from content", sqlite_callback_gen_chunk, &data, NULL);
  sqlite3_exec(db, "END TRANSACTION", NULL, NULL, NULL);
}
