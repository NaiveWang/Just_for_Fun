#ifndef DB_H_
#define DB_H_
#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <glib.h>

extern const char *db_name;

extern const char *delimiter;
extern wchar_t *wdelimiter;
typedef struct cmp_result_set_node_verbose{
  int src;
  int dst;
  int pos_s;
  int pos_d;
  char* content;
  struct cmp_result_set_node_verbose* next;
} cmp_node_v;
typedef struct cmp_result_set_node_length{
  int src;
  int dst;
  int pos_s;
  int pos_d;
  int length;
  struct cmp_result_set_node_verbose* next;
} cmp_node;
void node_v_debug(cmp_node_v*);
void node_debug(cmp_node_v*);
cmp_node_v* build_node_v(int, int, int, int, char*);
cmp_node_v* build_node(int, int, int, int, int);
void purge_node(cmp_node_v*);
void purge_node_v(cmp_node_v*);

sqlite3* db_init();
void db_close(sqlite3*);
void utf8_test(sqlite3*);
void gen_block(sqlite3*);
void gen_chunk(sqlite3*, int);
void cmp_core(sqlite3*, int, int);
void cmp_core_len(sqlite3*, int, int);

void temp_init(sqlite3*);
void gen_block_temp(sqlite3*, char*);
void gen_chunk_temp(sqlite3*);


#endif
