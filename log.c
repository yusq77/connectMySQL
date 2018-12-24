#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>  
#include <syslog.h>
#include <error.h>
#include <sys/stat.h>
#include "log.h"


#define SIZE_16M               16777216  //1024*1024*16
#define LOG_FILE_PATH          "./test.log"  //日志文件路径
#define LOG_PARAMS             LOG_FILE_PATH,__FILE__,__func__,__LINE__  //日志文件路径 调用函数所在文件 调用函数名 调用debugInfo时所在行号
#define STR_LEN_2048           2048
#define VS_ERR 1 
#define VS_OK  0

//显示调用debugInfo接口的函数所在的文件名、函数名、行号
int debugInfo(char *pLogPath, char *pFile, const char *pFuncName, int iLineNumb, char *fmt, ...);

//日志的编号
int giInfoNumb = 1;

int debugInfo(char *pLogPath, char *pFile, const char *pFuncName, int iLineNumb, char *fmt, ...)
{
    if(NULL == pLogPath ||'\0' == pLogPath[0] || NULL == pFile || '\0' == pFile[0] || NULL == pFuncName ||'\0' == pFuncName[0])
        return VS_ERR;

    //判断文件大小是否清空该文件，每1000次写日志里检测1次文件大小
    if(0 == (giInfoNumb % 1000))
    {
        struct stat fileStat;
        if(0 == stat(pLogPath, &fileStat) && fileStat.st_size > SIZE_16M)
            remove(pLogPath);
    }
    
    //打开文件，写入日志
    FILE *pLogHandle = fopen(pLogPath, "a+");
    if(NULL == pLogHandle)
        return VS_ERR;

    //写入日期、函数信息
    time_t timeSecs = time(NULL);
    struct tm *timeInfo = localtime(&timeSecs);
    char acTitle[STR_LEN_2048] = { 0 };
    snprintf(acTitle, sizeof(acTitle), "[%04d] [%d%02d%02d/%02d:%02d:%02d] [%s] [%s:%d]\n", giInfoNumb++,
             timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday, 
             timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, pFile, pFuncName, iLineNumb);
    int iLen = strlen(acTitle);
    fwrite(acTitle, iLen, 1, pLogHandle);
    
    //写入日志
    fwrite("\t\t\t", 3, 1, pLogHandle);
    memset(acTitle, 0, sizeof(acTitle));
    va_list args;
    va_start(args, fmt);
    vsnprintf(acTitle, sizeof(acTitle), fmt, args);
    va_end(args);
    iLen = strlen(acTitle);
    fwrite(acTitle, iLen, 1, pLogHandle);
    fwrite("\n", 1, 1, pLogHandle);
    
    //关闭日志文件
    fclose(pLogHandle);
    return VS_OK;
}
