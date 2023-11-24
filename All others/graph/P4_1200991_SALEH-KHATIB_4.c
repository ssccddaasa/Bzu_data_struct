// Saleh Khatib 1200991.
// this project is about graph and how to use it to find the paths and the distances between the cities.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define infinity for cost array.
#define in 99999

int size =0;

// load information from the file to three arrays.
// one to source cities two to destention city and three for the distance.
void load(char so[50][20],char d[50][20],int o[50],int i,char s[100]){

sscanf(s,"%s %s %d",&so[i],&d[i],&o[i]);

}


// find the number of the vertices (cities) and put them in reference array.
void make_impo_array(char so[50][20],char d[50][20],int h,char cloo[100][20]){

for(int i=0;i<h;i++){
   strcpy(cloo[i],so[i]);
}
for(int i=h;i<2*h;i++){
   strcpy(cloo[i],d[i-h]);
}
int num = 2*h;
for(int i=0;i<num;i++){
    for(int j=i+1;j<num;j++){
        if(strcmp(cloo[i],cloo[j])==0){
            for(int k=j;k<num;k++){
                strcpy(cloo[k],cloo[k+1]);
            }
            j--;
            num--;
        }
    }
}
size = num;

}


//find the index of the city from the reference array.
int find(char cloo[100][20],char s[50]){
for(int i=0;i<size;i++){
    if(strcmp(cloo[i],s)==0){
        return i;
    }
}
return -1;

}

// make the adjacency Matrix to make the graph and put the weight (distance) in the matrix.
void make_graph(char so[50][20],char d[50][20],int o[50],char cloo[100][20],int g[size][size],int h){

for(int i=0;i<h;i++){
    int x = find(cloo,so[i]);
    int y = find(cloo,d[i]);
    g[x][y] = o[i];
    g[y][x] = o[i];
}


}


// take the two arrays of the path from Dijkstra's function and form it in one array that have the shortest bath and print it.
void shor_path(int s[30],int d[30],int sh[size],int x,int y,char cloo[100][20],int g[size][size]){
int c=-1;
for(int i=0;i<30;i++){
    if(y == d[i]){
        c= i;


    }
}

int t=0;
sh[t] = y;
while(c != -1 ){

   sh[t] = y;
   y = s[c];

    c=-1;
for(int i=0;i<30;i++){
    if(y == d[i]){
        c= i;

    }
}

t++;
sh[t] = y;
}

if(t == 0){
    printf("the shortest path is : from source (%s) to destination (%s)\n",cloo[x],cloo[y]);
}

else{
   printf("the shortest path is : from source (%s) ->",cloo[x]);
   for(int i=t;i>=1;i--){
    printf("%s ->",cloo[sh[i]]);
   }
    printf(" destination (%s) \n",cloo[sh[0]]);
    printf("%s -> %s is %d\n",cloo[x],cloo[sh[t]],g[x][sh[t]]);
   for(int i=t;i>=1;i--){
    printf("%s -> %s is %d\n",cloo[sh[i]],cloo[sh[i-1]],g[sh[i]][sh[i-1]]);
   }

}


}





// take the two arrays of the path from Dijkstra's function and form it in one array that have the shortest bath and print it in file.
void shor_pathf(int s[30],int d[30],int sh[size],int x,int y,char cloo[100][20],int g[size][size],FILE *shord){
int c=-1;
for(int i=0;i<30;i++){
    if(y == d[i]){
        c= i;


    }
}

int t=0;
sh[t] = y;
while(c != -1 ){

   sh[t] = y;
   y = s[c];

    c=-1;
for(int i=0;i<30;i++){
    if(y == d[i]){
        c= i;

    }
}

t++;
sh[t] = y;
}

if(t == 0){
    fprintf(shord,"the shortest path is : from source (%s) to destination (%s)\n",cloo[x],cloo[y]);
}

else{
   fprintf(shord,"the shortest path is : from source (%s) ->",cloo[x]);
   for(int i=t;i>=1;i--){
    fprintf(shord,"%s ->",cloo[sh[i]]);
   }
    fprintf(shord," destination (%s) \n",cloo[sh[0]]);
    fprintf(shord,"%s -> %s is %d\n",cloo[x],cloo[sh[t]],g[x][sh[t]]);
   for(int i=t;i>=1;i--){
    fprintf(shord,"%s -> %s is %d\n",cloo[sh[i]],cloo[sh[i-1]],g[sh[i]][sh[i-1]]);
   }

}


}






