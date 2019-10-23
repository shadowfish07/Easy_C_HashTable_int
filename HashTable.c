#include <stdio.h>
#include <string.h>

//powered by shadowfish
//该代码用于建立key为正整数，value为整数的哈希表。哈希算法为key与哈希表长度取余。

typedef struct HashData
{
    int key;
    int value;
    struct HashData *next;
}HashData;

typedef struct
{
    HashData **head;
    int width;
}HashTable;

int Hash_Init(HashTable *hashTable,int width);
int Hash_addr(HashTable hashTable,int key);
int Hash_insert(HashTable hashTable,int key,int value);
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
int Hash_addr(HashTable hashTable,int key)
{
    int addr = abs(key)%hashTable.width;
    return addr;
}

//插入
int Hash_insert(HashTable hashTable,int key,int value)
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