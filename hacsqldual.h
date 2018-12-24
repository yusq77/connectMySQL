
#ifdef __cplusplus
extern "C" {
#endif
extern int sql_get_table( char *sql, char ***res_ptr, int *nrow, int *ncolumn, char **ErrMsg );
extern int SpaceFree( char **result, int number );
extern int sql_init( int flag );
extern int sql_exec( char *sql, char **ErrMsg );
extern int sql_exec_ref( char *sql, char **ErrMsg );
extern long long sql_get_insert_id(void);
extern int sql_insert( char *sql, char **ErrMsg );
extern int sql_insert_ref( char *sql, char **ErrMsg );
extern int sql_update( char *sql, char **ErrMsg );
extern int sql_delete( char *sql, char **ErrMsg );
extern int sql_close( void );
extern int sql_change( char *name );
extern const char *GetDBUser(void);
extern const char *GetDBPswd(char *user); 
extern const char *GetDBHost( void );
extern int GetDBPort( void );
extern const char *GetDBDomainSocket( void );
#ifdef __cplusplus
}
#endif

#define SQLLENGTH 512
