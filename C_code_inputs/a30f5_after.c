typedef struct {
char *fpos; /* Current position of file pointer (absolute address) */
void *base; /* Pointer to the base of the file */
unsigned short handle; /* File handle */
short flags; /* Flags (see FileFlags) */
short unget; /* 1-byte buffer for ungetc (b15=1 if non-empty) */
unsigned long alloc; /* Number of currently allocated bytes for the file */
unsigned short buffincrement; /* Number of bytes allocated at once */
} FILE;


typedef float  HeapElementType;
typedef  struct {
     HeapElementType key;
    // int Data;
} HeapNode;


typedef struct {
        int Size;
        HeapNode Element[MaxElements+1];
} HeapType;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateMinHeap(HeapType *Heap);
boolean FullHeap(HeapType Heap);
void InsertMinHeap(HeapType *Heap, HeapNode Item);
boolean EmptyHeap(HeapType Heap);
void DeleteMinHeap(HeapType *Heap, HeapNode *Item);
void PrintHeap(HeapType Heap);

HeapType AHeap;
HeapNode AnItem, Item;
FILE *fp;

int main()
{
    int answer;
    CreateMinHeap(&AHeap);
    printf("Give m: ");
    scanf("%d", &answer);
    fp=fopen("transactions.txt","r");
    while(1)
    {
        fscanf(fp,"%f",&AnItem.key);
        if(feof(fp))
        {
            break;
        }
        InsertMinHeap(&AHeap, AnItem);
        if(AHeap.Size>answer)
        {
            DeleteMinHeap(&AHeap, &AnItem);
        }
    }
    PrintHeap(AHeap);
    printf("Transactions\n");
    while(!EmptyHeap(AHeap))
    {
        DeleteMinHeap(&AHeap, &AnItem);
        printf("%.2f ",AnItem.key);
    }
    fclose(fp);

}

void CreateMinHeap(HeapType *Heap)
{
  (*Heap).Size=0;
}

boolean EmptyHeap(HeapType Heap)
{
  return (Heap.Size==0);
}

boolean FullHeap(HeapType Heap)
{
  return (Heap.Size==MaxElements);
}

void InsertMinHeap(HeapType *Heap, HeapNode Item)
{
   int hole;

   if (!FullHeap(*Heap))
   {
          (*Heap).Size++;

          hole=(*Heap).Size;
          while (hole>1 && Item.key < Heap->Element[hole/2].key)
          {
            (*Heap).Element[hole]=(*Heap).Element[hole/2];
                      hole=hole/2;
          }
          (*Heap).Element[hole]=Item;
   }
   else
     printf("Full Heap...\n");
}

void DeleteMinHeap(HeapType *Heap, HeapNode *Item)
{
   int parent, child;
   HeapNode last;
   boolean done;

   if (!EmptyHeap(*Heap))
   {
        done=FALSE;
        *Item=(*Heap).Element[1];
        last=(*Heap).Element[(*Heap).Size];
        (*Heap).Size--;

        parent=1; child=2;

        while (child<=(*Heap).Size && !done)
        {
            if (child<(*Heap).Size)
                if ((*Heap).Element[child].key > (*Heap).Element[child+1].key)
                    child++;
            if (last.key < (*Heap).Element[child].key)
                done=TRUE;
            else
            {
               (*Heap).Element[parent]=(*Heap).Element[child];
               parent=child;
               child=2*child;
            }
        }
        (*Heap).Element[parent]=last;
    }
   else
       printf("Empty heap...\n");
}

void PrintHeap(HeapType Heap)
{
    int i;
     printf("Data Structure size=%d\n",Heap.Size);
     for (i=1; i<=Heap.Size;i++)
        printf("%.2f ",Heap.Element[i].key);
    printf(" \n");
}
