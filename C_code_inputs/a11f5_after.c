typedef struct {
char *fpos; /* Current position of file pointer (absolute address) */
void *base; /* Pointer to the base of the file */
unsigned short handle; /* File handle */
short flags; /* Flags (see FileFlags) */
short unget; /* 1-byte buffer for ungetc (b15=1 if non-empty) */
unsigned long alloc; /* Number of currently allocated bytes for the file */
unsigned short buffincrement; /* Number of bytes allocated at once */
} FILE;

typedef char BinTreeElementType[20];

typedef struct BinTreeNode *BinTreePointer;
 struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateBST(BinTreePointer *Root);
boolean EmptyBST(BinTreePointer Root);
void BSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
    BinTreePointer *LocPtr, BinTreePointer *Parent);
void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void InorderTraversal(BinTreePointer Root);
void CreateDictionary(BinTreePointer *Root, FILE *fp);
int SpellingCheck(BinTreePointer Root, FILE *fp);

BinTreePointer ARoot, LocPtr;
BinTreeElementType AnItem, answer;
boolean Found;

int main()
{
    CreateBST(&ARoot);
    FILE *fp1, *fp2;
    fp1=fopen("i112f5.txt","r");
    fp2=fopen("i111f5.txt","r");
    printf("**********Dictionary**********\n");
    CreateDictionary(&ARoot, &(*fp1));
    InorderTraversal(ARoot);
    printf("\n");
    printf("**********Not in Dictionary**********\n");
    printf("Number of words not in Dictionary: %d", SpellingCheck(ARoot, &(*fp2)));

}

void CreateDictionary(BinTreePointer *Root, FILE *fp)
{
    while(!feof(fp)){
        fscanf(fp,"%s",AnItem);
        BSTInsert(&ARoot, AnItem);
   }
}

int SpellingCheck(BinTreePointer Root, FILE *fp)
{
    boolean Found;
    BinTreePointer LocPtr;
    int count;
    count=0;
    while(!feof(fp)){
        fscanf(fp,"%s",AnItem);
        BSTSearch(ARoot, AnItem, &Found, &LocPtr);
        if(Found==FALSE){
            printf("%s\n ",AnItem);
            count=count+1;
        }
   }
   return count;



}

void CreateBST(BinTreePointer *Root)
{
    *Root = NULL;
}

boolean EmptyBST(BinTreePointer Root)
{   return (Root==NULL);
}

void BSTInsert(BinTreePointer *Root, BinTreeElementType Item)
{
  /*  BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (strcmp(Item, LocPtr->Data)<0)
            LocPtr = LocPtr ->LChild;
        else if (strcmp(Item, LocPtr ->Data)>0)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("To %s EINAI HDH STO DDA\n", Item);
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        strcpy(LocPtr->Data, Item);
        //LocPtr ->Data = Item;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (Item < Parent ->Data)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
    */

    if( *Root == NULL ) {
        *Root = (BinTreePointer) malloc( sizeof( struct BinTreeNode ) );
        strcpy ((*Root)->Data, Item);
        (*Root)->LChild = NULL;
        (*Root)->RChild = NULL;
    } else {
        if(strcmp(Item, (*Root)->Data)<0)
            BSTInsert(&(*Root)->LChild, Item);
        else if(strcmp(Item, (*Root)->Data)>0)
            BSTInsert(&(*Root)->RChild, Item);
        else
            printf ("%s", Item);
    }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr)
{

    (*LocPtr) = Root;
    (*Found) = FALSE;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (strcmp(KeyValue, (*LocPtr)->Data)<0)
            (*LocPtr) = (*LocPtr)->LChild;
        else
            if (strcmp(KeyValue, (*LocPtr)->Data)>0)
                (*LocPtr) = (*LocPtr)->RChild;
            else (*Found) = TRUE;
    }
}

void BSTSearch2(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
    BinTreePointer *LocPtr, BinTreePointer *Parent)
{
    *LocPtr = Root;
    *Parent=NULL;
    *Found = FALSE;
    while (!(*Found) && *LocPtr != NULL)
    {
        if (KeyValue < (*LocPtr)->Data) {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (KeyValue > (*LocPtr)->Data) {
                *Parent=*LocPtr;
                *LocPtr = (*LocPtr)->RChild;
            }
            else *Found = TRUE;
    }

}

void BSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
{

   BinTreePointer
   n,
   Parent,
   nNext,
   SubTree;
   boolean Found;

     BSTSearch2(*Root, KeyValue, &Found , &n, &Parent);
     if (!Found)
        printf("TO STOIXEIO %s DEN EINAI STO DDA\n", KeyValue);
     else {
          if (n->LChild != NULL && n->RChild != NULL)
          {
                 nNext = n->RChild;
                 Parent = n;
                 while (nNext->LChild !=NULL)  //* DIASXISH PROS TA ARISTERA *)
                 {
                      Parent = nNext;
                      nNext = nNext->LChild;
                 }
//                n->Data = nNext->Data;
                n = nNext;
          }
          SubTree = n->LChild;
          if (SubTree == NULL)
             SubTree = n->RChild;
          if (Parent == NULL)                 //* 8A DIAGRAFEI H RIZA *)
             *Root = SubTree;
          else if (Parent->LChild == n)
                  Parent->LChild = SubTree;
               else
                   Parent->RChild = SubTree;
          free(n);
     }
}

void InorderTraversal(BinTreePointer Root)
{
    if (Root!=NULL) {
        InorderTraversal(Root->LChild);
        printf(" %s\n ",Root->Data);
        InorderTraversal(Root->RChild);
    }
}

