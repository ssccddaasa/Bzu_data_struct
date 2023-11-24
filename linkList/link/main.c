#include <stdio.h>
#include <stdlib.h>
#include "Linkk.h"

int max(struct node* );
void radix_sortt(struct node*);
void init();
struct node *make_new_node(int);
int get_max_digit(int *,int);
void insert_into_bin(int , int );
void display(int *, int);
void radix_sort(int *, int );

int mainn()
{
    printf("Hello world!\n");


    struct node* L1;
    L1 = MakeEmpty(NULL);

    printf("%d\n", L1 == NULL);

    Insert(503, L1, L1);
    //PrintList(L1);
    Insert(905, L1, L1);
    //PrintList(L1);
    Insert(4059, L1, L1);
    //PrintList(L1);
    Insert(899, L1, L1);
    //PrintList(L1);
    Insert(54977, L1, L1);
    PrintList(L1);
    printf("%d",max(L1));

    init();
    int arr[6] = { 655, 12, 7845, 227, 45, 45122 };
    //display(arr, 6);
    //radix_sort(arr, 6);
    radix_sortt(L1);
    //PrintList(L1);
   // display(arr, 6);

    /*InsertLast(100, L1);
    PrintList(L1);
    InsertLast(200, L1);
    PrintList(L1);

    /*struct node* p = Find(4, L1);

    if(p!=NULL)
    {
        printf("Found: %d\n", p->Data);
    }*/


    return 0;
}

int max(struct node* L){

struct node* p = L->Next;
int maxx = p->Data;

while( p!= NULL){
    if(p->Data > maxx){
        maxx = p->Data;
    }
    p = p->Next;
}
int c = 0;
while(maxx !=0){
    c++;
    maxx /= 10;
}
return c;

}


struct node *radix[10];

// initializing all list head with null
void init() {
    int i;
    for (i = 0; i < 10; i++) {
        radix[i] = NULL;
    }
}



void radix_sortt(struct node* L) {
    struct node *p = L ->Next;
    int i, j = 0, k, pass, digit, div = 1;
    int n = size(L);
    pass = max(L);

    for (i = 1; i <= pass; i++) {
            L = p;
       // printf("\ndiv = %d\n\n", div);
        while(L != NULL) {
            // getting the corresponding digit
            digit = (L->Data / div) % 10;

            // inserting into the bin
            insert_into_bin(L->Data, digit);
            L = L->Next;
        }
        break;
        // now multiplying div with 10 and storing it in div
        div *= 10;
        // Now the list is sorted in the array of linked list
        // Time to retrieve them
        L = p;
        for (k = 0; k < 10; k++) {
            struct node *temp = radix[k];
            radix[k] = NULL;
            while (temp != NULL) {
                struct node *Next = temp->Next;
                L->Data = temp->Data;
                free(temp);
                temp = Next;
                L = L->Next;
            }

        }
    }
}













struct node *make_new_node(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->Next = NULL;
    new_node->Data = data;
    return new_node;
}

int get_max_digit(int *arr, int n) {
    int i, max = arr[0], count = 0;
    // This loop is for finding the maximum number
    for (i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    // This loop is for getting the total number digits of the maximum number
    while (max != 0) {
        max /= 10;
        count++;
    }
    return count;
}

void insert_into_bin(int data, int rad) {
    struct node *new_node = make_new_node(data);
    struct node *temp = radix[rad];
    if (temp == NULL) {
        radix[rad]  = new_node;
    } else {
        while (temp->Next != NULL) {
            temp = temp->Next;
        }
        temp->Next = new_node;
    }


}

void radix_sort(int *arr, int n) {
    int i, j = 0, k, pass, digit, div = 1;
    pass = get_max_digit(arr, n);

    for (i = 1; i <= pass; i++) {
        printf("\ndiv = %d\n\n", div);
        for (j = 0; j < n; j++) {
            // getting the corresponding digit
            digit = (arr[j] / div) % 10;

            // inserting into the bin
            insert_into_bin(arr[j], digit);
        }
        // now multiplying div with 10 and storing it in div
        div *= 10;
        // Now the list is sorted in the array of linked list
        // Time to retrieve them
        j = 0;
        for (k = 0; k < 10; k++) {
            struct node *temp = radix[k];
            radix[k] = NULL;
            while (temp != NULL) {
                struct node *Next = temp->Next;
                arr[j++] = temp->Data;
                free(temp);
                temp = Next;
            }
        }
    }
}

void display(int *arr, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

