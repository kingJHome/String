#include "HString.h"

void freeAlloc(HString t){
	if(t->chars && t->length){
		free(t->chars);
	}
}

void StrAssign(HString t,char *chars){
	size_t clen = strlen(chars);

	if( !t->chars ){
		t->chars = (char*)malloc(clen+1);
		memset(t->chars,'\0',clen+1);
	}
	strcpy(t->chars, chars);
	t->length = clen;
}

String strtoString(char *chars){
	String gerate;
	size_t clen = strlen(chars);

	if(clen){
		gerate.chars = (char*)malloc(clen+1);
		if(gerate.chars){
			memset(gerate.chars,'\0',clen+1);
			for(size_t i = 0; i < clen; ++i){
				gerate.chars[i] = chars[i];
			}
			gerate.length = clen;
		}
	}else{
		gerate.chars = NULL;
		gerate.length = 0;
	}

	return gerate;
}

void StrCopy(HString t,String s){
	char *temp = (char*)malloc((s.length+1));
	if(temp){
		freeAlloc(t);
		memset(temp,'\0',s.length+1);
		strcpy(temp, s.chars);
		t->chars = temp;
		t->length = s.length;
	}
}

int StrEmpty(String s){
	return (s.length==0);
}

int StrCompare(String s,String t){
	int result = strcmp(s.chars, t.chars);

	return result;
}

size_t StrLength(HString s){
	return s->length;
}

void ClearString(HString s){
	static char emptyStr = '\0';

	s->length = 0;
	free(s->chars);
	s->chars = &emptyStr;
}

void Concat(HString t,String s1,String s2){
	size_t slen1 = s1.length,
		   newlen = slen1 + s2.length,
		   start = 0,
		   cur = 0;
	char *temp = (char*)malloc(newlen+1);
	
	if(temp){
		memset(temp,'\0',newlen+1);
		for( ; start < slen1; ++start,++cur){
			temp[cur] = s1.chars[start];
		}
		for(start = 0; start < s1.length; ++start,++cur){
			temp[cur] = s2.chars[start];
		}
		freeAlloc(t);
		t->chars = temp;
		t->length = newlen;
	}
}

void SubString(HString Sub,String s,size_t pos,size_t len){
	static char emptyStr = '\0';

	if(pos>=0 && len>0 && pos<=s.length-len-1){
		char *temp = (char*)malloc(len);
		
		freeAlloc(Sub);
		if(temp){
			Sub->length = len;
			Sub->chars = temp;
			for(size_t i = 0; i < len; ++i){
				Sub->chars[i] = s.chars[pos+i];
			}
		}else{
			Sub->chars = &emptyStr;
			Sub->length = 0;
		}
	}
}

long int Index(String s,String t,size_t pos){
	long int result = -1;

	if(pos>=0 && pos+t.length<=s.length){
		size_t tempIndex,
			   innerIndex,
			   tlen = t.length;
		
		for(tempIndex = pos; tempIndex <= s.length-tlen; ++tempIndex){
			for(innerIndex = 0; innerIndex < tlen; ++innerIndex){
				if(s.chars[tempIndex+innerIndex] != t.chars[innerIndex]){
					break;
				}
			}

			if(innerIndex==tlen){
				result = tempIndex;
				break;
			}
		}
	}

	return result;
}

void Replace(HString s,String t,String v){
	size_t pos = 1,
		   find = 0;

	while((find = Index(*s,t,pos)) != -1){
		StrDelete(s,find,t.length);
		StrInsert(s,find,v);
		pos = find + v.length;
	}
}

void StrInsert(HString s,size_t pos,String t){
	if(s->chars){//当被插入的源字符已分配存储空间
		if(pos>=0 && pos<=s->length){
			size_t start,
			   	   cur = 0,
			   	   newlen = s->length + t.length;
			char *temp = (char*)malloc(newlen + 1);
		
			if(temp){
				for(start = 0; start < pos; ++start,++cur){
					temp[cur] = s->chars[start];
				}
				for(start = 0; start < t.length; ++start,++cur){
					temp[cur] = t.chars[start];
				}
				for(start = pos; start < s->length; ++start,++cur){
					temp[cur] = s->chars[start];
				}
				temp[cur] = '\0';
				s->length = newlen;
				freeAlloc(s);
				s->chars = temp;
			}
		}
	}else{//无分配存储空间
		StrCopy(s,t);
	}
}

void StrDelete(HString s,size_t pos,size_t len){
	if(pos>0 && len>0 && pos<=s->length-len+1){
		size_t start = 0,
			   cur = 0,
			   newlen = s->length - len;
		char *newchars = (char*)malloc(newlen+1);

		if(newchars){
			for( ; start < pos; ++start,++cur){
				newchars[cur] = s->chars[start];
			}
			for(start = pos+len; start < s->length; ++start,++cur){
				newchars[cur] = s->chars[start];
			}
			newchars[cur] = '\0';
			s->length = newlen;
			freeAlloc(s);
			s->chars = newchars;
		}
	}
}

void tolowercase(HString s){
	for(size_t i = 0; i < s->length; ++i){
		s->chars[i] = tolower(s->chars[i]);
	}
}

void touppercase(HString s){
	for(size_t i = 0; i < s->length; ++i){
		s->chars[i] = toupper(s->chars[i]);
	}
}

void DestroyString(HString s){
	free(s->chars);
	s->chars = NULL;
	s->length = 0;
}
