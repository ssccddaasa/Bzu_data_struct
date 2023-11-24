#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// SALEH KHATIB 1200991.

//In this project, we will work on linking the courses,
//including information from the name, number of hours,
//course code, department and topics, using hash.
int si =10;
int councld = 0;
int councll = 0;
int cap = 0;

struct cour
{
    int hours;
    char CName[50];
    char Code[10];
    char Depar[50];
    char Topics[500];
};



// function to find prime number
int prime(){
for(int i=si;i>0;i--){
        int c =0;
for(int j=1;j<=i;j++){
    if(i%j == 0){
       c++;
    }
}
if(c == 2){
    return i;
}
else{
    continue;
}
}

}



// function to calculate th hash value for string
int hash(char* keyy){

int hashValue = 0;

while( *keyy != '\0' ){

hashValue = ( hashValue << 5 ) + *keyy++;

}

return hashValue;

}

// use double hash function to solve the collisions and get empty index.
int Double_hash(struct cour a[si],char str[50]){
int pri = prime();
int x = hash(str);
int i=0;
for(int i=0;i<si*2;i++){
int y = ((x%si) + i*(pri - (x%pri)))%si;
  if(strcmp(a[y].CName,"")==0){
    return y;

  }
  else{
    i++;
    councld++;
  }


}
return -1;


}

// get the index for a spcefic course.
int SDouble_hash(struct cour a[si],char str[50]){
int pri = prime();
int x = hash(str);
int i=0;
for(int i=0;i<si*2;i++){
int y = ((x%si) + i*(pri - (x%pri)))%si;
  if(strcmp(a[y].CName,str)==0){
    return y;

  }
  else{
    i++;
  }


}

return -1;
}




// use liner hash function to solve the collisions and get empty index.
int Lin_hash(struct cour a[si],char str[50]){

int x = hash(str);

int i=0;
for(int i=0;i<si*2;i++){
int y = (x+i)%si;
  if(strcmp(a[y].CName,"")==0){
    return y;

  }
  else{
    i++;
    councll++;
  }


}
return -1;

}

// get the index for a spcefic course.
int SLin_hash(struct cour a[si],char str[50]){

int x = hash(str);

int i=0;
for(int i=0;i<si*2;i++){
int y = (x+i)%si;
  if(strcmp(a[y].CName,str)==0){
    return y;

  }
  else{
    i++;
  }


}
return -1;

}




//load infromtion from files.
void load(char s[700],struct cour a[si],struct cour a2[si]){
int i=0;
    while(s[i]!='\0')
    {
        if(s[i]=='#' || s[i]==':' || s[i]=='/')
        {
            s[i]=' ';
        }
        i++;
    }

struct cour t;

sscanf(s,"%s %d %s %s %s",&t.CName,&t.hours,&t.Code,&t.Depar,&t.Topics);
int d = Double_hash(a,t.CName);
a[d] = t;
int l = Lin_hash(a2,t.CName);
a2[l] = t;
cap++;

}


// add new courses
void addCo(struct cour a[si],struct cour a2[si]){

printf("put the information in this way:\n");
printf("CourseName Hours Code Dep Topic(t,t1,...)\n");
struct cour t;
scanf("%s %d %s %s %s",&t.CName,&t.hours,&t.Code,&t.Depar,&t.Topics);
int d = Double_hash(a,t.CName);
a[d] = t;
int l = Lin_hash(a2,t.CName);
a2[l] = t;

cap++;
}
// print the data from the double table.
void print_dou(struct cour D[si]){
    for(int i=0;i<si;i++){
        if(strcmp(D[i].CName,"")==0){
            printf("Empty spot\n");
        }
        else{
            printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",D[i].CName,D[i].hours,D[i].Code,D[i].Depar,D[i].Topics);
    }

}

}
// print the data from the linear table.
void print_lin(struct cour D[si]){
    for(int i=0;i<si;i++){
        if(strcmp(D[i].CName,"")==0){
            printf("Empty spot\n");
        }
        else{
            printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",D[i].CName,D[i].hours,D[i].Code,D[i].Depar,D[i].Topics);
    }

}

}

// print the data from the double table to file.
void Fprint_dou(struct cour D[si],FILE*f){
    for(int i=0;i<si;i++){
        if(strcmp(D[i].CName,"")==0){
            continue;
        }
        else{
            fprintf(f,"%s:%d#%s#%s/%s\n",D[i].CName,D[i].hours,D[i].Code,D[i].Depar,D[i].Topics);
    }

}

}

