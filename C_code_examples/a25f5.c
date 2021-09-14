#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>


typedef int BinTreeElementType;

typedef struct BinTreeNode *BinTreePointer;

struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} ;

typedef enum {
    FALSE, TRUE
} boolean;

void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue);
void RecBSTInorder(BinTreePointer Root);
void RecBSTPreorder(BinTreePointer Root);
void RecBSTPostorder(BinTreePointer Root);

int CountLeaves(BinTreePointer Root);

int main()
{
    BinTreePointer ARoot;
    int num;
    char ch;
    int count;

    CreateBST(&ARoot);

    do{
        printf("Enter a number for insertion in the Tree: ");
        scanf("%d",&num);
        RecBSTInsert(&ARoot, num);
        printf("Continue Y/N: ");

        do{
            scanf("%c",&ch);
          }while(ch!='N' && ch!='n' && ch!='Y' && ch!='y');

          if (ch=='n' || ch=='N') break;
    }while(ch!='N' || ch!='n');


    printf("Elements of BST\n");
    RecBSTInorder(ARoot);
    printf("\n");

    count=CountLeaves(ARoot);
    printf("Number of leaves %d",count);

    return 0;
}

int CountLeaves(BinTreePointer Root)
{

    if(Root == NULL)
        return 0;

    if(Root->LChild == NULL && Root->RChild == NULL)
        return 1;

    return CountLeaves(Root->LChild) + CountLeaves(Root->RChild);
}

void CreateBST(BinTreePointer *Root)
{
    *Root = NULL;
}

boolean BSTEmpty(BinTreePointer Root)
{
    return (Root==NULL);
}

void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item)
{
    if (BSTEmpty(*Root)) {
        (*Root) = (BinTreePointer)malloc(sizeof (struct BinTreeNode));
        (*Root) ->Data = Item;
        (*Root) ->LChild = NULL;
        (*Root) ->RChild = NULL;
    }
    else
        if (Item < (*Root) ->Data)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item > (*Root) ->Data)
            RecBSTInsert(&(*Root) ->RChild,Item);
        else
            printf("TO STOIXEIO EINAI HDH STO DDA\n");
}

void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue,
                    boolean *Found, BinTreePointer *LocPtr)
{
    if (BSTEmpty(Root))
        *Found=FALSE;
    else
        if (KeyValue < Root->Data)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue > Root->Data)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}

void RecBSTDelete(BinTreePointer *Root, BinTreeElementType KeyValue)
{

   BinTreePointer TempPtr;

    if (BSTEmpty(*Root))
        printf("TO STOIXEIO DEN BRE8HKE STO DDA\n");
     else

          if (KeyValue < (*Root)->Data)
             RecBSTDelete(&((*Root)->LChild), KeyValue);
          else
            if (KeyValue > (*Root)->Data)
                  RecBSTDelete(&((*Root)->RChild), KeyValue);
            else
                if ((*Root)->LChild ==NULL)
                 {
                      TempPtr = *Root;
                      *Root = (*Root)->RChild;
                      free(TempPtr);
                 }
                else if ((*Root)->RChild == NULL)
                   {
                        TempPtr = *Root;
                        *Root = (*Root)->LChild;
                        free(TempPtr);
                   }
                   else
                   {

                        TempPtr = (*Root)->RChild;
                        while (TempPtr->LChild != NULL)
                              TempPtr = TempPtr->LChild;

                        (*Root)->Data = TempPtr->Data;
                        RecBSTDelete(&((*Root)->RChild), (*Root)->Data);
                   }
}

void RecBSTInorder(BinTreePointer Root)
{
    if (Root!=NULL) {

        RecBSTInorder(Root->LChild);
        printf("%d ",Root->Data);

        RecBSTInorder(Root->RChild);
    }

}

void RecBSTPreorder(BinTreePointer Root)
{
    if (Root!=NULL) {
        printf("%d ",Root->Data);

        RecBSTPreorder(Root->LChild);

        RecBSTPreorder(Root->RChild);
    }

}

void RecBSTPostorder(BinTreePointer Root)
{
    if (Root!=NULL) {

        RecBSTPostorder(Root->LChild);

        RecBSTPostorder(Root->RChild);
        printf("%d ",Root->Data);
    }
}
