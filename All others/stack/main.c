#include <stdio.h>
#include <stdlib.h>


typedef struct node* PtrToNode;
typedef PtrToNode Stack;

struct node{

int Element;
PtrToNode Next;

};



int IsEmpty( Stack S ){

return S->Next == NULL;

}




Stack CreateStack( ){

Stack S;

S = (struct node*)malloc( sizeof( struct node ) );

if( S == NULL ){

printf( "Out of space!" );
}
S->Next = NULL;
MakeEmpty( S );

return S;

}





void MakeEmpty( Stack S ){

if( S == NULL ){

printf( "Out of space!" );
}
else

while( !IsEmpty( S ))

Pop( S );

}




void Pop( Stack S ){

PtrToNode firstCell;

if( IsEmpty( S ) ){

printf( "Empty stack" );
}

else{

firstCell = S->Next;
S->Next = S->Next->Next;
free( firstCell );

}

}




int Top( Stack S ){

if( !IsEmpty( S ) ){
return S->Next->Element;
}

printf( "Empty stack" );

return 0;

}


void Push( int X, Stack S ){

PtrToNode temp;

temp = ( Stack )malloc( sizeof( struct node ) );

if( temp == NULL){

printf( "Out of space!" );
}

else{

temp->Element = X;
temp->Next = S->Next;
S->Next = temp;

}

}





void DisposeStack( Stack S ){

MakeEmpty( S );
free( S );

}





int mainff(){

printf("zhhahahahahzzzhahahaha\n");


Stack s = CreateStack();
Push(1,s);
Push(9,s);
Push(20,s);
Push(30,s);

Stack c = CreateStack();
Push(5,c);
Push(6,c);
Push(7,c);
Push(8,c);


Stack v = CreateStack();
while(s->Next != NULL){
    Push(Top(s),v);
    Pop(s);
}


Stack x = CreateStack();
while(c->Next != NULL){
    Push(Top(c),x);
    Pop(c);
}

Stack re = CreateStack();
    while(x->Next != NULL || v->Next != NULL){
            if(v->Next == NULL){
               Push(Top(x),re);
               Pop(x);
               printf("\nhjn\n");
            }
            else if(x->Next == NULL){
               Push(Top(v),re);
               Pop(v);
                printf("\nhjn\n");
            }
         else if(Top(x)<Top(v)){
           Push(Top(x),re);
           Pop(x);
        }
        else if (Top(v)<Top(x)){
            Push(Top(v),re);
            Pop(v);
        }
    }


printf("%d  ",Top(re));
Pop(re);
printf("%d  ",Top(re));
Pop(re);

printf("%d  ",Top(re));
Pop(re);

printf("%d  ",Top(re));
Pop(re);

printf("%d  ",Top(re));
Pop(re);

printf("%d  ",Top(re));
Pop(re);

printf("%d  ",Top(re));
Pop(re);

printf("%d  ",Top(re));
Pop(re);



DisposeStack(s);
DisposeStack(c);
DisposeStack(v);
DisposeStack(x);
DisposeStack(re);



return 0;

}
