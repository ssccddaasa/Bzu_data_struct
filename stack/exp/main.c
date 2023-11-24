#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char String[100];

//Linked List For Busess
struct nodeBus // Define a struct which contain a pointer leads to the second struct & a place to the string which will put
{
    int id;
    char date[10];
    char time[10];
    char fromThisCity[100];
    char toThisCity[100];
    int price;
    int capacity;
    int space;

    struct nodeBus* Next ;
}nodeBus;
struct nodeBus* headB = NULL;// the head for the list of busess
//headB = MakeEmpty(headB) ;

struct nodeBus* MakeEmpty(struct nodeBus* L) // to ensure that the Linked List L is empty
{
    if(L != NULL)         // if not empty..
        DeleteList( L ); // call function to delete the Linked List as a data and as a struct
    L = (struct nodeBus*)malloc(sizeof(struct nodeBus)); // give the Linked List(head) a new place with struct node size
    if(L == NULL) // if there is no place for the Linked List, print that
        printf("Out of memory!\n");
    L->Next = NULL; // make the pointer in the struct node points on NULL
    return L;
}

void DeleteList(struct nodeBus* L)
{
    struct nodeBus* P; // to leads to the struct node to delete
    struct nodeBus* temp; // to keep catching the next struct node that will be deleted after P get rid of its struct node
    P = L->Next;
    L->Next = NULL;
    while(P != NULL) // while there is a struct node to delete, do the next statements
    {
        temp = P->Next; // temp catchs the next struct
        free(P); // P get rid of the current struct node,
        P=temp; // and look to the next struct node that will be deleted if it is not NULL
    }
}

void loadBusFile(struct nodeBus*L){
    struct nodeBus *P = L;
    FILE *fp = fopen("busses.txt", "r");
    if(fp==NULL)
    {
        printf("File could not be opened.\n");//If the file is empty, it will do nothing.
        exit(0);
    }
    struct nodeBus b1;
    struct nodeBus*node;
    char line[250];
    char *endLine = fgets(line, 250, fp);
    while(endLine != NULL){
        char *temp = strtok(line, "#");
        if(temp!= NULL)
        {
             struct nodeBus*node;
        node = MakeEmpty(NULL);

            b1.id = atoi(temp);
            node-> id= b1.id;

            temp = strtok(NULL, "#");
            strcpy(b1.date ,temp);
            strcpy( node->date, b1.date);

            temp = strtok(NULL, "#");
            strcpy(b1.time ,temp);
            strcpy( node->time, b1.time );

            temp = strtok(NULL, "#");
             strcpy(b1.fromThisCity ,temp);
            strcpy( node->fromThisCity, b1.fromThisCity );

            temp = strtok(NULL, "#");
            strcpy(b1.toThisCity ,temp);
            strcpy( node->toThisCity, b1.toThisCity );

            temp = strtok(NULL, "#");
            b1.price = atoi(temp);
            node->price =  b1.price;

            b1.capacity = atoi(temp);
            node->capacity = b1.capacity;


        }
        while(P->Next != NULL){
        P=P->Next;
        }
        node ->Next = NULL;
        P ->Next = node;
        endLine = fgets(line, 250, fp);
        printf("gg\n");
    }

    fclose(fp);//close the file


}

int isEmptyB(struct nodeBus* L){
    return L->Next == NULL;
}

void printBlist(struct nodeBus*L){
    struct nodeBus* p = L ->Next;
    if(isEmptyB(L))
        printf("Empty List!!\n");
    else
    {
        printf("\nID:\tDate:\tTime:\tFrom:\tTo:\tPrice:\tCapacity\n");
        printf("----------------------------------------------------------------------------------------------------\n");
        while(p!= NULL)
        {
            printf("ID: %d, Date: %s, Time: %s, From: %s, To: %s, Price: %d, capacity: %d\n", p->id, p->date, p->time, p->fromThisCity, p->toThisCity,p->price, p->capacity);
             p = p->Next;
        }
    }


}
int main()
{
    struct nodeBus* headB = NULL;// the head for the list of busess
    headB = MakeEmpty(headB) ;


    int choice;//variable to choice from the menu.
    printf("----------------------------------------------------\n");
    do
    {
        //the menu or list.
        printf("1. Load the bus information file. \n");
        printf("2. Load the passenger information file.\n");
        printf("3. Assign passengers and print assignment information of all busses.\n");
        printf("4. Print a specific bus information along with its passengers information (names and IDs).\n");
        printf("5. Print unmatched passengers.\n");
        printf("6. Add new passenger.\n");
        printf("7. Delete passenger.\n");
        printf("8. Delete bus number.\n");
        printf("8. Exit.\n");
        printf("Enter your choice 1 to 9 from the following menu: ");
        scanf("%d", &choice);
        printf("----------------------------------------------------\n");

        /*The user has a list and he has to choose a number
               from 1 to 9 and the compiler will do what the user requests
               and call the function for each cases*/


        switch(choice)
        {
        case 1:
            loadBusFile(headB);
           printBlist(headB);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            printf("\n");
            break;
        case 5:

            break;
        case 6:
            printf("\n");
            break;
        case 7:
            printf("\n");
            break;
        case 8:
            printf("\n");
            break;
        case 9:
            printf("Exiting...");
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }
    while(choice != 9);
    return(0);
}



