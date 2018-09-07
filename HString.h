#ifndef HSTRING_MY
#define HSTRING_MY

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char *chars;
	size_t length;
}*HString,String;

void freeAlloc(HString t);

void StrAssign(HString t,char *chars);

String strtoString(char *chars);

void StrCopy(HString t,String s);

int StrEmpty(String s);

int StrCompare(String s,String t);

size_t StrLength(HString s);

void ClearString(HString s);

void Concat(HString t,String s1,String s2);

void SubString(HString Sub,String s,size_t pos,size_t len);

long int Index(String s,String t,size_t pos);

void Replace(HString s,String t,String v);

void StrInsert(HString s,size_t pos,String t);

void StrDelete(HString s,size_t pos,size_t len);

void tolowercase(HString s);

void touppercase(HString s);

void DestroyString(HString s);
#endif
