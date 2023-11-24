#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SALEH KHATIB 1200991.

//In this project, we will work on linking the courses,
//including information from the name, number of hours,
//course code, department and topics, using Avl tree.


// counter to know the number of nodes.
int counter = 0;
int counter2 = 0;
// Create Node for the avl tree with it's information.
struct Node {
  int key;
  char cName[50];
  char dep[50];
  char code[50];
  char cour[500];
  struct Node *left;
  struct Node *right;
  int height;
};
// get the max between two numbers.
int max(int a, int b);

// Calculate height for the Node.
int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Create a node (make new Course) with all needed information.
struct Node *newNode(int key,char n[50],char d[50],char c[50],char o[500]) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->key = key;
  strcpy(node->cName,n);
  strcpy(node->dep,d);
  strcpy(node->code,c);
  strcpy(node->cour,o);
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

// Right rotate (y--l>x--r>T2) -> (x--r>y--l>T2).
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate (y--l>x--r>T2) <- (x--r>y--l>T2).
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
struct Node *insertNode(struct Node *node, int key,char n[50],char d[50],char c[50],char o[500]) {
  // Find the correct position to insertNode the node and insertNode it

  if (node == NULL)
    return (newNode(key,n,d,c,o));

  if (strcmp(c,node->code)<0)
    node->left = insertNode(node->left, key,n,d,c,o);
  else if (strcmp(c,node->code)>0)
    node->right = insertNode(node->right, key,n,d,c,o);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  //single right rotate.
  if (balance > 1 && strcmp(c,node->left->code)<0)
    return rightRotate(node);
  //single left rotate.
  if (balance < -1 && strcmp(c,node->right->code)>0)
    return leftRotate(node);
  // double left right rotate.
  if (balance > 1 && strcmp(c,node->left->code)>0) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  // double right left rotate.
  if (balance < -1 && strcmp(c,node->right->code)<0) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a any node by input the code.
struct Node *deleteNode(struct Node *root, char c[50]) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (strcmp(c,root->code)<0)
    root->left = deleteNode(root->left, c);

  else if (strcmp(c,root->code)>0)
    root->right = deleteNode(root->right, c);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
      counter2++;
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;
      strcpy(root->cName,temp->cName);
      strcpy(root->dep,temp->dep);
      strcpy(root->code,temp->code);
      strcpy(root->cour,temp->cour);

      root->right = deleteNode(root->right, temp->code);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}





// Delete the courses by input the department.
struct Node *deleteNodee(struct Node *root, char d[50]) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (strcmp(d,root->dep)<0)
    root->left = deleteNodee(root->left, d);

  else if (strcmp(d,root->dep)>0)
    root->right = deleteNodee(root->right, d);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
      counter2++;
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;
      strcpy(root->cName,temp->cName);
      strcpy(root->dep,temp->dep);
      strcpy(root->code,temp->code);
      strcpy(root->cour,temp->cour);

      root->right = deleteNodee(root->right, temp->dep);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}




// delete the courses by input the first letter from the course code.
struct Node *deleteNodeee(struct Node *root, char d) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (d<root ->code[0])
    root->left = deleteNodeee(root->left, d);

  else if (d>root ->code[0])
    root->right = deleteNodeee(root->right, d);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
      counter2++;
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;
      strcpy(root->cName,temp->cName);
      strcpy(root->dep,temp->dep);
      strcpy(root->code,temp->code);
      strcpy(root->cour,temp->cour);

      root->right = deleteNodeee(root->right, temp->code[0]);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}













// find a node by input the code;
struct Node* Find( char c[50],struct Node* T)
{
    if( T == NULL )
        return NULL;
    if( strcmp(c,T->code)<0 )
        return Find( c, T->left );
    else if( strcmp(c,T->code)>0 )
        return Find( c, T->right );
    else
        return T;
}


// Print the tree in inorder way(just codes).
void printInOrder(struct Node *root) {

  if (root != NULL) {
    printInOrder(root->left);
    printf("%s  ", root->code);
    printInOrder(root->right);
  }
}

// Print the tree in inorder way.
void printInOrder2(struct Node *root) {
  if (root != NULL) {
    printInOrder2(root->left);
    printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",root->cName,root->key,root->code,root->dep,root->cour);
    printInOrder2(root->right);
  }
}


// Print the tree in inorder way(just with input department).
void printInOrder3(struct Node *root,char d[50]) {
  if (root != NULL) {
    printInOrder3(root->left,d);
    if(strcmp(d,root->dep) == 0){
     printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",root->cName,root->key,root->code,root->dep,root->cour);
    }
    printInOrder3(root->right,d);
  }
}

// Print the tree in inorder way(in a file).
void fprintInOrder2(struct Node *root,FILE * offe) {
  if (root != NULL) {
    fprintInOrder2(root->left,offe);
    fprintf(offe,"CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",root->cName,root->key,root->code,root->dep,root->cour);
    fprintInOrder2(root->right,offe);
  }
}





