#include <stdio.h>
#include <string.h>

//powered by shadowfish
//该代码用于建立key为正整数，value为字符数组的哈希表。哈希算法为key与哈希表长度取余。

#define MAXICHAR_INDEX_ROW 20
#define MAXICHAR_INDEX_COLUMN 30
#define MAXICHAR_INDEX_KEY 30

typedef struct HashData
{
    char *key;
    char (*value)[MAXICHAR_INDEX_COLUMN];
    struct HashData *next;
}HashData;

typedef struct
{
    HashData **head;
    int width;
}HashTable;

int Hash_Init(HashTable *hashTable,int width);
unsigned int Hash_addr(HashTable hashTable,char *key);
int Hash_insert(HashTable hashTable,char* key,char**value);
HashData *Hash_Search(HashTable hashTable,int key);

//初始化
int Hash_Init(HashTable *hashTable,int width)
{
    if (width<1)
        return 0;
    //创建存放指向HashData的指针的指针数组
    HashData **tmp = malloc(sizeof(HashData *)*width);
    //为指针数组赋初值0
    memset(tmp,0,sizeof(HashData *)*width);
    hashTable->head=tmp;
    hashTable->width=width;
    return 1;
}

//哈希算法，输出K值
unsigned int Hash_addr(HashTable hashTable, char *key)
{//来自https://blog.csdn.net/liaoshengshi/article/details/47302153
    unsigned int h=0;
    for(;*key;key++)
        h=*key+h*31;//将整个字符串按照特定关系转化为一个整数，然后对hash长度取余
    return h%hashTable.width;
}

//插入
int Hash_insert(HashTable hashTable,char* key,char **value)
{
    //新建一个HashData
    HashData *tmp =malloc(sizeof(HashData));
    tmp->key=key;
    tmp->value=value;
    
    
    //插入时检测是否已经存在key值
    if (Hash_Search(hashTable,key)!= NULL)
        return 0;

    int k=Hash_addr(hashTable,key);
    //插入新创建的HashData至链表首;
    //新节点的next指向旧的链表首
    tmp->next=hashTable.head[k];
    //链表首现在是新的节点
    hashTable.head[k]=tmp;
    return 1;
}

//查询
HashData *Hash_Search(HashTable hashTable,int key)
{
    int k=Hash_addr(hashTable,key);
    HashData *search_head = hashTable.head[k];
    while (search_head !=NULL)
    {
        if (search_head->key==key)
            return search_head;
        search_head = search_head->next;
    }
    return NULL;
}

int main()
{
    HashTable ht;
    int a=0,b=0;
    HashData *data;
    Hash_Init(&ht,a);

char (*cp)[20]={"ABCDEFDG12122"};
char bbb[]={"23328888888888888888888888ydfgdfgdfggdgf"};
cp=bbb;
printf("%s",cp);
    char* aa[30]={"232323","asdsdad2","asdr22"};
    char* *ap=aa;
    
    printf("%s",ap[0]);
    printf("%s",aa);
    Hash_insert(ht,"my",ap);
    printf("用C实现的int哈希表\n\n");
    printf("1.初始化散列表\n请输入散列表长度\n");
    while (1)
    {
        fflush(stdin);
        scanf("%d",&a); 
        if(a<=0) 
            printf("散列表初始化失败，请输入有效数值\n");
        else
            break;
    }
    Hash_Init(&ht,a);
    printf("散列表初始化完成（长度%d）\n",a);
    printf("2.插入数据\n请输入键值对,输入-99 -99以结束\n");
    while(1)
    {
        scanf("%d %d",&a,&b);
        if (a==-99 && b==-99)
            break;
        if  (Hash_insert(ht,a,b))
            printf("key %d,value %d添加成功\n",a,b);
        else
            printf("key %d,value %d添加失败\n",a,b);
        
    } 
    printf("数据添加完成\n");
    printf("3.查找数据\n请输入键以查找值\n");
    while (1)
    {
        scanf("%d",&a);
        data = Hash_Search(ht,a);
        if (data==NULL)
            printf("未找到该键值对\n");
        else
            printf("键 %d 的值为 %d\n",a,data->value);
    }    
}