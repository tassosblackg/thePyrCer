#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int amka;
    int afm;
    int age;
} BinTreeElementType;

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

BinTreePointer ARoot1, ARoot2, LocPtr;
BinTreeElementType AnItem, AnItem2, Item;
boolean Found;

int main()
{
    int i;
    char answer;
    CreateBST(&ARoot1);
    CreateBST(&ARoot2);
    do{
        printf("Give AMKA? ");
        scanf("%d",&AnItem.amka);
        printf("Give AFM? ");
        scanf("%d",&AnItem.afm);
        printf("Give age? ");
        scanf("%d",&AnItem.age);
        printf("\n");
        printf("Continue Y/N: ");
        scanf("%c",&answer);
        answer=getchar();
        if(AnItem.age<=60)
        {
        BSTInsert(&ARoot1, AnItem);
        }else if(AnItem.age>60)
        {
        BSTInsert(&ARoot2,  AnItem);
        }
    }while(answer=='Y' || answer=='y');

    printf("People with age less-equal 60\n");
    InorderTraversal(ARoot1);
    printf("People with age greater than 60\n");
    InorderTraversal(ARoot2);
    for(i=0;i<3;i++){
    printf("Give AMKA: ");
    scanf("%d",&AnItem.amka);
    printf("Give age: ");
    scanf("%d",&AnItem.age);
    if(AnItem.age<=60)
    {
        BSTSearch(ARoot1, AnItem, &Found, &LocPtr);
    }else if(AnItem.age>60)
    {
        BSTSearch(ARoot2, AnItem, &Found, &LocPtr);
    }
     if (Found)
        if (LocPtr->Data.age == AnItem.age)
            printf("The person with AMKA %d,AFM %d and age %d is the catalogue", AnItem.amka, LocPtr->Data.afm, LocPtr->Data.age);
        else
            printf("The person with AMKA %d has age %d different from the person you are looking for", AnItem.amka, LocPtr->Data.age);
     else
         printf("The person with AMKA %d and age %d is Unknown", AnItem.amka, AnItem.age);
    printf("\n");
    }
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
    BinTreePointer LocPtr, Parent;
    boolean Found;

    LocPtr = *Root;
    Parent = NULL;
    Found = FALSE;
    while (!Found && LocPtr != NULL) {
        Parent = LocPtr;
        if (Item.amka < LocPtr->Data.amka && Item.afm < LocPtr->Data.afm &&Item.age < LocPtr->Data.age )
            LocPtr = LocPtr ->LChild;
        else if (Item.amka > LocPtr ->Data.amka && Item.afm > LocPtr ->Data.afm && Item.age > LocPtr ->Data.age)
            LocPtr = LocPtr ->RChild;
        else
            Found = TRUE;
    }
    if (Found)
        printf("To %d EINAI HDH STO DDA\n", Item.amka);
    else {
        LocPtr = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        LocPtr ->Data.amka = Item.amka;
        LocPtr ->Data.afm = Item.afm;
        LocPtr ->Data.age = Item.age;
        LocPtr ->LChild = NULL;
        LocPtr ->RChild = NULL;
        if (Parent == NULL)
            *Root = LocPtr;
        else if (Item.amka < Parent ->Data.amka && Item.afm < Parent ->Data.afm && Item.age < Parent ->Data.age)
            Parent ->LChild = LocPtr;
        else
            Parent ->RChild = LocPtr;
    }
}

void BSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found,
                BinTreePointer *LocPtr)
{

    (*LocPtr) = Root;
    (*Found) = FALSE;
    while (!(*Found) && (*LocPtr) != NULL)
    {
        if (KeyValue.amka < (*LocPtr)->Data.amka)
            (*LocPtr) = (*LocPtr)->LChild;

        else
            if (KeyValue.amka > (*LocPtr)->Data.amka)
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
        if (KeyValue.amka < (*LocPtr)->Data.amka) {
            *Parent=*LocPtr;
            *LocPtr = (*LocPtr)->LChild;
        }
        else
            if (KeyValue.amka > (*LocPtr)->Data.amka) {
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
        printf("TO STOIXEIO  DEN EINAI STO DDA\n");
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

                n->Data = nNext->Data;
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
        printf("(%d,%d,%d)",Root->Data.amka, Root->Data.afm, Root->Data.age);
        InorderTraversal(Root->RChild);
        printf("\n");
    }
}




