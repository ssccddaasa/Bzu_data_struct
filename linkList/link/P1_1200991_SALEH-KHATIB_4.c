#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// SALEH KHATIB 1200991.

/*
This program connects passengers with the appropriate buses for them
from some files
by using linked lists.

*/





// node for passengers and their information.
struct node
{
    int id;
    int date;
    int time;
    int time2;
    char from [30];
    char dest[30];
    struct node* Next;
};
// node for buses and their information.
struct nodeb
{
    int num;
    int date;
    int time;
    int time2;
    char from [30];
    char dest[30];
    int price;
    int cap;
    struct nodeb* Next;
    struct node* Nextp;
};


// function to make linked list and make it empty for passengers.
struct node* MakeEmpty(struct node* L)
{
    if(L != NULL)
        DeleteList( L );
    L = (struct node*)malloc(sizeof(struct node));

    if(L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    return L;
}


// function to make linked list and make it empty for buses.
struct nodeb* MakeEmptyy(struct nodeb* L)
{
    if(L != NULL)
        DeleteListt( L );
    L = (struct nodeb*)malloc(sizeof(struct nodeb));

    if(L == NULL)
        printf("Out of memory!\n");

    L->Next = NULL;
    L->Nextp = MakeEmpty(NULL);
    return L;
}


//function to know if linked list is empty or not for passengers.
int IsEmpty(struct node* L)
{
    return L->Next == NULL;
}


//function to know if linked list is empty or not for buses.
int IsEmptyy(struct nodeb* L)
{
    return L->Next == NULL && L->Nextp == NULL;
}


//function to know if the node is last for the linked list or not for passengers.
int IsLast(struct node* P, struct node* L)
{
    return P->Next == NULL;
}


//function to know if the node is last for the linked list or not for buses.
int IsLastt(struct nodeb* P, struct nodeb* L)
{
    return P->Next == NULL ;
}


// function to find specific node by the id for passengers and return it.
struct node* Find(int X, struct node* L)
{
    struct node* P;
    P = L->Next;

    while(P != NULL && P->id != X)
        P =P->Next;

    return P;
}



// function to find specific node by the number for buses and return it.
struct nodeb* Findd(int X, struct nodeb* L)
{
    struct nodeb* P;
    P = L->Next;

    while(P != NULL && P->num != X)
        P =P->Next;

    return P;
}




// function to find specific previous node by the id for passengers and return it.
struct node* FindPrevious(int X, struct node* L)
{
    struct node* P;
    P = L;

    while(P->Next != NULL && P->Next->id != X)
        P = P->Next;

    return P;
}




// function to find specific previous node by the number for buses and return it
struct nodeb* FindPreviouss(int X, struct nodeb* L)
{
    struct nodeb* P;
    P = L;

    while(P->Next != NULL && P->Next->num != X)
        P = P->Next;

