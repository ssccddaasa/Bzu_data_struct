#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int Cost;
    struct node *next;
    char Name[20];
    int FinalCost;
} node;
typedef struct Graph
{
    node *ArrayOfLL[30];
} Graph;
int ArraySize = 0;
node *Dikisra(Graph *G, char Initial[]);
node *CityExist(char Name[], node **Array);
Graph *ReadFile(Graph *G);
node *Previous(node *Head, node *P);
node *Insert(int Cost, char Name[], node *Head);
int AllVisited(int Visited[]);
int FindIndex(char Name[], node *ArrayofLL[]);
int FindCost(node *src, char Dest[]);
int Exist(node *, char Dest[]);
int FinMinIndex(int Visited[], int Costs[]);
node *Last(node *Head);
char *PathBetween(node *Head, char Dest[]);
void PrintPath(node *Head, char Name[]);
void menu(Graph *G);
void PrintPath(node *Head, char Destination[]);
int main()
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    menu(G);
    return 0;
}
node *Previous(node *Head, node *P)
{

    node *temp = (node *)malloc(sizeof(node));
    temp = Head;
    while (temp != NULL && temp->next != P)
    {
        temp = temp->next;
    }
    return temp;
}
node *Insert(int Cost, char Name[], node *Head)
{
    node *P = (node *)malloc(sizeof(node));
    P->Cost = Cost;
    P->FinalCost = 100000;
    strcpy(P->Name, Name);
    if (Head->next == NULL)
    {
        Head->next = P;
        P->next = NULL;
        return Head;
    }
    node *temp = Head->next;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = P;
    P->next = NULL;
    return Head;
}
Graph *ReadFile(Graph *G)
{
    int i = 0;
    FILE *in;
    in = fopen("cities.txt", "r");
    char line[100];
    G->ArrayOfLL[i] = (node *)malloc(sizeof(node));
    G->ArrayOfLL[i]->next = NULL;
    char *token;
    char Name[20];
    int Cost;

    char Dest[20];
    while (fgets(line, 100, in) != NULL)
    {


        sscanf(line,"%s %s %d",&Name,&Dest,&Cost);

        if (i == 0)
        {
            strcpy(G->ArrayOfLL[0]->Name, Name);
            Insert(Cost, Dest, G->ArrayOfLL[0]);
            i++;
            ArraySize++;
        }
        else if (i != 0)
        {
            if (CityExist(Name, G->ArrayOfLL) != NULL)
            {
                Insert(Cost, Dest, CityExist(Name, G->ArrayOfLL));
            }
            else
            {
                G->ArrayOfLL[i] = (node *)malloc(sizeof(node));
                G->ArrayOfLL[i]->next = NULL;
                strcpy(G->ArrayOfLL[i]->Name, Name);
                Insert(Cost, Dest, G->ArrayOfLL[i]);
                i++;
                ArraySize++;
            }
        }
    }

    fclose(in);
    return G;
}
node *CityExist(char Name[], node *Array[])
{
    int i;
    for (i = 0; i < ArraySize; i++)
    {
        if (strcmp(Name, Array[i]->Name) == 0)
        {
            return Array[i];
        }
    }
    if (i == ArraySize)
        return NULL;
}
node *Dikisra(Graph *G, char Initial[])
{
    char FinalDistance[3];
    char Additional[30];
    int Visited[ArraySize];
    int Costs[ArraySize];
    for (int i = 0; i < ArraySize; i++)
    {
        Costs[i] = 100000;
    }

    int index = FindIndex(Initial, G->ArrayOfLL);
    node *P;
    int InitialIndex = index;
    char NextVertix[20];
    if (index == -1)
    {
        printf("Not Found City\n");
        return NULL;
    }

    G->ArrayOfLL[index]->FinalCost = 0;
    Costs[index] = 0;
    P = G->ArrayOfLL[index]->next;

    while (P != NULL)
    {
        index = FindIndex(P->Name, G->ArrayOfLL);
        if (index != -1)
        {

            Costs[index] = P->Cost;
            P->FinalCost = P->Cost;
        }

        P = P->next;
    }

    Visited[InitialIndex] = 1;
    int Current;
    int u = 0;
    while (u != 15)
    {

        index = FinMinIndex(Visited, Costs);

        P = G->ArrayOfLL[index]->next;
        if(P== NULL){
            break;
        }

        while (P != NULL)
        {

            Current = FindCost(G->ArrayOfLL[index], P->Name) + FindCost(G->ArrayOfLL[InitialIndex], G->ArrayOfLL[index]->Name);

            if (Current < Costs[FindIndex(P->Name, G->ArrayOfLL)])
            {
                if (!Exist(G->ArrayOfLL[InitialIndex], P->Name))
                {
                    Insert(Current, P->Name, G->ArrayOfLL[InitialIndex]);
                    Last(G->ArrayOfLL[index])->FinalCost = Current;
                    if (FindIndex(P->Name, G->ArrayOfLL) != -1)
                    {
                        Costs[FindIndex(P->Name, G->ArrayOfLL)] = Current;
                        P->FinalCost = Current;

                    }
                }
                else
                {
                    Costs[FindIndex(P->Name, G->ArrayOfLL)] = Current;
                    P->FinalCost = Current;
                }
            }


            P = P->next;
        }

u++;
    }
    printf("\nsssrett\n");
    return G->ArrayOfLL[InitialIndex];
}
int AllVisited(int Visited[])
{

    for (int i = 0; i < ArraySize; i++)
    {
        if (Visited[i] != 1)
            return 0;
    }
    return 1;
}
int FindIndex(char Name[], node *ArrayofLL[])
{
    for (int i = 0; i < ArraySize; i++)
    {
        if (strcmp(Name, ArrayofLL[i]->Name) == 0)
            return i;
    }
    return -1;
}
int FindCost(node *src, char Dest[])
{
    node *P = src->next;
    while (P != NULL)
    {
        if (strcmp(P->Name, Dest) == 0)
            return P->Cost;
        P = P->next;
    }
    return P->FinalCost;
}
int Exist(node *Head, char Dest[])
{
    node *P = Head;
    while (P != NULL)
    {
        if (strcmp(P->Name, Dest) == 0)
            return 1;
        P = P->next;
    }
    return 0;
}

int FinMinIndex(int Visited[], int Costs[])
{
    int min = 100001;
    int index = -1;
    for (int i = 1; i < ArraySize; i++)
    {
        if (Costs[i] < min && Visited[i] != 1)
        {
            min = Costs[i];
            index = i;
        }
    }
    return index;
}
node *Last(node *Head)
{
    node *P = Head->next;
    if (P == NULL)
        return Head;
    else
    {
        while (P->next != NULL)
        {
            P = P->next;
        }
        return P;
    }
}
void menu(Graph *G)
{
    char Source[20];
    char Destination[20];
    int choice;
    node *Printed = (node *)malloc(sizeof(node));
    while (choice != 4)
    {
        printf("Choose an option :\n");
        printf("1. Load cities\n");
        printf("2. Enter source city\n");
        printf("3. Enter destination city\n");
        printf("4. Exit\n");
        printf("Choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            G = ReadFile(G);
            break;
        case 2:
            printf("Enter the source City : \n");
            getchar();

            gets(Source);
            strcpy(Source, strtok(Source, "\n"));
            Printed = Dikisra(G, Source);
            break;
        case 3:
            printf("Enter the Destination City : \n");
            getchar();
            gets(Destination);
            strcpy(Destination, strtok(Destination, "\n"));

            break;

        default:
            break;
        }
    }
}