// Dijkstra's function to find the shortest distance between two cities and form the two arrays of bath.
//Dijkstra's Algorithm works on the basis that any subpath B -> D of the shortest path A -> D between vertices A and D is also the shortest path between vertices B and D.
void Dijk(int infgra[size][size],int x,int y,char cloo[100][20],int f,FILE *shr){

    int off[size];
    int temp[30] = {0};
    int temp2[30] = {0};
    int isvis[size];
    int cou,teoff,next;
    int r[size][size];


         for(int i=0;i<2*size;i++){
    temp[i] = in;
}
     for(int i=0;i<2*size;i++){
    temp2[i] = in;
}





     for(int i=0;i<size;i++){
        off[i] = infgra[x][i];

        isvis[i] = 0;
     }
     off[x] = 0;
     isvis[x] = 0;
     cou =1;
     int t=0;
     while(cou<size){
        teoff = in;
         for(int i=0;i<size;i++){
            if(off[i]<teoff && !isvis[i]){
                teoff = off[i];
                next = i;

            }
         }


         isvis[next] =1;


          for(int i=0;i<size;i++){
            if(!isvis[i]){
                if(teoff + infgra[next][i]<off[i]){
                    off[i] = teoff + infgra[next][i];
                    temp[cou+t] = next;
                    temp2[cou+t] = i;
                    t++;

                }

            }

          }

          cou++;
     }

     int sh[size];
     for(int i=0;i<size;i++){
    sh[i] = in;
}
if(off[y] == in){
    printf("there is no path between the two cities.\n");
}
else{
    if(f==0){
     shor_path(temp,temp2,sh,x,y,cloo,infgra);
        printf("the shortest distance from source(%s) to destination (%s) is %d\n",cloo[x],cloo[y],off[y]);
    }
    else{
        shor_pathf(temp,temp2,sh,x,y,cloo,infgra,shr);
        fprintf(shr,"the shortest distance from source(%s) to destination (%s) is %d\n",cloo[x],cloo[y],off[y]);
    }

}

}



// Dijkstra's function for single source shortest path.
void Dijk2(int g[size][size],int x,char cloo[100][20]){
int min=g[x][0];
int y=0;

for(int i=0;i<size;i++){
    if(g[x][i]<min){
        min = g[x][i];
        y= i;
    }
}

 printf("the shortest path is : from source (%s) to the nearest city (%s) with distance = %d\n",cloo[x],cloo[y],min);


}








int main()
{
    char sor[50][20] ;    // make the three arrays.
    char dest[50][20] ;
    int distant[50];
    FILE *city;
    city = fopen("cities.txt","r");
    if(city == NULL){
    printf("Erorr!");
    exit(1);
}


char s [100] ;

int h =0;
while(fgets(s,100,city)!=NULL){
load(sor,dest,distant,h,s);
h++;
}



char cloo[100][20];  // reference array.
make_impo_array(sor,dest,h,cloo);


int graph[size][size]; // make the matrix(graph).
for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
        graph[i][j] = 0;
    }
}
make_graph(sor,dest,distant,cloo,graph,h);

int infgra[size][size];  // make cost graph.
for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(graph[i][j]==0){
                infgra[i][j] = in;
            }
            else{
                infgra[i][j] = graph[i][j];
            }
        }
    }


// make the menu.
int ch = 0;
int sours = -1;
int destna = -1;
printf("Welcome to my project ladies and gentlemen.");
printf("this project is about graph and how to use it.\n");
printf("This project is how to use graph to connect cities and find the shortest way between any two cities.\n\n");

while(ch != 4){
    printf("\nlet's make a choice,put the number for your choice\n\n");
    printf("1-) print the graph\n");
    printf("2-) Enter source city:\n");
    printf("3-) Enter destination city:\n");
    printf("4-) Exit\n");

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
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(graph[i][j] != 0){
                        printf("%s -> %s and the distance is %d\n",cloo[i],cloo[j],graph[i][j]);
                    }
                }
            }


    }
    else if(ch == 2){
            printf("Enter source city:\n");
            char so[20];
            scanf("%s",&so);
    sours = find(cloo,so);
    printf("\n\n");
    if(sours == -1){
        printf("invalid source city name!!\n");
    }
    else{
    Dijk2(infgra,sours,cloo);
    }

    }
    else if(ch == 3){
            printf("Enter destination city:\n");
            char so[20];
            scanf("%s",&so);
    destna = find(cloo,so);
    printf("\n\n");
    if(destna == -1 || sours == -1){
    printf("invalid source or destination city name!!\n");
    }
    else {
       Dijk(infgra,sours,destna,cloo,0,city);
    }

    }
    else if(ch == 4){
                FILE *saved;
          saved = fopen("shortest_path.txt","w");
      if (saved == NULL) {
        printf("Error!");
        exit(1);
    }
    if(destna == -1 || sours == -1){
   printf("invalid source or destination city name!!\n");
    }
    else {
       Dijk(infgra,sours,destna,cloo,1,saved);
       printf("it will be saved Belieeeeeeeeeeve That.\n");
    }
        fclose(saved);
        printf("I hope you enjoyed the project and I hope you liked it. Best regards.");
    }
    else{
        printf("you put invalid choice\n\n");
    }


}


    fclose(city);
    return 0;
}
