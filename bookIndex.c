#include <stdio.h>
#include <stdlib.h>
#include "HString.h"
#include "bookIndex.h"

int main(int argc,char *argv[]){
	FILE *ff = fopen("Books.txt","r"),
		 *gf = fopen("BookIndex.txt","w");
	ElemType BookNo;
	IdxListType *idxlist = (IdxListType*)malloc(sizeof(IdxListType));

	if(ff && gf && idxlist){
		InitIdxList(idxlist);

		while( !feof(ff) ){
			GetLine(ff);
			ExtractKeyWord(&BookNo);
			InsIdxList(idxlist, BookNo);
		}
		PutText(gf, idxlist);
	}
}

void InitIdxList(IdxListType *idxlist){
}

void Append(LinkList collect,LinkList p){
}

void GetLine(FILE *f){
}

void ExtractKeyWord(ElemType *bn){
}

int InsIdxList(IdxListType *idxlist,ElemType bno){
	HString wd = (HString)malloc(sizeof(String));
	int result = 0;

	if(wd){
		for(int i = 0; i < wdlist.last; ++i){
			GetWord(i, wd);
			j = Locate(idxlist, wd, &result);
			if( !result ){
				InsertNewKey(idxlist, j, wd);					//插入新的索引项
			}else{
				result = InsertBook(idxlist, j, bno);			//插入书号索引
			}
		}
	}

	return result;
}

void PutText(FILE *g,IdxListType idxlist){
}

void GetWord(int i,HString wd){
	char *p = *(wdlist.item + i);	//取词表中第i个字符串
	StrAssign(wd, p);
}

int Locate(IdxListType idxlist,HString wd,int *b){
	int m,
		result;

	for(int i = idxlist.last - 1; (m = StrCompare(idxlist.item[i].key, wd)) > 0; --i);
	if(m == 0){
		*b = 1;
		result = i;
	}else{
		*b = 0;
		result = i+1;
	}

	return result;
}

void InsertNewKey(IdxListType *idxlist,int i,HString wd){
	for(int j = idxlist.last - 1; j >= i; --j){//后移索引项
		idxlist.item[j+1] = idxlist.item[j];
	}
	//插入新的索引项
	StrCopy(idxlist.item[i].key, wd);
	InitList(idxlist.item[i].bnolist);
	++idxlist.last;
}

int InsertBook(IdxListType *idxlist,int i,int bno){
	LinkList p = (LinkList)malloc(sizeof(sBookNo));

	if(!p){
		return 0;
	}else{
		p->bookno = bno;
		Append(idxlist.item[i].bnolist,p);
		return 1;
	}
}
