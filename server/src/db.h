#ifndef SQL_GAME_H
#define SQL_GAME_H

//#include <sqlite3.h>
#include "hiredis.h"

/*
sqlite3* db;
void init_sql(char* database);
void bind_param(sqlite3_stmt* stmt, char* name, char* value);
sqlite3_stmt* create_stmt(char* sql);
char** get_result(sqlite3_stmt* stmt);
*/

redisContext* rcontext;
redisReply* reply;
void connect_redis(char* url, int port);


#endif