// load the information from file.
struct Node* load(char s[700],struct Node*r){
int i=0;
    while(s[i]!='\0')
    {
        if(s[i]=='#' || s[i]==':' || s[i]=='/')
        {
            s[i]=' ';
        }
        i++;
    }
int ch = 0;
char n[50];
strcpy(n,"");
char d[50];
strcpy(d,"");
char c[50];
strcpy(c,"");
char o[500];
strcpy(o,"");
sscanf(s,"%s %d %s %s %s",&n,&ch,&c,&d,&o);
r = insertNode(r,ch,n,d,c,o);
counter++;
return r;

}

// function to let the user to add courses.
struct Node* addCo(struct Node*R){

int ch = 0;
char n[50];
strcpy(n,"");
char d[50];
strcpy(d,"");
char c[50];
strcpy(c,"");
char o[500];
strcpy(o,"");
printf("put the information in this way:\n");
printf("CourseName Hours Code Dep Topic(t,t1,...)\n");
scanf("%s %d %s %s %s",&n,&ch,&c,&d,&o);
if(strcmp(n,"") == 0 || strcmp(d,"")==0 || strcmp(o,"") == 0 || strcmp(c,"")==0 || ch<0){
    printf("miss informtion!!\n");
    return R;
}
R = insertNode(R,ch,n,d,c,o);
printf("the course is added or updated\n");
counter++;
return R;
}

// find a course and support to update it.
struct Node* FiUp(struct Node*R){

char c[50];
printf("put the code to course you want\n");
scanf("%s",&c);
struct Node* r= Find(c,R);
if(r == NULL){
    printf("there is no course with this code\n");
    return R;
}
printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",r->cName,r->key,r->code,r->dep,r->cour);
int a = 0;
printf("if you want to update put number 1 and if you don't press any number\n");
scanf("%d",&a);
if(a==1){
    R = deleteNode(R,c);
    R = addCo(R);
}
else{
    printf("as you wish\n");
}
return R;


}










int main() {

    // make the tree and call the files to read and write.
  struct Node *root = NULL;
  FILE *cours;
cours= fopen("courses.txt","r");


 if (cours == NULL) {
        printf("Error!");
        exit(1);
    }


char s [700] ;

while(fgets(s,700,cours)!=NULL){
   root = load(s,root);
}




// a menu to let the user use the program.

int ch = 0;
printf("Welcome to my project ladies and gentlemen.");
printf("this project is about Avl trees and how to use it.\n");
printf("This project gives an example of how to deal with the Courses and there information by Avl tree.\n\n");
while(ch != 10){
    printf("\nlet's make a choice,put the number for your choice\n\n");
    printf("1-) print the information for courses\n");
    printf("2-) add new course\n");
    printf("3-) find and update course\n");
    printf("4-) list topics for given course\n");
    printf("5-) list all courses for same department\n");
    printf("6-) delete course\n");
    printf("7-) delete courses have the same first letter\n");
    printf("8-) delete courses have the same department\n");
    printf("9-) save the tree to file\n");
    printf("10-) exit\n");

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
        printInOrder2(root);
    }
    else if(ch == 2){
        root = addCo(root);
    }
    else if(ch == 3){
     root = FiUp(root);
    }
    else if(ch == 4){
    char c[50];
    printf("put the code for the course\n");
    scanf("%s",&c);
            struct Node* y = Find(c,root);
            if(y == NULL){
    printf("there is no course with this code\n");
}
      else{
            printf("%s",y->cour);
    }
    }
    else if(ch == 5){
          char d[50];
    printf("put the department you want(it won't print any thing if the department was not found or exisit)\n");
    scanf("%s",&d);
    printInOrder3(root,d);
    }
    else if(ch == 6){
    char c[50];
    printf("put the code for the course you want to delete\n");
    scanf("%s",&c);
    if(Find(c,root) == NULL){
        printf("this course is not found!\n");
    }
    else{
    root = deleteNode(root,c);
    counter -=counter2;
    counter2 = 0;
    printf("the course is deleted\n");
    }
}
    else if(ch == 7){
            char d[3];
        printf("put the first letter for the courses (Code) you want to delete\n");
        scanf("%s",&d);
        for(int i=0;i<counter;i++){
            root = deleteNodeee(root,d[0]);
        }
        if(counter2 == 0){
            printf("you put invalid letter\n");
        }
        else{
    counter -=counter2;
    counter2 = 0;
    printf("the courses are deleted\n");
    }
    }
    else if(ch == 8){
            char d[50];
        printf("put the department for the courses you want to delete\n");
        scanf("%s",&d);
        for(int i=0;i<counter;i++){
            root = deleteNodee(root,d);
        }
          if(counter2 == 0){
            printf("you put invalid department\n");
        }
           else{
    counter -=counter2;
    counter2 = 0;
    printf("the courses are deleted\n");
    }
    }
    else if(ch == 9){
            FILE *offer;
          offer = fopen("offered_courses.txt","w");
      if (offer == NULL) {
        printf("Error!");
        exit(1);
    }
            printf("it will be saved Belieeeeeeeeeeve That.\n");
        fprintInOrder2(root,offer);
        fclose(offer);
    }

    else if(ch == 10){
        printf("I hope you enjoyed the project and I hope you liked it. Best regards.");
    }
    else{
        printf("you put invalid choice\n\n");
    }

}



fclose(cours);
  return 0;
}

