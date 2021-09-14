#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct
{
    int code;
    int RecNo;
}BinTreeElementType;

typedef struct
{
    int code;
    char surname[20];
    char name[20];
    char sex;
    int year;
    float grade;
}studentT;

typedef struct BinTreeNode *BinTreePointer;
typedef struct BinTreeNode {
    BinTreeElementType Data;
    BinTreePointer LChild, RChild;
} BinTreeNode;

typedef enum {
    FALSE, TRUE
} boolean;


void CreateBST(BinTreePointer *Root);
boolean BSTEmpty(BinTreePointer Root);
void RecBSTInsert(BinTreePointer *Root, BinTreeElementType Item);
void RecBSTSearch(BinTreePointer Root, BinTreeElementType KeyValue, boolean *Found, BinTreePointer *LocPtr);
void RecBSTInorder(BinTreePointer Root);
int BuildBST(BinTreePointer *Root);
void writeNewStudents(BinTreePointer *Root, int *size);
void printStudentsWithGrade(float theGrade);
void PrintStudent(int recNum);


int main()
{
    BinTreePointer ARoot, LocPtr;
    BinTreeElementType recn;
    studentT student;
    boolean found;
    int size;

    printf("Q1. Build BST from a file\n");
    size=BuildBST(&ARoot);

    printf("Q2. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(ARoot);

    printf("\nQ3. Write new students, update file and BST\n");
    writeNewStudents(&ARoot, &size);

    printf("Q4. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(ARoot);

    printf("\nQ5. Search for a student\n");
    printf("Give student's code? ");
    scanf("%d", &recn.code);
    RecBSTSearch(ARoot, recn, &found, &LocPtr);
    if(found)
        PrintStudent(LocPtr->Data.RecNo);
    else
        printf("The student with code %d not found\n", recn.code);

    printf("Q6. Print size and BST\n");
    printf("Size=%d\n", size);
    printf("Nodes of BST\n");
    RecBSTInorder(ARoot);

    printf("\nQ7. Print students with grades >= given grade\n");
    printf("Give the grade: ");
    scanf("%f", &student.grade);
    printStudentsWithGrade(student.grade);


    return 0;
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
        if (Item.code < (*Root) ->Data.code)
            RecBSTInsert(&(*Root) ->LChild,Item);
        else if (Item.code > (*Root) ->Data.code)
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
        if (KeyValue.code < Root->Data.code)
            RecBSTSearch(Root->LChild, KeyValue, &(*Found), &(*LocPtr));
        else
            if (KeyValue.code > Root->Data.code)
                RecBSTSearch(Root->RChild, KeyValue, &(*Found), &(*LocPtr));
            else
                {
                    *Found = TRUE;
                    *LocPtr=Root;
                }
}

void RecBSTInorder(BinTreePointer Root)
{
    if (Root!=NULL) {
        RecBSTInorder(Root->LChild);
        printf("(%d, %d), ",Root->Data.code, Root->Data.RecNo);
        RecBSTInorder(Root->RChild);
    }
}

int BuildBST(BinTreePointer *Root)
{
    FILE *fp;
    int nscan;
    char ch;
    studentT student;
    BinTreeElementType rec;
    int size;

    CreateBST(&(*Root));

    fp=fopen("foitites.dat", "r");
    size=0;
    if(fp!=NULL){
        while(TRUE){
            nscan=fscanf(fp, "%d, %20[^,], %20[^,], %c, %d, %f%c", &student.code, student.name, student.surname, &student.sex, &student.year, &student.grade, &ch);
            if(nscan==EOF) break;
            if(nscan!=7 || ch!='\n'){
                printf("Improper file format");
                exit(1);
            }
            else{
                rec.code=student.code;
                rec.RecNo=size;
                RecBSTInsert(&(*Root), rec);
                size++;
            }
        }
        fclose(fp);
    }
    return size;
}

void writeNewStudents(BinTreePointer *Root, int *size)
{
    FILE *fp;
    studentT student;
    BinTreeElementType rec;
    boolean found;
    BinTreePointer LocPtr;
    char ch;

    fp=fopen("foitites.dat", "a");
    if(fp!=NULL){
        do
        {
            printf("Give student's AM? ");
            scanf("%d", &rec.code);
            RecBSTSearch(*Root, rec, &found, &LocPtr);
            if(!found){
                student.code=rec.code;
                printf("Give student surname? ");
                scanf("%s", student.surname); getchar();
                printf("Give student name? ");
                scanf("%s", student.name); getchar();
                printf("Give student sex F/M? ");
                scanf("%c", &student.sex); getchar();
                printf("Give student's registration year? ");
                scanf("%d", &student.year);
                printf("Give student's grade? ");
                scanf("%f", &student.grade);
                rec.RecNo=*size;
                RecBSTInsert(&(*Root), rec);
                fprintf(fp, "%d, %s, %s, %c, %d, %.1f\n", student.code, student.name, student.surname, student.sex, student.year, student.grade);
                (*size)++;
                printf("Size=%d\n", *size);
            }
            else printf("The student with AM %d is already exists\n", student.code);
            printf("\nContinue Y/N: ");
            do
            {
                scanf("%c", &ch);
            } while (toupper(ch)!= 'N' && toupper(ch)!= 'Y');
        }while (toupper(ch)!='N');
    }
    fclose(fp);
}

void printStudentsWithGrade(float theGrade)
{
    FILE *fp;
    int nscan;
    char ch;
    studentT student;

    fp=fopen("foitites.dat", "r");
    if(fp!=NULL)
    {
        while(TRUE)
        {
            nscan=fscanf(fp, "%d, %20[^,], %20[^,], %c, %d, %f%c", &student.code, student.name, student.surname, &student.sex, &student.year, &student.grade, &ch);
            if(nscan==EOF) break;
            if(nscan!=7 || ch!='\n'){
                printf("Improper file format");
                exit(1);
            }
            else
                if(student.grade>=theGrade)
                    printf("%d, %s, %s, %c, %d, %.1f\n", student.code, student.name, student.surname, student.sex, student.year, student.grade);
        }
        fclose(fp);
    }
}

void PrintStudent(int recNum)
{
    FILE *fp;
    int nscan;
    char ch;
    studentT student;
    int lines;

    fp=fopen("foitites.dat", "r");
    lines=0;
    if(fp!=NULL){
        while(lines<=recNum){
            nscan=fscanf(fp, "%d, %20[^,], %20[^,], %c, %d, %f%c", &student.code, student.name, student.surname, &student.sex, &student.year, &student.grade, &ch);
            if(nscan==EOF) break;
            if(nscan!=7 || ch!='\n'){
                printf("Improper file format");
                exit(1);
            }
            lines++;
        }
        if(lines==recNum+1)
            printf("%d, %s, %s, %c, %d, %.1f\n", student.code, student.name, student.surname, student.sex, student.year, student.grade);
    }
    fclose(fp);
}

