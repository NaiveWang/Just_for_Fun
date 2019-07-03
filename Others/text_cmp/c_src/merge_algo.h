#ifndef MERGE_ALGO_H_
#define MERGE_ALGO_H_
#include <stdlib.h>
typedef struct merge_link_list_node{
    int l, r;
    struct merge_link_list_node* next;
}merge_node;

void insert_node(merge_node*, int, int);
void release_list(merge_node*);
int check_out(merge_node*);
#ifdef debug
#include <stdio.h>
void debug(merge_node*);
#endif
#endif
