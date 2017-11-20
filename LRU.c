#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct node
{
    int *address;
    struct node* next;
    struct node* prev;
}NODE;
typedef struct queue
{
    int count;
    NODE *f;
    NODE* r;
}QUEUE;
typedef struct hash
{
    int capacity;
    NODE* array[100000];
}HASH;
void create(HASH *h,QUEUE *q)
{
    h->capacity = 100000;
    q->r = q->f = NULL;
    q->count = 0;
    for(int i=0;i<h->capacity;i++)
        h->array[i] = NULL;
    
    return;
}
void EnQ(QUEUE *q,HASH *h,int* add)
{
    int data = *add;
    int f1 = 0;
    int i;
    if(q->count == 5)
    {
        if(h->array[data]!=NULL && data == *h->array[data]->address){
            f1 = 1;
        }
        
        if(f1 == 1)
        {
            
            //printf("Cache hit\n");
            NODE* p = h->array[data];
            if(p == q->r){
                return;}
            if(p==q->f){
                q->f = p->next;
                
            }
            else p->prev->next = p->next;
            
            q->r->next = p;
            p->next->prev = p->prev;
            p->prev = q->r;
            p->next = NULL;
            q->r = p;
            return;
        }
        
        else
        {
            //printf("Cache miss\n");
            h->array[data] = NULL;
            q->f = q->f->next;
            free(q->f->prev);
            q->f->prev = NULL;
            NODE *tmp = (NODE*)malloc(sizeof(NODE));
            tmp->address = add;
            tmp->next = NULL;
            tmp->prev = q->r;
            q->r->next = tmp;
            tmp->prev = q->r;
            q->r = tmp;
            h->array[data] = tmp;
        }
        
        return;
    }
    else
    {
        NODE *p = NULL;
        NODE* tmp = (NODE*)malloc(sizeof(NODE));
        tmp->address = add;
        tmp->next = NULL;
        tmp->prev = NULL;
        p = q->f;
        if(p == NULL)
        {
            q->f = tmp;
            q->r = tmp;
        }
        else
        {
            q->r->next = tmp;
            tmp->prev = q->r;
        }
        q->r = tmp;
        (q->count)++;
        h->array[data] = tmp;
        
        return;
    }
    
    
}
void dispCache(QUEUE *q)
{
    NODE *tmp = q->f;
    
    while(tmp!=NULL)
    {
        printf("%d",*tmp->address);
        tmp = tmp->next;
    }
    printf("\nrear:%d\nfront:%d\n",*q->r->address,*q->f->address);
}

int normalSearch(int data,int ar[100000]){
    int i;
    for(i=0;i<100000;i++){
        if(ar[i]==data)break;
    }
   // printf("Element found at index %d\n",i);
    
    //print time taken here
    return i;
}

void cacheSearch(HASH *h,QUEUE* q,int data,int ar[100000]){
	int i;
    if(h->array[data] == NULL){
       // printf("Element not found in cache. Proceeding with normal search\n");
        
        EnQ(q,h,&ar[normalSearch(data,ar)]);
        return;
    }
    //printf("element %d found\n",*(h->array[data]->address));
    i = *(h->array[data]->address);
    //print time taken here
}
int main()
{
    QUEUE q;
    HASH h;
    int n;
    int i;
    int ar[100000];
	for(i=0;i<100000;i++){
		ar[i] = rand()%100000;
	}
    printf("Sizeof the cache is 5\n");
    create(&h,&q);
    
    double sum=0;
int flag=1;
    do{
        printf("1.Append to queue and to hash table from the main array\n2.Display\nOther for comparison\nEnter your choice\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                printf("Enter index of element to Enqueue to cache\n");
                int i;
                scanf("%d",&i);
                EnQ(&q,&h,&ar[i]);
                break;
            case 2:
                dispCache(&q);
                break;
            
            default:
                //printf("%f",avg_elapse);
                flag=0;
		break;

        }
        
    }while(flag);

    
    for(int j=0;j<1000;j++)
                {
                    int r=rand()%100000;
                    clock_t START,END;
                    START = clock();
                    cacheSearch(&h,&q,ar[r],ar);
                    END = clock();
                    float elapsed = ((float)END-(float)START)/CLOCKS_PER_SEC;
                    sum=sum+elapsed;
                }
    printf("Cache time taken(10000 searches) is %f",sum/10000);
	sum = 0;
	for(int j=0;j<10000;j++)
                {
                    int r=rand()%100000;
                    clock_t START,END;
                    START = clock();
                    normalSearch(ar[r],ar);
                    END = clock();
                    float elapsed = ((float)END-(float)START)/CLOCKS_PER_SEC;
		    sum=sum+elapsed;
                 
	}
printf("Normal access average time(10000 searches) taken is %f",sum/10000); 
	
}







