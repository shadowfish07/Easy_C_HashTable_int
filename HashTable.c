#include <stdio.h>
#include <string.h>

//powered by shadowfish
//�ô������ڽ���keyΪ��������valueΪ�����Ĺ�ϣ����ϣ�㷨Ϊkey���ϣ����ȡ�ࡣ

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

//��ʼ��
int Hash_Init(HashTable *hashTable,int width)
{
    if (width<1)
        return 0;
    //�������ָ��HashData��ָ���ָ������
    HashData **tmp = malloc(sizeof(HashData *)*width);
    //Ϊָ�����鸳��ֵ0
    memset(tmp,0,sizeof(HashData *)*width);
    hashTable->head=tmp;
    hashTable->width=width;
    return 1;
}

//��ϣ�㷨�����Kֵ
int Hash_addr(HashTable hashTable,int key)
{
    int addr = abs(key)%hashTable.width;
    return addr;
}

//����
int Hash_insert(HashTable hashTable,int key,int value)
{
    //�½�һ��HashData
    HashData *tmp =malloc(sizeof(HashData));
    tmp->key=key;
    tmp->value=value;

    //����ʱ����Ƿ��Ѿ�����keyֵ
    if (Hash_Search(hashTable,key)!= NULL)
        return 0;

    int k=Hash_addr(hashTable,key);
    //�����´�����HashData��������;
    //�½ڵ��nextָ��ɵ�������
    tmp->next=hashTable.head[k];
    //�������������µĽڵ�
    hashTable.head[k]=tmp;
    return 1;
}

//��ѯ
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
    
    printf("��Cʵ�ֵ�int��ϣ��\n\n");
    printf("1.��ʼ��ɢ�б�\n������ɢ�б���\n");
    while (1)
    {
        fflush(stdin);
        scanf("%d",&a); 
        if(a<=0) 
            printf("ɢ�б��ʼ��ʧ�ܣ���������Ч��ֵ\n");
        else
            break;
    }
    Hash_Init(&ht,a);
    printf("ɢ�б��ʼ����ɣ�����%d��\n",a);
    printf("2.��������\n�������ֵ��,����-99 -99�Խ���\n");
    while(1)
    {
        scanf("%d %d",&a,&b);
        if (a==-99 && b==-99)
            break;
        if  (Hash_insert(ht,a,b))
            printf("key %d,value %d��ӳɹ�\n",a,b);
        else
            printf("key %d,value %d���ʧ��\n",a,b);
        
    } 
    printf("����������\n");
    printf("3.��������\n��������Բ���ֵ\n");
    while (1)
    {
        scanf("%d",&a);
        data = Hash_Search(ht,a);
        if (data==NULL)
            printf("δ�ҵ��ü�ֵ��\n");
        else
            printf("�� %d ��ֵΪ %d\n",a,data->value);
    }    
}