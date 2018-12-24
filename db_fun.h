/*******************************************************
 * functions for mysql db access
 *******************************************************/

#ifndef DB_H_
#define DB_H_

//#define SQLITE_SUPPORT

#include "mysql/mysql.h"
#ifdef SQLITE_SUPPORT
#include <sqlite3.h>
#endif

// ***BEGIN*** VTPS-3566 数据库访问公共接口修改 added by xiey 2015/07/24
#include "hacsqldual.h"
// ***END*** VTPS-3566 数据库访问公共接口修改 added by xiey 2015/07/24

#define DB_MAX_ERROR_LEN 256
#define DB_MYSQL 0
#define DB_SQLITE 1
// default database type is DB_MYSQL
// ***BEGIN*** VTPS-3566 数据库访问公共接口修改 added by xiey 2015/07/24
#define DBUSER_NULL	""
// ***END*** VTPS-3566 数据库访问公共接口修改 added by xiey 2015/07/24

#ifdef __cplusplus
extern "C" {
#endif
typedef struct{	
	char host[64];
	char user[64];
	char passwd[64];
	char dbname[64];
	unsigned int port;
	int actived;	
	int errorno;
	int dbtype;
	char errormsg[DB_MAX_ERROR_LEN];
#ifdef SQLITE_SUPPORT
	char sqlitefile[256];
	sqlite3 *sqlitedb;	
#endif	
	MYSQL * connection;
}db_conn;

typedef struct{
	MYSQL_RES *res_ptr;   /* store result data*/
	char ** sqlite_res; /* store sqlite result data, 
							index from 0 to fields is field names */
	int dbtype;		/* database type */
	int rows;		/* result data rows */
	int fields;		/* result data fields */
}db_data;

int db_connect(db_conn * conn);
void db_close(db_conn * conn);

int db_query(db_conn * conn,const char *query,db_data * data);
int db_ping(db_conn * conn);

//result data procesess
// ***BEGIN*** VTPS-3566 数据库访问公共接口修改 added by xiey 2015/07/24
MYSQL_FIELD * db_data_field(db_data * data, int index);
// ***END*** VTPS-3566 数据库访问公共接口修改 added by xiey 2015/07/24
char * db_data_field_name(db_data * data, int index);
char ** db_data_row(db_data * data,int index);
void db_data_free(db_data * data);
#ifdef __cplusplus
}
#endif
#endif
