#include "db.h"
#include <stdio.h>
int main(int argc, char** argv){
    sqlite3 *db = db_init();
    //utf8_test(db);
    //gen_block(db);
    gen_chunk(db, 7);
    db_close(db);
    return 0;
}
