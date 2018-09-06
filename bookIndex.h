#define MaxBookNum 1000				// 假设只对1000本书建索引表
#define MaxKeyNum 2500				// 索引表的最大容量
#define MaxLineLen 500				// 书目串的最大长度
#define MaxWordNum 10				// 词表的最大容量

typedef struct{
	char *item[];		// 字符串的数组
	int last;			// 词表的长度
}WordListType;			// 词表类型(顺序表)

typedef int ElemType;	//定义连表的数据元素类型为整形(书号类型)

typedef struct{
	HString key;		//关键词
	LinkList bnolist;	//存放书号索引的连表
}IdxTermType;			//索引项类型

typedef struct{
	IdxTermType item[MaxKeyNum+1];
	int last;
}IdxListType;			//索引表类型(有序表)

//主要变量
char *buf;				//书目串缓冲区
WordListType wdlist;	//词表

/*******************基本操作************************/
//初始化操作，置索引表idexlist为空表，且在idxlist.item[0]设一空串
void InitIdxList(IdxListType *idxlist);

//从文件f读入一个书目信息到书目缓冲区buf
void getLine(FILE *f);

//从buf中提取书名关键词到词表wdlist，书号存入bno
void ExtractKeyWord(ElemType *bn);

//将书号为bno的书名关键词按辞典顺序插入索引表idxlist
int InsIdxList(IdxListType *idxlist,ElemType bno);

//将生成的索引表idxlist输出到文件g
void PutText(FILE *g,IdxListType idxlist);

//用wd返回词表wdlist中第i个关键词
void GetWord(int i,HString wd);

//在索引表idxlist中查询是否存在与wd相等的关键词。若存在，则返回其在索引表
//中的位置，且b取之TRUE；否则返回插入位置，且b取值FALSE
int Locate(IdxListType idxlist,HString wd,_Bool *b);

//在索引表idxlist的第i项上插入新关键词wd，并初始化书号索引的链表为空表
void InsertNewKey(IdxListType *idxlist,int i,HString wd);

//在索引表idxlist的第i项中插入书号为bno的索引
int InsertBook(IdxListType *idxlist,int i,int bno);
