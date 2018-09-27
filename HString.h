#ifndef HSTRING_MY
#define HSTRING_MY

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *chars;
	size_t length;
}*HString,String;

//释放字符串
void freeAlloc(HString t);

//设置字符串
void StrAssign(HString t,char *chars);

//转换char×为HString
String strtoString(char *chars);

//copy字符串
void StrCopy(HString t,String s);

//字符串是否为空
int StrEmpty(String s);

//比较字符串
int StrCompare(String s,String t);

//字符串长度
size_t StrLength(HString s);

//清空字符串
void ClearString(HString s);

//连接字符串
void Concat(HString t,String s1,String s2);

//获取字符串的子串
void SubString(HString Sub,String s,size_t pos,size_t len);

long int Index(String s,String t,size_t pos);

void Replace(HString s,String t,String v);

void StrInsert(HString s,size_t pos,String t);

void StrDelete(HString s,size_t pos,size_t len);

void tolowercase(HString s);

void touppercase(HString s);

void DestroyString(HString s);

#endif
