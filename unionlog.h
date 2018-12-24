#ifndef _LOG_H_
#define _LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

   #define SIZE_16M               16777216  //1024*1024*16
   #define LOG_FILE_PATH          "./test.log"  //?¥å????»¶è·??
   #define LOG_PARAMS             LOG_FILE_PATH,__FILE__,__func__,__LINE__  //?¥å????»¶è·?? è°?????½æ???€?¨æ??ä»?è°?????½æ?????è°????debugInfo?¶æ???¨è??|7
   #define STR_LEN_2048           2048
   #define VS_ERR 1 
   #define VS_OK  0

   extern  int debugInfo(char *pLogPath, char *pFile, const char *pFuncName, int iLineNumb, char *fmt, ...); 

#ifdef __cplusplus
}
#endif

#endif
