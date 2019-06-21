#ifndef DB_H_
#define DB_H_
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <glib.h>

extern const char *db_name;
extern const char *tb_post;
extern const char *tb_block;
extern const char *tb_chunk;
extern const char *tb_block_tmp;
extern const char *tb_chunk_tmp;
extern const char *delimiter;
extern wchar_t *wdelimiter;

sqlite3* db_init();
void db_close(sqlite3*);
void utf8_test(sqlite3*);
void gen_block(sqlite3*);
void gen_chunk(sqlite3*, int);


#endif
