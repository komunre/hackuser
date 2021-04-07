#include "db.h"
/*
void init_sql(char* database){
    int rc = sqlite3_open(database, &db);
    if (rc){
        printf("Can't open database: %d\n", sqlite3_errmsg(db));
        return 0;
    }
    else{
        pintf("Database opened\n");
    }
}

void bind_param(sqlite3_stmt* stmt, char* name, char* value){
    int index = sqlite3_bind_parameter_index(stmt, name);
    if (index == 0){
        printf("can't prepare request");
    }

    int res = sqlite3_bind_text(stmt, index, value, -1, SQLITE_TRANSIENT);
}

sqlite3_stmt* create_stmt(char* sql){
    sqlite3_stmt* stmt;
    sqlite3_prepare16_v2(db, sql, -1, stmt, NULL);
    return stmt;
}

char** get_result(sqlite3_stmt* stmt, int coulmn_counter){
    int state;
    while ((state = sqlite3_step(stmt)) != SQLITE_DONE){
        if (state == SQLITE_ROW){
            for (int i = 0; i < sqlite3_column_count; i++){
                sqlite3_column_text(stmt, i);
            }
        }
    }
}
*/

void connect_redis(char* url, int port){
    rcontext = redisConnect(url, port);
    if (rcontext != NULL && rcontext->err){
        printf("Error: %s\n", rcontext->errstr);
        return;
    }
    else{
        printf("Connected to redis");
    }
}