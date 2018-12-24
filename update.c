#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "log.h"
#include "mysql/mysql.h"

extern int debugInfo(char *pLogPath, char *pFile, const char *pFuncName, int iLineNumb, char *fmt, ...);

//输入文件最大行数
#define MAX_LEN 1024*8
#define LOG_FILE_PATH          "./test.log"
#define LOG_PARAMS             LOG_FILE_PATH,__FILE__,__func__,__LINE__ 

//修改用户字段结构体
typedef struct User{
	char username[65];
	char email[65];
	char phone[65];
}USER;


int main(int argc, char **argv)
{
	int ret = 0, i = 0;
  	MYSQL mysql;
	MYSQL * connect = NULL; 
	connect = mysql_init(&mysql);  
	if(connect == NULL)
	{
		ret = mysql_errno(&mysql);  
		printf("mysql_init error, %s\n", mysql_error(&mysql));  
		return ret; 
	}
	debugInfo(LOG_PARAMS, "mysql_init success !\n"); 

	connect = mysql_real_connect(connect,"localhost", "root", "p@s#0fSPV", "hacconf", 3306, NULL, 0); 
	if (NULL ==connect)
	{
		ret = mysql_errno(&mysql);  
		debugInfo(LOG_PARAMS, "mysql_init error！ %s\n", mysql_error(&mysql));  
		return ret; 
	}
	debugInfo(LOG_PARAMS, "mysql_real_connect success !\n");  
  

  	//-------------------------start----------------------//
	//从文件中读取用户信息到结构体中
	FILE *fp = NULL;
	while(!(fp=fopen(argv[1],"r")))
	{
		printf("打开文件错误！\n");
	}
	USER user[MAX_LEN] = {0};
	for (i=0;i<MAX_LEN&&!feof(fp);i++)
	{
		//以逗号 “，”来区分
		fscanf(fp,"%[^,],%[^,],%s\n",user[i].username,user[i].email,user[i].phone);
	}
	debugInfo(LOG_PARAMS ,  " username: %s email: %s  phone: %s ",user[i].username,user[i].email,user[i].phone);
	
	
  	//更新hac用户信息表
	int j=0;
	char sql[1024] = {0};
	for(j=1;j<i;j++)
	{
		debugInfo(LOG_PARAMS , "the %d  :           username: %s email: %s  phone: %s ",j,user[j].username,user[j].email,user[j].phone);
	  	memset(sql,0,1024);
	  	snprintf(sql,1024," update user set email='%s',phone='%s' where username = '%s' ", user[j].email,user[j].phone,user[j].username);

		debugInfo(LOG_PARAMS , "------------------------sql=       %s-------------------\n",sql); 
	 	ret = mysql_query(connect, sql);      
	 	if(ret != 0)
		{
			debugInfo(LOG_PARAMS , "Inserted %lu rows\n",(unsigned long)mysql_affected_rows(connect));   
		} 
	}

  //--------------------------end----------------------//

	fclose(fp);
	fp=NULL;
	mysql_close(&mysql); 
 	return 0;
}

