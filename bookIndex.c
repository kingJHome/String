#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "HString.h"
#include "bookIndex.h"

int main(int argc,char *argv[]){
	FILE *ff = fopen("books.txt","r"),
		 *gf = fopen("bookIndex.txt","w");
	HString BookNo;
	IdxListType *idxlist;

	if(ff && gf){
		InitIdxList(&idxlist);

		while( !feof(ff) ){
			GetLine(ff);
			ExtractKeyWord(&BookNo);
			InsIdxList(idxlist,BookNo);
		}
		PutText(gf, idxlist);
		//关闭文件
		fclose(ff);
		fclose(gf);
	}
}

void InitIdxList(IdxListType **idxlist){
	*idxlist = (IdxListType*)malloc(sizeof(IdxListType));

	if( *idxlist ){
		(*idxlist)->last = 0;
	}
}

void InitList(LinkList *bnostruct){
	LinkList temp = (LinkList)malloc(sizeof(sBookNo));

	if(temp){
		temp->next = NULL;
		*bnostruct = temp;
	}
}

void tolowerFn(char *chars){
	size_t clen = strlen(chars);

	for(size_t i = 0; i < clen; ++i){
		if(isalpha(chars[i]) && isupper(chars[i])){
			chars[i] = tolower(chars[i]);
		}
	}
}

int iskeyword(char *chars){
	int keyword = 1;
	String temp = strtoString(chars);
	long int result = Index(nokeyword,temp,0);

	if(result>=0){
		keyword = 0;
	}
	
	return keyword;
}

void Append(LinkList collect,LinkList p){
	LinkList first = collect;

	for( ; first && first->next; first = first->next);
	first->next = p;
}

void GetLine(FILE *f){
	_IO_ssize_t read;
	size_t readin = 0;

	read = getline(&buf, &readin, f);
	if( read!=-1 && read>=1 ){
		buf[read-1] = '\0';
	}
}

void ExtractKeyWord(HString *bn){
	char *bresult = strtok(buf," ");
	
	if( bresult ){
		int i;
		
		*bn = (HString)malloc(sizeof(String));
		if( *bn ){
			StrAssign(*bn,bresult);
			bresult = strtok(NULL," ");
			while( bresult ){
				tolowerFn(bresult);
				if( iskeyword(bresult) ){
					for(i = 0; i < wdlist.last; ++i){
						if( strcmp(bresult,wdlist.item[i])==0 ){
							break;
						}
					}
					if(i==wdlist.last){
						wdlist.item[i] = bresult;
						wdlist.last++;
					}
				}
				bresult = strtok(NULL," ");
			}
		}
	}
}

int InsIdxList(IdxListType *idxlist,HString bno){
	HString wd = (HString)malloc(sizeof(String));
	int result = 0;

	if(wd){
		for(int i = 0; i < wdlist.last; ++i){
			GetWord(i, wd);
			int j = Locate(*idxlist, wd, &result);
			if( !result ){
				InsertNewKey(idxlist, j, wd);					//插入新的索引项
			}
			result = InsertBook(idxlist, j, bno);				//插入书号索引
		}
	}

	return result;
}

void PutText(FILE *g,IdxListType *idxlist){
	LinkList temp;

	for(int i = 0; i < idxlist->last; ++i){
		fputs(idxlist->item[i].key->chars,g);
		fputc(' ', g);
		temp = idxlist->item[i].bnolist->next;
		while( temp ){
			fputs(temp->bookno->chars, g);
			temp = temp->next;
			if(temp){
				fputc(',', g);
			}
		}
		fputc('\n', g);
	}
}

void GetWord(int i,HString wd){
	char *p = *(wdlist.item + i);	//取词表中第i个字符串
	StrAssign(wd, p);
}

int Locate(IdxListType idxlist,HString wd,int *b){
	int m,i,
		result = 0;
	
	if(idxlist.last >= 1){
		for(i = idxlist.last - 1; i>=0 && (m = StrCompare(*(idxlist.item[i].key), *wd)) > 0; --i);
		if(m == 0){
			*b = 1;
			result = i;
		}else{
			*b = 0;
			result = i+1;
		}
	}else{
		*b = 0;
	}

	return result;
}

void InsertNewKey(IdxListType *idxlist,int i,HString wd){
	for(int j = idxlist->last - 1; j >= i; --j){//后移索引项
		idxlist->item[j+1] = idxlist->item[j];
	}
	//插入新的索引项
	if(idxlist->item[i].key==NULL){
		idxlist->item[i].key = (HString)malloc(sizeof(String));
	}
	StrCopy(idxlist->item[i].key, *wd);
	InitList(&(idxlist->item[i].bnolist));
	++idxlist->last;
}

int InsertBook(IdxListType *idxlist,int i,HString bno){
	LinkList p = (LinkList)malloc(sizeof(sBookNo));

	if(!p){
		return 0;
	}else{
		p->bookno = bno;
		p->next = NULL;
		Append(idxlist->item[i].bnolist,p);
		return 1;
	}
}