    return P;
}




// function to delete specific node by the id for passengers.
void Delete(int X, struct node* L)
{

    struct node *P, *temp;
    P = FindPrevious(X, L);

    if( !IsLast(P, L) )
    {
        temp = P->Next;
        P->Next = temp->Next; //bypass delete cell
        free(temp);
    }
}



// function to delete specific node by the number for buses.
void Deletee(int X, struct nodeb* L)
{
    struct nodeb *P, *temp;
    P = FindPreviouss(X, L);

    if( !IsLastt(P, L) )
    {

        temp = P->Next;
        P->Next = temp->Next; //bypass delete cell
       // DeleteList(temp->Nextp);
        free(temp);
    }
}



//function to add nodes with their information between two specific nodes for passengers.
void Insert(int X,int datee,int timee,int time2,char f[30],char t[30], struct node* L, struct node* P)
{
    struct node* temp;
    temp = (struct node*)malloc(sizeof(struct node));
    temp->id = X;
    temp->date = datee;
    temp->time = timee;
    temp->time2 = time2;
    strcpy(temp->from,f);
    strcpy(temp->dest,t);

    temp->Next = P->Next;
    P->Next = temp;
}



//function to add nodes with their information between two specific nodes for buses.
void Insertt(int X,int datee,int timee,int time2,char f[30],char t[30],int pr,int cap, struct nodeb* L, struct nodeb* P)
{
    struct nodeb* temp;
    temp = (struct node*)malloc(sizeof(struct nodeb));
    temp->num = X;
    temp->date = datee;
    temp->time = timee;
    temp->time2 = time2;
    strcpy(temp->from,f);
    strcpy(temp->dest,t);
    temp->price = pr;
    temp->cap = cap;
    temp->Nextp = NULL;

    temp->Next = P->Next;
    P->Next = temp;
}



//function to add nodes with their information at the last of list nodes for passengers.
void InsertLast(int X,int datee,int timee,int time2,char f[30],char t[30], struct node* L)
{
    struct node* temp, *P=L;

     if(time2>60){
        time2 = timee%60;
        timee +=1;
    }

    if(timee>24){
        timee = timee%24;
    }

    temp = (struct node*)malloc(sizeof(struct node));
    temp->id = X;
    temp->date = datee;
    temp->time = timee;
    temp->time2 = time2;
    strcpy(temp->from,f);
    strcpy(temp->dest,t);
    while(P->Next != NULL)
        P=P->Next;

    P->Next = temp;
    temp->Next = NULL;

}



//function to add nodes with their information at the last of list nodes for buses.
void InsertLastt(int X,int datee,int timee,int time2,char f[30],char t[30],int pr,int cap, struct nodep* L)
{
    struct nodeb* temp, *P=L;
      if(time2>60){
        time2 = timee%60;
        timee +=1;
    }

    if(timee>24){
        timee = timee%24;
    }

    temp = (struct nodeb*)malloc(sizeof(struct nodeb));
    temp->num = X;
    temp->date = datee;
    temp->time = timee;
    temp->time2 = time2;
    strcpy(temp->from,f);
    strcpy(temp->dest,t);
    temp->price = pr;
    temp->cap = cap;
    temp->Nextp = MakeEmpty(NULL);




    while(P->Next != NULL)
        P=P->Next;

    P->Next = temp;

    temp->Next = NULL;

}




//function to print all the information for every node for passengers.
void PrintList(struct node* L)
{
    struct node* P = L;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
        do
        {
            P=P->Next;
            printf("Passenger.Id: %d ,Date: %d ,Time: %d:%d,From: %s ,To: %s\n", P->id,P->date,P->time,P->time2,P->from,P->dest);
        }
        while( P->Next != NULL );
    printf("\n");
}




void PrintList2(struct node* L)
{
    struct node* P = L;
    if( IsEmpty(L))
        printf("Empty list\n");
    else
        do
        {
            P=P->Next;
            printf("Passenger.Id: %d", P->id);
        }
        while( P->Next != NULL );
    printf("\n");
}



//function to print all the information for every node for buses.
void PrintListt(struct nodeb* L)
{
    struct nodeb* P = L;
    if( IsEmptyy(L))
        printf("Empty list\n");
    else
        do
        {

            P=P->Next;
            printf("Bus.Number: %d ,Date: %d ,Time: %d:%d,From: %s ,To: %s ,Price: %d ,Capacity: %d\n", P->num,P->date,P->time,P->time2,P->from,P->dest,P->price,P->cap);
        }
        while( !IsLastt(P, L) && P->Next->num != -1 );
    printf("\n");
}



//function to delete all the information for every node for passengers.
void DeleteList(struct node* L)
{
    struct node *P, *temp;
    P = L->Next;
    L->Next = NULL;

    while(P != NULL)
    {
        temp = P->Next;
        free(P);
        P=temp;
    }
}


//function to delete all the information for every node for buses.
void DeleteListt(struct nodeb* L)
{
    struct nodeb *P, *temp;
    P = L->Next;
    L->Next = NULL;

    while(P != NULL)
    {
        temp = P->Next;
        free(P);
        P=temp;
    }
}



// function to find the size of the list for passengers.
int size( struct node* L)
{
    struct node* p = L->Next;
    int count = 0;
    while(p != NULL )
    {
        count += 1;
        p = p->Next;
    }
    return count;
}



// function to find the size of the list for buses.
int sizee( struct nodeb* L)
{
    struct nodeb* p = L->Next;
    int count = 0;
    while(p != NULL )
    {
        count += 1;
        p = p->Next;
    }
    return count;
}


// function to Concatenate two list for passengers.
void Concatenate(struct node** L1, struct node** L2)
{
    if( *L1 == NULL )
    {
        *L1 = *L2;

        //return L2;
    }
    else
    {
        //iterate to the end of L1
        struct node* temp = *L1;

        while(temp->Next != NULL)
            temp = temp->Next;

        temp->Next = (*L2)->Next;
    }
}




//function take a string and Splits it based on the information the node need for passengers.
void load(char s [100],struct node*L){
int i=0;
    while(s[i]!='\0')
    {
        if(s[i]==' ')
        {
            s[i]='.';
        }
        i++;
    }
    i=0;
      while(s[i]!='\0')
    {
        if(s[i]=='#')
        {
            s[i]=' ';
        }
        i++;
    }


 int id;
    int date;
    int time;
    int time2;
    char from [30];
    char dest[30];

    sscanf(s,"%d %d %d:%d %s %s",&id,&date,&time,&time2,&from,&dest);

    int ck = 0;
    struct node*k=L;

    while(k != NULL){
        if(id == k->id){
            ck = 1;
        }
        k = k->Next;
    }

    if(ck != 1){
    InsertLast(id,date,time,time2,from,dest,L);
}
else
    printf("");

}



//function take a string and Splits it based on the information the node need for buses.
void load2(char s [100],struct nodeb* L){
int i=0;
    while(s[i]!='\0')
    {
        if(s[i]==' ')
        {
            s[i]='.';
        }
        i++;
    }
    i=0;
      while(s[i]!='\0')
    {
        if(s[i]=='#')
        {
            s[i]=' ';
        }
        i++;
    }

    int id;
    int date;
    int time;
    int time2;
    char from [30];
    char dest[30];
    int pir;
    int cap;


    sscanf(s,"%d %d %d:%d %s %s %d %d",&id,&date,&time,&time2,&from,&dest,&pir,&cap);

     int ck = 0;
    struct nodeb*k=L;

    while(k != NULL){
        if(id == k->num){
            ck = 1;
        }
        k = k->Next;
    }

    if(ck != 1){
    InsertLastt(id,date,time,time2,from,dest,pir,cap,L);
}
else
    printf("");



}


//function take two lists: one for passengers & the other for buses.
//it's connects passengers with the appropriate buses by some conditions.
//the conditions are: That the time between them coincides and be on the same day and in the same destination and place of departure.
//If the passenger does not match any bus, he will be moved to the list of unmatched.
struct node* link(struct node*L,struct nodeb*B){
struct node* p = L;
struct node* o = MakeEmpty(NULL);
L = L->Next;
B = B->Next;

while(B->num != -1){
while(L != NULL){

    if(B->cap > 0){
        if(B->time+B->time2 >= L->time+L->time2 && B->date == L->date && strcmp(B->from,L->from) == 0 && strcmp(B->dest,L->dest)==0){
            InsertLast(L->id,L->date,L->time,L->time2,L->from,L->dest,B->Nextp);
            B->cap--;
            InsertLast(L->id,L->date,L->time,L->time2,L->from,L->dest,o);
            Delete(L->id,p);
        }
    }
 L = L->Next;

}

L=p;


B = B->Next;
}
L = L->Next;
while(L != NULL){
    InsertLast(L->id,L->date,L->time,L->time2,L->from,L->dest,B->Nextp);
    InsertLast(L->id,L->date,L->time,L->time2,L->from,L->dest,o);
    Delete(L->id,p);
    L = L->Next;
}


return o;


}




//function To add passengers and match them with buses.
void add_Pass(struct node*L,struct nodeb*B){
    struct nodeb* y = B;
int id = 0;
    int date = 0;
    int time = 0;
    int time2 = 0;
    char from [30];
    char dest[30];
    strcpy(from,"");
    strcpy(dest,"");
    printf("put the info of the new passenger in this way:\n");
    printf("id date timeInHours timeInMin from to\n");

    scanf("%d %d %d %d %s %s",&id,&date,&time,&time2,&from,&dest);

     int ck = 0;
    struct node*k=L;

    while(k != NULL){
        if(id == k->id){
            ck = 1;
        }
        k = k->Next;
    }

    if(ck != 1){
    if(id == 0 || date == 0 || isdigit(time) || isdigit(time2) || strcmp(from,"") == 0 || strcmp(dest,"")==0){
        printf("you miss some information!\n\n");
    }
    else{
    InsertLast(id,date,time,time2,from,dest,L);

   struct node* g = Find(id,L);
   int f=0;
   while(B->num != -1){
    if(B->cap > 0){
        if(B->time+B->time2 >= g->time+g->time2 && B->date == g->date && strcmp(B->from,g->from) == 0 && strcmp(B->dest,g->dest)==0){
            InsertLast(g->id,g->date,g->time,g->time2,g->from,g->dest,B->Nextp);
            B->cap--;
            f=1;
        }
    }
 B = B->Next;

}

if(f == 0){
    InsertLast(g->id,g->date,g->time,g->time2,g->from,g->dest,B->Nextp);
}
B = y;

printf("the passenger is added\n\n");
}

}
else
    printf("he is already exsist!");

}

//function to delete passengers by the id.
void del_Pass(struct node*L,struct nodeb*B){
    int id;
    printf("put the id you want to delete:\n");
    int ck = 0;
    struct node*k=L;

    scanf("%d", &id);
    printf("\n\n");



    while(k != NULL){
        if(id == k->id){
            ck = 1;
        }
        k = k->Next;
    }


    if(ck == 1 || isdigit(id)){
    while(B != NULL){
        Delete(id,B->Nextp);
        B=B->Next;
    }
    Delete(id,L);
    printf("the passenger is deleted\n\n");
}
else
    printf("the passenger you want to delete is not found\n\n");

}




//function to delete buses by the number .
void del_Bus(struct nodeb*B){
struct node* L = MakeEmpty(NULL);
struct nodeb *h;
int num = 0;
printf("put the number of bus you want to delete\n");
scanf("%d",&num);
printf("\n\n");

int ck = 0;
    struct nodeb*k=B;
    while(k != NULL){
        if(num == k->num){
            ck = 1;
        }
        k = k->Next;
    }
if(ck == 1 || isdigit(num)){
h = Findd(num,B);
h->Nextp = h->Nextp->Next;
while(h->Nextp!=NULL){
    InsertLast(h->Nextp->id,h->Nextp->date,h->Nextp->time,h->Nextp->time2,h->Nextp->from,h->Nextp->dest,L);
    h->Nextp = h->Nextp->Next;
}

Deletee(num,B);
DeleteList(link(L,B));
printf("the bus is deleted\n\n");
}
else
    printf("the bus you want to delete not found\n\n");


}





int main(){

    // make two passenger list
   struct node* L;
    L=MakeEmpty(NULL);
// make two bus list
    struct nodeb* B;
    B = MakeEmptyy(NULL);

// make two files to read information for buses and passengers.
FILE *pass,*bus;
pass= fopen("passengers.txt","r");
bus= fopen("busses.txt","r");
char s [100] ;

while(fgets(s,100,pass)!=NULL){
    load(s,L);
}

char s1 [100] ;

while(fgets(s1,100,bus)!=NULL){
    load2(s1,B);
}
//node for unmatched passengers.
InsertLastt(-1,0,0,0,"","",0,0,B);
L = link(L,B);

//menu so that the user can deal with it and work on it
int ch = 0;
printf("Welcome to my project ladies and gentlemen.");
printf("this project is about linked list and how to use it.\n");
printf("This project gives an example of how to connect passengers with the appropriate buses for them by linked list.\n\n");
while(ch != 9){
    printf("\nlet's make a choice,put the number for your choice\n\n");
    printf("1-) print the information for passengers\n");
    printf("2-) print the information for busses\n");
    printf("3-) print the information for busses after assign passengers\n");
    printf("4-) print the information for specific bus by bus number\n");
    printf("5-) print the information for unmatched passengers\n");
    printf("6-) add new passenger\n");
    printf("7-) delete a passenger\n");
    printf("8-) delete a bus\n");
    printf("9-) exit\n");

 if (scanf("%d", &ch) != 1) {
        int c;
        /* read and ignore the rest of the line */
        while ((c = getchar()) != EOF && c != '\n')
            continue;
        if (c == EOF) {
            /* premature end of file */
            return 1;
        }
        ch = -1;
    }
    printf("\n\n");


    if(ch == 1){
        PrintList(L);
    }
    else if(ch == 2){
        PrintListt(B);
    }
    else if(ch == 3){
        struct nodeb *k =B;
        B=B->Next;
        while(B->num != -1){
            printf("Bus.Number: %d ,Date: %d ,Time: %d:%d,From: %s ,To: %s ,Price: %d ,Capacity: %d\n",B->num,B->date,B->time,B->time2,B->from,B->dest,B->price,B->cap);
            if(B->Nextp != NULL){
                PrintList(B->Nextp);
            }
            else{
                printf("there is no passengers\n");
            }
            B=B->Next;
        }
       B=k;
    }
    else if(ch == 4){
            int num = 0;
        printf("put the bus number please:\n");
        scanf("%d",&num);
        printf("\n");
        int ck = 0;
    struct nodeb*k=B;
    while(k != NULL){
        if(num == k->num){
            ck = 1;
        }
        k = k->Next;
    }
    if(ck == 1 || isdigit(num)){
        struct nodeb* k = Findd(num,B);
           printf("Bus.Number: %d ,Date: %d ,Time: %d:%d,From: %s ,To: %s ,Price: %d ,Capacity: %d\n",k->num,k->date,k->time,k->time2,k->from,k->dest,k->price,k->cap);
             if(k->Nextp != NULL){
                PrintList2(k->Nextp);
            }
            else{
                printf("there is no passengers\n\n");
            }

    }
        else{
            printf("there is no bus with this number\n\n");
        }


    }
    else if(ch == 5){
        struct nodeb* k = Findd(-1,B);
        if(k != NULL){
             if(k->Nextp != NULL){
                PrintList(k->Nextp);
            }
            else{
                printf("there is no passengers\n");
            }
        }
    }
    else if(ch == 6){
        add_Pass(L,B);
    }
    else if(ch == 7){
        del_Pass(L,B);
    }
    else if(ch == 8){
        del_Bus(B);
    }
    else if(ch == 9){
        printf("I hope you enjoyed the project and I hope you liked it. Best regards.");
    }
    else{
        printf("you put invalid choice\n\n");
    }

}






fclose(pass);
DeleteList(L);

fclose(bus);
DeleteListt(B);

return 1;






}
