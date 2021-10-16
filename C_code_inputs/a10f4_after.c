typedef int StackElementType;
typedef struct  {
    int Top;
    StackElementType Element[StackLimit];
} StackType;
typedef enum {
    FALSE, TRUE
} boolean;

void CreateStack(StackType *Stack);
boolean EmptyStack(StackType Stack);
boolean FullStack(StackType Stack);
void Push(StackType *Stack, StackElementType Item);
void Pop(StackType *Stack, StackElementType *Item);
void TraverseStack(StackType Stack);

int main()
{
    StackType AStack1, AStack2;
    StackElementType AnItem;
    int i, n;
    CreateStack(&AStack1);
    CreateStack(&AStack2);

    printf("PLITHOS STOIXEIWN:");
    scanf("%d", &n);
    for(i=1;i<=n;i++)
    {
        printf("DWSE TO %do STOIXEIO:", i);
        scanf("%d", &AnItem);
        Push(&AStack1, AnItem);
    }
    printf("*********1i stoiva***********\n");
    TraverseStack(AStack1);

    while(i>1)
    {
        Pop(&AStack1, &AnItem);
        Push(&AStack2, AnItem);
        i--;
    }
    printf("*********2i stoiva***********\n");
    TraverseStack(AStack2);

    return 0;
}
void CreateStack(StackType *Stack)
{
    Stack -> Top = -1;
}

boolean EmptyStack(StackType Stack)
{
    return (Stack.Top == -1);
}

boolean FullStack(StackType Stack)
{
    return (Stack.Top == (StackLimit - 1));
}

void Push(StackType *Stack, StackElementType Item)
{
    if (!FullStack(*Stack)) {
        Stack -> Top++;
        Stack -> Element[Stack -> Top] = Item;
    } else
        printf("Full Stack...");
}

void Pop(StackType *Stack, StackElementType *Item)
{
    if (!EmptyStack(*Stack)) {
        *Item = Stack -> Element[Stack -> Top];
        Stack -> Top--;
    } else
        printf("Empty Stack...");
}
void TraverseStack(StackType Stack)
{
    int i;
    for (i=Stack.Top;i>=0;i--) {
        printf("%d ",Stack.Element[i]);
    }
    printf("\n");
}