// re hashing to all values and double the size in double table.
struct cour* Re_hash_Dou(struct cour D[si]){
struct cour *Dt;
Dt = (struct cour *)malloc(si*sizeof(struct cour));
for(int i=0;i<si/2;i++){
    if(strcmp(D[i].CName,"")==0){
        continue;
    }
    int x = Double_hash(Dt,D[i].CName);
    Dt[x] = D[i];
}

free(D);
D = Dt;
Dt = NULL;

return D;
}
// re hashing to all values and double the size in linear table.
struct cour* Re_hash_Lin(struct cour L[si]){
struct cour *Lt;
Lt = (struct cour *)malloc(si*sizeof(struct cour));
for(int i=0;i<si/2;i++){
    if(strcmp(L[i].CName,"")==0){
        continue;
    }
    int x = Lin_hash(Lt,L[i].CName);
    Lt[x] = L[i];
}

free(L);
L = Lt;
Lt = NULL;

return L;
}








int main()
{
    int sf = si;
    struct cour *Darr;
    struct cour *Larr;
    Darr = (struct cour *)malloc(si*sizeof(struct cour));
    Larr = (struct cour *)malloc(si*sizeof(struct cour));
    struct cour b;
     FILE *cours;
cours= fopen("offered_courses.txt","r");
if(cours == NULL){
    printf("Erorr!");
    exit(1);
}
char s [700] ;


while(fgets(s,700,cours)!=NULL){
        load(s,Darr,Larr);
}

float LF = (float)cap/(float)si;






int ch = 0;

printf("Welcome to my project ladies and gentlemen.");
printf("this project is about hashing and how to use it.\n");
printf("This project gives an example of how to deal with the Courses and there information by hash functions.\n\n");
while(ch != 9){
    printf("\nlet's make a choice,put the number for your choice\n\n");
    printf("1-) print hash tables\n");
    printf("2-) Print out table size and the load factor\n");
    printf("3-) Print out the used hash functions\n");
    printf("4-) Insert a new record to hash table\n");
    printf("5-) Search for a specific word(course)\n");
    printf("6-) delete course\n");
    printf("7-) know who is best: double hashing or open address(in my case liner)\n");
    printf("8-) save the double table to file\n");
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
            print_dou(Darr);
            printf("\n\n *************************************\n\n");
    print_lin(Larr);

    }
    else if(ch == 2){
            printf("the size is: %d and the load factor is: %.2f\n",si,LF);

    }
    else if(ch == 3){
     printf("I use the shift string hash function which is:\n");
     printf("for all letters : hashValue = ( hashValue << 5 ) + *key++;\n");
     printf("then I use double hash and linear hash to avoid collisions\n");
    }
    else if(ch == 4){
            if(LF>=0.75){
                    si = si*2;
                Darr = Re_hash_Dou(Darr);
                Larr = Re_hash_Lin(Larr);
            }
  addCo(Darr,Larr);
  LF = (float)cap/(float)si;
    }
    else if(ch == 5){
            int chh = 0;
            printf("put 1 for double table put 2 for linear table\n");
            scanf("%d",&chh);
            if(chh == 1){
            char n[50];
            printf("put the name for the course you want to find:\n");
            scanf("%s",&n);
            int x = SDouble_hash(Darr,n);
              if(x == -1){
        printf("there is no course with this name!!\n");
    }
    else{
             printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",Darr[x].CName,Darr[x].hours,Darr[x].Code,Darr[x].Depar,Darr[x].Topics);
    }
    }
    else if (chh == 2){

    char n[50];
    printf("put the name for the course you want to find:\n");
    scanf("%s",&n);
    int x = SLin_hash(Larr,n);
    if(x == -1){
        printf("there is no course with this name!!\n");
    }
    else{
             printf("CourseName: %s Hours: %d Code: %s Dep: %s Topics: %s\n",Larr[x].CName,Larr[x].hours,Larr[x].Code,Larr[x].Depar,Larr[x].Topics);
    }
    }
    else
        printf("you put invalid choise\n");

    }
    else if(ch == 6){
         char n[50];
    printf("put the name for the course you want to Delete:\n");
    scanf("%s",&n);
    struct cour d;
    int x = SLin_hash(Larr,n);
    int y = SDouble_hash(Darr,n);
      if(x == -1){
        printf("there is no course with this name!!\n");
        continue;
    }
    Darr[y] = d;
    Larr[x] = d;

}
    else if(ch == 7){
  if(councld> councll){
    printf("Double hash with %d collisions is better than linear with %d collisions\n",councld,councll);
  }
  else if(councld < councll){
      printf("Double hash with %d collisions is worse than linear with %d collisions\n",councld,councll);
  }
  else{
    printf("they are the same with %d collisions",councld);
  }
    }
    else if(ch == 8){
                FILE *saved;
          saved = fopen(" saved_courses.txt","w");
      if (saved == NULL) {
        printf("Error!");
        exit(1);
    }
    printf("it will be saved Belieeeeeeeeeeve That.\n");
        Fprint_dou(Darr,saved);
        fclose(saved);
    }

    else if(ch == 9){
        printf("I hope you enjoyed the project and I hope you liked it. Best regards.");
    }
    else{
        printf("you put invalid choice\n\n");
    }





}
fclose(cours);
    return 0;

}


